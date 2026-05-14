use std::{
    net::UdpSocket,
    sync::mpsc::{Receiver, Sender},
    time::{Duration, Instant},
};

use chrono::Utc;
use egui::Context;

use crate::{
    protocol::{decode, encode, Packet},
    types::{AppCmd, NetEvent, TextMessage},
};

const UDP_PORT: u16 = 23232;
const HEARTBEAT_INTERVAL: Duration = Duration::from_secs(3);
/// How long with no heartbeat before a peer is considered gone.
pub const PEER_TIMEOUT: Duration = Duration::from_secs(10);

/// Blocking network loop — run on a dedicated OS thread.
/// Sends heartbeats, processes inbound UDP, forwards events via `event_tx`,
/// and handles outbound commands from `cmd_rx`.
pub fn run(
    uuid:   String,
    name:   String,
    avatar: String,
    event_tx: Sender<NetEvent>,
    cmd_rx:   Receiver<AppCmd>,
    ctx:      Context,       // used to request a GUI repaint on incoming events
) {
    let socket = match UdpSocket::bind(format!("0.0.0.0:{}", UDP_PORT)) {
        Ok(s)  => s,
        Err(e) => {
            eprintln!("[net] Failed to bind UDP port {}: {}", UDP_PORT, e);
            return;
        }
    };
    socket.set_broadcast(true).expect("set_broadcast failed");
    socket.set_read_timeout(Some(Duration::from_millis(50)))
          .expect("set_read_timeout failed");

    let broadcast_addr = format!("255.255.255.255:{}", UDP_PORT);
    let mut buf            = [0u8; 65_507];
    let mut last_heartbeat = Instant::now() - HEARTBEAT_INTERVAL; // fire immediately

    loop {
        // ── Send heartbeat ──────────────────────────────────────────────────
        if last_heartbeat.elapsed() >= HEARTBEAT_INTERVAL {
            let pkt = Packet::Heartbeat {
                sender_uuid: uuid.clone(),
                name:        name.clone(),
                avatar:      avatar.clone(),
            };
            let _ = socket.send_to(&encode(&pkt), &broadcast_addr);
            last_heartbeat = Instant::now();
        }

        // ── Receive ─────────────────────────────────────────────────────────
        match socket.recv_from(&mut buf) {
            Ok((len, src)) => {
                let ip = src.ip().to_string();
                if let Some(pkt) = decode(&buf[..len]) {
                    match pkt {
                        Packet::Heartbeat { sender_uuid, name, avatar } => {
                            if sender_uuid != uuid {
                                let _ = event_tx.send(NetEvent::PeerSeen {
                                    uuid: sender_uuid, name, avatar, ip,
                                });
                                ctx.request_repaint();
                            }
                        }
                        Packet::Text { sender_uuid, receiver_uuid, message, time } => {
                            if receiver_uuid == uuid {
                                let msg = TextMessage {
                                    sender_uuid,
                                    receiver_uuid,
                                    message,
                                    time,
                                    from_me: false,
                                };
                                let _ = event_tx.send(NetEvent::Message(msg));
                                ctx.request_repaint();
                            }
                        }
                        Packet::Leave { sender_uuid } => {
                            let _ = event_tx.send(NetEvent::PeerLeft { uuid: sender_uuid });
                            ctx.request_repaint();
                        }
                    }
                }
            }
            // WouldBlock / TimedOut are expected — just continue.
            Err(_) => {}
        }

        // ── Commands from GUI ────────────────────────────────────────────────
        while let Ok(cmd) = cmd_rx.try_recv() {
            match cmd {
                AppCmd::SendMessage { receiver_uuid, receiver_ip, message } => {
                    let pkt = Packet::Text {
                        sender_uuid:   uuid.clone(),
                        receiver_uuid,
                        message,
                        time: Utc::now().timestamp(),
                    };
                    let addr = format!("{}:{}", receiver_ip, UDP_PORT);
                    let _ = socket.send_to(&encode(&pkt), addr);
                }
                AppCmd::Shutdown => {
                    let pkt = Packet::Leave { sender_uuid: uuid.clone() };
                    let _ = socket.send_to(&encode(&pkt), &broadcast_addr);
                    return;
                }
            }
        }
    }
}

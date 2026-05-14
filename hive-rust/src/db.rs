use std::{fs, path::PathBuf};
use crate::types::{Settings, TextMessage};

// ── Paths ─────────────────────────────────────────────────────────────────────

pub fn data_dir() -> PathBuf {
    dirs::data_dir()
        .unwrap_or_else(|| PathBuf::from("."))
        .join("Hive")
}

fn history_dir() -> PathBuf {
    data_dir().join("history")
}

// ── Settings ──────────────────────────────────────────────────────────────────

pub fn load_settings() -> Settings {
    let path = data_dir().join("settings.json");
    match fs::read(&path) {
        Ok(bytes) => serde_json::from_slice(&bytes).unwrap_or_default(),
        Err(_) => {
            let s = Settings::default();
            save_settings(&s);
            s
        }
    }
}

pub fn save_settings(s: &Settings) {
    let dir = data_dir();
    let _ = fs::create_dir_all(&dir);
    if let Ok(bytes) = serde_json::to_vec_pretty(s) {
        let _ = fs::write(dir.join("settings.json"), bytes);
    }
}

// ── Message history ───────────────────────────────────────────────────────────

pub fn load_messages(peer_uuid: &str, my_uuid: &str) -> Vec<TextMessage> {
    let path = history_dir().join(format!("{}.json", peer_uuid));
    match fs::read(&path) {
        Ok(bytes) => {
            let mut msgs: Vec<TextMessage> =
                serde_json::from_slice(&bytes).unwrap_or_default();
            // Restore `from_me` which is not stored on disk.
            for m in &mut msgs {
                m.from_me = m.sender_uuid == my_uuid;
            }
            msgs
        }
        Err(_) => vec![],
    }
}

pub fn append_message(peer_uuid: &str, my_uuid: &str, msg: &TextMessage) {
    let mut msgs = load_messages(peer_uuid, my_uuid);
    msgs.push(msg.clone());
    let dir = history_dir();
    let _ = fs::create_dir_all(&dir);
    if let Ok(bytes) = serde_json::to_vec_pretty(&msgs) {
        let _ = fs::write(dir.join(format!("{}.json", peer_uuid)), bytes);
    }
}

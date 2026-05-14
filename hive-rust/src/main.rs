mod app;
mod db;
mod network;
mod protocol;
mod types;

use std::{sync::mpsc, thread};

use app::HiveApp;
use db::load_settings;

fn main() {
    // ── Load or create settings ───────────────────────────────────────────────
    let settings = load_settings();

    // ── Channels ──────────────────────────────────────────────────────────────
    let (event_tx, event_rx) = mpsc::channel(); // net  → GUI
    let (cmd_tx,   cmd_rx)   = mpsc::channel(); // GUI  → net

    // ── Bootstrap ─────────────────────────────────────────────────────────────
    // The egui Context is only available after eframe initialises, so we pass
    // it to the network thread via a one-shot channel.
    let (ctx_tx, ctx_rx) = mpsc::sync_channel::<egui::Context>(1);

    let uuid   = settings.profile_uuid.clone();
    let name   = settings.profile_name.clone();
    let avatar = settings.profile_avatar.clone();

    thread::spawn(move || {
        let ctx = ctx_rx.recv().expect("eframe context channel closed unexpectedly");
        network::run(uuid, name, avatar, event_tx, cmd_rx, ctx);
    });

    // ── eframe window ─────────────────────────────────────────────────────────
    let native_options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_title("Hive!")
            .with_inner_size([settings.window_width, settings.window_height])
            .with_min_inner_size([600.0, 400.0]),
        ..Default::default()
    };

    eframe::run_native(
        "Hive!",
        native_options,
        Box::new(move |cc| {
            // Hand the Context to the network thread before the first frame.
            let _ = ctx_tx.send(cc.egui_ctx.clone());
            Ok(Box::new(HiveApp::new(cc, settings, event_rx, cmd_tx)))
        }),
    )
    .expect("eframe failed to start");
}

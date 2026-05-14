use std::{
    collections::HashMap,
    sync::mpsc::{Receiver, Sender},
    time::Instant,
};

use egui::{
    Align, Align2, Color32, Context, FontId, Frame, Key, Layout, Margin, Rounding,
    ScrollArea, Ui, Vec2,
};

use crate::{
    db,
    network::PEER_TIMEOUT,
    types::{AppCmd, Contact, NetEvent, Settings, TextMessage, UserProfile},
};

// ── Tabs ──────────────────────────────────────────────────────────────────────

#[derive(PartialEq, Clone, Copy)]
enum Tab {
    Contacts,
    Settings,
}

// ── App state ─────────────────────────────────────────────────────────────────

pub struct HiveApp {
    settings:         Settings,
    contacts:         HashMap<String, Contact>,
    messages:         HashMap<String, Vec<TextMessage>>,
    selected_uuid:    Option<String>,
    current_tab:      Tab,
    input_text:       String,
    // Settings panel edit buffer
    name_buf:         String,
    scroll_to_bottom: bool,
    event_rx:         Receiver<NetEvent>,
    cmd_tx:           Sender<AppCmd>,
}

impl HiveApp {
    pub fn new(
        settings: Settings,
        event_rx: Receiver<NetEvent>,
        cmd_tx:   Sender<AppCmd>,
    ) -> Self {
        let name_buf = settings.profile_name.clone();
        HiveApp {
            settings,
            contacts:         HashMap::new(),
            messages:         HashMap::new(),
            selected_uuid:    None,
            current_tab:      Tab::Contacts,
            input_text:       String::new(),
            name_buf,
            scroll_to_bottom: false,
            event_rx,
            cmd_tx,
        }
    }

    // ── Network event pump ────────────────────────────────────────────────────

    fn poll_events(&mut self) {
        while let Ok(ev) = self.event_rx.try_recv() {
            match ev {
                NetEvent::PeerSeen { uuid, name, avatar, ip } => {
                    let contact = self.contacts.entry(uuid.clone()).or_insert_with(|| {
                        let profile = UserProfile {
                            uuid:   uuid.clone(),
                            name:   name.clone(),
                            avatar: avatar.clone(),
                        };
                        Contact::new(profile, ip.clone())
                    });
                    contact.online         = true;
                    contact.last_seen      = Instant::now();
                    contact.profile.name   = name;
                    contact.profile.avatar = avatar;
                    contact.ip             = ip;
                    // Lazily load history on first sight.
                    self.messages
                        .entry(uuid.clone())
                        .or_insert_with(|| db::load_messages(&uuid, &self.settings.profile_uuid));
                }
                NetEvent::PeerLeft { uuid } => {
                    if let Some(c) = self.contacts.get_mut(&uuid) {
                        c.online = false;
                    }
                }
                NetEvent::Message(msg) => {
                    let peer = msg.sender_uuid.clone();
                    db::append_message(&peer, &self.settings.profile_uuid, &msg);
                    self.messages.entry(peer.clone()).or_default().push(msg);
                    if self.selected_uuid.as_deref() == Some(&peer) {
                        self.scroll_to_bottom = true;
                    } else if let Some(c) = self.contacts.get_mut(&peer) {
                        c.unread_count += 1;
                    }
                }
            }
        }
        // Mark timed-out peers offline.
        for c in self.contacts.values_mut() {
            if c.online && c.last_seen.elapsed() > PEER_TIMEOUT {
                c.online = false;
            }
        }
    }

    // ── Send outgoing message ─────────────────────────────────────────────────

    fn send_message(&mut self) {
        let text = self.input_text.trim().to_string();
        if text.is_empty() { return; }
        let uuid = match self.selected_uuid.clone() { Some(u) => u, None => return };
        let ip   = match self.contacts.get(&uuid)   { Some(c) => c.ip.clone(), None => return };

        let msg = TextMessage {
            sender_uuid:   self.settings.profile_uuid.clone(),
            receiver_uuid: uuid.clone(),
            message:       text.clone(),
            time:          chrono::Utc::now().timestamp(),
            from_me:       true,
        };
        let _ = self.cmd_tx.send(AppCmd::SendMessage {
            receiver_uuid: uuid.clone(),
            receiver_ip:   ip,
            message:       text,
        });
        db::append_message(&uuid, &self.settings.profile_uuid, &msg);
        self.messages.entry(uuid).or_default().push(msg);
        self.input_text.clear();
        self.scroll_to_bottom = true;
    }

    // ── Sidebar ───────────────────────────────────────────────────────────────

    fn render_sidebar(&mut self, ui: &mut Ui) {
        // Tab bar — resolve clicks before borrowing contacts.
        let avail_w = ui.available_width();
        let w = avail_w / 2.0;
        let contacts_selected = self.current_tab == Tab::Contacts;
        let settings_selected  = self.current_tab == Tab::Settings;

        ui.horizontal(|ui: &mut Ui| {
            ui.spacing_mut().item_spacing.x = 0.0;
            if ui.add_sized([w, 34.0], egui::SelectableLabel::new(contacts_selected, "💬  Contacts")).clicked() {
                self.current_tab = Tab::Contacts;
            }
            if ui.add_sized([w, 34.0], egui::SelectableLabel::new(settings_selected, "⚙  Settings")).clicked() {
                self.current_tab = Tab::Settings;
            }
        });
        ui.separator();

        match self.current_tab {
            Tab::Contacts => self.render_contact_list(ui),
            Tab::Settings => self.render_settings_panel(ui),
        }
    }

    fn render_contact_list(&mut self, ui: &mut Ui) {
        // Collect + sort outside the rendering loop to avoid repeated borrows.
        let mut uuids: Vec<String> = self.contacts.keys().cloned().collect();
        uuids.sort_by(|a, b| {
            let ca = &self.contacts[a];
            let cb = &self.contacts[b];
            cb.online.cmp(&ca.online).then_with(|| ca.profile.name.cmp(&cb.profile.name))
        });

        if uuids.is_empty() {
            ui.vertical_centered(|ui: &mut Ui| {
                ui.add_space(60.0);
                ui.label(egui::RichText::new("🐝").size(48.0));
                ui.add_space(8.0);
                ui.label("No peers found yet.");
                ui.label(egui::RichText::new("Make sure others are on the same LAN.").small());
            });
            return;
        }

        // Snapshot display data so we can render without holding borrows.
        struct Row {
            uuid:    String,
            name:    String,
            avatar:  String,
            ip:      String,
            online:  bool,
            unread:  usize,
        }
        let rows: Vec<Row> = uuids.iter().map(|uuid| {
            let c = &self.contacts[uuid];
            Row {
                uuid:   uuid.clone(),
                name:   c.profile.name.clone(),
                avatar: c.profile.avatar.clone(),
                ip:     c.ip.clone(),
                online: c.online,
                unread: c.unread_count,
            }
        }).collect();

        let selected_uuid = self.selected_uuid.clone();
        let mut clicked: Option<String> = None;

        ScrollArea::vertical().show(ui, |ui: &mut Ui| {
            for row in &rows {
                let is_selected = selected_uuid.as_deref() == Some(row.uuid.as_str());
                let (rect, response) = ui.allocate_exact_size(
                    Vec2::new(ui.available_width(), 60.0),
                    egui::Sense::click(),
                );

                if ui.is_rect_visible(rect) {
                    let bg = if is_selected {
                        ui.visuals().selection.bg_fill
                    } else if response.hovered() {
                        ui.visuals().widgets.hovered.bg_fill
                    } else {
                        Color32::TRANSPARENT
                    };
                    ui.painter().rect_filled(rect, 0.0, bg);

                    ui.painter().text(
                        rect.left_center() + Vec2::new(22.0, 0.0),
                        Align2::CENTER_CENTER,
                        &row.avatar,
                        FontId::proportional(26.0),
                        Color32::WHITE,
                    );

                    let name_color = if is_selected {
                        ui.visuals().selection.stroke.color
                    } else {
                        ui.visuals().text_color()
                    };
                    ui.painter().text(
                        rect.left_top() + Vec2::new(52.0, 11.0),
                        Align2::LEFT_TOP,
                        &row.name,
                        FontId::proportional(14.0),
                        name_color,
                    );

                    let (status_text, status_color): (&str, Color32) = if row.online {
                        (&row.ip, Color32::from_rgb(80, 190, 80))
                    } else {
                        ("Offline", Color32::GRAY)
                    };
                    ui.painter().text(
                        rect.left_top() + Vec2::new(52.0, 32.0),
                        Align2::LEFT_TOP,
                        status_text,
                        FontId::proportional(11.0),
                        status_color,
                    );

                    if row.unread > 0 {
                        let badge_center = rect.right_center() + Vec2::new(-20.0, 0.0);
                        ui.painter().circle_filled(badge_center, 10.0, Color32::from_rgb(240, 60, 60));
                        ui.painter().text(
                            badge_center,
                            Align2::CENTER_CENTER,
                            &row.unread.to_string(),
                            FontId::proportional(10.0),
                            Color32::WHITE,
                        );
                    }
                }
                if response.clicked() {
                    clicked = Some(row.uuid.clone());
                }
            }
        });

        if let Some(uuid) = clicked {
            self.selected_uuid = Some(uuid.clone());
            if let Some(c) = self.contacts.get_mut(&uuid) {
                c.unread_count = 0;
            }
            if !self.messages.contains_key(&uuid) {
                let msgs = db::load_messages(&uuid, &self.settings.profile_uuid);
                self.messages.insert(uuid.clone(), msgs);
            }
            self.scroll_to_bottom = true;
        }
    }

    fn render_settings_panel(&mut self, ui: &mut Ui) {
        ui.add_space(16.0);
        ui.vertical_centered(|ui: &mut Ui| {
            ui.label(egui::RichText::new(&self.settings.profile_avatar).size(56.0));
        });
        ui.add_space(12.0);

        ui.label("Display name");
        let name_resp = ui.add_sized(
            [ui.available_width(), 28.0],
            egui::TextEdit::singleline(&mut self.name_buf),
        );
        if (name_resp.lost_focus() && ui.input(|i: &egui::InputState| i.key_pressed(Key::Enter)))
            || ui.button("Save name").clicked()
        {
            let trimmed = self.name_buf.trim().to_string();
            if !trimmed.is_empty() {
                self.settings.profile_name = trimmed;
                db::save_settings(&self.settings);
            }
        }

        ui.add_space(12.0);
        ui.separator();
        ui.add_space(8.0);

        ui.label("Avatar");
        let avatars = ["🐝", "🐛", "🐞", "🌻", "💾", "🤖", "🦊", "🦋"];
        let mut new_avatar: Option<String> = None;
        ui.horizontal_wrapped(|ui: &mut Ui| {
            for &a in &avatars {
                let selected = self.settings.profile_avatar == a;
                if ui.add(egui::SelectableLabel::new(
                    selected,
                    egui::RichText::new(a).size(30.0),
                )).clicked() {
                    new_avatar = Some(a.to_string());
                }
            }
        });
        if let Some(av) = new_avatar {
            self.settings.profile_avatar = av;
            db::save_settings(&self.settings);
        }

        ui.add_space(12.0);
        ui.separator();
        ui.add_space(8.0);
        ui.label("Your UUID (read-only)");
        let mut uuid_copy = self.settings.profile_uuid.clone();
        ui.add_enabled(
            false,
            egui::TextEdit::singleline(&mut uuid_copy).font(FontId::monospace(10.0)),
        );
    }

    // ── Chat panels ───────────────────────────────────────────────────────────

    fn render_chat_header(&self, ctx: &Context) {
        let uuid = match &self.selected_uuid { Some(u) => u, None => return };
        let (name, online) = self.contacts.get(uuid.as_str())
            .map(|c| (c.profile.name.clone(), c.online))
            .unwrap_or_else(|| (uuid.clone(), false));

        egui::TopBottomPanel::top("chat_header")
            .min_height(42.0)
            .show(ctx, |ui: &mut Ui| {
                ui.horizontal(|ui: &mut Ui| {
                    ui.add_space(10.0);
                    ui.label(egui::RichText::new(&name).size(16.0).strong());
                    ui.add_space(6.0);
                    if online {
                        ui.label(egui::RichText::new("● online")
                            .color(Color32::from_rgb(70, 190, 70)).size(11.0));
                    } else {
                        ui.label(egui::RichText::new("● offline")
                            .color(Color32::GRAY).size(11.0));
                    }
                });
            });
    }

    /// Returns true when the user triggers send.
    fn render_chat_input(&mut self, ctx: &Context) -> bool {
        let mut send = false;
        egui::TopBottomPanel::bottom("chat_input")
            .min_height(58.0)
            .show(ctx, |ui: &mut Ui| {
                ui.add_space(8.0);
                ui.horizontal(|ui: &mut Ui| {
                    let send_w  = 70.0;
                    let spacing = ui.spacing().item_spacing.x;
                    let edit_w  = ui.available_width() - send_w - spacing;

                    let resp = ui.add_sized(
                        [edit_w, 38.0],
                        egui::TextEdit::singleline(&mut self.input_text)
                            .hint_text("Type a message…"),
                    );
                    if resp.lost_focus()
                        && ui.input(|i: &egui::InputState| i.key_pressed(Key::Enter))
                    {
                        send = true;
                        resp.request_focus();
                    }
                    if ui.add_sized([send_w, 38.0], egui::Button::new("Send")).clicked() {
                        send = true;
                        resp.request_focus();
                    }
                });
            });
        send
    }

    fn render_messages(&mut self, ctx: &Context) {
        let uuid = match self.selected_uuid.clone() { Some(u) => u, None => return };
        let messages     = self.messages.get(&uuid).cloned().unwrap_or_default();
        let scroll_now   = self.scroll_to_bottom;
        self.scroll_to_bottom = false;

        egui::CentralPanel::default().show(ctx, |ui: &mut Ui| {
            let mut scroll = ScrollArea::vertical().auto_shrink([false; 2]).stick_to_bottom(true);
            if scroll_now {
                scroll = scroll.vertical_scroll_offset(f32::MAX);
            }
            scroll.show(ui, |ui: &mut Ui| {
                ui.add_space(6.0);
                for msg in &messages {
                    render_bubble(ui, msg);
                    ui.add_space(4.0);
                }
                ui.add_space(6.0);
            });
        });
    }

    fn render_welcome(&self, ctx: &Context) {
        egui::CentralPanel::default().show(ctx, |ui: &mut Ui| {
            ui.vertical_centered(|ui: &mut Ui| {
                ui.add_space(ui.available_height() / 3.0);
                ui.label(egui::RichText::new("🐝").size(72.0));
                ui.add_space(12.0);
                ui.label(egui::RichText::new("Hive!").size(30.0).strong());
                ui.add_space(6.0);
                ui.label("Select a contact to start chatting.");
            });
        });
    }
}

// ── Chat bubble (free function avoids borrow conflicts) ───────────────────────

fn render_bubble(ui: &mut Ui, msg: &TextMessage) {
    let from_me    = msg.from_me;
    let bubble_bg  = if from_me { Color32::from_rgb(255, 204, 0) } else { Color32::from_rgb(58, 58, 60) };
    let text_color = if from_me { Color32::BLACK }                else { Color32::WHITE };
    let align      = if from_me { Align::RIGHT }                  else { Align::LEFT };

    ui.with_layout(Layout::top_down(align), |ui: &mut Ui| {
        let max_w = ui.ctx().screen_rect().width() * 0.55;
        ui.set_max_width(max_w);
        Frame::none()
            .fill(bubble_bg)
            .rounding(Rounding::same(12.0))
            .inner_margin(Margin::symmetric(12.0, 7.0))
            .show(ui, |ui: &mut Ui| {
                ui.label(egui::RichText::new(&msg.message).size(14.0).color(text_color));
            });
    });
}

// ── eframe::App ───────────────────────────────────────────────────────────────

impl eframe::App for HiveApp {
    fn update(&mut self, ctx: &Context, _frame: &mut eframe::Frame) {
        self.poll_events();
        // Periodic repaint ensures peer-timeout display stays accurate.
        ctx.request_repaint_after(std::time::Duration::from_secs(4));

        egui::SidePanel::left("sidebar")
            .resizable(false)
            .exact_width(260.0)
            .show(ctx, |ui: &mut Ui| self.render_sidebar(ui));

        if self.selected_uuid.is_some() {
            self.render_chat_header(ctx);
            let send = self.render_chat_input(ctx);
            self.render_messages(ctx);
            if send { self.send_message(); }
        } else {
            self.render_welcome(ctx);
        }
    }

    fn on_exit(&mut self, _gl: Option<&eframe::glow::Context>) {
        let _ = self.cmd_tx.send(AppCmd::Shutdown);
        db::save_settings(&self.settings);
    }
}

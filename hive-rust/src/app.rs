use std::{
    collections::HashMap,
    sync::mpsc::{Receiver, Sender},
    time::Instant,
};

use egui::{
    Align, Align2, Color32, Context, FontId, Frame, Key, Layout, Margin, Rect,
    Rounding, ScrollArea, Sense, Stroke, Ui, Vec2,
};

use crate::{
    db,
    network::PEER_TIMEOUT,
    types::{AppCmd, Contact, NetEvent, Settings, TextMessage, UserProfile},
};

// ── Hive colour palette (sampled from hivechat.org screenshots) ───────────────

const YELLOW:       Color32 = Color32::from_rgb(252, 196, 25);   // primary accent
const YELLOW_SEL:   Color32 = Color32::from_rgb(255, 243, 191);  // selected contact bg
const YELLOW_HOVER: Color32 = Color32::from_rgb(255, 233, 140);  // hovered row
const SIDEBAR_BG:   Color32 = Color32::from_rgb(245, 245, 245);  // sidebar panel
const MAIN_BG:      Color32 = Color32::from_rgb(255, 255, 255);  // chat area
const BUBBLE_OUT:   Color32 = Color32::from_rgb(252, 196, 25);   // my messages
const BUBBLE_IN:    Color32 = Color32::from_rgb(235, 235, 235);  // peer messages
const ONLINE_DOT:   Color32 = Color32::from_rgb(82,  196,  82);  // green
const OFFLINE_DOT:  Color32 = Color32::from_rgb(180, 180, 180);  // grey
const TEXT_MAIN:    Color32 = Color32::from_rgb(28,  28,   28);
const TEXT_SUB:     Color32 = Color32::from_rgb(130, 130,  130);
const DIVIDER:      Color32 = Color32::from_rgb(228, 228,  228);
const ICON_INACT:   Color32 = Color32::from_rgb(170, 170,  170); // inactive tab icon

// ── Avatar background colours keyed by emoji ─────────────────────────────────

fn avatar_bg(avatar: &str) -> Color32 {
    match avatar {
        "🐝" => Color32::from_rgb(255, 193,   7),
        "🐞" => Color32::from_rgb(229,  57,  53),
        "🌻" => Color32::from_rgb(255, 152,   0),
        "💾" => Color32::from_rgb( 66, 133, 244),
        "🐛" => Color32::from_rgb( 67, 160,  71),
        "🤖" => Color32::from_rgb( 84, 110, 122),
        "🦊" => Color32::from_rgb(244,  81,  30),
        "🦋" => Color32::from_rgb(142,  36, 170),
        _    => Color32::from_rgb(120, 120, 120),
    }
}

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
    name_buf:         String,
    scroll_to_bottom: bool,
    event_rx:         Receiver<NetEvent>,
    cmd_tx:           Sender<AppCmd>,
}

impl HiveApp {
    pub fn new(
        cc:       &eframe::CreationContext<'_>,
        settings: Settings,
        event_rx: Receiver<NetEvent>,
        cmd_tx:   Sender<AppCmd>,
    ) -> Self {
        setup_style(&cc.egui_ctx);
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
                    let entry = self.contacts.entry(uuid.clone()).or_insert_with(|| {
                        Contact::new(
                            UserProfile { uuid: uuid.clone(), name: name.clone(), avatar: avatar.clone() },
                            ip.clone(),
                        )
                    });
                    entry.online         = true;
                    entry.last_seen      = Instant::now();
                    entry.profile.name   = name;
                    entry.profile.avatar = avatar;
                    entry.ip             = ip;
                    self.messages.entry(uuid.clone())
                        .or_insert_with(|| db::load_messages(&uuid, &self.settings.profile_uuid));
                }
                NetEvent::PeerLeft { uuid } => {
                    if let Some(c) = self.contacts.get_mut(&uuid) { c.online = false; }
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
        for c in self.contacts.values_mut() {
            if c.online && c.last_seen.elapsed() > PEER_TIMEOUT { c.online = false; }
        }
    }

    // ── Send ──────────────────────────────────────────────────────────────────

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
        let _ = self.cmd_tx.send(AppCmd::SendMessage { receiver_uuid: uuid.clone(), receiver_ip: ip, message: text });
        db::append_message(&uuid, &self.settings.profile_uuid, &msg);
        self.messages.entry(uuid).or_default().push(msg);
        self.input_text.clear();
        self.scroll_to_bottom = true;
    }

    // ── Sidebar ───────────────────────────────────────────────────────────────

    fn render_sidebar(&mut self, ui: &mut Ui) {
        // Fill sidebar background explicitly so it stays grey.
        let full = ui.max_rect();
        ui.painter().rect_filled(full, 0.0, SIDEBAR_BG);

        self.render_tab_bar(ui);

        match self.current_tab {
            Tab::Contacts => self.render_contact_list(ui),
            Tab::Settings => self.render_settings_panel(ui),
        }
    }

    fn render_tab_bar(&mut self, ui: &mut Ui) {
        let w = ui.available_width();
        let h = 44.0;
        let (bar_rect, _) = ui.allocate_exact_size(Vec2::new(w, h), Sense::hover());

        // Bottom divider
        ui.painter().hline(
            bar_rect.x_range(),
            bar_rect.bottom(),
            Stroke::new(1.0, DIVIDER),
        );

        let tabs: &[(&str, Tab)] = &[("☰", Tab::Contacts), ("⚙", Tab::Settings)];
        let tab_w = w / tabs.len() as f32;

        for (i, &(icon, tab)) in tabs.iter().enumerate() {
            let tab_rect = Rect::from_min_size(
                bar_rect.left_top() + Vec2::new(i as f32 * tab_w, 0.0),
                Vec2::new(tab_w, h),
            );
            let resp = ui.interact(tab_rect, ui.id().with(("tab", i)), Sense::click());
            if resp.clicked() { self.current_tab = tab; }

            let is_active = self.current_tab == tab;

            // Hover bg
            if resp.hovered() && !is_active {
                ui.painter().rect_filled(tab_rect, 0.0, YELLOW_HOVER.linear_multiply(0.35));
            }
            // Icon
            ui.painter().text(
                tab_rect.center(),
                Align2::CENTER_CENTER,
                icon,
                FontId::proportional(20.0),
                if is_active { YELLOW } else { ICON_INACT },
            );
            // Active underline
            if is_active {
                ui.painter().hline(
                    tab_rect.x_range(),
                    tab_rect.bottom() - 1.5,
                    Stroke::new(3.0, YELLOW),
                );
            }
        }
    }

    fn render_contact_list(&mut self, ui: &mut Ui) {
        if self.contacts.is_empty() {
            ui.vertical_centered(|ui: &mut Ui| {
                ui.add_space(60.0);
                ui.label(egui::RichText::new("🐝").size(52.0));
                ui.add_space(10.0);
                ui.label(egui::RichText::new("No peers on the LAN yet.").color(TEXT_SUB).size(13.0));
                ui.add_space(4.0);
                ui.label(egui::RichText::new("Waiting for heartbeats…").color(ICON_INACT).size(11.0));
            });
            return;
        }

        // Sort: online first, then by name.
        let mut uuids: Vec<String> = self.contacts.keys().cloned().collect();
        uuids.sort_by(|a, b| {
            let ca = &self.contacts[a];
            let cb = &self.contacts[b];
            cb.online.cmp(&ca.online).then_with(|| ca.profile.name.cmp(&cb.profile.name))
        });

        // Snapshot data to avoid borrow conflicts inside the scroll closure.
        struct Row { uuid: String, name: String, avatar: String, ip: String, online: bool, unread: usize }
        let rows: Vec<Row> = uuids.iter().map(|u| {
            let c = &self.contacts[u];
            Row { uuid: u.clone(), name: c.profile.name.clone(), avatar: c.profile.avatar.clone(),
                  ip: c.ip.clone(), online: c.online, unread: c.unread_count }
        }).collect();
        let selected = self.selected_uuid.clone();
        let mut clicked: Option<String> = None;

        ScrollArea::vertical().show(ui, |ui: &mut Ui| {
            for row in &rows {
                let is_sel = selected.as_deref() == Some(&row.uuid);
                let (rect, resp) = ui.allocate_exact_size(
                    Vec2::new(ui.available_width(), 58.0), Sense::click(),
                );
                if ui.is_rect_visible(rect) {
                    // Background
                    let bg = if is_sel { YELLOW_SEL } else if resp.hovered() { YELLOW_HOVER.linear_multiply(0.35) } else { SIDEBAR_BG };
                    ui.painter().rect_filled(rect, 0.0, bg);
                    // Bottom divider
                    ui.painter().hline(rect.x_range(), rect.bottom(), Stroke::new(0.5, DIVIDER));

                    // ── Avatar circle ──
                    let avatar_center = rect.left_center() + Vec2::new(34.0, 0.0);
                    ui.painter().circle_filled(avatar_center, 18.0, avatar_bg(&row.avatar));
                    ui.painter().text(
                        avatar_center, Align2::CENTER_CENTER, &row.avatar,
                        FontId::proportional(16.0), Color32::WHITE,
                    );

                    // ── Name ──
                    let name_pos = rect.left_top() + Vec2::new(62.0, 12.0);
                    ui.painter().text(name_pos, Align2::LEFT_TOP, &row.name,
                        FontId::proportional(13.5), TEXT_MAIN);

                    // ── Status dot + IP ──
                    let dot_pos = rect.left_top() + Vec2::new(62.0, 35.0);
                    ui.painter().circle_filled(dot_pos + Vec2::new(4.0, 4.0), 4.0,
                        if row.online { ONLINE_DOT } else { OFFLINE_DOT });
                    let status = if row.online { row.ip.as_str() } else { "Offline" };
                    ui.painter().text(dot_pos + Vec2::new(13.0, 0.0), Align2::LEFT_TOP,
                        status, FontId::proportional(11.0), TEXT_SUB);

                    // ── Unread badge ──
                    if row.unread > 0 {
                        let bc = rect.right_center() + Vec2::new(-18.0, 0.0);
                        ui.painter().circle_filled(bc, 10.0, Color32::from_rgb(240, 60, 60));
                        ui.painter().text(bc, Align2::CENTER_CENTER, &row.unread.to_string(),
                            FontId::proportional(10.0), Color32::WHITE);
                    }
                }
                if resp.clicked() { clicked = Some(row.uuid.clone()); }
            }
        });

        if let Some(uuid) = clicked {
            self.selected_uuid = Some(uuid.clone());
            if let Some(c) = self.contacts.get_mut(&uuid) { c.unread_count = 0; }
            if !self.messages.contains_key(&uuid) {
                let msgs = db::load_messages(&uuid, &self.settings.profile_uuid);
                self.messages.insert(uuid.clone(), msgs);
            }
            self.scroll_to_bottom = true;
        }
    }

    fn render_settings_panel(&mut self, ui: &mut Ui) {
        ui.add_space(24.0);

        // My avatar card
        ui.vertical_centered(|ui: &mut Ui| {
            let avatar_r = 34.0_f32;
            let (avatar_rect, _) = ui.allocate_exact_size(Vec2::splat(avatar_r * 2.0 + 4.0), Sense::hover());
            ui.painter().circle_filled(avatar_rect.center(), avatar_r, avatar_bg(&self.settings.profile_avatar));
            ui.painter().text(avatar_rect.center(), Align2::CENTER_CENTER,
                &self.settings.profile_avatar, FontId::proportional(30.0), Color32::WHITE);
        });

        ui.add_space(8.0);
        ui.vertical_centered(|ui: &mut Ui| {
            ui.label(egui::RichText::new(&self.settings.profile_name)
                .size(15.0).strong().color(TEXT_MAIN));
        });
        ui.add_space(16.0);

        // Name field
        section_label(ui, "DISPLAY NAME");
        let name_resp = ui.add_sized(
            [ui.available_width(), 32.0],
            egui::TextEdit::singleline(&mut self.name_buf)
                .frame(true)
                .hint_text("Your name…"),
        );
        ui.add_space(4.0);
        if ui.add_sized([ui.available_width(), 30.0],
            egui::Button::new("Save").fill(YELLOW)).clicked()
            || (name_resp.lost_focus() && ui.input(|i: &egui::InputState| i.key_pressed(Key::Enter)))
        {
            let t = self.name_buf.trim().to_string();
            if !t.is_empty() { self.settings.profile_name = t; db::save_settings(&self.settings); }
        }

        ui.add_space(16.0);
        section_label(ui, "AVATAR");
        let avatars = ["🐝", "🐞", "🌻", "💾", "🐛", "🤖", "🦊", "🦋"];
        let mut new_av: Option<&str> = None;
        ui.horizontal_wrapped(|ui: &mut Ui| {
            for &av in &avatars {
                let selected = self.settings.profile_avatar == av;
                let (r, resp) = ui.allocate_exact_size(Vec2::splat(46.0), Sense::click());
                let bg = if selected { YELLOW } else if resp.hovered() { YELLOW_HOVER } else { Color32::from_rgb(230, 230, 230) };
                ui.painter().circle_filled(r.center(), 20.0, bg);
                ui.painter().text(r.center(), Align2::CENTER_CENTER, av, FontId::proportional(22.0), Color32::WHITE);
                if resp.clicked() { new_av = Some(av); }
            }
        });
        if let Some(av) = new_av {
            self.settings.profile_avatar = av.to_string();
            db::save_settings(&self.settings);
        }

        ui.add_space(16.0);
        section_label(ui, "UUID");
        let mut uuid_copy = self.settings.profile_uuid.clone();
        ui.add_enabled(false, egui::TextEdit::singleline(&mut uuid_copy)
            .font(FontId::monospace(10.5)));
    }

    // ── Chat panels ───────────────────────────────────────────────────────────

    fn render_chat_header(&self, ctx: &Context) {
        let uuid = match &self.selected_uuid { Some(u) => u, None => return };
        let (name, avatar, ip, online) = self.contacts.get(uuid.as_str())
            .map(|c| (c.profile.name.clone(), c.profile.avatar.clone(), c.ip.clone(), c.online))
            .unwrap_or_else(|| (uuid.clone(), "🐝".into(), String::new(), false));

        egui::TopBottomPanel::top("chat_header")
            .frame(Frame::none().fill(MAIN_BG).inner_margin(Margin::symmetric(0.0, 0.0)))
            .min_height(52.0)
            .show(ctx, |ui: &mut Ui| {
                ui.painter().rect_filled(ui.max_rect(), 0.0, MAIN_BG);

                ui.horizontal(|ui: &mut Ui| {
                    ui.add_space(14.0);
                    // Avatar
                    let (ar, _) = ui.allocate_exact_size(Vec2::splat(38.0), Sense::hover());
                    ui.painter().circle_filled(ar.center(), 17.0, avatar_bg(&avatar));
                    ui.painter().text(ar.center(), Align2::CENTER_CENTER, &avatar,
                        FontId::proportional(16.0), Color32::WHITE);

                    ui.add_space(10.0);
                    ui.vertical(|ui: &mut Ui| {
                        ui.add_space(8.0);
                        ui.label(egui::RichText::new(&name).size(15.0).strong().color(TEXT_MAIN));
                        ui.horizontal(|ui: &mut Ui| {
                            ui.painter_at(ui.min_rect()).circle_filled(
                                ui.min_rect().left_center() + Vec2::new(5.0, 0.0),
                                4.0,
                                if online { ONLINE_DOT } else { OFFLINE_DOT },
                            );
                            ui.add_space(13.0);
                            let status = if online { ip.as_str() } else { "Offline" };
                            ui.label(egui::RichText::new(status).size(11.0).color(TEXT_SUB));
                        });
                    });
                });

                // Yellow bottom divider
                let r = ui.max_rect();
                ui.painter().hline(r.x_range(), r.bottom(), Stroke::new(1.5, YELLOW));
            });
    }

    fn render_chat_input(&mut self, ctx: &Context) -> bool {
        let mut send = false;
        egui::TopBottomPanel::bottom("chat_input")
            .frame(Frame::none().fill(MAIN_BG))
            .min_height(62.0)
            .show(ctx, |ui: &mut Ui| {
                // Yellow top divider
                let r = ui.max_rect();
                ui.painter().hline(r.x_range(), r.top() + 0.5, Stroke::new(1.5, YELLOW));

                ui.add_space(10.0);
                ui.horizontal(|ui: &mut Ui| {
                    ui.add_space(12.0);
                    // Text input
                    let send_btn_w = 48.0;
                    let spacing = ui.spacing().item_spacing.x;
                    let edit_w = ui.available_width() - send_btn_w - spacing - 12.0;

                    let resp = ui.add_sized(
                        [edit_w, 36.0],
                        egui::TextEdit::singleline(&mut self.input_text)
                            .hint_text("Message…")
                            .frame(true),
                    );
                    if resp.lost_focus() && ui.input(|i: &egui::InputState| i.key_pressed(Key::Enter)) {
                        send = true;
                        resp.request_focus();
                    }

                    // Round yellow Send button
                    let (btn_rect, btn_resp) = ui.allocate_exact_size(Vec2::splat(38.0), Sense::click());
                    let btn_color = if btn_resp.hovered() { YELLOW_HOVER } else { YELLOW };
                    ui.painter().circle_filled(btn_rect.center(), 19.0, btn_color);
                    ui.painter().text(btn_rect.center(), Align2::CENTER_CENTER, "▶",
                        FontId::proportional(14.0), Color32::WHITE);
                    if btn_resp.clicked() { send = true; resp.request_focus(); }
                });
            });
        send
    }

    fn render_messages(&mut self, ctx: &Context) {
        let uuid       = match self.selected_uuid.clone() { Some(u) => u, None => return };
        let messages   = self.messages.get(&uuid).cloned().unwrap_or_default();
        let scroll_now = self.scroll_to_bottom;
        self.scroll_to_bottom = false;

        egui::CentralPanel::default()
            .frame(Frame::none().fill(MAIN_BG).inner_margin(Margin::same(0.0)))
            .show(ctx, |ui: &mut Ui| {
                let mut scroll = ScrollArea::vertical()
                    .auto_shrink([false; 2])
                    .stick_to_bottom(true);
                if scroll_now { scroll = scroll.vertical_scroll_offset(f32::MAX); }
                scroll.show(ui, |ui: &mut Ui| {
                    ui.add_space(8.0);
                    for msg in &messages {
                        render_bubble(ui, msg);
                        ui.add_space(3.0);
                    }
                    ui.add_space(8.0);
                });
            });
    }

    fn render_welcome(&self, ctx: &Context) {
        egui::CentralPanel::default()
            .frame(Frame::none().fill(MAIN_BG))
            .show(ctx, |ui: &mut Ui| {
                let avail_h = ui.available_height();
                ui.add_space(avail_h * 0.28);
                ui.vertical_centered(|ui: &mut Ui| {
                    // Big bee avatar
                    let (r, _) = ui.allocate_exact_size(Vec2::splat(96.0), Sense::hover());
                    ui.painter().circle_filled(r.center(), 44.0, YELLOW);
                    ui.painter().text(r.center(), Align2::CENTER_CENTER, "🐝",
                        FontId::proportional(46.0), Color32::WHITE);

                    ui.add_space(16.0);
                    ui.label(egui::RichText::new("Hive!").size(28.0).strong().color(TEXT_MAIN));
                    ui.add_space(6.0);
                    ui.label(egui::RichText::new("A cute LAN chat. Select a contact to start.")
                        .size(13.0).color(TEXT_SUB));
                });
            });
    }
}

// ── Helpers ───────────────────────────────────────────────────────────────────

fn section_label(ui: &mut Ui, text: &str) {
    ui.label(egui::RichText::new(text).size(10.5).color(ICON_INACT).strong());
    ui.add_space(3.0);
}

fn render_bubble(ui: &mut Ui, msg: &TextMessage) {
    let from_me = msg.from_me;
    let (bg, fg, align) = if from_me {
        (BUBBLE_OUT, TEXT_MAIN, Align::RIGHT)
    } else {
        (BUBBLE_IN, TEXT_MAIN, Align::LEFT)
    };

    ui.with_layout(Layout::top_down(align), |ui: &mut Ui| {
        let avail = ui.available_width();
        Frame::none()
            .fill(bg)
            .rounding(Rounding { nw: 14.0, ne: 14.0,
                sw: if from_me { 14.0 } else { 3.0 },
                se: if from_me { 3.0  } else { 14.0 } })
            .inner_margin(Margin::symmetric(13.0, 8.0))
            .show(ui, |ui: &mut Ui| {
                ui.set_max_width(avail * 0.62);
                ui.label(egui::RichText::new(&msg.message).size(14.0).color(fg));
            });
    });
}

// ── Global style ──────────────────────────────────────────────────────────────

fn setup_style(ctx: &egui::Context) {
    let mut vis = egui::Visuals::light();
    vis.panel_fill              = SIDEBAR_BG;
    vis.window_fill             = MAIN_BG;
    vis.selection.bg_fill       = YELLOW_SEL;
    vis.selection.stroke        = Stroke::new(0.0, Color32::TRANSPARENT);
    vis.widgets.hovered.bg_fill = YELLOW_HOVER;
    vis.widgets.active.bg_fill  = YELLOW;
    vis.widgets.inactive.bg_stroke = Stroke::new(1.0, DIVIDER);
    vis.widgets.hovered.bg_stroke  = Stroke::new(1.5, YELLOW);
    vis.widgets.active.bg_stroke   = Stroke::new(2.0, YELLOW);
    vis.window_rounding         = Rounding::same(8.0);
    ctx.set_visuals(vis);

    let mut style = (*ctx.style()).clone();
    style.spacing.item_spacing   = Vec2::new(8.0, 5.0);
    style.spacing.button_padding = Vec2::new(14.0, 7.0);
    style.spacing.scroll         = egui::style::ScrollStyle::solid();
    ctx.set_style(style);
}

// ── eframe::App ───────────────────────────────────────────────────────────────

impl eframe::App for HiveApp {
    fn update(&mut self, ctx: &Context, _frame: &mut eframe::Frame) {
        self.poll_events();
        ctx.request_repaint_after(std::time::Duration::from_secs(4));

        egui::SidePanel::left("sidebar")
            .resizable(false)
            .exact_width(210.0)
            .frame(Frame::none().fill(SIDEBAR_BG))
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

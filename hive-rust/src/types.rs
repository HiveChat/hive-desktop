use serde::{Deserialize, Serialize};
use std::time::Instant;

// ── User / contact ────────────────────────────────────────────────────────────

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct UserProfile {
    pub uuid:   String,
    pub name:   String,
    pub avatar: String,
}

/// Live contact entry (not persisted directly).
pub struct Contact {
    pub profile:      UserProfile,
    pub ip:           String,
    pub online:       bool,
    pub last_seen:    Instant,
    pub unread_count: usize,
}

impl Contact {
    pub fn new(profile: UserProfile, ip: String) -> Self {
        Contact {
            profile,
            ip,
            online:       true,
            last_seen:    Instant::now(),
            unread_count: 0,
        }
    }
}

// ── Messages ──────────────────────────────────────────────────────────────────

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct TextMessage {
    pub sender_uuid:   String,
    pub receiver_uuid: String,
    pub message:       String,
    pub time:          i64,
    /// Not stored on disk; set from context when loading history.
    #[serde(default)]
    pub from_me:       bool,
}

// ── Settings ──────────────────────────────────────────────────────────────────

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Settings {
    pub profile_name:   String,
    pub profile_uuid:   String,
    pub profile_avatar: String,
    pub window_width:   f32,
    pub window_height:  f32,
}

impl Default for Settings {
    fn default() -> Self {
        Settings {
            profile_name:   "Anonymous Bee".to_string(),
            profile_uuid:   uuid::Uuid::new_v4().to_string(),
            profile_avatar: "🐝".to_string(),
            window_width:   900.0,
            window_height:  620.0,
        }
    }
}

// ── Cross-thread communication ────────────────────────────────────────────────

/// Events sent from the network thread → GUI thread.
pub enum NetEvent {
    PeerSeen {
        uuid:   String,
        name:   String,
        avatar: String,
        ip:     String,
    },
    PeerLeft {
        uuid: String,
    },
    Message(TextMessage),
}

/// Commands sent from the GUI thread → network thread.
pub enum AppCmd {
    SendMessage {
        receiver_uuid: String,
        receiver_ip:   String,
        message:       String,
    },
    Shutdown,
}

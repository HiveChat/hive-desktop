use serde::{Deserialize, Serialize};

/// Every UDP packet is one of these JSON variants.
/// `#[serde(tag = "type", rename_all = "snake_case")]` means
/// the JSON field `"type"` selects the variant, e.g. `"type":"heartbeat"`.
#[derive(Serialize, Deserialize, Debug)]
#[serde(tag = "type", rename_all = "snake_case")]
pub enum Packet {
    /// Presence broadcast — sent every HEARTBEAT_INTERVAL to 255.255.255.255.
    Heartbeat {
        sender_uuid: String,
        name:        String,
        avatar:      String,
    },
    /// Unicast text message to a specific peer.
    Text {
        sender_uuid:   String,
        receiver_uuid: String,
        message:       String,
        time:          i64,
    },
    /// Graceful departure broadcast.
    Leave {
        sender_uuid: String,
    },
}

pub fn encode(packet: &Packet) -> Vec<u8> {
    serde_json::to_vec(packet).unwrap_or_default()
}

pub fn decode(data: &[u8]) -> Option<Packet> {
    serde_json::from_slice(data).ok()
}

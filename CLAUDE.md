# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

Hive is a LAN-only peer-to-peer desktop chat application in alpha (0.0.7). It is written in C++14 with Qt5 for GUI and networking glue, and libagio (built on libuv) for async I/O. There is no central server; peers discover each other by broadcasting UDP heartbeats on port 23232.

## Building

**Dependencies:**
- Qt5 (core, gui, widgets, network modules)
- [libParsley / libagio](https://github.com/ultrasilicon/libparsley) >= 0.0.8
- libuv (macOS: `brew install libuv`; Linux: build from source)

**Build commands (from `src/`):**
```bash
qmake Hive.pro        # generate Makefile
make                  # build
make clean            # clean artifacts
```

Debug vs release is controlled via qmake's `CONFIG` variable:
```bash
qmake Hive.pro CONFIG+=debug
qmake Hive.pro CONFIG+=release
```

There is no automated test suite; verification is done by running the application.

## Architecture

The app has three concurrent layers connected exclusively by Qt signals/slots:

```
GUI thread (QApplication)
  Hive ─── Window
               ├── SideBar  (HomeTab | ContactsTab | SettingsTab)
               └── MainBlock (QStackedWidget for static views + ChatStack)

Data thread
  AppDataManager (QThread) ─── DB::Database (JSON file store)
                           ─── DoubleBuffer<NetPacket*> (inbound/outbound)

Network thread
  NetworkManager (QObject moved to QThread)
    └── HiveServer (QThread)
          ├── HiveUdpServer (Agio::UdpSocket, port 23232)
          └── Agio::TcpServer
```

**Key signal-slot wiring (all in `Hive::Hive()`):**
- `ChatStack::sendMessage` → `Hive::onTextMessageToSend` → `NetworkManager::udpSendMessage`
- `NetworkManager::messageRecieved` → `AppDataManager::onMessageCome` → `Window::onMessageReceived`
- `AppDataManager::usrProfileLoaded/Changed` → `Window::addUsr/changeUsr`
- `NetworkManager::updateAvailable` → `AppDataManager::onUpdateAvailable` → `Window::onUpdateAvailable`

## Cross-Thread Packet Passing

`DoubleBuffer<NetPacket*>` (in `HiveDoubleBuffer.h`) is a lock-free double-buffer template used to pass raw network packets from the network thread to `AppDataManager` without blocking either side. `AppDataManager::pushInboundBuffer()` is called from the network side; `readInboundNetBuffer()` drains it on the data thread via an `Agio::AsyncEvent`.

## Protocol

Messages are JSON objects sent over UDP. The message type is determined by the `MessageType` enum (`Message.h`). `HiveProtocol` encodes/decodes these packets. `protocol.json` documents the intended wire format (still being implemented for 0.0.8 with encryption). Heartbeat broadcasts handle peer presence; `UsrLeave` signals departure.

## Data Storage

All persistence uses `DB::Database` subclasses (`DB::Map`, `DB::Array`) which read/write JSON files via `Agio::File`. Locations are defined in `Global` static members:
- `data_location_dir` / `user_data_dir` – per-user app data (platform-standard paths via `QStandardPaths`)
- `contacts_file_dir`, `settings_file_dir`, `update_file_dir` – specific JSON files

`UsrData` manages per-contact message history as a list of "bundles" (arrays of up to 100 messages each), written to `<app_data>/usr/<uuid>/`.

## Global State

`Global` (in `Global.h`) is a static class holding all shared state: fonts, colours, `Settings::SettingsStruct` (loaded by `AppDataManager`), the local UUID (`profile_uuid_str`), and file-transfer progress tracking.

## GUI Structure

- `Window` owns `SideBar` (left panel) and `MainBlock` (right panel).
- `MainBlock` switches between a `QStackedWidget` of static views (`HomeStack_*`, `SettingsStack_*`) and `ChatStack` for active conversations.
- `ChatStack` contains `MessageViewer` (scrollable bubble list) and `MessageEditor` (text input with send button).
- `SideBar` stacks `HomeTab` (contact list), `ContactsTab`, and `SettingsTab`.
- Custom widget primitives live in `Gui/Frameworks/Widgets/` (TextBubble, Button, AvatarWidgets, ColorPicker, BadgeIcon, SearchBar).
- `GUI::StaticStackType` enum drives which static stack `MainBlock` displays.

## Platform Notes

- macOS: links `AppKit` framework; `Gui/macos/WindowOptions.mm` handles native title-bar customisation.
- Windows: loads fonts differently (cannot load from QRC); uses `RC_FILE` for app icon.
- Linux: uses `pkg-config` to link libagio (debug: `libagio-d`, release: `libagio`).

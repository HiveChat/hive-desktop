# Hive Frame V3 Document
## Global Variables (GlobalVar)
### GUI

Type | Name | Default Value | Description
------- | ------- | ------- | -------
QFont | gui_font_chatBubble |  | Font in chat bubble
QFont | gui_font_chatEditor |  | Font in message editor
QFont | gui_font_combWidgetTitle |  | Font in comb widget title
QFont | gui_font_combWidgetSubtitle |  | Font in comb widget subtitle
QFont | gui_font_menuButton |  | Font in menu button
QFont | gui_font_scrollStackTitle |  | Font in scroll stack title
QFont | gui_font_scrollStackSubtitle |  | Font in scroll stack title
QFont | gui_font_scrollStackContent |  | Font in scroll stack content
QColor | gui_color_bkg_window | RGBA: 255,255,255,255 | Background color for the main window
QColor | gui_color_bkg_tabBlock | RGBA: 255,255,255,230 | Background color for tab block
QColor | gui_color_bkg_combScrollArea | RGBA: 0,0,0,0 | Background color for comb scroll area
QColor | gui_color_bkg_chatBubbleIn | RGBA: 255,215,126,255 | Background color in chat bubble sent in
QColor | gui_color_bkg_chatBubbleOut | RGBA: 225,225,225,255 | Background color in chat bubble sent out

## AppDataManager
### Construction: 
>  initVariable();
>  checkFiles();
>  loadMySettings();
>  loadUsrList();
>  loadFonts();
>  loadTimerTasks();

### Theme


## TCP JSON Packages
### Heart Beat
Key | type | Note
------- | ------- | -------
key | string | User key
name | string | User name
time | int | UNIX time stamp
### File Info
Key | type | Note
------- | ------- | -------
index | int | 16 digit random number
sender | string | Sender
receiver | string | Receiver
name | string | File Name
size | int | File Size
md5 | str | File Md5

### FileContent
Key | type | Note
------- | ------- | -------
index | int | 16 digit random number
sender | string | Sender
receiver | string | Receiver
content | string | File Segment in Base64
index | int | Segment Number
md5 | str | File Md5 (as identification)

### FileAccept
Key | type | Note
------- | ------- | -------
index | int | 16 digit random number
sender | string | Sender
receiver | string | Receiver
md5 | str | File Md5
position | int | The position to start transfer

### FileReject
Key | type | Note
------- | ------- | -------
index | int | 16 digit random number
sender | string | Sender
receiver | string | Receiver
md5 | str | File Md5
reason | int | Enum reason for rejecting

### ErrorDelivery
Key | type | Note
------- | ------- | -------
index | int | 16 digit random number
sender | string | Sender
receiver | string | Receiver


## UDP JSON Packages
### Heart Beat
Key | type | Note
------- | ------- | -------
key | string | User key
name | string | User name
avatar | string | Avatar Selection

### Text Message
Key | type | Note
------- | ------- | -------
sender | string | User key of the sender
receiver | string | User key of the receiver
index | int | 16 digit random number
time | int | UNIX time stamp
message | string | Message

### File Transfer Request
Key | type | Note
------- | ------- | -------
sender | string | User key of the sender
receiver | string | User key of the receiver
index | int | 16 digit random number
size | int | File size
name | string | File name




# Hive Frame V3 Document
## Global Variables (GlobalVar)

## Data Manager (AppDataManager)
> Construction: 
>  initVariable();
>  checkFiles();
>  loadMySettings();
>  loadUsrList();
>  loadFonts();
>  loadTimerTasks();

## TCP JSON Packages
### File Info
Key | type | Note
------- | ------- | -------
sender | string | Sender
receiver | string | Receiver
name | string | File Name
size | int | File Size
md5 | str | File Md5

### FileContent
Key | type | Note
------- | ------- | -------
sender | string | Sender
receiver | string | Receiver
content | string | File Segment in Base64
index | int | Segment Number
md5 | str | File Md5 (as identification)

### FileAccept
Key | type | Note
------- | ------- | -------
sender | string | Sender
receiver | string | Receiver
md5 | str | File Md5
position | int | The position to start transfer

### FileReject
Key | type | Note
------- | ------- | -------
sender | string | Sender
receiver | string | Receiver
md5 | str | File Md5
reason | int | Enum reason for rejecting

### ErrorDelivery

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




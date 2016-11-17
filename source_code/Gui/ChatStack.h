#ifndef GUICHATSTACK_H
#define GUICHATSTACK_H

#include "Gui/Frameworks/Widgets/LabelButton.h"
#include "Gui/Frameworks/Widgets/AvatarButton.h"
#include "Gui/Frameworks/Widgets/TextBubble.h"
#include "GlobalData.h"
#include "UsrData.h"
#include "ThreadData.h"
#include "Gui/Frameworks/ScrollStack.h"

#include <QScrollBar>
#include <QScrollArea>
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QJsonArray>
#include <QHash>

class TextEdit;
class ChatScrollWidget;
class ChatMessageEditor;
class ChatStack;


class TextEdit : public QTextEdit
{
  Q_OBJECT

public:
	explicit TextEdit(QWidget *parent = 0);
	~TextEdit();

protected:
///Do not delete!
//  void keyPressEvent(QKeyEvent *e);
//  void keyReleaseEvent(QKeyEvent *e);
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

private:
  bool control_pressed = false;

signals:
  void keyEnterTriggered(bool pressed);
};



class ChatScrollWidget : public QWidget
{
  Q_OBJECT

public:
	explicit ChatScrollWidget(UsrData *usrData, QWidget *parent = 0);
	~ChatScrollWidget();

  void clearChatBubbles();

	void flipUnreadMessage();
	void flipLatestMessage();
	void flipUpMessage();
	void flipDownMessage();

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *chat_bubble_layout;
  TextBubble *gui_chat_bubble;

	UsrData *usr_data;

  QList<TextBubble*> chat_bubble_list;

public slots:
  void addChatBubble(const QString &message, const bool &fromMe);

};


class ChatMessageEditor : public QWidget
{
  Q_OBJECT

public:
	explicit ChatMessageEditor(QWidget *parent = 0);
	~ChatMessageEditor();

	LabelButton *send_btn;
	TextEdit *text_editor;

protected:
  bool eventFilter(QObject *obj, QEvent *e);

private:
  QVBoxLayout *edit_layout;
  QHBoxLayout *tool_layout;

	LabelButton *expression_label;
	LabelButton *image_label;
	LabelButton *file_label;

  QHBoxLayout *main_layout;

  bool control_pressed = false;


signals:
  void sendTriggered();

};



class ChatStack : public GuiScrollStack
{
  Q_OBJECT

public:
	explicit ChatStack(QWidget *parent = 0);
	~ChatStack();

  void setUsrData(UsrData *usrData);
  void display(const QString &usrKey);
  bool refreshProfile(const QString &usrKey);
  bool refreshMessage(const QString &usrKey);

protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

  LayoutStyle layout_style = LayoutStyle::Profile;

private:
	QHash<QString, ChatScrollWidget*> chat_scroll_widget_hash;

  //UI
//	ChatScrollWidget *chat_widget; <<
	ChatMessageEditor *message_editor;

  //Data
  UsrData *usr_data;

#ifdef Q_OS_OSX
	QTimer *timer;
#endif

  //Function
  void flipUnreadMessage();
	void flipLatestMessage();
  void flipUpMessage(const bool &clear);
  void flipDownMessage(const bool &clear);
  bool isDisplaying(const QString &usrKey);

public slots:
  void onSendButtonClicked();
  void onKeyEnterTriggered(bool &pressed);

signals:
  void sendMessage(QString usrKey, QString message);

};






#endif // GUICHATSTACK_H

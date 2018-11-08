#ifndef GUICHATSTACK_H
#define GUICHATSTACK_H

#include "Global.h"
#include "UsrData.h"
#include "Data/AppDataManager.h"
#include "Gui/Frameworks/ScrollStack.h"
#include "Gui/Frameworks/Widgets/LabelButton.h"
#include "Gui/Frameworks/Widgets/AvatarWidgets.h"
#include "Gui/Frameworks/Widgets/TextBubble.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QScrollArea>
#include <QTextEdit>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QJsonArray>
#include <QProgressBar>
#include <QVariantAnimation>

class TextEdit;
class MessageViewer;
class MessageEditor;
class ChatStack;


class TextEdit : public QTextEdit
{
  Q_OBJECT

public:
  explicit TextEdit(QWidget *parent = nullptr);
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

class MessageViewer : public QWidget
{
  Q_OBJECT

public:
  explicit MessageViewer(QWidget *parent = nullptr);
  ~MessageViewer();

  void clearChatBubbles();

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *chat_bubble_layout;
  TextBubble *chat_bubble;

  QList<TextBubble*> chat_bubble_list;

public slots:
  void addChatBubble(const QString &message, const bool &fromMe);

};

class MessageEditor : public QWidget
{
  Q_OBJECT

public:
  explicit MessageEditor(QWidget *parent = nullptr);
  ~MessageEditor();

  QString currentFileName();

  TextEdit *text_editor;
  LabelButton *send_btn;

protected:
  //! Capture QEvent outside the class!
  bool eventFilter(QObject *obj, QEvent *e);

private:
  QVBoxLayout *edit_layout;
  QHBoxLayout *tool_layout;
  QHBoxLayout *main_layout;

  LabelButton *expression_label;
  LabelButton *image_label;
  LabelButton *file_label;
  QProgressBar *file_progress_bar;
  QLabel *file_progress_label;

  QVariantAnimation *file_tran_ani;

  QString current_file_name;

  bool control_pressed = false;
  bool file_label_hovered = false;

signals:
  void sendFile();
  void sendTriggered();

};

class ChatStack : public ScrollStack
{
  Q_OBJECT

public:
  explicit ChatStack(QWidget *parent = nullptr);
  ~ChatStack();

  void display(const QString &usrKey);
  bool refreshProfile(const QString &usrKey);
  bool refreshMessage(const QString &usrKey);

protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

  LayoutStyle layout_style = LayoutStyle::Profile;

private:
  //UI
  QHash<QString, MessageViewer*> chat_widget_hash;
  QHash<QString, QString> editing_message_hash;

  MessageViewer *chat_widget;
  MessageEditor *message_editor;

  //Data
  UsrData *usr_data;
  QPair<int, int> file_tran_progress_pair;

  int click_num = 0;
  QTime first_click_time;
  bool easter_animating = false;
  bool key_lock = false;

  //Function
  void flipUnreadMessage();
  void flipLatestMessage(const bool &clear);
  void flipUpMessage(const bool &clear);
  void flipDownMessage(const bool &clear);
  bool isDisplaying(const QString &usrKey);
  void setUsrData(UsrData *usrData);
  void updateFileTranProgress();

public slots:
  void onSendButtonClicked();
  void onKeyEnterTriggered(bool &pressed);

signals:
  void sendMessage(QString usrKey, QString message);

};






#endif // GUICHATSTACK_H

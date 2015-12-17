#include "GuiTabLabel.h"

GuiTabLabel::GuiTabLabel(QWidget *parent)
{
  QPalette pa;
  pa.setColor(QPalette::WindowText, Qt::darkGreen);
  setPalette(pa);
}

GuiTabLabel::GuiTabLabel(const QString &text)
{
  setText(text);
}

void GuiTabLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit clicked();//(this);
}

/*void GuiTabLabel::enterEvent(QEvent * )
{
    QPalette pa;
    pa.setColor(QPalette::Background, Qt::blue);
    setPalette(pa);
}

void GuiTabLabel::leaveEvent(QEvent *)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);
}*/

#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("sub");
    b.setParent(this);
    b.setText("show main window");

    connect(&b,&QPushButton::pressed,this,&SubWidget::sendSlot);
}

void SubWidget::sendSlot()
{
    emit mySignal();//按下按钮后发送信号，需要再编写主窗口接收程序
    emit mySignal(7,"OK"); //重载,产生二义性
}

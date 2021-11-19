#ifndef SUBWIDGET_H
#define SUBWIDGET_H

//子窗口头文件被主窗口包含，避免双向引用

#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = nullptr);

private:
    QPushButton b;
    void sendSlot();

//信号必须有这个关键字来声明，没有返回值，但可以有参数，就是函数声明，只需声明，无需定义
//Qt才有的关键词，编译时会自动处理
//signals支持重载
signals:
     void mySignal();
     void mySignal(int, QString);

};

#endif // SUBWIDGET_H

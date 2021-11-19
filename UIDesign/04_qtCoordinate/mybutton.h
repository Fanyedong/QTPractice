#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>

class myButton : public QPushButton//修改基类
{
    Q_OBJECT
public:
    explicit myButton(QWidget *parent = nullptr);
    ~myButton();

signals:

};

#endif // MYBUTTON_H

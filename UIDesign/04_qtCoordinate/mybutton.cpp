#include "mybutton.h"

myButton::myButton(QWidget *parent) : QPushButton(parent) //通过参数列表的方式给基类传参
{

}

myButton::~myButton()
{
    qDebug()<<"The user-defined button is deleted!";
}

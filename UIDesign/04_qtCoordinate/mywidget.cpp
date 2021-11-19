#include "mywidget.h"

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
{
    move(200,200);//为什么按钮和窗口都可以用move?所有空间都是继承于QWidget
    /*
     * 对于父窗口，坐标系统相对于屏幕
     * 原点相对于屏幕左上角
     * x向右递增，y向下递增
    */

    QPushButton *b1 = new QPushButton(this);
    b1->move(100,100);
    b1->setText("B1");
    b1->resize(200,200);

    //b2的父窗口为第一个按键b1，相对坐标关系根据b1
    QPushButton *b2 = new QPushButton(b1);
    b2->move(20,20);
    b2->setText("B2");
    b2->resize(100,100);

    /* 动态分配了两个空间
     * 对象树： QObject-QWidget-b1-b2
     * 从下至上自动释放，回收资源
     * 验证手动写一个按钮类，myButton，析构函数有输出；关闭程序后，new了没有delete,但是析构函数已执行，有输出
     * 子对象如果是动态分配空间的，不需要手动释放
     * 前提：指定父对象;直接或间接继承于QObject
     */
    myButton *b3 = new myButton(this);
    b3->setText("B3");
}

myWidget::~myWidget()
{
}


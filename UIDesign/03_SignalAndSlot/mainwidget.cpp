#include "mainwidget.h"

//F4: .cpp, .h切换
//信号与槽：Qt对象之间通信的接口

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    /* 错误示例:局部变量不能显示
    QPushButton b;
    b.setParent(this);
    b.setText("Press");
    b.show();
    */

    b1.setParent(this);
    b1.setText("close");
    b1.move(100,100);

    //如果是指针，需要动态分配空间
    b2 = new QPushButton;
    b2->setParent(this);
    b2->setText("Change text and hide another button");

    /* 信号与槽
    头文件 #include <QPushButton>两次F1，查看帮助查看信号，Esc退出
    */
    connect(&b1,&QPushButton::pressed,this,&MainWidget::close);
    /*
     * &b1信号发出者，指针类型；
     * &QPushButton::pressed 处理的信号， &发送者的类名::信号的名字
     * this信号接收者
     * &MainWidget::close槽函数，信号处理函数 &接收的类名::槽函数的名字
     */

    /* 自定义槽，普通函数的用法
     * QT5：任意的成员函数，普通全局函数，静态函数
     * 槽函数需要和信号一致（参数，返回值）
     * 由于信号没有返回值，槽函数一定没有返回值
     */
    //接收对象分别为窗口和按钮，后面的类也跟着改变
    connect(b2,&QPushButton::released,this,&MainWidget::mySlot);
    connect(b2,&QPushButton::released,&b1,&QPushButton::hide);

    /* 信号类似于短信，槽类似于手机 */

    setWindowTitle("MainWindow");

    b3.setParent(this);
    b3.setText("showSubWindow");
    b3.move(200,200);
    connect(&b3,&QPushButton::pressed,this,&MainWidget::changeToSub);//主窗口切换至子窗口
    //问题信号是按钮发出的还是窗口发出的？按钮不发送信号，按钮调用了函数，函数发送信号，函数属于窗口

    /* 信号的重载
     * 方法一：指向函数的指针
     * void fun(int){}
     * void (*p)(int) =fun;
     *
     * 方法二：
     * 直接调用SIGNAL,SLOT(不推荐)
     * 原因：不做错误检查；必须用slot修饰;写明函数参数
     * 如果SINGAL不能自动检索，需要选帮助-插件-去掉ClangCodeModel，重启
    */

//    //方法1：
//    void (SubWidget::*p1)() = &SubWidget::mySignal;//指针需要增加作用域
//    connect(&sub,p1,this,&MainWidget::dealSignalsFromSub);//不带参数的信号

//    void (SubWidget::*p2)(int,QString) = &SubWidget::mySignal;//指针需要增加作用域
//    connect(&sub,p2,this,&MainWidget::dealSignalsWithPara);//带参数的信号

    //方法2：
    connect(&sub,SIGNAL(mySignal()),this,SLOT(dealSignalsFromSub()));
    connect(&sub,SIGNAL(mySignal(int, QString)),this,SLOT(dealSignalsWithPara(int,QString)));

    /* Lambda表达式，匿名函数对象
     * .pro文件CONFIG += c++11
     * Qt配合信号一起使用，非常方便
     * 对比：void fun(){}
     * (){}相同，[]不同,[]放需要用到的外部变量
     * []中尽量不要用引用&
     *
    */

    int a=10, b=20;
    QPushButton *b4 = new QPushButton(this);
    b4->setText("Lambda");
    b4->move(150,150);

    connect(b4,&QPushButton::released,
            [b4,a,b]() mutable//[=]把外部所有局部变量、类中所有成员以值的方式传递，[=]非常常用
        {
            b4->setText("CHANGED");
            qDebug()<<"Lambda "<< a<<" "<<b;
        }
    );

    connect(b4,&QPushButton::clicked,
            [](bool isCheck) mutable
        {
            qDebug()<< isCheck;
        }
    );



    //sub.show();
}

void MainWidget::dealSignalsWithPara(int a, QString str)
{
    qDebug()<< a<<" "<<str;
}

void MainWidget::dealSignalsFromSub()
{
   sub.hide();
   this->show();
}

void MainWidget::changeToSub()
{
    sub.show();
    this->hide();
}

void MainWidget::mySlot()
{
    b2->setText("changed");
}

MainWidget::~MainWidget()
{
}

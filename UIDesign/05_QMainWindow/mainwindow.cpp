#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //(1)菜单栏
    QMenuBar *mBar = menuBar();
    QMenu *pFile = mBar->addMenu("File");
    //添加菜单项，添加动作
    QAction *pNew = pFile->addAction("New");
    connect(pNew,&QAction::triggered,
            []()
    {
        qDebug()<<"New button is pressed!";
    }
    );

    pFile->addSeparator();//添加分割线
    QAction *pOpen = pFile->addAction("Open");

    //(2)工具栏，菜单项的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");
    toolBar->addAction(pNew);


    QPushButton *b = new QPushButton(this);
    b->setText("Press");
    toolBar->addWidget(b);

    connect(b,QPushButton::clicked,[=]()
    {
        b->setText("Changed");
    }

    );

    //(3)状态栏
    QStatusBar *sBar = statusBar();
    QLabel *label = new QLabel(this);
    label->setText("Normal Running");
    sBar->addWidget(label);
    sBar->addWidget(new QLabel("1",this));
    sBar->addPermanentWidget(new QLabel("2",this));


    //核心控件
    //浮动窗口
}

MainWindow::~MainWindow()
{
}


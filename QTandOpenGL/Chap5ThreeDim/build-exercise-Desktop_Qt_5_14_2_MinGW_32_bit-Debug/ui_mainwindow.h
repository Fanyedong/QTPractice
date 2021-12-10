/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <axbopenglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiondraw;
    QAction *actionclear;
    QAction *action1;
    QAction *action2;
    QAction *action3;
    QAction *action1_2;
    QAction *action2_2;
    QAction *action1_3;
    QAction *action2_3;
    QAction *action3_2;
    QWidget *centralwidget;
    AXBOpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menuA;
    QMenu *menuB;
    QMenu *menuC;
    QMenu *menuD;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("D:/Desktop/cube.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"background-color:rgb(68,68,68);\n"
"color:rgb(255,255,255);\n"
"font:10pt \"\345\271\274\345\234\206\";\n"
"}\n"
"QMenuBar\n"
"{\n"
"background-color:rgb(200,200,200);\n"
"color:rgb(60,60,60);\n"
"}"));
        actiondraw = new QAction(MainWindow);
        actiondraw->setObjectName(QString::fromUtf8("actiondraw"));
        actionclear = new QAction(MainWindow);
        actionclear->setObjectName(QString::fromUtf8("actionclear"));
        action1 = new QAction(MainWindow);
        action1->setObjectName(QString::fromUtf8("action1"));
        action2 = new QAction(MainWindow);
        action2->setObjectName(QString::fromUtf8("action2"));
        action3 = new QAction(MainWindow);
        action3->setObjectName(QString::fromUtf8("action3"));
        action1_2 = new QAction(MainWindow);
        action1_2->setObjectName(QString::fromUtf8("action1_2"));
        action2_2 = new QAction(MainWindow);
        action2_2->setObjectName(QString::fromUtf8("action2_2"));
        action1_3 = new QAction(MainWindow);
        action1_3->setObjectName(QString::fromUtf8("action1_3"));
        action2_3 = new QAction(MainWindow);
        action2_3->setObjectName(QString::fromUtf8("action2_3"));
        action3_2 = new QAction(MainWindow);
        action3_2->setObjectName(QString::fromUtf8("action3_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new AXBOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(100, 130, 601, 301));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuA = new QMenu(menubar);
        menuA->setObjectName(QString::fromUtf8("menuA"));
        menuB = new QMenu(menubar);
        menuB->setObjectName(QString::fromUtf8("menuB"));
        menuC = new QMenu(menubar);
        menuC->setObjectName(QString::fromUtf8("menuC"));
        menuD = new QMenu(menubar);
        menuD->setObjectName(QString::fromUtf8("menuD"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuA->menuAction());
        menubar->addAction(menuB->menuAction());
        menubar->addAction(menuC->menuAction());
        menubar->addAction(menuD->menuAction());
        menuA->addAction(action1);
        menuA->addAction(action2);
        menuA->addAction(action3);
        menuB->addAction(action1_2);
        menuB->addAction(action2_2);
        menuC->addAction(action1_3);
        menuC->addAction(action2_3);
        menuC->addAction(action3_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Demo", nullptr));
        actiondraw->setText(QCoreApplication::translate("MainWindow", "drawA", nullptr));
        actionclear->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        action1->setText(QCoreApplication::translate("MainWindow", "Rect", nullptr));
        action2->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        action3->setText(QCoreApplication::translate("MainWindow", "WireFrame", nullptr));
        action1_2->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        action2_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        action1_3->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        action2_3->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        action3_2->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        menuA->setTitle(QCoreApplication::translate("MainWindow", "A", nullptr));
        menuB->setTitle(QCoreApplication::translate("MainWindow", "B", nullptr));
        menuC->setTitle(QCoreApplication::translate("MainWindow", "C", nullptr));
        menuD->setTitle(QCoreApplication::translate("MainWindow", "D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

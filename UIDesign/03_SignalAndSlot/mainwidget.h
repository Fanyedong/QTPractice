#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include "subwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;

    SubWidget sub;

public slots:
    void mySlot();
    void changeToSub();
    void dealSignalsFromSub();
    void dealSignalsWithPara(int a, QString str);

};
#endif // MAINWIDGET_H

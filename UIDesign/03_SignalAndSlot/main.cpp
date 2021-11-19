#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;//执行到此处时，不是继续执行下面的代码，而是执行构造函数
    w.show();
    return a.exec();
}

#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("Empty");
//    w.show();

//    QPushButton b;
//    b.setText("Press");
//    b.show(); //控件不show无法显示

    /*如果不指定父对象，对象和对象没有关系，独立
    a指定b为它的父对象，a放在b的上面
    指定父对象的2种方法：
    (1)setParent
    (2)通过构造函数传参
    指定父对象，只需要父对象显示，上面的子对象自动显示
    */

    // Method 1
    QPushButton b;
    b.setText("Press");
    b.setParent(&w); //控件不show无法显示
    b.move(100,100);

    // Method 2
    QPushButton b1(&w);
    b1.setText("Touch");

    //父子窗口=父子对象=父子控件

    w.show();

    app.exec();
    return 0;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action1_triggered()
{
    ui->openGLWidget->drawShape(AXBOpenGLWidget::Rect);
}

void MainWindow::on_action2_triggered()
{
    ui->openGLWidget->drawShape(AXBOpenGLWidget::None);
}

void MainWindow::on_action3_triggered()
{
    ui->openGLWidget->setWireFrame(1);
}

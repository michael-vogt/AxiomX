#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "point.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Point* p = new Point(0, 0);
    delete p;
}

MainWindow::~MainWindow()
{
    delete ui;
}

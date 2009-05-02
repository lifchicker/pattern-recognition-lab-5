#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    setup_connections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::choose_color_1()
{
}

void MainWindow::choose_color_2()
{
}

void MainWindow::setup_connections()
{
}

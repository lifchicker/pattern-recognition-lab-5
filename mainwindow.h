#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class QPainterPath;
class QRectF;
class QGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

private slots:
//    void calculate_values();
    void choose_color_1();
    void choose_color_2();
//    void draw();
//    void generate();
//    void load();
//    void save_selection();

private:
    void choose_color();
    void setup_connections();

private:
    Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H

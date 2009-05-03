#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "distribution.h"
#include "distributioninfo.h"

class QPainterPath;
class QRectF;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

private slots:
    void calculate_values();
    void choose_color_1();
    void choose_color_2();
//    void draw();
//    void generate();
    void load();
    void save_selection();

private:
    void choose_color();
    double plot_x(double x);
    double plot_y(double y);
    void setup_connections();

private:
    Ui::MainWindowClass ui; //gui

    Distribution* distributions;
    DistributionInfo distributionsInfo[2];
};

#endif // MAINWINDOW_H

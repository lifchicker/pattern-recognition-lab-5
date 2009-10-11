#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "distribution.h"

class QPainterPath;
class QGraphicsScene;

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
    void draw();
    void generate();
    void load();
    void save_selection();

private:
    void choose_color();
    void draw_axises(QGraphicsScene * scene);
    void draw_distribution(int activeDistributionNumber, QGraphicsScene * scene);
    void draw_ellipse(int activeDistributionNumber, QPainterPath &path, double p);
    void draw_isolines(int activeDistributionNumber, QGraphicsScene * scene);
    void draw_middle_point(int activeDistributionNumber, QGraphicsScene * scene);
    void draw_points(int activeDistributionNumber, QPen & pen, QGraphicsScene * scene);
    double plot_x(double x);
    double plot_y(double y);
    void setup_connections();
    void setup_active_distributions_and_components();

private:
    Ui::MainWindowClass ui; //gui

    QVector<Distribution> distributions;

    //dimention of X
    int m;

    //true if selection was generated
    bool selectionGenerated;

    //selection size
    int selectionSize;

    //active distributions
    int activeDistribution[2];

    //active components of active distributions
    int activeComponent[2];

    double kxy[2];
    double r[2];
};

#endif // MAINWINDOW_H

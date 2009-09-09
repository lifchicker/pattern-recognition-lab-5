#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"


#include "distribution.h"
#include "activedistribution.h"

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
    void calculate_values();
    void choose_color_1();
    void choose_color_2();
    void draw();
    void generate();
    void load();
    void save_selection();

private:
    void calculate_bounding_rect(double * x, double * y, int size);
    void choose_color();
    void draw_axises(QGraphicsScene * scene);
    void draw_distribution(DistributionInfo * distributionInfo, QGraphicsScene * scene);
    void draw_ellipse(DistributionInfo * distributionInfo, QPainterPath &path, double p);
    void draw_isolines(DistributionInfo * distributionInfo, QGraphicsScene * scene);
    void draw_middle_point(DistributionInfo * distributionInfo, QGraphicsScene * scene);
    void draw_points(double * x, double * y, int size, QPen & pen, QGraphicsScene * scene);
    double plot_x(double x);
    double plot_y(double y);
    void setup_connections();

private:
    Ui::MainWindowClass ui; //gui

    QRectF boundingRect;

    //info about distributions: ||A|| matrix,
    //matrix of correlations, vector of average values
    QVector<Distribution> distributions;

    //dimention of X
    int m;

    //true if selection was generated
    bool selectionGenerated;

    //selection size
    int selectionSize;

    //info about 2 current selected dustributions
    ActiveDistribution activeDistributions[2];
};

#endif // MAINWINDOW_H

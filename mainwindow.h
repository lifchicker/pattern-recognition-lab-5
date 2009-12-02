#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "formwithtable.h"

#include "distribution.h"
#include "classifier.h"

class QPainterPath;
class QGraphicsScene;
class QColor;

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
    void load_regret_matrix();
    void recognize();
    void save_selection();
    void show_matrix_of_correlations1();
    void show_matrix_of_correlations2();
    void show_transformation_matrix();
    void formWithTableDestroyed();

private:
    double calculate_classification_error_probability();
    void calculate_middle_risk();
    matrix<int> calculate_transformation_matrix();
    void choose_color();
    void draw_axises(QGraphicsScene * scene);
    void draw_distribution(const int activeDistributionNumber, QGraphicsScene * scene);
    void draw_ellipse(const int activeDistributionNumber, QPainterPath &path, double p);
    void draw_isolines(const int activeDistributionNumber, QGraphicsScene * scene);
    void draw_middle_point(const int activeDistributionNumber, QGraphicsScene * scene);
    void draw_points(const int activeDistributionNumber, QGraphicsScene * scene);
    double plot_x(double x);
    double plot_y(double y);
    void setup_connections();
    void setup_active_distributions_and_components();

private:
    Ui::MainWindowClass ui; //gui

    FormWithTable * formForVisualizationMatrices;

    QVector<Distribution> distributions;

    //regret matrix
    matrix<double> regretMatrix;

    //dimention of X
    int m;

    //true if selection was generated
    bool selectionGenerated;

    //selection size
    int selectionSize;

    //active distributions
    int activeDistribution[2];
    QColor actualColors[2];

    //active components of active distributions
    int activeComponent[2];

    double kxy[2];
    double r[2];

    Classifier * classifier;
};

#endif // MAINWINDOW_H

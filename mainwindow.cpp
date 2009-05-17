#include <QtGui>
#include "mainwindow.h"

#include <fstream>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
    distributions(NULL)
{
    ui.setupUi(this);

    setup_connections();

    srand(QTime::currentTime().elapsed());
}

MainWindow::~MainWindow()
{
    if (distributions != NULL)
    {
        delete[] distributions;
        distributions = NULL;
    }
}

void MainWindow::calculate_values()
{
    if (!distributions)
        return;

    if (!selectionGenerated)
        generate();

    int distr1 = ui.distribution1->value() - 1;
    int distr2 = ui.distribution2->value() - 1;
    int vec1 = ui.component1->value() - 1;
    int vec2 = ui.component2->value() - 1;

    distributionsInfo[0].set_vectors(distributions[distr1].get_x()[vec1], distributions[distr1].get_x()[vec2]);
    distributionsInfo[1].set_vectors(distributions[distr2].get_x()[vec1], distributions[distr2].get_x()[vec2]);

    distributionsInfo[0].calculate_info(distributions[distr1].get_selectionSize());
    distributionsInfo[1].calculate_info(distributions[distr2].get_selectionSize());

    ui.labelMiddleX->setText(QString("%1").arg(distributionsInfo[0].middleX));
    ui.labelMiddleY->setText(QString("%1").arg(distributionsInfo[0].middleY));
    ui.labelSigmaX->setText(QString("%1").arg(distributionsInfo[0].sigmaX));
    ui.labelSigmaY->setText(QString("%1").arg(distributionsInfo[0].sigmaY));
    ui.labelKxy->setText(QString("%1").arg(distributionsInfo[0].kxy));
    ui.labelR->setText(QString("%1").arg(distributionsInfo[0].r));

    ui.labelMiddleX_2->setText(QString("%1").arg(distributionsInfo[1].middleX));
    ui.labelMiddleY_2->setText(QString("%1").arg(distributionsInfo[1].middleY));
    ui.labelSigmaX_2->setText(QString("%1").arg(distributionsInfo[1].sigmaX));
    ui.labelSigmaY_2->setText(QString("%1").arg(distributionsInfo[1].sigmaY));
    ui.labelKxy_2->setText(QString("%1").arg(distributionsInfo[1].kxy));
    ui.labelR_2->setText(QString("%1").arg(distributionsInfo[1].r));

    draw();
}

//setup color for the first distribution
void MainWindow::choose_color_1()
{
    //getting color
    QColor color = QColorDialog::getColor();
    if (!color.isValid())
        return;

    //setting up background brush with a new color
    ui.distributionColor1->setBackgroundBrush(QBrush(color, Qt::SolidPattern));

    //if scene not created, create it
    if (!ui.distributionColor1->scene())
        ui.distributionColor1->setScene(new QGraphicsScene(ui.distributionColor1->rect(), this));

    //set and show new color
    distributionsInfo[0].color = color;
    ui.distributionColor1->show();

}

//setup color for the second distribution
void MainWindow::choose_color_2()
{
    //getting color
    QColor color = QColorDialog::getColor();
    if (!color.isValid())
        return;

    //setting up background brush with a new color
    ui.distributionColor2->setBackgroundBrush(QBrush(color, Qt::SolidPattern));

    //if scene not created, create it
    if (!ui.distributionColor2->scene())
        ui.distributionColor2->setScene(new QGraphicsScene(ui.distributionColor2->rect(), this));

    //show new color
    distributionsInfo[1].color = color;
    ui.distributionColor2->show();

}

//drawing function
void MainWindow::draw()
{
    if (!selectionGenerated)
        return;

    if (!ui.graphicsView->scene())
        ui.graphicsView->setScene(new QGraphicsScene(this));

    ui.graphicsView->scene()->clear();

    if (ui.checkBoxDrawReal->isChecked())
    {
        //draw info about first distribution
        draw_distribution(0, ui.graphicsView->scene());

        //draw info about second distribution
        draw_distribution(1, ui.graphicsView->scene());
    }
}

void MainWindow::draw_all_points(int current, QGraphicsScene * scene)
{
    QPen pen;
    pen.setColor(distributionsInfo[current].color);
    pen.setWidth(2);

    for (int i = 0; i < selectionSize; ++i)
        scene->addLine(plot_x(distributionsInfo[current].x[i]), plot_y(distributionsInfo[current].y[i]),
                       plot_x(distributionsInfo[current].x[i]), plot_y(distributionsInfo[current].y[i]), pen);
}

//drawing all about (current) distribution
void MainWindow::draw_distribution(int current, QGraphicsScene * scene)
{
    if (ui.checkBoxSelection->isChecked())
        draw_all_points(current, scene);

    if (ui.checkBoxMiddle->isChecked())
        draw_middle_point(current, scene);

    if (ui.checkBoxIsolines->isChecked())
        draw_isolines(current, scene);
}

void MainWindow::draw_isolines(int current, QGraphicsScene * scene)
{
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 255));
    pen.setWidth(2);
}

void MainWindow::draw_middle_point(int current, QGraphicsScene * scene)
{
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 255));
    pen.setWidth(2);

    scene->addLine(plot_x(distributionsInfo[current].middleX), plot_y(distributionsInfo[current].middleY),
                   plot_x(distributionsInfo[current].middleX), plot_y(distributionsInfo[current].middleY), pen);
}

//generate selection
void MainWindow::generate()
{
    if (!distributions)
        return;

    selectionSize = ui.selectionDimention->value();

    for (int i = 0; i < numberOfDistributions; ++i)
        distributions[i].generate_selection(selectionSize);

    selectionGenerated = true;
}

//load distributions from file
void MainWindow::load()
{
    //getting name of the file with info about distributions
    QString filename = QFileDialog::getOpenFileName(this, tr("Select the input file"));

    if (filename.isEmpty())
        return;

    //open file
    std::fstream in;
    in.open(filename.toAscii().data(), std::ios_base::in);
    if (!in.is_open())
        return;

    //get number of distributions
    in >> numberOfDistributions;

    //delete old distributions
    if (distributions)
        delete distributions;

    //allocate memory for new distributions
    distributions = new (Distribution[numberOfDistributions]);

    //get dimention of X
    in >> m;

    for (int i = 0; i < numberOfDistributions; ++i)
    {
        //allocate memory for vector of average values
        double * a = new (double[m]);

        //load vector of average values
        for (int j = 0; j < m; ++j)
            in >> a[j];

        //allocate memory for matrix of correlations
        double ** b = new (double*[m]);
        for (int k = 0; k < m; ++k)
            b[k] = new (double[m]);

        //load matrix of correlations
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < m; ++k)
                in >> b[j][k];

        //set distribution values
        distributions[i].set_a(a);
        distributions[i].set_b(b);

        distributions[i].generate__a__(m);
    }

    in.close();

    ui.distribution1->setMaximum(numberOfDistributions);
    ui.distribution2->setMaximum(numberOfDistributions);

    ui.component1->setMaximum(m);
    ui.component2->setMaximum(m);

    ui.label_numberOfDistributions->setText(QString("%1").arg(numberOfDistributions));
    ui.label_m->setText(QString("%1").arg(m));
}

//get transformed x coordinate
double MainWindow::plot_x(double x)
{
    return x*static_cast<double>(ui.zoomX->value())*10.0;
}

//get transformed y coordinate
double MainWindow::plot_y(double y)
{
    //negative y value give to us right direction of y axis
    return -y*static_cast<double>(ui.zoomY->value())*10.0;
}

//save generated selection to file
void MainWindow::save_selection()
{
    //get name of the file to save selection in
    QString filename = QFileDialog::getSaveFileName(this, tr("Save selection to..."));

    if (filename.isEmpty())
        return;

    //open file for writing
    std::fstream out;
    out.open(filename.toAscii().data(), std::ios_base::out);
    if (!out.is_open())
        return;

    //TODO: code for saving selection to file must be here

    out.close();
}

void MainWindow::setup_connections()
{
    //connect buttons for choosing colors for distribution visualization
    connect(ui.chooseColorButton1, SIGNAL(clicked()), this, SLOT(choose_color_1()));
    connect(ui.chooseColorButton2, SIGNAL(clicked()), this, SLOT(choose_color_2()));

    //connect button for load distributions from file
    connect(ui.loadButton, SIGNAL(clicked()), this, SLOT(load()));

    //connect button for saving selection
    connect(ui.buttonSaveSelection, SIGNAL(clicked()), this, SLOT(save_selection()));

    //connect button for generate selection
    connect(ui.generateButton, SIGNAL(clicked()), this, SLOT(generate()));

    //connect button for calculate values
    connect(ui.drawButton, SIGNAL(clicked()), this, SLOT(calculate_values()));
    connect(ui.component1, SIGNAL(editingFinished()), this, SLOT(calculate_values()));
    connect(ui.component2, SIGNAL(editingFinished()), this, SLOT(calculate_values()));

    //connect zoom sliders
    connect(ui.zoomX, SIGNAL(valueChanged(int)), this, SLOT(draw()));
    connect(ui.zoomY, SIGNAL(valueChanged(int)), this, SLOT(draw()));
}

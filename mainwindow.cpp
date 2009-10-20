#include <QtGui>

#include <fstream>

#include "mainwindow.h"

//this definitions given from linux kernel source
#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

#include "bayesianclassifier.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), formForVisualizationMatrices(NULL),
    m(0), selectionGenerated(false),
    selectionSize(0), classifier(NULL)
{
    ui.setupUi(this);

    setup_connections();

    srand(QTime::currentTime().elapsed());
}

MainWindow::~MainWindow()
{
    if (classifier)
    {
        delete classifier;
        classifier = NULL;
    }

    if (formForVisualizationMatrices)
    {
        delete formForVisualizationMatrices;
        formForVisualizationMatrices = NULL;
    }
}

double MainWindow::calculate_classification_error_probability()
{
    int error = 0;

    for (int i = 0; i < distributions.size(); ++i)
        for (int j = 0; j < distributions[i].selectionVectorsInfo.size(); ++j)
            if (distributions[i].selectionVectorsInfo[j].recognizedDistribution !=
                distributions[i].selectionVectorsInfo[j].trueDistribution)
                error++;

    return static_cast<double>(error)/static_cast<double>(ui.selectionDimention->value());
}

matrix<int> MainWindow::calculate_transformation_matrix()
{
    matrix<int> transformationMatrix(distributions.size(), distributions.size());

    for (int i = 0; i < distributions.size(); ++i)
        for (int j = 0; j < distributions.size(); ++j)
            for (int k = 0; k < distributions[j].selectionVectorsInfo.size(); ++k)
                if (distributions[j].selectionVectorsInfo[k].recognizedDistribution == i)
                    transformationMatrix(i, j)++;

    return transformationMatrix;
}

void MainWindow::calculate_values()
{
    if (distributions.isEmpty())
        return;

    if (!selectionGenerated)
        generate();

    setup_active_distributions_and_components();

    //calculate distribution info
    distributions[activeDistribution[0]].calculate_distribution_info();
    distributions[activeDistribution[1]].calculate_distribution_info();

    kxy[0] = distributions[activeDistribution[0]].calculate_correlation_of_components(activeComponent[0], activeComponent[1]);
    kxy[1] = distributions[activeDistribution[1]].calculate_correlation_of_components(activeComponent[0], activeComponent[1]);

    r[0] = kxy[0]/(distributions[activeDistribution[0]].info.sigma(0, activeComponent[0])
                   *distributions[activeDistribution[0]].info.sigma(0, activeComponent[1]));

    r[1] = kxy[1]/(distributions[activeDistribution[1]].info.sigma(0, activeComponent[0])
                   *distributions[activeDistribution[1]].info.sigma(0, activeComponent[1]));

    ui.labelMiddleX->setText(QString("%1").arg(distributions[activeDistribution[0]].info.middle(0, activeComponent[0])));
    ui.labelMiddleY->setText(QString("%1").arg(distributions[activeDistribution[0]].info.middle(0, activeComponent[1])));
    ui.labelSigmaX->setText(QString("%1").arg(distributions[activeDistribution[0]].info.sigma(0, activeComponent[0])));
    ui.labelSigmaY->setText(QString("%1").arg(distributions[activeDistribution[0]].info.sigma(0, activeComponent[1])));
    ui.labelKxy->setText(QString("%1").arg(kxy[0]));
    ui.labelR->setText(QString("%1").arg(r[0]));

    ui.labelMiddleX_2->setText(QString("%1").arg(distributions[activeDistribution[1]].info.middle(0, activeComponent[0])));
    ui.labelMiddleY_2->setText(QString("%1").arg(distributions[activeDistribution[1]].info.middle(0, activeComponent[1])));
    ui.labelSigmaX_2->setText(QString("%1").arg(distributions[activeDistribution[1]].info.sigma(0, activeComponent[0])));
    ui.labelSigmaY_2->setText(QString("%1").arg(distributions[activeDistribution[1]].info.sigma(0, activeComponent[1])));
    ui.labelKxy_2->setText(QString("%1").arg(kxy[1]));
    ui.labelR_2->setText(QString("%1").arg(r[1]));

    draw();
}

//setup color for the first distribution
void MainWindow::choose_color_1()
{
    setup_active_distributions_and_components();

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
    distributions[activeDistribution[0]].info.color = color;
    ui.distributionColor1->show();

    draw();
}

//setup color for the second distribution
void MainWindow::choose_color_2()
{
    setup_active_distributions_and_components();

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
    distributions[activeDistribution[1]].info.color = color;
    ui.distributionColor2->show();

    draw();
}

//drawing function
void MainWindow::draw()
{
    setup_active_distributions_and_components();

    if (!selectionGenerated)
        return;

    if (!ui.graphicsView->scene())
        ui.graphicsView->setScene(new QGraphicsScene(this));

    ui.graphicsView->scene()->clear();

    if (ui.checkBoxDrawAxises->isChecked())
        draw_axises(ui.graphicsView->scene());

    if (ui.checkBoxDrawReal->isChecked())
    {
        //draw info about first distribution
        draw_distribution(0, ui.graphicsView->scene());

        //draw info about second distribution
        draw_distribution(1, ui.graphicsView->scene());
    }
}

void MainWindow::draw_axises(QGraphicsScene * scene)
{
    QPen pen;
    pen.setColor(QColor(10, 155, 10, 255));
    pen.setWidth(1);

    scene->addLine(plot_x(-1.0), plot_y(0.0), plot_x(1.0), plot_y(0.0), pen);
    scene->addLine(plot_x(0.0), plot_y(-1.0), plot_x(0.0), plot_y(1.0), pen);
}

//drawing all about (current) distribution
void MainWindow::draw_distribution(int activeDistributionNumber, QGraphicsScene * scene)
{
    if (ui.checkBoxSelection->isChecked())
        draw_points(activeDistribution[activeDistributionNumber], scene);

    if (ui.checkBoxMiddle->isChecked())
        draw_middle_point(activeDistribution[activeDistributionNumber], scene);

    if (ui.checkBoxIsolines->isChecked())
        draw_isolines(activeDistribution[activeDistributionNumber], scene);
}

void MainWindow::draw_ellipse(int activeDistributionNumber, QPainterPath &path, double p)
{
    const int STEP_OF_GRID = 300;

    QRectF boundingRect(distributions[activeDistribution[activeDistributionNumber]].calculate_bounding_box(activeComponent[0], activeComponent[1]));

    double width = boundingRect.width();
    width /= static_cast<double>(STEP_OF_GRID);
    double left = boundingRect.left();

    bool first = true;
    for (int i = 0; i <= STEP_OF_GRID; ++i)
    {
        double currentX = left + static_cast<double>(i)*width;
        double currentY = distributions[activeDistribution[activeDistributionNumber]].calculate_y1(activeComponent[0], activeComponent[1], r[activeDistributionNumber], currentX, p);
        if (unlikely(first))
        {
            if (!(isnan(currentY) || isinf(currentY)))
            {
                path.moveTo(plot_x(currentX), plot_y(currentY));
                first = false;
            }
        }
        else
            if (!(isnan(currentY) || isinf(currentY)))
                path.lineTo(plot_x(currentX), plot_y(currentY));
    }

    for (int i = STEP_OF_GRID; --i; )
    {
        double currentX = left + static_cast<double>(i)*width;
        double currentY = distributions[activeDistribution[activeDistributionNumber]].calculate_y2(activeComponent[0], activeComponent[1], r[activeDistributionNumber], currentX, p);
        if (!(isnan(currentY) || isinf(currentY)))
            path.lineTo(plot_x(currentX), plot_y(currentY));
    }
    path.connectPath(path);
}

void MainWindow::draw_isolines(int activeDistributionNumber, QGraphicsScene * scene)
{
    QPen pen;
    pen.setColor(QColor(10, 155, 10, 255));
    pen.setWidth(1);

    QPainterPath path1;
    QPainterPath path2;
    QPainterPath path3;
    draw_ellipse(activeDistributionNumber, path1, 0.3);
    draw_ellipse(activeDistributionNumber, path2, 0.6);
    draw_ellipse(activeDistributionNumber, path3, 0.9);
    scene->addPath(path1, pen);
    scene->addPath(path2, pen);
    scene->addPath(path3, pen);
}

void MainWindow::draw_middle_point(int activeDistributionNumber, QGraphicsScene * scene)
{
    QPen pen;
    pen.setColor(QColor(10, 155, 10, 255));
    pen.setWidth(2);

    scene->addLine(plot_x(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].info.middle(0, activeComponent[0])),
                   plot_y(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].info.middle(0, activeComponent[1])),
                   plot_x(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].info.middle(0, activeComponent[0])),
                   plot_y(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].info.middle(0, activeComponent[1])), pen);
}

void MainWindow::draw_points(int activeDistributionNumber, QGraphicsScene * scene)
{
    if (distributions.isEmpty())
        return;

    if (!distributions[activeDistribution[activeDistributionNumber]].selection.RowNo())
        return;

    QPen pen;
    pen.setWidth(2);

    for (size_t i = 0; i < distributions[activeDistribution[activeDistributionNumber]].selection.RowNo(); ++i)
    {
        //wrong recognized points draw in red color
        if (ui.checkBoxRecognized->isChecked() &&
            (distributions[activeDistribution[activeDistributionNumber]].selectionVectorsInfo[i].recognizedDistribution !=
             distributions[activeDistribution[activeDistributionNumber]].selectionVectorsInfo[i].trueDistribution))
            pen.setColor(QColor(255, 0, 0, 255));
        else
            pen.setColor(distributions[activeDistribution[activeDistributionNumber]].info.color);

        scene->addLine(plot_x(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].selection(i, activeComponent[0])),
                       plot_y(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].selection(i, activeComponent[1])),
                       plot_x(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].selection(i, activeComponent[0])),
                       plot_y(distributions[activeDistribution[activeDistribution[activeDistributionNumber]]].selection(i, activeComponent[1])),
                       pen);
    }
}

void MainWindow::formWithTableDestroyed()
{
    formForVisualizationMatrices = NULL;
}

//generate selection
void MainWindow::generate()
{
    if (distributions.isEmpty())
        return;

    selectionSize = ui.selectionDimention->value();

    //generate selections for all distributions
    for (int i = 0; i < distributions.size(); ++i)
    {
        int selection_size_for_current_distribution = static_cast<int>(static_cast<double>(selectionSize)*distributions[i].parameters.get_a_priori_probability());

        distributions[i].selection.SetSize(selection_size_for_current_distribution, distributions[i].parameters.get_m());

        distributions[i].selectionVectorsInfo.resize(selection_size_for_current_distribution);

        //generate random vectors with a given distribution
        distributions[i].parameters.generate_selection(distributions[i].selection);

        //set true distribution for all generated random vectors
        for (int j = 0; j < distributions[i].selectionVectorsInfo.size(); ++j)
        {
            distributions[i].selectionVectorsInfo[j].trueDistribution = i;
            distributions[i].selectionVectorsInfo[j].recognizedDistribution = 65535;
        }
    }

    selectionGenerated = true;

    calculate_values();
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
    int numberOfDistributions;
    in >> numberOfDistributions;

    //get dimention of X
    in >> m;

    //prepare for loading distributions
    //delete old distributions
    if (!distributions.isEmpty())
        distributions.clear();

    //resize vector for new distributions
    distributions.resize(numberOfDistributions);

    double summOfAPrioriProbability = 0.0;

    for (int i = 0; i < numberOfDistributions; ++i)
    {
        //get a priori probability
        double a_priori_probability;

        in >> a_priori_probability;

        summOfAPrioriProbability += a_priori_probability;
        if (summOfAPrioriProbability > 1.0)
        {
            QMessageBox::critical(this, tr("Invalid sum of a priori probabilities"),
                                  tr("Sum of all a priori probabilities >1"),
                                  QMessageBox::Ok);

            distributions.clear();
            return;
        }

        //allocate memory for vector of average values
        matrix<double> a(1, m);

        //load vector of average values
        in >> a;

        matrix<double> b(m, m);

        //load matrix of correlations
        in >> b;

        //fill distribution with correct parameters
        distributions[i].parameters.set_a(a);
        distributions[i].parameters.set_a_priori_probability(a_priori_probability);
        distributions[i].parameters.set_b(b);

        //generate ||A|| matrix
        if (!distributions[i].parameters.generate__a__(m))
        {
            //invalid matrix of correlations - let's say about it
            QMessageBox::critical(this, tr("Generation of ||A|| failed"),
                                  QString("Invalid matrix of correlations #%1!").arg(i+1),
                                  QMessageBox::Ok);
            //clear memory
            distributions.clear();

            //close input file
            in.close();

            //exit from load function
            return;
        }
    }

    //close input file
    in.close();

    ui.distribution1->setMaximum(numberOfDistributions);
    ui.distribution2->setMaximum(numberOfDistributions);

    ui.component1->setMaximum(m);
    ui.component2->setMaximum(m);

    ui.label_numberOfDistributions->setText(QString("%1").arg(numberOfDistributions));
    ui.label_m->setText(QString("%1").arg(m));

    selectionGenerated = false;
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

void MainWindow::recognize()
{
    if (classifier)
        delete classifier;

    switch (ui.classifierTypeComboBox->currentIndex())
    {
        case 0:
        {
            classifier = new BayesianClassifier();
        }
        break;

        default:
        QMessageBox::critical(this, tr("Choosing of classifier type failed"),
                              tr("Selected classifier not implemented! Choose another one."),
                              QMessageBox::Ok);
        return;
    }

    for (int i = 0; i < distributions.size(); ++i)
        distributions[i].calculate_E();

    matrix<double> tempX(1, distributions[0].parameters.get_m());

    for (int i = 0; i < distributions.size(); ++i)
        for (size_t j = 0; j < distributions[i].selection.RowNo(); ++j)
        {
            for (size_t k = 0; k < distributions[i].selection.ColNo(); ++k)
                tempX(0, k) = distributions[i].selection(j, k);

            distributions[i].selectionVectorsInfo[j].recognizedDistribution =
                    classifier->classify(tempX, distributions);
        }

    ui.labelClassificationErrorRisk->setText(QString("%1").arg(calculate_classification_error_probability()));
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

    //connect button for recognizing
    connect(ui.recognizeButton, SIGNAL(clicked()), this, SLOT(recognize()));

    //connect button for calculate values
    connect(ui.drawButton, SIGNAL(clicked()), this, SLOT(calculate_values()));
    connect(ui.component1, SIGNAL(editingFinished()), this, SLOT(calculate_values()));
    connect(ui.component2, SIGNAL(editingFinished()), this, SLOT(calculate_values()));

    //connect zoom sliders
    connect(ui.zoomX, SIGNAL(valueChanged(int)), this, SLOT(draw()));
    connect(ui.zoomY, SIGNAL(valueChanged(int)), this, SLOT(draw()));

    //connect checkboxes
    connect(ui.checkBoxDrawAxises, SIGNAL(clicked()), this, SLOT(draw()));
    connect(ui.checkBoxDrawReal, SIGNAL(clicked()), this, SLOT(draw()));
    connect(ui.checkBoxIsolines, SIGNAL(clicked()), this, SLOT(draw()));
    connect(ui.checkBoxMiddle, SIGNAL(clicked()), this, SLOT(draw()));
    connect(ui.checkBoxRecognized, SIGNAL(clicked()), this, SLOT(draw()));
    connect(ui.checkBoxSelection, SIGNAL(clicked()), this, SLOT(draw()));

    //connect button click action to transformationMatrixDialog show action
    connect(ui.transformationButton, SIGNAL(clicked()), this, SLOT(show_transformation_matrix()));
}

void MainWindow::setup_active_distributions_and_components()
{
    activeDistribution[0] = ui.distribution1->value() - 1;
    activeDistribution[1] = ui.distribution2->value() - 1;

    activeComponent[0] = ui.component1->value() - 1;
    activeComponent[1] = ui.component2->value() - 1;
}

void MainWindow::show_transformation_matrix()
{
    if (formForVisualizationMatrices)
    {
        delete formForVisualizationMatrices;
        formForVisualizationMatrices = NULL;
    }

    formForVisualizationMatrices = new FormWithTable(calculate_transformation_matrix());
    connect(formForVisualizationMatrices, SIGNAL(destroyed()), this, SLOT(formWithTableDestroyed()));
    formForVisualizationMatrices->setWindowTitle(tr("Transformation matrix"));
    formForVisualizationMatrices->show();
}

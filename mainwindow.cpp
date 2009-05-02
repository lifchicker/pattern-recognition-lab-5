#include <QtGui>
#include "mainwindow.h"

#include <fstream>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    setup_connections();
}

MainWindow::~MainWindow()
{
}

//setup color for the first distribution
void MainWindow::choose_color_1()
{
    //getting color
    QColor color = QColorDialog::getColor();
    if (color.isValid())
    {
        //setting up background brush with a new color
        ui.distributionColor1->setBackgroundBrush(QBrush(color, Qt::SolidPattern));

        //if scene not created, create it
        if (!ui.distributionColor1->scene())
            ui.distributionColor1->setScene(new QGraphicsScene(ui.distributionColor1->rect(), this));

        //show new color
        ui.distributionColor1->show();
    }
}

//setup color for the second distribution
void MainWindow::choose_color_2()
{
    //getting color
    QColor color = QColorDialog::getColor();
    if (color.isValid())
    {
        //setting up background brush with a new color
        ui.distributionColor2->setBackgroundBrush(QBrush(color, Qt::SolidPattern));

        //if scene not created, create it
        if (!ui.distributionColor2->scene())
            ui.distributionColor2->setScene(new QGraphicsScene(ui.distributionColor2->rect(), this));

        //show new color
        ui.distributionColor2->show();
    }
}

//load distributions from file
void MainWindow::load()
{
    //getting name of the file with info about distributions
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Select the input file"));

    if (filename.isEmpty())
        return;

    //open file
    std::fstream in;
    in.open(filename.toAscii().data(), std::ios_base::in);
    if (!in.is_open())
        return;

    //TODO: code with loading info about distributions must be here

    in.close();
}

//save generated selection to file
void MainWindow::save_selection()
{
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
}

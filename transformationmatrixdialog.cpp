#include "transformationmatrixdialog.h"
#include "ui_transformationmatrixdialog.h"

#include "matrix/include/matrix.h"
using namespace math;

TransformationMatrixDialog::TransformationMatrixDialog(QWidget *parent)
        :QDialog(parent),
        ui(new Ui::TransformationMatrixDialog)
{
    ui->setupUi(this);

    setup_connections();
}

TransformationMatrixDialog::TransformationMatrixDialog(matrix<int> transformationMatrix, QWidget *parent)
        :QDialog(parent),
        ui(new Ui::TransformationMatrixDialog)
{
    ui->setupUi(this);

    setup_connections();

    ui->transformationMatrixTableWidget->setColumnCount(transformationMatrix.ColNo());
    ui->transformationMatrixTableWidget->setRowCount(transformationMatrix.RowNo());
    for (size_t i = 0; i < transformationMatrix.RowNo(); ++i)
        for (size_t j = 0; j < transformationMatrix.ColNo(); ++j)
            ui->transformationMatrixTableWidget->setItem(i, j, new QTableWidgetItem(QString("%1").arg(transformationMatrix(i, j))));
}

TransformationMatrixDialog::~TransformationMatrixDialog()
{
    delete ui;
}

void TransformationMatrixDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TransformationMatrixDialog::setup_connections()
{
}

#include "formwithtable.h"
#include "ui_formwithtable.h"

#include "matrix/include/matrix.h"

FormWithTable::FormWithTable(QWidget *parent)
        :QWidget(parent),
        ui(new Ui::FormWithTable)
{
    ui->setupUi(this);
}

FormWithTable::FormWithTable(math::matrix<int> inputMatrix, QWidget *parent)
        :QWidget(parent),
        ui(new Ui::FormWithTable)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(inputMatrix.ColNo());
    ui->tableWidget->setRowCount(inputMatrix.RowNo());
    for (size_t i = 0; i < inputMatrix.RowNo(); ++i)
        for (size_t j = 0; j < inputMatrix.ColNo(); ++j)
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString("%1").arg(inputMatrix(i, j))));
}


FormWithTable::~FormWithTable()
{
    delete ui;
}

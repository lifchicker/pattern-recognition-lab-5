#ifndef TRANSFORMATIONMATRIXDIALOG_H
#define TRANSFORMATIONMATRIXDIALOG_H

#include <QtGui/QDialog>

namespace math
{
    template <class T>
            class matrix;
}

namespace Ui {
    class TransformationMatrixDialog;
}

class TransformationMatrixDialog : public QDialog {
    Q_OBJECT
public:
    TransformationMatrixDialog(QWidget *parent = 0);
    TransformationMatrixDialog(math::matrix<int> transformationMatrix, QWidget *parent = 0);
    ~TransformationMatrixDialog();

protected:
    void changeEvent(QEvent *e);

private:
    void setup_connections();

private:
    Ui::TransformationMatrixDialog *ui;
};

#endif // TRANSFORMATIONMATRIXDIALOG_H

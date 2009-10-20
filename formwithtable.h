#ifndef FORMWITHTABLE_H
#define FORMWITHTABLE_H

#include <QtGui/QWidget>

namespace math
{
    template <class T>
            class matrix;
}

namespace Ui {
    class FormWithTable;
}

class FormWithTable : public QWidget {
    Q_OBJECT
public:
    FormWithTable(QWidget *parent = 0);
    FormWithTable(math::matrix<int> inputMatrix, QWidget *parent = 0);
    ~FormWithTable();

private:
    Ui::FormWithTable *ui;
};

#endif // FORMWITHTABLE_H

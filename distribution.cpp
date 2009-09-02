#include "distribution.h"

#include <memory.h>
#include <math.h>
#include <stdlib.h>

double drand ()
{
    return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

Distribution::Distribution()
        :a(NULL), b(NULL), m(0), selectionSize(0),
        __a__(NULL), x(NULL)
{
}

Distribution::~Distribution()
{
    if (a != NULL)
    {
        delete[] a;
        a = NULL;
    }

    if (b != NULL)
        delete_array(b);

    if (__a__ != NULL)
        delete_array(__a__);

    if (x != NULL)
        delete_array(x);
}

//generate ||A|| matrix
//must be called after loading new data
bool Distribution::generate__a__(int _m)
{
    //set new dimention of x
    m = _m;

    if (__a__ != NULL)
        delete_array(__a__);

    __a__ = new double*[m];

    for (int i = 0; i < m; ++i)
    {
        __a__[i] = new double[m];
        memset(__a__[i], 0, sizeof(double)*m);
    }

    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= i; ++j)
        {
            double sum1 = 0.0;
            for (int k = 0; k < j; ++k)
                sum1 += __a__[i][k]*__a__[j][k];

            double sum2 = 0.0;
            for (int k = 0; k < j; ++k)
                sum2 += __a__[j][k]*__a__[j][k];

            if ((b[j][j] - sum2) <= 0.0)
            {
//                QMessageBox::critical(this, tr("Generation ||A|| failed"),
//                                      tr("Invalid matrix of correlations!"),
//                                      QMessageBox::Ok);
                delete[] __a__;
                __a__ = NULL;

                //invalid matrix of correlations, return false value
                return false;
            }

            __a__[i][j] = (b[i][j] - sum1)/sqrt(b[j][j] - sum2);
        }

    return true;
}

// generate random vector with normal distribution
void Distribution::generate_normal_vector(double * vec)
{
    if (!vec)
        return;

    for (int i = 0; i < m; ++i)
        vec[i] = drand();
}

// generate random vector with predefined partition law
void Distribution::generate_vector(double * vec)
{
    if (!vec)
        return;

    double * nv = new double[m];
    generate_normal_vector(nv);

    for (int i = 0; i < m; ++i)
    {
        double stringSum = 0.0;
        for (int j = 0; j < m; ++j)
            stringSum += __a__[i][j]*nv[j];
        vec[i] = stringSum + a[i];
    }

    delete[] nv;
}

//generate new selection
void Distribution::generate_selection(int _selectionSize)
{
    selectionSize = _selectionSize;

    if (x != NULL)
        delete_array(x);


    x = new (double*[m]);
    for (int i = 0; i < m; ++i)
        x[i] = new (double[selectionSize]);

    double * tmp_x = new (double[m]);
    for (int i = 0; i < selectionSize; ++i)
    {
        generate_vector(tmp_x);
        for (int j = 0; j < m; j++)
            x[j][i] = tmp_x[j];
    }
    delete[] tmp_x;
}

void Distribution::set_a(double * _a)
{
    if (!_a)
        return;

    if (a != NULL)
        delete[] a;

    a = _a;
}

void Distribution::set_b(double ** _b)
{
    if (!_b)
        return;

    if (b != NULL)
        delete_array(b);

    b = _b;
}

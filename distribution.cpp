#include "distribution.h"

#include <memory.h>
#include <math.h>
#include <stdlib.h>

double drand ()
{
    return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

Distribution::Distribution()
        :a(NULL), b(NULL),
        m(0), __a__(NULL)
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
                //invalid matrix of correlations

                //we need to free memory
                delete_array(__a__);

                //return false
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
void Distribution::generate_vector(RandomVector & vec, double * tmpVector)
{
    if (!vec.values.isEmpty())
        vec.values.clear();

    vec.values.resize(m);

    generate_normal_vector(tmpVector);

    for (int i = 0; i < m; ++i)
    {
        double stringSum = 0.0;
        for (int j = 0; j < m; ++j)
            stringSum += __a__[i][j]*tmpVector[j];
        vec.values[i] = stringSum + a[i];
    }

}

//generate new selection
void Distribution::generate_selection(Selection & selection)
{
    //if we have no vectors to fill random values
    if (selection.vectors.isEmpty())
        //go back
        return;

    //create temp vector wich will be contain normal vector
    //this is some sort of my optimization
    double * nv = new double[m];

    //for all vectors in current selection
    //generate vector with current distribution
    for (int i = 0; i < selection.vectors.size(); ++i)
        generate_vector(selection.vectors[i], nv);

    //delete temp vector
    delete[] nv;

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

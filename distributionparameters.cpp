#include "distributionparameters.h"

#include "matrix/include/matrix.h"
using namespace math;

#include <memory.h>
#include <math.h>
#include <stdlib.h>

#if defined(__WIN32__)
double drand48()
{
    return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}
#endif

double random_with_probability_distribution()
{
    double res = 0.0;
    for (int i = 0; i < 12; ++i)
        res += drand48();
    return res - 6.0;
}

DistributionParameters::DistributionParameters()
        :m(0)
{
}

DistributionParameters::~DistributionParameters()
{
}

//generate ||A|| matrix
//must be called after loading new data
bool DistributionParameters::generate__a__(int _m)
{
    //set new dimention of x
    m = _m;

    __a__.SetSize(m ,m);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= i; ++j)
        {
            double sum1 = 0.0;
            double sum2 = 0.0;
            for (int k = 0; k < j; ++k)
            {
                sum1 += __a__(i, k)*__a__(j, k);
                sum2 += __a__(j, k)*__a__(j, k);
            }

            if ((b(j, j) - sum2) <= 0.0)
                //invalid matrix of correlations
                //return false
                return false;

            __a__(i, j) = (b(i, j) - sum1)/sqrt(b(j, j) - sum2);
        }

    return true;
}

// generate random vector with normal distribution
void DistributionParameters::generate_normal_vector(double * vec)
{
    if (!vec)
        return;

    for (int i = 0; i < m; ++i)
        vec[i] = random_with_probability_distribution();
}

// generate random vector with predefined partition law
void DistributionParameters::generate_vector(math::matrix<double> & selection, int vec, double * tmpVector)
{
    generate_normal_vector(tmpVector);

    for (int i = 0; i < m; ++i)
    {
        double stringSum = 0.0;
        for (int j = 0; j <= i; ++j)
            stringSum += __a__(i, j)*tmpVector[j];
        selection(vec, i) = stringSum + a(0, i);
    }

}

//generate new selection
void DistributionParameters::generate_selection(math::matrix<double> & selection)
{
    //create temp vector wich will be contain normal vector
    //this is some sort of my optimization
    double * nv = new double[m];

    //for all vectors in current selection
    //generate vector with current distribution
    for (size_t i = 0; i < selection.RowNo(); ++i)
        generate_vector(selection, i, nv);

    //delete temp vector
    delete[] nv;

}

void DistributionParameters::set_a(matrix<double> _a)
{
    a = _a;
}

void DistributionParameters::set_b(matrix<double> _b)
{
    b = _b;
}

#include "bayesianclassifier.h"

#include "distribution.h"

#include <math.h>

BayesianClassifier::BayesianClassifier()
{
}

int BayesianClassifier::classify(const math::matrix<double> & x, const QVector<Distribution> & distributions)
{
    QVector<double> gi;
    gi.resize(distributions.size());

    int max = 0;

    for (int i = 0; i < distributions.size(); ++i)
    {
        gi[i] = g(x, distributions[i]);

        if (gi[max] < gi[i])
            max = i;
    }

    return max;
}

double BayesianClassifier::calculate_recognition_error(const math::matrix<double> & x,
                                                       const QVector<Distribution> & distributions,
                                                       const math::matrix<double> & regretMatrix)
{
    double R = 0.0;

    bool first = true;
    for (size_t i = 0; i < regretMatrix.RowNo(); ++i)
    {
        double tR = 0.0;

        for (int j = 0; j < distributions.size(); ++j)
            tR += regretMatrix(i, j)*g(x, distributions[j]);

        if (first)
        {
            R = tR;
            first = false;
        }

        if (R > tR)
            R = tR;
    }

    return -R;
}

double BayesianClassifier::calculate_mahalanobis_distance(const math::matrix<double> & x,
                                                          const Distribution & distribution)
{
    return (((x - distribution.info.middle)*(!distribution.info.E))*(~(x - distribution.info.middle)))(0,0);
    //return (((x - distribution.parameters.get_a())*(!distribution.parameters.get_b()))*(~(x - distribution.parameters.get_a())))(0,0);
    //return (((x - distribution.parameters.get_a())*(!distribution.info.E))*(~(x - distribution.parameters.get_a())))(0,0);
    //return (((x - distribution.info.middle)*(!distribution.parameters.get_b()))*(~(x - distribution.info.middle)))(0,0);
}

double BayesianClassifier::g(const math::matrix<double> & x, const Distribution & distribution)
{
    //          1        T  -1
    // gi(x) = --(x - mi) Ei  (x - mi) + Ln P(wi) + ci
    //          2

    //ci = -(1/2)Ln 2PI - (1/2) Ln |Ei|

    double distance, lp, ci;

    distance = -0.5*calculate_mahalanobis_distance(x, distribution);

    lp = log(distribution.parameters.get_a_priori_probability());

    ci = -0.5*(log(2*M_PI) + log(distribution.info.E.Det()));

    return distance + lp + ci;
}

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

double BayesianClassifier::calculate_mahalanobis_distance(const math::matrix<double> & x, const Distribution & distribution)
{
    return ((-0.5)*(((x - distribution.info.middle)*(!distribution.info.E))*(~(x - distribution.info.middle))))(0,0);
    //return (-0.5*(((x - distribution.parameters.get_a())*(!distribution.parameters.get_b()))*(~(x - distribution.parameters.get_a()))))(0,0);
    //return (-0.5*(((x - distribution.parameters.get_a())*(!distribution.info.E))*(~(x - distribution.parameters.get_a()))))(0,0);
    //return (-0.5*(((x - distribution.info.middle)*(!distribution.parameters.get_b()))*(~(x - distribution.info.middle))))(0,0);
}

double BayesianClassifier::g(const math::matrix<double> & x, const Distribution & distribution)
{
    //          1        T  -1
    // gi(x) = --(x - mi) Ei  (x - mi) + Ln P(wi) + ci
    //          2

    //ci = -(1/2)Ln 2PI - (1/2) Ln |Ei|

    double distance, lp, ci;

    distance = calculate_mahalanobis_distance(x, distribution);

    lp = log(distribution.parameters.get_a_priori_probability());

    //ci = -0.5*log(2*M_PI) - log(distribution.parameters.get_b().Det());
    ci = -0.5*log(2*M_PI) - log(distribution.info.E.Det());

    return distance + lp + ci;
}

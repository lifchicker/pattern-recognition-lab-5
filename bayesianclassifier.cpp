#include "bayesianclassifier.h"

#include "distribution.h"

BayesianClassifier::BayesianClassifier()
{
}

int BayesianClassifier::classify(const math::matrix<double> & x, const QVector<Distribution> & distributions)
{
    QVector<double> gi;
    gi.reserve(distributions.size());

    int max = 0;

    for (int i = 0; i < distributions.size(); ++i)
    {
        gi[i] = g(x, distributions[i]);

        if (gi[max] < gi[i])
            max = i;
    }

    return max;
}

double BayesianClassifier::g(const math::matrix<double> & x, const Distribution & distribution)
{
    //          1        T  -1
    // gi(x) = --(x - mi) Ei  (x - mi) + Ln P(wi) + ci
    //          2

    //ci = -(1/2)Ln 2PI - (1/2) Ln |Ei|


}

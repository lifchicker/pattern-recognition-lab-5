#include "bayesianclassifier.h"

#include "distribution.h"

BayesianClassifier::BayesianClassifier()
{
}

int BayesianClassifier::classify(const RandomVector & vector, const QVector<Distribution> & distributions)
{
    QVector<double> gi;
    gi.reserve(distributions.size());

    int max = 0;

    for (int i = 0; i < distributions.size(); ++i)
    {
        gi[i] = g(vector, distributions[i]);

        if (gi[max] < gi[i])
            max = i;
    }

    return max;
}

double BayesianClassifier::g(const RandomVector & vector, const Distribution & distribution)
{
}

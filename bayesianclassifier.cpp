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
    int size = distributions.size();

    for (int i = 0; i < distributions.size(); ++i)
    {
        double result = g(x, distributions[i]);
        gi[i] = result;

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

    matrix<double> result(1, 1);
    double ci;
    double lp;

    //result = (-0.5)*(((~(x - distribution.info.middle))*(!distribution.info.E))*(x - distribution.info.middle));
    result = (-0.5)*(((x - distribution.info.middle)*(!distribution.info.E))*(~(x - distribution.info.middle)));

    if ((result.ColNo() != 1) && (result.RowNo() != 1))
        REPORT_ERROR("Result matrix have dimentions are not 1");

    lp = log(distribution.parameters.get_a_priori_probability());

    ci = (-0.5)*log(2*M_PI) - 0.5*log(distribution.info.E.Det());

    return result(0, 0) + lp + ci;
}

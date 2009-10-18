#ifndef BAYESIANCLASSIFIER_H
#define BAYESIANCLASSIFIER_H

#include "classifier.h"

class BayesianClassifier : public Classifier
{
public:
    BayesianClassifier();

public:
    int classify(const math::matrix<double> & x, const QVector<Distribution> & distributions);
    double calculate_mahalanobis_distance(const math::matrix<double> & x, const Distribution & distribution);
    double g(const math::matrix<double> & x, const Distribution & distribution);
};

#endif // BAYESIANCLASSIFIER_H

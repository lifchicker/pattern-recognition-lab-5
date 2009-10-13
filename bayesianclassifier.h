#ifndef BAYESIANCLASSIFIER_H
#define BAYESIANCLASSIFIER_H

#include "classifier.h"

class BayesianClassifier : public Classifier
{
public:
    BayesianClassifier();

public:
    int classify(const RandomVector & vector, const QVector<Distribution> & distributions);
    double g(const RandomVector & vector, const Distribution & distribution);
};

#endif // BAYESIANCLASSIFIER_H

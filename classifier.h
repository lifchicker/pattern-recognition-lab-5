#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QVector>

class Distribution;

namespace math
{
    template <class T>
            class matrix;
}

class Classifier
{
public:
    Classifier() {}

public:
    //return distribution number wich belong generated vector
    virtual int classify(const math::matrix<double> & x, const QVector<Distribution> & distributions) = 0;

    //calculate g value
    virtual double g(const math::matrix<double> & x, const Distribution & distribution) = 0;
};

#endif // CLASSIFIER_H

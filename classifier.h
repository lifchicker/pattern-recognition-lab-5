#ifndef CLASSIFIER_H
#define CLASSIFIER_H

class RandomVector;
class Distribution;

#include <QVector>

class Classifier
{
public:
    Classifier() {}

public:
    //return distribution number wich belong generated vector
    virtual int classify(const RandomVector & vector, const QVector<Distribution> & distributions) = 0;

    //calculate g value
    virtual double g(const RandomVector & vector, const Distribution & distribution) = 0;
};

#endif // CLASSIFIER_H

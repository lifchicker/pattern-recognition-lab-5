#ifndef ACTIVEDISTRIBUTION_H
#define ACTIVEDISTRIBUTION_H

#include "distributioninfo.h"

class QPoint;

class ActiveDistribution
{
public:
    ActiveDistribution();

public:
    //setters
    void set_vectors(double * vec1, double * vec2);

public:
    double * x;
    double * y;

    int selectionSize;
};

#endif // ACTIVEDISTRIBUTION_H

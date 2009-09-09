/*
    Active Distribution contain components
    from selection for current selected distribution
*/
#ifndef ACTIVEDISTRIBUTION_H
#define ACTIVEDISTRIBUTION_H

#include "distributioninfo.h"

#include <QVector>

struct Components
{
    Components():first(0.0), second(0.0) {}

    //first component
    union
    {
        double first;
        double x;
    };

    //second component
    union
    {
        double second;
        double y;
    };
};

class ActiveDistribution
{
public:
    ActiveDistribution();

public:
    //calculate distribution info from values
    DistributionInfo calculateDistributionInfo();

public:
    //first component
    QVector<Components> components;
};

#endif // ACTIVEDISTRIBUTION_H

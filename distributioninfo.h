#ifndef DISTRIBUTIONINFO_H
#define DISTRIBUTIONINFO_H

#include <QColor>

class DistributionInfo
{
public:
    DistributionInfo();

public:
    double calculate_y1(double x, double p);
    double calculate_y2(double x, double p);

public:
    double kxy;
    double middleX;
    double middleY;
    double sigmaX;
    double sigmaY;
    double r;
    QColor color;
};

#endif // DISTRIBUTIONINFO_H

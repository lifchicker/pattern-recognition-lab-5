#ifndef DISTRIBUTIONINFO_H
#define DISTRIBUTIONINFO_H

#include <QColor>
#include <QRectF>

class DistributionInfo
{
public:
    DistributionInfo();
    DistributionInfo(const DistributionInfo & info);

public:
    double calculate_y1(double x, double p);
    double calculate_y2(double x, double p);

    DistributionInfo & operator = (const DistributionInfo & info);

public:
    double kxy;
    double middleX;
    double middleY;
    double sigmaX;
    double sigmaY;
    double r;
    QColor color;

    QRectF boundingRect;
};

#endif // DISTRIBUTIONINFO_H

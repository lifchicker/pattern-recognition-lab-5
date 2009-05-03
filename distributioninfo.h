#ifndef DISTRIBUTIONINFO_H
#define DISTRIBUTIONINFO_H

#include <QColor>

class DistributionInfo
{
public:
    DistributionInfo();

public:
    void calculate_info(int selectionSize);

    //setters
    void set_vectors(double * vec1, double * vec2);

public:
    double * x;
    double * y;

    double kxy;
    double middleX;
    double middleY;
    double sigmaX;
    double sigmaY;
    double r;
    QColor color;
};

#endif // DISTRIBUTIONINFO_H

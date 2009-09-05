#ifndef DISTRIBUTIONINFO_H
#define DISTRIBUTIONINFO_H

#include <QColor>

class DistributionInfo
{
public:
    DistributionInfo();

public:
    void calculate_info(int _selectionSize);
    double calculate_y1(double x, double p);
    double calculate_y2(double x, double p);

    //setters
    void set_vectors(double * vec1, double * vec2);

public:
    double * x;
    double * y;

    int selectionSize;

    double kxy;
    double middleX;
    double middleY;
    double sigmaX;
    double sigmaY;
    double r;
    QColor color;
};

#endif // DISTRIBUTIONINFO_H

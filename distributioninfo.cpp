#include "distributioninfo.h"
#include "distribution.h"

#include <math.h>

DistributionInfo::DistributionInfo()
        :x(NULL), y(NULL),
        kxy(0.0), middleX(0.0), middleY(0.0),
        sigmaX(0.0), sigmaY(0.0), r(0.0)
{
}

void DistributionInfo::calculate_info(int selectionSize)
{
    if ((selectionSize == 0) || !x || !y)
        return;

    middleX = 0.0;
    middleY = 0.0;
    for (int i = 0; i < selectionSize; ++i)
    {
        middleX += x[i];
        middleY += y[i];
    }
    middleX /= static_cast<double>(selectionSize);
    middleY /= static_cast<double>(selectionSize);

    sigmaX = 0.0;
    sigmaY = 0.0;
    kxy = 0.0;
    for (int i = 0; i < selectionSize; ++i)
    {
        sigmaX += (x[i] - middleX)*(x[i] - middleX);
        sigmaY += (y[i] - middleY)*(y[i] - middleY);
        kxy += (x[i] - middleX)*(y[i] - middleY);
    }
    sigmaX /= selectionSize;
    sigmaY /= selectionSize;
    kxy /= selectionSize;

    sigmaX = sqrt(sigmaX);
    sigmaY = sqrt(sigmaY);

    r = kxy/(sigmaX*sigmaY);

}

double DistributionInfo::calculate_y1(double x, double p)
{
    double sx2 = sigmaX*sigmaX;
    double sy2 = sigmaY*sigmaY;

    double lambdad = -log(p);//fabs(2.0*(1.0 - r*r)*log(2.0*M_PI*sigmaX*sigmaY*sqrt(1.0 - r*r)*p));

    return (r*sigmaY*x + sigmaX*middleY - r*sigmaY*middleX +
                sqrt(r*r*sy2*x*x - 2.0*r*r*sy2*x*middleX +
                r*r*sy2*middleX*middleX - sy2*x*x +
                2.0*sy2*x*middleX - sy2*middleX*middleX +
                lambdad*sx2*sy2)
            )/sigmaX;
}

double DistributionInfo::calculate_y2(double x, double p)
{
    double sx2 = sigmaX*sigmaX;
    double sy2 = sigmaY*sigmaY;

    double lambdad = -log(p);//fabs(2.0*(1.0 - r*r)*log(2.0*M_PI*sigmaX*sigmaY*sqrt(1.0 - r*r)*p));

    return (r*sigmaY*x + sigmaX*middleY - r*sigmaY*middleX -
                sqrt(r*r*sy2*x*x - 2.0*r*r*sy2*x*middleX +
                r*r*sy2*middleX*middleX - sy2*x*x +
                2.0*sy2*x*middleX - sy2*middleX*middleX +
                lambdad*sx2*sy2)
            )/sigmaX;
}

void DistributionInfo::set_vectors(double * vec1, double * vec2)
{
    x = vec1;
    y = vec2;
}

#include "distributioninfo.h"
#include "distribution.h"

#include <math.h>

DistributionInfo::DistributionInfo():
        kxy(0.0), middleX(0.0), middleY(0.0),
        sigmaX(0.0), sigmaY(0.0), r(0.0)
{
}

DistributionInfo::DistributionInfo(const DistributionInfo & info)
{
    kxy = info.kxy;
    middleX = info.middleX;
    middleY = info.middleY;
    sigmaX = info.sigmaX;
    sigmaY = info.sigmaY;
    r = info.r;
    color = info.color;
}

DistributionInfo & DistributionInfo::operator = (const DistributionInfo & info)
{
    kxy = info.kxy;
    middleX = info.middleX;
    middleY = info.middleY;
    sigmaX = info.sigmaX;
    sigmaY = info.sigmaY;
    r = info.r;
    color = info.color;

    return *this;
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

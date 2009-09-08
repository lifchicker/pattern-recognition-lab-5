#include "activedistribution.h"

ActiveDistribution::ActiveDistribution()
{
}

DistributionInfo ActiveDistribution::calculateInfo()
{
    DistributionInfo info;

    if (components.isEmpty())
        return info;

    info.middleX = 0.0;
    info.middleY = 0.0;
    for (int i = 0; i < components.size(); ++i)
    {
        info.middleX += components[i].x;
        info.middleY += components[i].y;
    }
    info.middleX /= static_cast<double>(components.size());
    info.middleY /= static_cast<double>(components.size());

    info.sigmaX = 0.0;
    info.sigmaY = 0.0;
    info.kxy = 0.0;
    for (int i = 0; i < components.size(); ++i)
    {
        info.sigmaX += (components[i].x - info.middleX)*(components[i].x - info.middleX);
        info.sigmaY += (components[i].y - info.middleY)*(components[i].y - info.middleY);
        info.kxy += (components[i].x - info.middleX)*(components[i].y - info.middleY);
    }
    info.sigmaX /= static_cast<double>(components.size());
    info.sigmaY /= static_cast<double>(components.size());
    info.kxy /= static_cast<double>(components.size());

    info.sigmaX = sqrt(sigmaX);
    info.sigmaY = sqrt(sigmaY);

    info.r = info.kxy/(info.sigmaX*info.sigmaY);

    return info;
}

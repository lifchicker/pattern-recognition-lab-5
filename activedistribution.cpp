#include "activedistribution.h"

#include <QRectF>
#include <math.h>

ActiveDistribution::ActiveDistribution()
        :distribution(0)
{
}

QRectF ActiveDistribution::calculateBoundingRect()
{
    QRectF boundingRect;

    for (int i = 0; i < components.size(); ++i)
    {
        if (components[i].x < boundingRect.left())
            boundingRect.setLeft(components[i].x);

        if (components[i].x > boundingRect.right())
            boundingRect.setRight(components[i].x);

        if (components[i].y < boundingRect.bottom())
            boundingRect.setBottom(components[i].y);

        if (components[i].y >  boundingRect.top())
            boundingRect.setTop(components[i].y);
    }

    return boundingRect;
}

void ActiveDistribution::calculateDistributionInfo()
{
    if (components.isEmpty())
        return;

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

    info.sigmaX = sqrt(info.sigmaX);
    info.sigmaY = sqrt(info.sigmaY);

    info.r = info.kxy/(info.sigmaX*info.sigmaY);

    info.boundingRect = calculateBoundingRect();
}

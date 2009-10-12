#include "distribution.h"

#include "math.h"

Distribution::Distribution()
{
}

QRectF Distribution::calculate_bounding_box(int component1, int component2)
{
    QRectF boundingRect;

    for (int i = 0; i < selection.vectors.size(); ++i)
    {
        if (selection.vectors[i].values[component1] < boundingRect.left())
            boundingRect.setLeft(selection.vectors[i].values[component1]);

        if (selection.vectors[i].values[component1] > boundingRect.right())
            boundingRect.setRight(selection.vectors[i].values[component1]);

        if (selection.vectors[i].values[component2] < boundingRect.bottom())
            boundingRect.setBottom(selection.vectors[i].values[component2]);

        if (selection.vectors[i].values[component2] >  boundingRect.top())
            boundingRect.setTop(selection.vectors[i].values[component2]);
    }

    return boundingRect;
}

double Distribution::calculate_correlation_of_components(int component1, int component2)
{
    double kxy = 0.0;

    for (int i = 0; i < selection.vectors.size(); ++i)
                kxy += (selection.vectors[i].values[component1] - info.middle[component1])*(selection.vectors[i].values[component2] - info.middle[component2]);

    kxy /= static_cast<double>(selection.vectors.size());

    return kxy;
}

void Distribution::calculate_distribution_info()
{
    if (selection.vectors.isEmpty())
        return;

    if (info.middle.isEmpty())
        info.middle.resize(selection.vectors.size());

    if (info.sigma.isEmpty())
        info.sigma.resize(selection.vectors.size());

    for (int i = 0; i < selection.vectors.size(); ++i)
    {
        for (int j = 0; j < selection.vectors[i].values.size(); ++j)
            info.middle[j] += selection.vectors[i].values[j];

    }

    for (int i = 0; i < selection.vectors.size(); ++i)
        for (int j = 0; j < selection.vectors[i].values.size(); ++j)
                info.sigma[j] += (selection.vectors[i].values[j] - info.middle[j])*(selection.vectors[i].values[j] - info.middle[j]);

    for (int i = 0; i < selection.vectors.size(); ++i)
    {
        info.middle[i] /= static_cast<double>(selection.vectors.size());
        info.sigma[i] /= static_cast<double>(selection.vectors.size());
        info.sigma[i] = sqrt(info.sigma[i]);
    }

    //info.r = info.kxy/(info.sigmaX*info.sigmaY);
}

double Distribution::calculate_y1(int component1, int component2, double r, double x, double p)
{
    double sigmaX = info.sigma[component1];
    double sigmaY = info.sigma[component2];
    double middleX = info.middle[component1];
    double middleY = info.middle[component2];

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

double Distribution::calculate_y2(int component1, int component2, double r, double x, double p)
{
    double sigmaX = info.sigma[component1];
    double sigmaY = info.sigma[component2];
    double middleX = info.middle[component1];
    double middleY = info.middle[component2];

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

#include "distribution.h"

#include "math.h"

Distribution::Distribution()
{
}

QRectF Distribution::calculate_bounding_box(int component1, int component2)
{
    QRectF boundingRect;

    for (size_t i = 0; i < selection.RowNo(); ++i)
    {
        if (selection(i, component1) < boundingRect.left())
            boundingRect.setLeft(selection(i, component1));

        if (selection(i, component1) > boundingRect.right())
            boundingRect.setRight(selection(i, component1));

        if (selection(i, component2) < boundingRect.bottom())
            boundingRect.setBottom(selection(i, component2));

        if (selection(i, component2) >  boundingRect.top())
            boundingRect.setTop(selection(i, component2));
    }

    return boundingRect;
}

double Distribution::calculate_correlation_of_components(int component1, int component2)
{
    double kxy = 0.0;

    for (size_t i = 0; i < selection.RowNo(); ++i)
                kxy += (selection(i, component1) - info.middle(0, component1))*(selection(i, component2) - info.middle(0, component2));

    kxy /= static_cast<double>(selection.RowNo());

    return kxy;
}

void Distribution::calculate_distribution_info()
{
    if (!selection.RowNo())
        return;

    info.middle.SetSize(1, selection.ColNo());
    info.sigma.SetSize(1, selection.ColNo());

    for (size_t i = 0; i < selection.RowNo(); ++i)
    {
        for (size_t j = 0; j < selection.ColNo(); ++j)
            info.middle(0, j) += selection(i, j);

    }

    for (size_t i = 0; i < selection.ColNo(); ++i)
        info.middle(0, i) /= static_cast<double>(selection.RowNo());


    for (size_t i = 0; i < selection.RowNo(); ++i)
        for (size_t j = 0; j < selection.ColNo(); ++j)
                info.sigma(0, j) += (selection(i, j) - info.middle(0, j))*(selection(i, j) - info.middle(0, j));

    for (size_t i = 0; i < selection.ColNo(); ++i)
    {
        info.sigma(0, i) /= static_cast<double>(selection.RowNo());
        info.sigma(0, i) = sqrt(info.sigma(0, i));
    }

    calculate_E();
}

void Distribution::calculate_E()
{
    //size of E must be mxm
    info.E.SetSize(selection.ColNo(), selection.ColNo());

    for (size_t i = 0; i < selection.ColNo(); ++i)
        for (size_t j = 0; j < selection.ColNo(); ++j)
            info.E(i, j) = calculate_correlation_of_components(i, j);
}

double Distribution::calculate_y1(int component1, int component2, double r, double x, double p)
{
    double sigmaX = info.sigma(0, component1);
    double sigmaY = info.sigma(0, component2);
    double middleX = info.middle(0, component1);
    double middleY = info.middle(0, component2);

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
    double sigmaX = info.sigma(0, component1);
    double sigmaY = info.sigma(0, component2);
    double middleX = info.middle(0, component1);
    double middleY = info.middle(0, component2);

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

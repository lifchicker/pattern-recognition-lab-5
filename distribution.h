#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "distributionparameters.h"

#include <QVector>
#include <QColor>
#include <QRectF>

#include "matrix/include/matrix.h"
using namespace math;

struct DistributionInfo
{
    DistributionInfo() {}
    DistributionInfo(const DistributionInfo & info)
    {
        middle = info.middle;
        sigma = info.sigma;
    }

    QVector<double> middle;
    QVector<double> sigma;

    QColor color;
};

struct RandomVectorInfo
{
    int trueDistribution;
    int recognizedDistribution;
};

class Distribution
{
public:
    Distribution();

public:
    QRectF calculate_bounding_box(int component1, int component2);
    double calculate_correlation_of_components(int component1, int component2);
    void calculate_distribution_info();

    double calculate_y1(int component1, int component2, double r, double x, double p);
    double calculate_y2(int component1, int component2, double r, double x, double p);

public:
    //info about distributions: ||A|| matrix,
    //matrix of correlations, vector of average values
    DistributionParameters parameters;

    //calculated info about distributions
    DistributionInfo info;

    //generated selection
    //Selection selection;
    matrix<double> selection;
    QVector<RandomVectorInfo> selectionVectorsInfo;
};

#endif // DISTRIBUTION_H

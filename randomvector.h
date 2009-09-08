#ifndef RANDOMVECTOR_H
#define RANDOMVECTOR_H

#include <QVector>

class RandomVector
{
public:
    RandomVector():trueDistribution(0),recognitionedDistribution(0) {}

    RandomVector(const RandomVector &vec)
    {
        values = vec.values;
        trueDistribution = vec.trueDistribution;
        recognitionedDistribution = vec.recognitionedDistribution;
    }

public:
    QVector<double> values;
    
    int trueDistribution;
    int recognitionedDistribution;
};

#endif // RANDOMVECTOR_H

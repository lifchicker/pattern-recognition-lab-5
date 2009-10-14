#ifndef RANDOMVECTOR_H
#define RANDOMVECTOR_H

#include <QVector>

class RandomVector
{
public:
    RandomVector():trueDistribution(0),recognizedDistribution(0) {}

    RandomVector(const RandomVector &vec)
    {
        values = vec.values;
        trueDistribution = vec.trueDistribution;
        recognizedDistribution = vec.recognizedDistribution;
    }

public:
    QVector<double> values;
    
    int trueDistribution;
    int recognizedDistribution;
};

#endif // RANDOMVECTOR_H

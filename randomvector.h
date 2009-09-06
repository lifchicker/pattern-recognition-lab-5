#ifndef RANDOMVECTOR_H
#define RANDOMVECTOR_H

class QVector;

class RandomVector
{

public:
    QVector<double> values;
    
    int trueDistribution;
    int recognitionedDistribution;
};

#endif // RANDOMVECTOR_H

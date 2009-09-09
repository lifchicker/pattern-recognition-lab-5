#ifndef SELECTION_H
#define SELECTION_H

#include "randomvector.h"

class Selection
{
public:
    Selection();

public:
    QVector<RandomVector> vectors;

    int distribution;
};

#endif // SELECTION_H

#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "selection.h"

class Distribution
{
public:
    Distribution();
    ~Distribution();

public:
    bool generate__a__(int _m);
    void generate_normal_vector(double * vec);
    void generate_vector(RandomVector & vec, double * tmpVector);
    void generate_selection(Selection & selection);

    //setters
    void set_a(double * _a);
    void set_b(double ** _b);

    //getters
    inline const double * get_a() const
    {
        return a;
    }

    inline double get_a_priori_probability() const
    {
        return a_priori_probability;
    }

    inline const double ** get_b() const
    {
        return b;
    }

    inline void delete_array(double ** array)
    {
        for (int i = 0; i < m; ++i)
            delete[] array[i];
        delete[] array;
        array = 0;
    }

private:
    //vector of average values
    double * a;

    //matrix of correlations
    double ** b;

    //dimention of X
    int m;

    //generated data
    // this is the ||A|| matrix
    double ** __a__;
};

#endif // DISTRIBUTION_H

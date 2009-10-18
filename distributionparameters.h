#ifndef DISTRIBUTIONPARAMETERS_H
#define DISTRIBUTIONPARAMETERS_H

#include "matrix/include/matrix.h"
using namespace math;

class DistributionParameters
{
public:
    DistributionParameters();
    ~DistributionParameters();

public:
    void calculate_distribution_info();

    bool generate__a__(int _m);
    void generate_normal_vector(double * vec);
    void generate_vector(math::matrix<double> & selection, int vec, double * tmpVector);
    void generate_selection(math::matrix<double> & selection);

    //setters
    void set_a(math::matrix<double> _a);
    void set_b(math::matrix<double> _b);

    inline void set_a_priori_probability(double _a_priori_probability)
    {
        a_priori_probability = _a_priori_probability;
    }

    //getters
    inline matrix<double> get_a() const
    {
        return a;
    }

    inline double get_a_priori_probability() const
    {
        return a_priori_probability;
    }

    inline matrix<double> get_b() const
    {
        return b;
    }

    inline int get_m() const
    {
        return m;
    }

private:
    //vector of average values
    matrix<double> a;

    //matrix of correlations
    matrix<double> b;

    //dimention of X
    int m;

    //generated data
    // this is the ||A|| matrix
    matrix<double> __a__;

    double a_priori_probability;
};

#endif // DISTRIBUTIONPARAMETERS_H

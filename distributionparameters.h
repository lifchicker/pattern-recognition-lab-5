#ifndef DISTRIBUTIONPARAMETERS_H
#define DISTRIBUTIONPARAMETERS_H

namespace math
{
    template <class T>
            class matrix;
}

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
    void set_a(double * _a);
    void set_b(double ** _b);

    inline void set_a_priori_probability(double _a_priori_probability)
    {
        a_priori_probability = _a_priori_probability;
    }

    //getters
    inline const double * get_a() const
    {
        return a;
    }

    inline double get_a_priori_probability() const
    {
        return a_priori_probability;
    }

    inline double ** get_b()
    {
        return b;
    }

    inline int get_m()
    {
        return m;
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

    double a_priori_probability;
};

#endif // DISTRIBUTIONPARAMETERS_H

#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

class Distribution
{
public:
    Distribution();
    ~Distribution();

public:
    bool generate__a__(int _m);
    void generate_normal_vector(double * vec);
    void generate_vector(double * vec);
    void generate_selection(int _selectionSize);

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

    inline double ** get_b() const
    {
        return b;
    }

    inline int get_selectionSize()
    {
        return selectionSize;
    }

    inline double ** get_x() const
    {
        return x;
    }

    //deleters
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

    //a priori probability
    double a_priori_probability;

    //dimention of X
    int m;

    //selection size
    int selectionSize;

    //generated data
    // this is the ||A|| matrix
    double ** __a__;

    //selection
    double ** x;

};

#endif // DISTRIBUTION_H

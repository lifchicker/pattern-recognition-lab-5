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

    //getters
    inline const double * get_a() const
    {
        return a;
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


private:
    double * a;         //vector of average values
    double ** b;        //matrix of correlations
    int m;              //dimention of X
    int selectionSize;  //selection size

    //generated data
    double ** __a__;    // this is the ||A|| matrix
    double ** x;        //selection

};

#endif // DISTRIBUTION_H

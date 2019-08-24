
#ifndef vec_pow_h
#define vec_pow_h

#include <chrono>
#include <iostream>
#include <cmath>
#include "experimento.hpp"



class vec_pow: public experimento {
    public:
        vec_pow(int);
        void experiment_code();
        int n;
        double* vector;
};

#endif
#include "experimento.hpp"
#include <iostream>
#include <chrono>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "vec_pow.hpp"
#include "vec_log.hpp"

using namespace std;
using namespace chrono;
double* gera_vetor(int n){
    srand (time(NULL));
    double *vector;
    vector =  new double[n];
    

    for(int i=0;i<n;i++){
        vector[i] = rand() % 99999;
    }

    return vector;
}

void vec_sqrt(double *vec,int n){
    for(int i=0;i<n;i++){
        sqrt(vec[i]);
    }    
}

void vec_pow2_mult(double *vec,int n){
    for(int i=0;i<n;i++){
        vec[i]*vec[i]*vec[i];
    }    
}

int vec_soma(double *vec,int n){
    double soma;
    for(int i=0;i<n;i++){
        soma += vec[i];
    }
    return soma;
}

int main(){
    int n = 1;
    int pos = 0;
    double *time_log = new double[1000];
    while (n <= 10000000){



        vec_pow c_pow(n);
        time_log[pos] = c_pow.duration();
        //pos++;

        vec_log c(n);
        high_resolution_clock::time_point log_time = high_resolution_clock::now();

        //vec_sqrt(vector, n);
        high_resolution_clock::time_point sqrt_time = high_resolution_clock::now();

        //vec_pow2_mult(vector, n);
        high_resolution_clock::time_point pow_mult_time = high_resolution_clock::now();

        //vec_soma(vector, n);
        high_resolution_clock::time_point soma_time = high_resolution_clock::now();

        //delete vector;

        high_resolution_clock::time_point end = high_resolution_clock::now();
        cout << "size:" << n << std::endl;
        cout << "complete time:"<<time_log[pos] << " seconds." << std::endl;
        /*
        cout << "pow time:"<<final_pow_time.count() << " seconds." << std::endl;
        cout << "log time:"<<final_log_time.count() << " seconds." << std::endl;
        cout << "sqrt time:"<<final_sqrt_time.count() << " seconds." << std::endl;
        cout << "mult time:"<<final_mult_time.count() << " seconds." << std::endl;
        cout << "soma time:"<<final_soma_time.count() << " seconds." << std::endl;
        */
        cout << "\n";

        n *= 10;

    }

delete time_log;

return 0;
}
#include "vec_pow.hpp"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

vec_pow::vec_pow(int n) : experimento(n){
    std::cout <<"vec errado: "<<experimento::vector[0]<<"\n";

    run();
}

void vec_pow::experiment_code(){

    for(int i=0;i<n;i++){
        pow(vector[i],3);
    }
}
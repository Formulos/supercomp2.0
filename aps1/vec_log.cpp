#include "vec_log.hpp"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

vec_log::vec_log(int n) : experimento(n){
    
}

void vec_log::experiment_code(){

    for(int i=0;i<n;i++){
        log10(vector[i]);
    }
}
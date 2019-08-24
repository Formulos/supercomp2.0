#include "experimento.hpp"
#include <iostream>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
using namespace chrono;
// A função abaixo é chamada ao criar um objeto ExemploRect
experimento::experimento(int n){
    std::cout << "Experimento criado\n";

    double *vector =  new double[n];
    srand((unsigned)time(0));     
    

    for(int i=0;i<n;i++){
        vector[i] = rand();
        std::cout <<"vec esta errado: "<<experimento::vector[n]<<"\n";
    }
    

    
}

double experimento::duration() {
    chrono::duration<double> diff = end-start;
    return diff.count();
}

void experimento::experiment_code(){
    std::cout << "chamando o experiment_code pai, provalmente algo esta errado"<<"\n";
}

void experimento::run(){
    auto start = high_resolution_clock::now();
    experiment_code();
    std::cout <<vector[0]<<"\n";
    delete vector;
    std::cout << "algo esta erra22222do"<<"\n";

    auto end = high_resolution_clock::now();
}
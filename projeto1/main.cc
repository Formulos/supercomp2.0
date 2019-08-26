#include "square.hpp"
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

int n = 1;
int step = 10;
int max_time = 10000;
int x_boundrie = 30;
int y_boundrie = 30;
bool cycle_colision = false;

square objects[1];
objects[0].new_square();

//dependendo do passo essa simulação vai quebrar muito, os blocos vão ser movidos para fora da tela
//tambem com velocidades muito altas

int main(){

    //simulation loop
    for (int i = 0; i < max_time; i+=step){
        cout << "c_time: "<< i <<std::endl;

        //calculates the next position of the squares
        for (int j = 0; i < n; i++){
            
        }
        
    }

return 0;
}
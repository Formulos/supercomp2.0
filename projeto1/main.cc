#include "square.hpp"
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;


//dependendo do passo essa simulação vai quebrar muito, os blocos vão ser movidos para fora da tela
//tambem com velocidades muito altas

int main(){
    int n = 1;
    int step = 1;
    int max_time = 10;
    int x_boundrie = 30;
    int y_boundrie = 30;
    double friction = 1;
    bool cycle_colision = false;
    double tmp_posx;
    double tmp_posy;

    //igor objects = new square[n]; ja inicia n square

   //cria a lista de retangulos e popula ela com retangulos.
    square *objects;
    objects = new square[n];

    square *new_objects; //copy of the list that will be changed first
    new_objects = new square[n];

    for (int i = 0; i < n; i++){
        //objects[i] = square();
        new_objects[i] = objects[i];
    }

    //simulation loop
    for (int i = 0; i < max_time; i+=step){
        cout << "c_time: "<< i <<std::endl;

        //calculates the next position of the square
        for (int j = 0; j < n; j++){
            tmp_posx = objects[j].posx;
            tmp_posy = objects[j].posy;
            
            cout << tmp_posx<<endl;
            tmp_posx += objects[j].speedx * step;
            tmp_posy += objects[j].speedy * step;
            cout <<tmp_posx<<endl;

            new_objects[j].update_pos(tmp_posx, tmp_posy);
            //add friction calculation here
            //new_objects[j].update_speed(new_objects[i].speedx, new_objects[i].speedy);
        }
        
        //intercepition
        //for each square
        for (int k = 0; k < n; k++){
            /*
            //look if one square colides with any other square (also the border)
            for (int k = 0; k < n; k++){
            }
            */
            // look if the square colides with the border
            if (!new_objects[k].ci){
                if  (!(((new_objects[k].posx + new_objects[k].width) <= x_boundrie) &&
                (new_objects[k].posx >= 0))){
                    new_objects[k].speedx = new_objects[k].speedx * -1;
                    new_objects[k].ci = true;
                }
                if  (!(((new_objects[k].posy + new_objects[k].height) <= y_boundrie) &&
                (new_objects[k].posy >= 0))){
                    new_objects[k].speedy = new_objects[k].speedy * -1;
                    new_objects[k].ci = true;
                }
            }
            

        }

        //update pos for the squeres that dont hit anything
        for (int m = 0; m < n; m++){
            if (!(new_objects[m].ci)){
                swap(objects[m] , new_objects[m]);
            }
            else{
                swap(objects[m].speedx , new_objects[m].speedx);
                swap(objects[m].speedy , new_objects[m].speedy);
            }
            // temp code
            
            /* lembra de dar update na velocidade de TODOS objetos, a unica diferança é que os coliden não mudam de posição */
            cout <<"pos(x,y)" << new_objects[m].posx <<" "<<new_objects[m].posy << endl ;
        }
        

        //update pos for the squeres that dont hit anything
        
    }
    delete objects;
    delete new_objects;

return 0;
}
#include "square.hpp"
#include <iostream>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



using namespace std;
using namespace chrono;
// A função abaixo é chamada ao criar um objeto ExemploRect
square::square(){
    ci = false;
}
square::square(int _height,int _width,int _mass,double _speedx,double _speedy,double _posx,double _posy){
    height = _height;
    width = _width;
    mass = _mass;
    speedx = _speedx;
    speedy = _speedy;
    posx = _posx;
    posy = _posy;

    
}
void square::colide(square c_square){
    if (((c_square.posx + c_square.width) <= posx) &&
    ((c_square.posy + c_square.height) <= posy) &&
    ((posx + width) <= c_square.posx) &&
    ((posy + height) <= c_square.posy)){
     ci = false;
    }

    else{
        ci = true;
    }
    

    //update speed here
}
void square::update_pos(double new_posx,double new_posy){
    posx = new_posx;
    posy = new_posy;
}
void square::update_speed(double new_speedx,double new_speedy){
    speedx = new_speedx;
    speedy = new_speedy;
}
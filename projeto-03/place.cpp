#include "place.hpp"
#include <iostream>


place::place(){
    posx = -1;
    posy = -1;
}
void place::add_point(double x,double y){
    posx = x;
    posy = y;
}
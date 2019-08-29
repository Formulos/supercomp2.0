#include "square.hpp"
#include <iostream>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
using namespace chrono;
// A função abaixo é chamada ao criar um objeto ExemploRect
square::square(){
    cout<<"\n\twidth : ";
    //cin>>width;
    width = 5;

    cout<<"\n\tsize : ";
    //cin>>size;
    height = 5;

    cout<<"\n\tmass : ";
    //cin>>mass;
    mass = 5;

    cout<<"\n\tspeedx : ";
    //cin>>speedx;
    speedx = 5;

    cout<<"\n\tspeedy : ";
    //cin>>speedy;
    speedy = 0;

    cout<<"\n\tposx : ";
    //cin>>posx;
    posx = 30;

    cout<<"\n\tposy : ";
    //cin>>posy;
    posy = 5;

    std::cout << "square criado\n";

    ci = false;

/*
    int height = height;
    int width = width;
    int mass = mass;
    double speedx = speedx;
    double speedy = speedy;
    double posx = posx;
    double posy = posy;
*/
    
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
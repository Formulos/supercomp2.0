#include "square.hpp"
#include <iostream>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
using namespace chrono;
// A função abaixo é chamada ao criar um objeto ExemploRect
square::square(){
    std::cout << "square criado\n";

/*
    int size = size;
    int width = width;
    int mass = mass;
    double speedx = speedx;
    double speedy = speedy;
    int posx = posx;
    int posy = posy;
*/
    
}
void square::new_square(){
    cout<<"\n\tsize : ";
    cin>>size;

    cout<<"\n\twidth : ";
    cin>>width;

    cout<<"\n\tmass : ";
    cin>>mass;

    cout<<"\n\tspeedx : ";
    cin>>speedx;

    cout<<"\n\tspeedy : ";
    cin>>speedy;

    cout<<"\n\tposx : ";
    cin>>posx;

    cout<<"\n\tposy : ";
    cin>>posy;
}
void square::update_pos(int posx,int posy){
    std::cout << "AAAAAAAAAAAAAAA\n";
}
void square::update_speed(double speedx,double speedy){
    std::cout << "BBBBBBBBBBBBBBBBBBBB\n";
}
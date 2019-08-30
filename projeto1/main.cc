#include "square.hpp"
#include <iostream>
#include <chrono>
#include <math.h>

#define AAA cout << "AAAAAAAAAAAAAAAAAAAAAAAA"<<std::endl;

using namespace std;
using namespace chrono;


int main(){
    int n = 1;
    int slow_square = 0;
    int step = 1;
    int max_time = 8;
    int x_boundrie = 40;
    int y_boundrie = 40;
    double friction = 0.1;
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
        cout<<"\n\twidth : ";
        int width;
        cin>>width;
        //int width = 5;

        cout<<"\n\tsize : ";
        //cin>>size;
        int height = 5;

        cout<<"\n\tmass : ";
        //cin>>mass;
        int mass = 5;

        cout<<"\n\tspeedx : ";
        //cin>>speedx;
        double speedx = 5;

        cout<<"\n\tspeedy : ";
        //cin>>speedy;
        double speedy = 0;

        cout<<"\n\tposx : ";
        //cin>>posx;
        double posx = 5;

        cout<<"\n\tposy : ";
        //cin>>posy;
        double posy = 5;

        objects[i] = square(width,height,mass,speedx,speedy,posx,posy);
        new_objects[i] = objects[i];
    }

    //simulation loop
    for (int i = 0; i < max_time; i+=step){
        cout << "c_time: "<< i <<std::endl;

        //calculates the next position of the square
        for (int j = 0; j < n; j++){

            objects[j].ci = false;
            new_objects[j].ci = false;
            tmp_posx = objects[j].posx;
            tmp_posy = objects[j].posy;
            
            //cout << tmp_posx<<endl;
            tmp_posx += objects[j].speedx * step;
            tmp_posy += objects[j].speedy * step;
            //cout <<tmp_posx<<endl;

            new_objects[j].update_pos(tmp_posx, tmp_posy);
            //add friction calculation here
            /*
            1.calculo do v
            2. angulo =arcos(vx/v)
            3. v = v0 -a*deltaT *9.8(gravidade)
            4.vx = v *cos(teta)
            5. vy = v *sen(teta)  
            */
            if (objects[j].speedx != 0 || objects[j].speedy != 0){
                double t_speed = sqrt((pow(objects[j].speedx,2)+pow(objects[j].speedy,2)));
                double angulo = acos(objects[j].speedx/t_speed);
                t_speed = t_speed - friction * step *9.8;
                if(t_speed<0){
                    t_speed = 0;
                    slow_square++;

                }
                new_objects[j].update_speed(t_speed * cos(angulo), t_speed*sin(angulo));
            }
            else{
                new_objects[j].update_speed(new_objects[j].speedx, new_objects[j].speedy);
            }
        }
        if (slow_square == n){
            cout <<"All squares have stoped" << endl ;
            break;
        }
        
        //intercepition
        //for each square
        for (int k = 0; k < n; k++){
            
            //look if one square colides with any other square...
            for (int l = 0; l < (n-1); l++){
                new_objects[k].colide(new_objects[l]);
            }
            
            // ... and the border
            if (!new_objects[k].ci){
                if  (!(((new_objects[k].posx + new_objects[k].width) < x_boundrie) &&
                (new_objects[k].posx > 0))){
                    new_objects[k].speedx = new_objects[k].speedx * -1;
                    new_objects[k].ci = true;
                }
                if  (!(((new_objects[k].posy + new_objects[k].height) < y_boundrie) &&
                (new_objects[k].posy > 0))){
                    new_objects[k].speedy = new_objects[k].speedy * -1;
                    new_objects[k].ci = true;
                }
            }
            

        }

        //update pos for the squeres that dont hit anything
        for (int m = 0; m < n; m++){
            if (!(new_objects[m].ci)){
                swap(objects[m] , new_objects[m]);
                //objects[m] = new_objects[m];
            }
            else{
                objects[m].update_speed(new_objects[m].speedx,new_objects[m].speedy);
                //swap(objects[m].speedx , new_objects[m].speedx);
                //swap(objects[m].speedy , new_objects[m].speedy);
            }
            // temp code
            
            /* lembra de dar update na velocidade de TODOS objetos, a unica diferança é que os coliden não mudam de posição */
            cout <<"pos(x,y)" << objects[m].posx <<" "<<objects[m].posy << endl ;
            cout <<"speed(x,y)" << objects[m].speedx <<" "<<objects[m].speedy << endl ;
        }
        

        //update pos for the squeres that dont hit anything
        
    }
    delete objects;
    delete new_objects;

return 0;
}
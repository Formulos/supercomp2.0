#include "square.hpp"
#include <iostream>
#include <chrono>
#include <math.h>

#define AAA cout << "AAAAAAAAAAAAAAAAAAAAAAAA"<<std::endl;

using namespace std;
using namespace chrono;


int main(){
    
    int slow_square = 0;

    double tmp_posx;
    double tmp_posy;
    int x_boundrie;
    int y_boundrie;

    cin >> x_boundrie;
    cin >> y_boundrie;

    double friction;
    cin >> friction;



    int n;
    cin >> n;


   //cria a lista de retangulos e popula ela com retangulos.
    square *objects;
    objects = new square[n];

    square *new_objects; //copy of the list that will be changed first
    new_objects = new square[n];


    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++){
        
        int mass;
        cin>>mass;
        //int mass = 5;
        
        int width;
        cin>>width;
        //int width = 5;

        int height;
        cin>>height;
        //int height = 5;

        double posx;
        cin>>posx;
        //double posx = 5;

        double posy;
        cin>>posy;
        //double posy = 5;

        double speedx;
        cin>>speedx;
        //double speedx = 5;

        double speedy;
        cin>>speedy;
        //double speedy = 0;


        objects[i] = square(width,height,mass,speedx,speedy,posx,posy);
        new_objects[i] = objects[i];
    }
    double step;
    int max_time;
    int print_freq;
    
    cin >>step;
    cin >>print_freq;
    cin >>max_time;
    //objects[0] = square(10,10,5,5,0,35,30);
    //objects[1] = square(10,10,5,-5,0,50,30);
    //new_objects[0] = objects[0];
    //new_objects[1] = objects[1];



    //simulation loop
    for (int i = 0; i < max_time; i+=step){
            cout << max_time<< endl;

        

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
            /*
            1.calculo do v
            2. angulo =arcos(vx/v)
            3. v = v0 -a*deltaT *9.8(gravidade)
            4.vx = v *cos(teta)
            5. vy = v *sen(teta)  
            */
            if (objects[j].speedx != 0 || objects[j].speedy != 0){
                double t_speed = sqrt((pow(objects[j].speedx,2)+pow(objects[j].speedy,2)));
                double angulo = atan2(objects[j].speedy,objects[j].speedx);
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
            //cout <<"All squares have stoped" << endl ;
            break;
        }
        slow_square = 0;
        
        //intercepition
        //for each square
        for (int k = 0; k < n; k++){

            //look if one square colides with any other square...
            for (int l = 0; l < n; l++){
                if ((!(new_objects[l].ci))&&(l != k)){
                    new_objects[k] = new_objects[l].colide(new_objects[k]);
                }
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
            
            if(i%print_freq == 0){
                cout << i <<std::endl;
                cout << objects[m].posx <<" "<<objects[m].posy <<" " << objects[m].speedx <<" " <<objects[m].speedy << endl;
            }
        }
        

        
    }
    delete objects;
    delete new_objects;
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cerr << elapsed.count();

return 0;
}
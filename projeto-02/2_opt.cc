#include "place.hpp"
#include <omp.h>
#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;
using namespace chrono;

double dist(place p1,place p2){
    return sqrt(pow(p1.posx - p2.posx,2) + pow(p1.posy - p2.posy,2) );
    }

double path_dist(int *seq, place *points,int n){
    double d = dist(points[seq[n-1]], points[seq[0]]);
    for (int i=0 ;i < (n-1); i++){
        d += dist(points[seq[i]], points[seq[i+1]]);
        }
    return d;
    }

void swap_2opt(int *aux,int i, int j){
    std::swap(aux[i], aux[j]);
}

void solver(place *points,int n,int *solution){
    bool improved = true;

    int *aux;
    aux = new int[n];

    for (int k = 0; k < n; k++){
        aux[k] = solution[k];
    }

    while (improved){
        
        double current_best = path_dist(solution,points,n);
        improved = false;
        for (int i = 0; i < n; i++){
            for (int j = i+1; j < n; j++){
            swap_2opt(aux,i,j);
            double possibel_best = path_dist(aux,points,n);
            if (possibel_best < current_best){
                improved = true;
                current_best = possibel_best;
                for (int k = 0; k < n; k++){
                    solution[k] = aux[k];
                    
                }
            }

            }
            
        }
        
    }
    delete aux;
    
}

int main(){
    int n;
    cin >> n;

    place *points;
    points = new place[n];

    int *solution;
    solution = new int[n];

    for (int i=0 ;i < n; i++){
        float x;
        float y;

        cin >> x;
        cin >> y;

        points[i].add_point(x,y);

        solution[i] = i; //solução inicial = a ordem de entrada
    }


    #pragma omp parallel
    {
        #pragma omp single
        {
        auto start = high_resolution_clock::now();
        solver(points,n,solution);
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        cerr << elapsed.count() << endl;
        }
    }

    cout << path_dist(solution, points,n) << " 1" << endl;

    for(int i=0 ;i < n; i++){
        cout << solution[i] << " ";
    }
    cout << endl;

    delete points;
    delete solution;
    return 0;
}
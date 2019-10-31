#include "place.hpp"
#include <omp.h>
#include <iostream>
#include <chrono>
#include <math.h>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <random>

using namespace std;
using namespace chrono;

double dist(place p1,place p2){
    return sqrt(pow(p1.posx - p2.posx,2) + pow(p1.posy - p2.posy,2) );
    }

double path_dist(vector<int> seq, place *points,int n){
    double d = dist(points[seq[n-1]], points[seq[0]]);
    for (int i=0 ;i < (n-1); i++){
        d += dist(points[seq[i]], points[seq[i+1]]);
        }
    return d;
    }

vector<int> swap_2opt(vector<int> aux,int i, int j){
    int tmp;
    tmp = aux[i];
    aux[i] = aux[j];
    aux[j] = tmp;
    return aux;
}

vector<int> solver(place *points,int n){
    unsigned seed = system_clock::now().time_since_epoch().count();
    auto rng = default_random_engine {seed};
    int max = 1000;
    vector<vector<int>> solution_list(max,vector<int>(n));
    vector<int> aux;
    vector<int> solution;

    for (int i=0 ;i < n; i++){
        solution.push_back(i);
    }
    
    #pragma omp parallel for shared(solution_list) firstprivate(aux,solution)
    for (int i = 0; i < max; i++)
    {
        std::shuffle(solution.begin()+1, solution.end(), rng);
    
        bool improved = true;
        aux = solution;
        while (improved){
            double current_best = path_dist(solution,points,n);
            improved = false;
            for (int i = 1; i < n; i++){
                for (int j = i+1; j < n; j++){
                aux = swap_2opt(aux,i,j);
                double possibel_best = path_dist(aux,points,n);
                if (possibel_best < current_best){
                    improved = true;
                    current_best = possibel_best;
                    solution = aux;

                }

                }
                
            }
        
        
        }
        solution_list[i] = solution;
    }
    for (int i = 0; i < max; i++){
        path_dist(solution, points,n) > path_dist(solution_list[i], points,n);
        solution =solution_list[i];
    }
    return solution;
}

int main(){
    int n;
    cin >> n;

    place *points;
    points = new place[n];


    for (int i=0 ;i < n; i++){
        float x;
        float y;

        cin >> x;
        cin >> y;

        points[i].add_point(x,y);

        
    }

     vector<int> solution;


    auto start = high_resolution_clock::now();
    solution = solver(points,n);
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cerr << elapsed.count() << endl;


    cout << path_dist(solution, points,n) << " 0" << endl;

    for(int i=0 ;i < n; i++){
        cout << solution[i] << " ";
    }
    cout << endl;

    delete points;
    return 0;
}
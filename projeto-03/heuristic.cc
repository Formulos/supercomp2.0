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
    int max = 1;
    vector<vector<int>> solution_list(max,vector<int>(n));
    vector<int> aux; // cotem todos nodes não usados
    vector<int> point_list;
    vector<int> solution; // comtem a solução, sempre começa em zero
    vector<double> dist_list;

    solution.push_back(0);
    for (int i=1 ;i < n; i++){
        aux.push_back(i);
        solution.push_back(-1);
        dist_list.push_back(-1);
    }
    

    for (int i = 0; i < n-1; i++){
        int best_node = -1;
        double best_dist = numeric_limits<double>::max();
        int pos = -1;

        #pragma omp parallel for
        for (int j = 0; j < aux.size(); j++){
            dist_list[j] = dist(points[solution[i]], points[aux[j]]);
        }
        for(int j =0; j < aux.size();j++){
            if (dist_list[j] < best_dist){
                best_dist = dist_list[j];
                best_node = aux[j];
                pos = j;
            }
        }
        aux.erase(aux.begin()+pos); // o melhor node ja foi usado

        solution[i+1] = best_node;
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
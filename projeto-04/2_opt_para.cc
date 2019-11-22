#include "place.hpp"
#include <iostream>
#include <chrono>
#include <math.h>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <random>
#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;
using namespace chrono;
namespace mpi = boost::mpi;

double dist(place p1,place p2){
    return sqrt(pow(p1.posx - p2.posx,2) + pow(p1.posy - p2.posy,2) );
    }

double path_dist(vector<int> seq, vector<place> points,int n){
    double d = dist(points[seq[n-1]], points[seq[0]]);
    for (int i=0 ;i < (n-1); i++){
        d += dist(points[seq[i]], points[seq[i+1]]);
        }
    return d;
    }

void swap_2opt(vector<int> &aux,int i, int j){
    int tmp;
    tmp = aux[i];
    aux[i] = aux[j];
    aux[j] = tmp;
}

void solver(vector<place> &points,int n,vector<int> &best){
    //unsigned seed = system_clock::now().time_since_epoch().count();
    mpi::communicator world;
    unsigned long rank = (unsigned long)world.rank();
    auto rng = default_random_engine {rank + 42};
    int max = 1000;
    vector<vector<int>> solution_list(max,vector<int>(n));
    vector<int> aux;
    vector<int> solution;

    for (int i=0 ;i < n; i++){
        solution.push_back(i);
    }
    
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
                swap_2opt(aux,i,j);
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
    best = solution;
}

int main(int argc, char *argv[]){
    mpi::environment env(argc, argv);
    mpi::communicator world;
    int n;
    vector<place> points;
    
    if (world.rank() == 0){
        cin >> n;
        points.resize(n);
        for (int i=0 ;i < n; i++){
            float x;
            float y;

            cin >> x;
            cin >> y;

            points[i].add_point(x,y);
        }
        
    }
    mpi::broadcast(world, n, 0);

    if (world.rank() != 0){
        points.resize(n);
    }

    mpi::broadcast(world, points, 0);

    vector<int> solution;


    //auto start = high_resolution_clock::now();
    solver(points,n,solution);
    //auto end = high_resolution_clock::now();
    //duration<double> elapsed = end - start;
    //cerr << elapsed.count() << endl;

    

    if(world.rank() == 0){
        vector<vector<int>> all_seq(world.size());
        mpi::gather(world,solution, all_seq, 0);
        for (int i = 0; i < world.size(); i++){
            if (path_dist(solution, points,n)> path_dist(all_seq[i], points,n)){
                solution = all_seq[i];
            }
            for(int j=0 ;j < n; j++){
                cerr << all_seq[i][j] << " ";
            }
        }

        cout << path_dist(solution, points,n) << " 0" << endl;

        for(int i=0 ;i < n; i++){
            cout << solution[i] << " ";
        }
        cout << endl;
        

    }
    else{
       mpi::gather(world, solution, 0);
    }

    return 0;
}
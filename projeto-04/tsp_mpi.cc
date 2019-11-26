#include "place.hpp"
#include <iostream>
#include <limits> 
#include <vector>
#include <math.h>
#include <chrono>
#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>


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

int backtrack_seq(vector<place> points,int n,int idx,double curr_cost,vector<int> curr_sol, 
              double best_cost,vector<int> &best_seq,vector<bool> usado){
    if (idx == n){
        curr_cost += dist(points[curr_sol[0]], points[curr_sol[n-1]]);
        if (curr_cost < best_cost){
            for (int i=0;i<n;i++){
                best_seq[i] = curr_sol[i];
            }
            best_cost = curr_cost;
            //cerr << "best: " << best_cost << endl;
        }
        return best_cost;
    }
    mpi::communicator world;
    
    for (int i=0 ;i < n; i++){
        if (!usado[i]){
            usado[i] = true;
            curr_sol[idx] = i;

            double new_cost = curr_cost + dist(points[curr_sol[idx-1]], points[curr_sol[idx]]);
            best_cost = backtrack_seq(points,n , idx+1, new_cost, curr_sol, best_cost, best_seq,usado);

            usado[i] = false;
            curr_sol[idx] = -1;
        }
    }
    return best_cost;

    }


int main(int argc, char *argv[]){
    mpi::environment env(argc, argv);
    mpi::communicator world;
    int n;

    //place *points;
    //points = new place[n];

    vector<place> points;
    vector<bool> usado;
    vector<int> curr_sol;
    vector<int> solution;
    vector<int> best_solution;
    

    //int *best_sol;
    //best_sol = new int[n];

    if (world.rank() == 0){
        cin >> n;
        points.resize(n);
        for (int i=0 ;i < n; i++){
            float x;
            float y;

            cin >> x;
            cin >> y;

            points[i].add_point(x,y);

            usado.push_back(false);
            curr_sol.push_back(-1);
            solution.push_back(-1);
            best_solution.push_back(-1);
        }
    }

    mpi::broadcast(world, n, 0);

    if (world.rank() != 0){
        points.resize(n);
        for (int i=0 ;i < n; i++){
            usado.push_back(false);
            curr_sol.push_back(-1);
            solution.push_back(-1);
            best_solution.push_back(-1);

        }
    }

    mpi::broadcast(world, points, 0);

    curr_sol[0] = 0;
    usado[0] = true;

    double best_cost = numeric_limits<int>::max();
    
    int size = world.size();
    if (size >= n){
        size = n-1;
    }

    auto start = high_resolution_clock::now();
    for (int i = world.rank()+1; i < n; i = i + size){
        usado[i] = true;
        curr_sol[1] = i;
        //cout << i << " ";
        double cost = dist(points[curr_sol[0]], points[curr_sol[1]]);
        cost = backtrack_seq(points,n, 2, cost, curr_sol, numeric_limits<int>::max(), solution,usado);
        //cout << cost << ",  " << best_cost << "\n";
        if(best_cost > cost){
            best_solution = solution;
            best_cost = cost;
        }
        usado[i] = false;
    }
    
    

    
    if(world.rank() == 0){
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        cerr << elapsed.count() << endl;


        vector<vector<int>> all_seq(size);
        mpi::gather(world,solution, all_seq, 0);
        for (int i = 0; i < size; i++){
            if (path_dist(solution, points,n)> path_dist(all_seq[i], points,n)){
                solution = all_seq[i];
            }
            //for(int j=0 ;j < n; j++){
            //    cerr << all_seq[i][j] << " ";
            //}
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
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

int backtrack_seq(place *points,int n,int idx,double curr_cost,int *curr_sol, 
              double best_cost,int *best_seq,bool *usado){
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

int backtrack_task(place *points,int n,int idx,double curr_cost,int *curr_sol, 
              double best_cost,int *best_seq,bool *usado){

    bool *usado_para;
    usado_para = new bool[n];

    int *curr_sol_para;
    curr_sol_para = new int[n];

    for (int i=0 ;i < n; i++){
        usado_para[i] = usado[i];
        curr_sol_para[i] = curr_sol[i];
    }

    if (idx == n){
        curr_cost += dist(points[curr_sol_para[0]], points[curr_sol_para[n-1]]);
        if (curr_cost < best_cost){
            for (int i=0;i<n;i++){
                best_seq[i] = curr_sol_para[i];
            }
            best_cost = curr_cost;
            //cerr << "best: " << best_cost << endl;
        }
        return best_cost;
    }

    for (int i=0 ;i < n; i++){
        if (!usado_para[i]){
            usado_para[i] = true;
            curr_sol_para[idx] = i;

            double new_cost = curr_cost + dist(points[curr_sol_para[idx-1]], points[curr_sol_para[idx]]);
            best_cost = backtrack_seq(points,n , idx+1, new_cost, curr_sol_para, best_cost, best_seq,usado_para);

            usado_para[i] = false;
            curr_sol_para[idx] = -1;
        }
    }

    delete usado_para;
    delete curr_sol_para;

    return best_cost;

    }

int backtrack_zero(place *points,int n,int idx,double curr_cost,int *curr_sol, 
              double best_cost,int *best_seq,bool *usado){
    

    int task_max_number = n-1;

    double all_cost[n];

    int *all_seq[n]; 
    
    //all_seq[0] = best_seq;

    for (int i=0;i<n;i++){
        all_seq[i] = new int[n];
        for(int j = 0;j<n;j++){
            all_seq[i][j]= best_seq[j];
        }
    }

    if (idx == n){
        curr_cost += dist(points[curr_sol[0]], points[curr_sol[n-1]]);
        if (curr_cost < best_cost){
            for (int i=0;i<n;i++){
                best_seq[i] = curr_sol[i];
            }
            best_cost = curr_cost;
            cerr << "best: " << best_cost << endl;
        }
        return best_cost;
    }

    for (int i=0 ;i < n; i++){
        if (!usado[i]){
            usado[i] = true;
            curr_sol[idx] = i;

            double new_cost = curr_cost + dist(points[curr_sol[idx-1]], points[curr_sol[idx]]);
            #pragma task
            {
            all_cost[i] = backtrack_task(points,n , idx+1, new_cost, curr_sol, best_cost, all_seq[i],usado);
            }
            

            usado[i] = false;
            curr_sol[idx] = -1;
        }
    }
    #pragma taskwait

    int index_max;
    for (int i=1 ;i < n; i++){
        if (best_cost > all_cost[i]){
            best_cost = all_cost[i];
            index_max = i;
        }

    }

    //jeito horrivel de fazer isso
    for(int i=0 ;i < n; i++){
        best_seq[i] = all_seq[index_max][i];
    }
    
    for (int i=0 ;i < n; i++){
        delete all_seq[i];   
    }
    return best_cost;

    }


int main(){
    int n;
    cin >> n;

    place *points;
    points = new place[n];

    bool *usado;
    usado = new bool[n];

    int *curr_sol;
    curr_sol = new int[n];

    int *best_sol;
    best_sol = new int[n];

    for (int i=0 ;i < n; i++){
        float x;
        float y;

        cin >> x;
        cin >> y;

        points[i].add_point(x,y);

        usado[i] = false;
        curr_sol[i] = -1;
        best_sol[i] = -1;
    }

    curr_sol[0] = 0;
    usado[0] = true;


    #pragma omp parallel
    {
        #pragma omp single
        {
        backtrack_zero(points,n, 1, 0, curr_sol, numeric_limits<int>::max(), best_sol,usado);
        }
    }

    cout << path_dist(best_sol, points,n) << " 1" << endl;

    for(int i=0 ;i < n; i++){
        cout << best_sol[i] << " ";
    }
    cout << endl;

    delete points;
    delete usado;
    delete best_sol;
    delete curr_sol;
    return 0;
}
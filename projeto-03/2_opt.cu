#include <omp.h>
#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <random>

#include "curand.h"
#include "curand_kernel.h"
#include "math.h"

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

using namespace std;

__host__ __device__ double dist(float p1x,float p1y,float p2x,float p2y){
    return sqrt(pow(p1x - p2x,2) + pow(p1y - p2y,2));
    }

/*double path_dist(vector<int> seq, place *points,int n){
    double d = dist(points[seq[n-1]], points[seq[0]]);
    for (int i=0 ;i < (n-1); i++){
        d += dist(points[seq[i]], points[seq[i+1]]);
        }
    return d;
    }*/

__device__ void swap_2opt(vector<int> aux,int i, int j){

}

__global__ void pre_calc(float *x,float *y,double *dist_matrix,int n){
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    int i = blockIdx.y * blockDim.y + threadIdx.y;

    //printf("%f \n", dist(x[i],y[i],x[j],y[j]));
    

    if ((i < n) && (j < n)){
        dist_matrix[i*n +j] = dist(x[i],y[i],x[j],y[j]);
    }
}

__global__ void solver(double *dist_matrix,int *all_seq,double *dis_calc,int n){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int begin = (i*n)+1;
    int end = begin +n -2; //-1 begin esta começando no 1 e mais -1 para acabar no final da lista não no começo do proximo

    curandState st;
    curand_init(0, i, 0, &st);

    for(int j=begin;j< end;j++){

        int place = (int) ((end-j) * curand_uniform(&st) + j);

        int tmp;
        tmp = all_seq[begin];
        all_seq[begin] = all_seq[place];
        all_seq[place] = tmp;
    }

    double my_dist = 0;

    for(int j=begin;j< end;j++){
        my_dist += dist_matrix[(all_seq[j]*n+all_seq[j+1])];
    }

    dis_calc[i] = my_dist;


    
}

int main(){
    const int maximum = 1;
    int n;
    cin >> n;

    thrust::host_vector<float> host_pointx(n);
    thrust::host_vector<float> host_pointy(n);

    thrust::device_vector<float> pointx(n);
    thrust::device_vector<float> pointy(n);
    

    for (int i=0 ;i < n; i++){
        float x;
        float y;

        cin >> x;
        cin >> y;

        

        host_pointx[i] = x;
        host_pointy[i] = y;
        
    }

    pointx = host_pointx;
    pointy = host_pointy;



    thrust::device_vector<double> dist_matrix(n*n);

    dim3 blocks(ceil(1024.0/n), ceil(1024.0/n), 1);
    dim3 th(32, 32, 1);

    

    pre_calc<<<blocks,th>>>(
        thrust::raw_pointer_cast(pointx.data()),
        thrust::raw_pointer_cast(pointy.data()),
        thrust::raw_pointer_cast(dist_matrix.data()), 
        n
        );
    
    //int all_seq_size = n*maximum*1024;
    int all_seq_size = n*3;
    
    thrust::host_vector<int> all_seq_host(all_seq_size);
    thrust::device_vector<int> all_seq(all_seq_size);
    thrust::device_vector<double> dis_calc(maximum* 3);





    for(int i=0;i<all_seq_size;i+=n){
        for (int j=0;j<n;j++){
            all_seq_host[i+j] = j;            
        }
    }
    
    //cout << "AAAAAAAAA" << endl;
    all_seq = all_seq_host;

    
    solver<<<1,3>>>(
        thrust::raw_pointer_cast(dist_matrix.data()),
        thrust::raw_pointer_cast(all_seq.data()),
        thrust::raw_pointer_cast(dis_calc.data()),
        n
        );

    thrust::host_vector<double> host_dis_calc(maximum* 3);
    thrust::device_vector<double> best_seq(n);
    thrust::host_vector<double> host_best_seq(n);

    host_dis_calc = dis_calc;
    int index_mult = 0;

    double best = host_dis_calc[0];
    for (int i =1;i<= 3;i++){
        if(host_dis_calc[0] < best){
            best = host_dis_calc[0];
            index_mult = i;
        }
    }

    thrust::copy_n(all_seq.begin()+(1*index_mult),n,best_seq.begin());

    
    for (auto i = all_seq.begin(); i != all_seq.end(); i++) {
        cout << *i << " "; // este acesso é lento! -- GPU
    }
    cout << endl;
    for (auto i = dis_calc.begin(); i != dis_calc.end(); i++) {
        cout << *i << " "; // este acesso é lento! -- GPU
    }
    cout << endl;
    for (auto i = best_seq.begin(); i != best_seq.end(); i++) {
        cout << *i << " "; // este acesso é lento! -- GPU
    }

    /*
    solver(points,n);
    cout << path_dist(solution, points,n) << " 0" << endl;

    for(int i=0 ;i < n; i++){
        cout << solution[i] << " ";
    }
    cout << endl;
    */

    return 0;
}
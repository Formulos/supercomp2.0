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

__global__ void pre_calc(float *x,float *y,double *dist_matrix,int n){
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    int i = blockIdx.y * blockDim.y + threadIdx.y;

    //printf("%f \n", dist(x[i],y[i],x[j],y[j]));
    

    if ((i < n) && (j < n)){
        dist_matrix[i*n +j] = dist(x[i],y[i],x[j],y[j]);
    }
}

__global__ void solver(double *dist_matrix,int *all_seq,double *dis_calc,int n,int total_iter){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < total_iter){
        int begin = (i*n);
        int end = begin +n -1; //-1 para acabar no final da lista não no começo do proximo (end inclusivo)

        curandState st;
        curand_init(0, i, 0, &st);

        for(int j=begin+1;j < end;j++){

            int place = (int) ((end-j-1) * curand_uniform(&st) + j);

            int tmp;
            tmp = all_seq[j];
            all_seq[j] = all_seq[place];
            all_seq[place] = tmp;
        }

        double my_dist = 0;

        for(int j=begin;j< end;j++){
            my_dist += dist_matrix[(all_seq[j]*n+all_seq[j+1])];
        }

        dis_calc[i] = my_dist;
    }


    
}

int main(){
    const int max_blocks = 10;
    const int max_th = 1024;
    const int total_iter = 10000;
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

    dim3 blocks(ceil(n/32.0), ceil(n/32.0), 1);
    dim3 th(32, 32, 1);

    

    pre_calc<<<blocks,th>>>(
        thrust::raw_pointer_cast(pointx.data()),
        thrust::raw_pointer_cast(pointy.data()),
        thrust::raw_pointer_cast(dist_matrix.data()), 
        n
        );
    
    int all_seq_size = n*total_iter;
    
    thrust::host_vector<int> all_seq_host(all_seq_size);
    thrust::device_vector<int> all_seq(all_seq_size);
    thrust::device_vector<double> dis_calc(total_iter);





    for(int i=0;i<all_seq_size;i+=n){
        for (int j=0;j<n;j++){
            all_seq_host[i+j] = j;            
        }
    }
    
    //cout << "AAAAAAAAA" << endl;
    all_seq = all_seq_host;

    
    solver<<<max_blocks,max_th>>>(
        thrust::raw_pointer_cast(dist_matrix.data()),
        thrust::raw_pointer_cast(all_seq.data()),
        thrust::raw_pointer_cast(dis_calc.data()),
        n,
        total_iter
        );

    

    thrust::device_vector<double>::iterator iter = thrust::min_element(dis_calc.begin(), dis_calc.end());
      
    unsigned int position = iter - dis_calc.begin();
    double best = *iter;
      
    thrust::host_vector<double> host_best_seq(all_seq.begin()+position*n,all_seq.begin()+position*n+n);

    cout << best <<endl;
    for (auto i = host_best_seq.begin(); i != host_best_seq.end(); i++) {
        cout << *i << " ";
    }
    
    
    //DEBUG
    /*
    cout << best <<endl;
    for (auto i = all_seq.begin(); i != all_seq.end(); i++) {
        cout << *i << " "; // este acesso é lento! -- GPU
    }
    cout << endl;
    for (auto i = dis_calc.begin(); i != dis_calc.end(); i++) {
        cout << *i << " "; // este acesso é lento! -- GPU
    }
    cout << endl;
    for (auto i = host_best_seq.begin(); i != host_best_seq.end(); i++) {
        cout << *i << " "; // este acesso é lento! -- GPU
    }
    /**/
    

    return 0;
}
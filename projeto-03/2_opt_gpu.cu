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



__device__ double find_dist(int begin,int end, double *dist_matrix, int *all_seq,int n){
    double my_dist = 0;
    for(int j=begin;j<= end;j++){//calc final dist
        my_dist += dist_matrix[(all_seq[j]*n+all_seq[j+1])];
    }
    return my_dist;
}

__device__ void opt_swap(int p1,int p2, int *vector){
    int tmp;
    tmp = vector[p1];
    vector[p1] = vector[p2];
    vector[p2] = tmp;
}


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
        int last = begin +n -1; //-1 para acabar no final da lista não no começo do proximo (end inclusivo)


        int tmp_counter = 0;
        for(int j=begin;j <= last;j++){
            all_seq[j] = tmp_counter;
            tmp_counter++;
        }    

        curandState st;
        curand_init(0, i, 0, &st);

        for(int j=begin+1;j < last;j++){
            int place = (int) ((last-j-1) * curand_uniform(&st) + j);
            opt_swap(j,place,all_seq);

        }
        
        bool improved = true;
        while (improved){
            double current_best = find_dist(begin,last, dist_matrix, all_seq,n);
            improved = false;
            for (int i = begin+1; i < last; i++){
                for (int j = i+1; j < last; j++){
                opt_swap(i,j,all_seq);
                double possibel_best = find_dist(begin,last, dist_matrix, all_seq,n);
                if (possibel_best < current_best){
                    improved = true;
                    current_best = possibel_best;
                }
                else{
                    opt_swap(i,j,all_seq);//swap back
                }

                }
                
            }
        
        
        }
        
        
        
        double my_dist = find_dist(begin,last, dist_matrix, all_seq,n);

        dis_calc[i] = my_dist;
    }


    
}

int main(){
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);

    const int total_iter = 10000;
    const int max_th = 1024;
    const int max_blocks = ceil((double) total_iter/max_th);
    
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
    
    thrust::device_vector<int> all_seq(all_seq_size);
    thrust::device_vector<double> dis_calc(total_iter);

    
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
    cudaEventRecord(stop);

    cout << best << " 0" <<endl;
    for (auto i = host_best_seq.begin(); i != host_best_seq.end(); i++) {
        cout << *i << " ";
    }
    cout <<endl;

    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    cerr << "time in milliseconds: " << milliseconds << endl;
    

    return 0;
}
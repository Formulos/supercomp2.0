#include <iostream>
#include <chrono>
#include <omp.h>
#include <thread>

static long num_steps = 100000000;


void divided_pi(int init,int end,double step,double *vector,int place){
    double tmp_sum=0.0;
    double x =0.0;
    for (int i = init; i < end; i++) {
        x = (i + 0.5) * step;
        tmp_sum = tmp_sum + 4.0 / (1.0 + x * x);
    }
    vector[place] = tmp_sum;
    
}
double pi_seq(long steps){
    double step;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)steps;

    for (int i = 0; i < steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    
    pi = step * sum;
    return pi;
}

double double_pi_threads_raiz(long steps){
    double step;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)steps;
    double vector_sums[4];
    int quarter = steps/4;

    std::thread t1(divided_pi, 0, quarter,step,vector_sums,0);
    std::thread t2(divided_pi, quarter, quarter*2,step,vector_sums,1);
    std::thread t3(divided_pi, quarter*2, quarter*3,step,vector_sums,2);
    std::thread t4(divided_pi, quarter*3, steps,step,vector_sums,3);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    for (int i = 0; i < 4; i++) {
        sum += vector_sums[i];
    }
    pi = step * sum;
    return pi;
}

double pi_omp_parallel(long steps){
    int max_threads = omp_get_max_threads();
    double step;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)steps;
    double vector[max_threads];
    int quarter = steps/max_threads;

    #pragma omp parallel
    {
        int current_thread = omp_get_thread_num();
        double tmp_sum=0.0;
        double x =0.0;
        int end = (current_thread+1)*quarter;
        for (int i = (current_thread*quarter); i < end; i++) {
            x = (i + 0.5) * step;
            tmp_sum = tmp_sum + 4.0 / (1.0 + x * x);
        }
        vector[current_thread] = tmp_sum;
    }


    for (int i = 0; i < max_threads; i++) {
        sum += vector[i];
    }
    pi = step * sum;
    return pi;
}

double pi_omp_parallel_atomic(long steps){
    int max_threads = omp_get_max_threads();
    double step;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)steps;
    int quarter = steps/max_threads;

    #pragma omp parallel
    {
        int current_thread = omp_get_thread_num();
        double tmp_sum=0.0;
        double x =0.0;
        int end = (current_thread+1)*quarter;
        for (int i = (current_thread*quarter); i < end; i++) {
            x = (i + 0.5) * step;
            tmp_sum = tmp_sum + 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        sum += tmp_sum;
    }

    pi = step * sum;
    return pi;
}

double pi_omp_parallel_critical(long steps){
    int max_threads = omp_get_max_threads();
    double step;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)steps;
    int quarter = steps/max_threads;

    #pragma omp parallel
    {
        int current_thread = omp_get_thread_num();
        double tmp_sum=0.0;
        double x =0.0;
        int end = (current_thread+1)*quarter;
        for (int i = (current_thread*quarter); i < end; i++) {
            x = (i + 0.5) * step;
            tmp_sum = tmp_sum + 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
        {
        sum += tmp_sum;
        }
    }

    pi = step * sum;
    return pi;
}

double pi_omp_parallel_critical_errado(long steps){
    int max_threads = omp_get_max_threads();
    double step;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)steps;
    int quarter = steps/max_threads;

    #pragma omp parallel
    {
        int current_thread = omp_get_thread_num();
        double tmp_sum=0.0;
        double x =0.0;
        int end = (current_thread+1)*quarter;
        #pragma omp critical
        {
            for (int i = (current_thread*quarter); i < end; i++) {
                x = (i + 0.5) * step;
                tmp_sum = tmp_sum + 4.0 / (1.0 + x * x);
            }
            sum += tmp_sum;
        }
    }

    pi = step * sum;
    return pi;
}

int main() {
    double pi;


    auto start_time = std::chrono::high_resolution_clock::now();

    pi = double_pi_threads_raiz(num_steps);
    auto end_time_threads = std::chrono::high_resolution_clock::now();
    std::cout.precision(17);
    std::cout << pi << std::endl;

    pi = pi_seq(num_steps);
    auto end_time_serial = std::chrono::high_resolution_clock::now();
    std::cout.precision(17);
    std::cout << pi << std::endl;

    pi = pi_omp_parallel(num_steps);
    auto end_time_omp_parallel = std::chrono::high_resolution_clock::now();
    std::cout.precision(17);
    std::cout << pi << std::endl;

    pi = pi_omp_parallel_atomic(num_steps);
    auto end_time_omp_parallel_atomic = std::chrono::high_resolution_clock::now();
    std::cout.precision(17);
    std::cout << pi << std::endl;

    pi = pi_omp_parallel_critical(num_steps);
    auto end_time_omp_parallel_critical = std::chrono::high_resolution_clock::now();
    std::cout.precision(17);
    std::cout << pi << std::endl;

    pi = pi_omp_parallel_critical_errado(num_steps);
    auto end_time_omp_parallel_critical_errado = std::chrono::high_resolution_clock::now();
    std::cout.precision(17);
    std::cout << pi << std::endl;

    
    
    auto runtime_t = std::chrono::duration_cast<std::chrono::milliseconds> (end_time_threads - start_time);
    auto runtime_s = std::chrono::duration_cast<std::chrono::milliseconds> (end_time_serial - end_time_threads);
    auto runtime_o = std::chrono::duration_cast<std::chrono::milliseconds> (end_time_omp_parallel - end_time_serial);
    auto runtime_a = std::chrono::duration_cast<std::chrono::milliseconds> (end_time_omp_parallel_atomic - end_time_omp_parallel);
    auto runtime_c = std::chrono::duration_cast<std::chrono::milliseconds> (end_time_omp_parallel_critical - end_time_omp_parallel_atomic);
    auto runtime_c_e = std::chrono::duration_cast<std::chrono::milliseconds> (end_time_omp_parallel_critical_errado - end_time_omp_parallel_critical);

    
    std::cout << "O valor de pi calculado com " << num_steps << " passos levou "<<std::endl;
    std::cout << runtime_s.count() << " milisegundos(s) em serie"<<std::endl;
    std::cout << runtime_t.count() << " milisegundos(s) com threads"<<std::endl;
    std::cout << runtime_o.count() << " milisegundos(s) com omp"<<std::endl;
    std::cout << runtime_a.count() << " milisegundos(s) com atomic"<<std::endl;
    std::cout << runtime_c.count() << " milisegundos(s) com critical"<<std::endl;
    std::cout << runtime_c_e.count() << " milisegundos(s) com critical errado"<<std::endl;


}
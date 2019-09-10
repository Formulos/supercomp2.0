#include <iostream>
#include <chrono>
#include <thread>

static long num_steps = 100000000;
double step;

void divided_pi(int init,int end,double step,double *vector,int place){
    double tmp_sum=0.0;
    double x =0.0;
    for (int i = init; i < end; i++) {
        x = (i + 0.5) * step;
        tmp_sum = tmp_sum + 4.0 / (1.0 + x * x);
    }
    vector[place] = tmp_sum;
    
}

int main() {
    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;
    double vector_sums[4];
    int quarter = num_steps/4;

    auto start_time = std::chrono::high_resolution_clock::now();
    std::thread t1(divided_pi, 0, quarter,step,vector_sums,0);
    std::thread t2(divided_pi, quarter, quarter*2,step,vector_sums,1);
    std::thread t3(divided_pi, quarter*2, quarter*3,step,vector_sums,2);
    std::thread t4(divided_pi, quarter*3, num_steps,step,vector_sums,3);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    for (i = 0; i < 4; i++) {
        sum += vector_sums[i];
    }

    pi = step * sum;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
    
    std::cout << "O valor de pi calculado com " << num_steps << " passos levou ";
    std::cout << runtime.count() << " milisegundos(s) e chegou no valor : ";
    std::cout.precision(17);
    std::cout << pi << std::endl;
}
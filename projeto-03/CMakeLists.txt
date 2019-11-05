cmake_minimum_required(VERSION 3.9)
project (projeto_basico)
find_package(OpenMP REQUIRED)
find_package(CUDA REQUIRED)


cuda_add_executable(opt_gpu 2_opt_gpu.cu OPTIONS -std=c++11)

cuda_add_executable(r_solver random_solver.cu OPTIONS -std=c++11)

add_executable(opt_para 2_opt_para.cc place.cpp)
target_link_libraries (opt_para OpenMP::OpenMP_CXX)
target_compile_definitions(opt_para PUBLIC O3 fopenmp)

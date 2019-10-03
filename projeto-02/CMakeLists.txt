cmake_minimum_required(VERSION 3.9)
project (projeto_basico)
find_package(OpenMP REQUIRED)

add_executable(seq tsp.cc place.cpp)
target_compile_definitions(seq PUBLIC O3)

add_executable(para tsp.cc place.cpp)
target_link_libraries (para OpenMP::OpenMP_CXX)
target_compile_definitions(para PUBLIC O3 fopenmp)

add_executable(opt 2_opt.cc place.cpp)
target_link_libraries (opt OpenMP::OpenMP_CXX)
target_compile_definitions(opt PUBLIC O3 fopenmp)

add_executable(heuristic heuristic.cc place.cpp)
target_link_libraries (heuristic OpenMP::OpenMP_CXX)
target_compile_definitions(heuristic PUBLIC O3 fopenmp)

add_executable(heuristic_seq heuristic.cc place.cpp)
target_compile_definitions(heuristic PUBLIC O3)

add_executable(opt_seq 2_opt.cc place.cpp)
target_compile_definitions(opt_seq  PUBLIC O3)
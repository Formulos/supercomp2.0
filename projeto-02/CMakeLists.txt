cmake_minimum_required(VERSION 3.9)
project (projeto_basico)

add_executable(seq tsp.cc place.cpp)
target_compile_definitions(seq PUBLIC O3)

add_executable(para tsp.cc place.cpp)
target_compile_definitions(para PUBLIC O3 fopenmp)

add_executable(opt tsp.cc place.cpp)
target_compile_definitions(opt PUBLIC O3)
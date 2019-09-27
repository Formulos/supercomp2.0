cmake_minimum_required(VERSION 3.9)
project (projeto_basico)

add_executable(main tsp.cc place.cpp)
target_compile_definitions(main PUBLIC O3)
cmake_minimum_required(VERSION 3.9)
project (projeto_basico)

add_executable(main main.cc square.cpp)
target_compile_definitions(main PUBLIC O3)

add_executable(main_zero main.cc square.cpp)
target_compile_definitions(main_zero PUBLIC O0)

add_executable(main_two main.cc square.cpp)
target_compile_definitions(main_two PUBLIC O2)

add_executable(main_fast main.cc square.cpp)
target_compile_definitions(main_fast PUBLIC O3 ftree-vectorize mavx ffast-math)
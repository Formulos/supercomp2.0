cmake_minimum_required(VERSION 3.9)
project (projeto_basico)
add_executable(oi main.cc square.cpp)
target_compile_definitions(oi PUBLIC O3)
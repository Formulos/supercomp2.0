cmake_minimum_required(VERSION 3.9)
project (projeto_basico)
add_executable(hello atividade_1.cc experimento.cpp vec_pow.cpp vec_log.cpp)
target_compile_definitions(hello PUBLIC O3)

add_executable(zero atividade_1.cc experimento.cpp)
target_compile_definitions(zero PUBLIC O0)

add_executable(one atividade_1.cc experimento.cpp)
target_compile_definitions(one PUBLIC O1)

add_executable(two atividade_1.cc experimento.cpp)
target_compile_definitions(two PUBLIC O2)

add_executable(tree atividade_1.cc experimento.cpp)
target_compile_definitions(tree PUBLIC O3)

add_executable(lala atividade_1.cc experimento.cpp)
target_compile_definitions(lala PUBLIC S c O2 ftree-vectorize mavx )
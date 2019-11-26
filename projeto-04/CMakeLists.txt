cmake_minimum_required(VERSION 3.9)
project (projeto)

find_package(Boost REQUIRED mpi serialization)
find_package(MPI)

add_executable(tsp tsp_mpi.cc place.cpp)

target_link_libraries(tsp Boost::mpi)
target_link_libraries(tsp MPI::MPI_CXX)

add_executable(2_opt_mpi 2_opt_mpi.cc place.cpp)

target_link_libraries(2_opt_mpi Boost::mpi)
target_link_libraries(2_opt_mpi MPI::MPI_CXX)
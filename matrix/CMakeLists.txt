cmake_minimum_required(VERSION 3.17)
project(matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix main.cpp)
add_executable(matrix_submatrix main.cpp submatrix.cpp musor.cpp)
add_executable(matrix_musor musor.cpp)

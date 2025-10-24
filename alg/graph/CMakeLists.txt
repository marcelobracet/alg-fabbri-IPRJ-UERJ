cmake_minimum_required(VERSION 3.10)
project(graph)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Executável do dynagraph original (C)
add_executable(dynagraph-c dynagraph.c)

# Executável do dynagraph com C++ e OOP
add_executable(dynagraph dynagraph.cpp)

# Executável de testes para o dynagraph C++
add_executable(test-dynagraph test_dynagraph.cpp)

# Executável de conversão para Matriz de Adjacências
add_executable(adjacency-matrix adjacency_matrix.cpp)

# Executável do tree (C++)
add_executable(tree tree.cpp)

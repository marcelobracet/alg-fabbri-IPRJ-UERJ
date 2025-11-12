cmake_minimum_required(VERSION 3.10)
project(bigstring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Biblioteca BigString
add_library(bigstring bigstring.cpp)

# Exporta o diretório de headers
target_include_directories(bigstring PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Executável de testes
add_executable(test-bigstring test_bigstring.cpp)
target_link_libraries(test-bigstring bigstring)

# Executável de exemplo
add_executable(bigstring-example example.cpp)
target_link_libraries(bigstring-example bigstring)


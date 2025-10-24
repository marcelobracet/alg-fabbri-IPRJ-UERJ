cmake_minimum_required(VERSION 3.10)
project(alg)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-g -ggdb3 -fsanitize=address -fno-omit-frame-pointer")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb3 -fsanitize=address -fno-omit-frame-pointer")

find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/third_party/benchmark/include)

add_subdirectory(third_party)

enable_testing()

add_subdirectory(alg)

# Ensure to link against Google Benchmark and pthread
# Replace 'your_target_name' with the actual target name in your project
# target_link_libraries(your_target_name benchmark Threads::Threads)


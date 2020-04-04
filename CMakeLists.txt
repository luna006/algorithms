cmake_minimum_required(VERSION 3.10)

project(algorithms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(test)
add_subdirectory(src/graph)

cmake_minimum_required(VERSION 3.10)

project(graph_app)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB GRAPH_APP_SRC "*.cpp")

add_executable(${PROJECT_NAME} ${GRAPH_APP_SRC})
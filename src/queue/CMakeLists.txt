cmake_minimum_required(VERSION 3.10)

project(queue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB QUEUE_APP_SRC "*.cpp")

add_executable(${PROJECT_NAME} ${QUEUE_APP_SRC})
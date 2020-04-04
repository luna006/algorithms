cmake_minimum_required(VERSION 3.10)

project(algorithms_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(GTEST_SRC_DIR "googletest/googletest")
set(GMOCK_SRC_DIR "googletest/googlemock")

file(GLOB SORT_SRC "../src/sort/*.cc" "ut/test_sort.cc")
file(GLOB GRAPH_SRC "../src/graph/*.cpp" "ut/graph_test.cpp")
file(GLOB MAIN_TEST_SRC "ut/main.cc")
file(GLOB GTEST_SRC "${GTEST_SRC_DIR}/src/gtest-all.cc" "${GMOCK_SRC_DIR}/src/gmock-all.cc")

add_executable(sort_test ${SORT_SRC} ${MAIN_TEST_SRC} ${GTEST_SRC})
add_executable(graph_test ${GRAPH_SRC} ${MAIN_TEST_SRC} ${GTEST_SRC})

include_directories(sort_test PUBLIC
        "${PROJECT_SOURCE_DIR}/../src/sort"
        "${PROJECT_SOURCE_DIR}/../src/graph"
        "${GTEST_SRC_DIR}/include"
        "${GMOCK_SRC_DIR}/include"
        "${GTEST_SRC_DIR}"
        "${GMOCK_SRC_DIR}")
target_link_libraries(sort_test pthread)
target_link_libraries(graph_test pthread)





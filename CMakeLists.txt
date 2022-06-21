cmake_minimum_required(VERSION 3.22)
project(pagerank CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Ofast")

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp pagerank.h)
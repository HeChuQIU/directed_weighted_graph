cmake_minimum_required(VERSION 3.26)
project(directed_weighted_graph)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(directed_weighted_graph
        directed_weighted_graph.cpp
        directed_weighted_graph.h)

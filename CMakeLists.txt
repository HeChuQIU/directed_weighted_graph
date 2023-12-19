cmake_minimum_required(VERSION 3.26)
project(directed_weighted_graph)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")

include_directories(.)

add_executable(directed_weighted_graph
        directed_weighted_graph.cpp
        directed_weighted_graph.h)

cmake_minimum_required(VERSION 3.26)
project(PEA_SA)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_SA main.cpp
        TSP.cpp
        TSP.h)

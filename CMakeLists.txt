cmake_minimum_required(VERSION 3.21)
project(_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(_
        knapsack.h
        random_library.h
        stone.h
        test_generators.h
        testing_knapsack.cpp)

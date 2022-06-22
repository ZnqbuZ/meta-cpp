cmake_minimum_required(VERSION 3.22)
project(meta_cpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(meta_cpp
        algorithms.h
        arithmetics.h
        types.h
        meta-cpp.cpp
        stream.h)

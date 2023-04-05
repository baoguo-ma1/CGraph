cmake_minimum_required(VERSION 3.1)

project(pyCGraph VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared -pthread -fPIC ")

file(GLOB_RECURSE CGRAPH_SRC_LIST "../src/*.cpp")

find_package(pybind11 REQUIRED)

pybind11_add_module(CGraph
        ../../../../../Desktop/py-chunel/python2/PyWrapper/py_export.cpp
        ${CGRAPH_SRC_LIST})

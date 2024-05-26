cmake_minimum_required(VERSION 3.19)
project(example)

set(CMAKE_PREFIX_PATH "C:/Program Files/Python311/Lib/site-packages/pybind11")
find_package(pybind11 REQUIRED)
# or add_subdirectory(pybind11)

pybind11_add_module(example main.cpp)
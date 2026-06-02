cmake_minimum_required(VERSION 3.28)
project(Piranha)

set(CMAKE_CXX_STANDARD 20)

add_executable(Piranha Src/main.cpp
        Src/tensor.cpp
        include/tensor.hpp
        include/Node.hpp
)

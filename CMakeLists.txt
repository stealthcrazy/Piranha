cmake_minimum_required(VERSION 3.28)
project(Piranha)

set(CMAKE_CXX_STANDARD 20)

add_executable(Piranha src/main.cpp
        include/Pir_Tensors/Pir_DTypes.hpp
        include/Pir_Tensors/Pir_Storage.hpp
        include/Pir_Tensors/Pir_Core.hpp
        include/Pir_Tensors/Pir_Tensor.hpp
        include/Pir_Tensors/Pir_Tensor.cpp
        include/Pir_Tensors/Pir_Core.cpp
        include/Pir_Tensors/Pir_binOps.cpp
        include/Pir_Tensors/Pir_binOps.hpp
        include/Pir_Tensors/Pir_Storage.cpp
        include/Pir_Tensors/Pir_Iterator.hpp
)

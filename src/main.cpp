#include <iostream>
#include "../include/Pir_Tensors/Pir_Core.hpp"

using namespace  Piranha;
int main() {
    std::cout << "Hello, World!" << std::endl;

    Core({4,3,2},DType::Float32);

    return 0;
}
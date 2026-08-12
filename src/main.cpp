#include <iostream>
#include "../include/Pir_Tensors/Pir_Core.hpp"
#include "../include/Pir_Tensors/Pir_Tensor.hpp"

using namespace  Piranha;
int main() {
    std::cout << "Hello, World!" << std::endl;

    Tensor t = Tensor({3,3},DType::Float32);
    Tensor b = t[1][1];
    t.transpose().all(1);
    return 0;
}
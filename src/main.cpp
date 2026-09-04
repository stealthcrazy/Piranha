#include <iostream>
#include "../include/Pir_Tensors/Pir_Core.hpp"
#include "../include/Pir_Tensors/Pir_Tensor.hpp"
#include "../include/Pir_Tensors/Pir_binOps.hpp"
#include "../include/Pir_Tensors/Pir_Functional.hpp"
#include <iostream>

using namespace  Piranha;
int main() {
    std::cout << "Hello, World!" << std::endl;

    Tensor t = Tensor({3,3},DType::Float32);
    t.all(3);
    Tensor a = Tensor({3,3},DType::Float32);

    a.all(2);

    Tensor b = tmm(t,a);
    for (int i = 0 ; i < 10 ; i++) {
        std::cout << i << std::endl;
    }
    b.raw_dump();

    return 0;
}
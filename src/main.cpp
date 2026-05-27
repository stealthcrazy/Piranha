#include <iostream>
#include "../include/tensor.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Piranha::Tensor<float> t1 = Piranha::Tensor<float>::ones({3,3});
    Piranha::Tensor<float> t2({3,3},{1,2,3,4,5,6,7,8,9});

    std::cout << (t1 & t2)[1][2].value();

    return 0;
}

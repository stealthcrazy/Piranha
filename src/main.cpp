#include <iostream>
#include "../include/tensor.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Piranha::Tensor<float> t1 = Piranha::Tensor<float>::ones({1,3,3});
    Piranha::Tensor<float> t2 = Piranha::Tensor<float>::all({1,3,3},2);

    std::cout << (t1+t2)[0][1][2].value();

    return 0;
}
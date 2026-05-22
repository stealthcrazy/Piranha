#include <iostream>
#include "../include/tensor.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Piranha::Tensor<float, 4,3,2> te;
    std::cout << "Bye, World!" << te[3][1][3].value() <<std::endl;
    return 0;
}

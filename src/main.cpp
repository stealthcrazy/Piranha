#include <iostream>
#include "../include/tensor.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Piranha::Tensor<float, 4,3,2> te;
    std::cout << typeid(te[0][0]).name();


    return 0;
}

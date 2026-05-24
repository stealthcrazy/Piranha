#include <iostream>
#include "../include/tensor.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Piranha::Tensor<float, 3,3> te({1,2,3,4,5,6,7,8,9});
    std::cout << "Bye, World!" << te[2].value() <<std::endl;


    return 0;
}

#include <iostream>
#include "../include/tensor.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Piranha::Tensor<float> t({3,3},{1,2,3,4,5,6,7,8,9});
    Piranha::Tensor<float> t1({3,3},{1,2,3,4,5,6,7,8,9});
    std::cout << t[0][0].value();


    return 0;
}

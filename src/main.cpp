#include <iostream>
#include "../include/tensor.hpp"
#include "../include/Node.hpp"

using namespace  Piranha;
int main() {
    std::cout << "Hello, World!" << std::endl;

    std::shared_ptr<Tensor<float>> a =    std::make_shared<Tensor<float>>(Tensor<float>::all({3,3},1));
    std::shared_ptr<Tensor<float>> b =    std::make_shared<Tensor<float>>(Tensor<float>::all({3,3},2));

    AddN<float> A({}, a,b);

    for (int i = 0; i<10;i++) {
        continue;
    }

    return 0;
}
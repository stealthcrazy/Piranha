#include <iostream>
#include "../include/tensor.hpp"
#include "../include/Node.hpp"

using namespace  Piranha;
int main() {
    std::cout << "Hello, World!" << std::endl;

    std::shared_ptr<Tensor<float>> a =    std::make_shared<Tensor<float>>(Tensor<float>::all({2,1},1));
    std::shared_ptr<Tensor<float>> b =    std::make_shared<Tensor<float>>(Tensor<float>::all({2,1},2));
    Tensor<float> S =    Tensor<float>::all({2,1},1);
    AddN<float> A({}, a,b);
    A.apply_grad(S);

    return 0;
}
//
// Created by Sohan Prabhu on 06/08/2026.
//
#include "Pir_Tensor.hpp"

using namespace Piranha;

Tensor Tensor::Reshape(std::vector<int64_t> shape_) const {
    if (Impl->numelm() !=  std::accumulate(shape_.begin(),shape_.end(),int64_t{1},std::multiplies<>())) {
        throw std::invalid_argument("Size Mismatch");
    }
    for (int64_t d : shape_)
        if (d < 0) throw std::invalid_argument("negative dimension");
    return  Tensor( std::make_shared<Core>(Impl->CoreStorage,shape_,Impl->type()));
}



//
// Created by Sohan Prabhu on 06/08/2026.
//
#include "Pir_Tensor.hpp"

#include <iostream>

using namespace Piranha;

Tensor Tensor::Reshape(std::vector<int64_t> shape_) const {
    if (Impl->numelm() !=  std::accumulate(shape_.begin(),shape_.end(),int64_t{1},std::multiplies<>())) {
        throw std::invalid_argument("Size Mismatch");
    }
    for (const int64_t d : shape_)
        if (d < 0) throw std::invalid_argument("negative dimension");
    return  Tensor( std::make_shared<Core>(Impl->CoreStorage,shape_,Core::getContiguousStrides(shape_),Impl->type(),Impl->Offset));
}

Tensor Tensor::transpose() const {
    std::vector<int64_t> new_shape = Impl->Shape;
    std::vector<int64_t> new_stride = Impl->Stride;
    auto swap = [](int64_t &x , int64_t &y) {
        int64_t temp = x;
        x = y;
        y = temp;
    };
    swap(new_shape[0],new_shape[1]);
    swap(new_stride[0],new_stride[1]);
    return  Tensor( std::make_shared<Core>(Impl->CoreStorage,new_shape,new_stride,Impl->type(),Impl->Offset));

}

Tensor Tensor::permute(const std::vector<int64_t>& order) const {
    if (order.size() > Impl->shape().size()) throw std::invalid_argument("Invalid Order Size");
    // need check for if order is unique set
    for (const int64_t d : order)
        if (d > Impl->Shape.size()) throw std::invalid_argument("Invalid Order Parameter Size");

    std::vector<int64_t> new_shape , new_stride;
    for (const int64_t d : order) {
        new_shape.push_back(Impl->Shape.at(d));
        new_stride.push_back(Impl->Stride.at(d));
    }
    return  Tensor( std::make_shared<Core>(Impl->CoreStorage,new_shape,new_stride,Impl->type(),Impl->Offset));

}

Tensor Tensor::operator[](int64_t i) {
    if (Impl->dim() == 0) throw std::out_of_range("Invalid ! Scalar Can't Be Indexed ");
    if (i >= Impl->Shape.at(0)) throw std::out_of_range("Invalid Index ");
    int64_t new_offset = Impl->Offset + (i*Impl->Stride.at(0));
    std::vector<int64_t> new_shape(Impl->dim()-1) , new_stride(Impl->dim()-1);
    std::copy(Impl->Shape.begin()+1,Impl->Shape.end(),new_shape.begin() );
    std::copy(Impl->Stride.cbegin()+1,Impl->Stride.cend(),new_stride.begin() );
    return  Tensor( std::make_shared<Core>(Impl->CoreStorage,new_shape,new_stride,Impl->type(),new_offset));
}

void Tensor::all(int64_t v) const {
    Impl->all(v);
}

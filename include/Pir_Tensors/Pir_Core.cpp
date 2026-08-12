//
// Created by Sohan Prabhu on 06/08/2026.
//
#include "Pir_Core.hpp"
#include <iostream>
#include <utility>

#include "Pir_Iterator.hpp"

using namespace Piranha;





Core::Core(std::shared_ptr<Storage> Storage_, std::vector<int64_t> Shape_, std::vector<int64_t> Stride_ , const DType Type_, const int64_t Offset_)
: Shape(std::move(Shape_)),Stride(std::move(Stride_)), Type(Type_), Offset(Offset_)
{
    Size = std::accumulate(Shape.begin(),Shape.end(),int64_t{1},std::multiplies<>());
    int64_t acc = 1;
    for (int64_t d : Shape)
        if (d < 0) throw std::invalid_argument("negative dimension");
    Stride.resize(Shape.size());
    CoreStorage = std::move(Storage_);
    contiguous = is_contiguous();
}

Core::Core(std::vector<int64_t> Shape_, const DType Type_ ) : Shape(std::move(Shape_)), Type(Type_) {
    Size = std::accumulate(Shape.begin(),Shape.end(),int64_t{1},std::multiplies<>());
    for (int64_t d : Shape)
        if (d < 0) throw std::invalid_argument("negative dimension");
    Stride = std::move(getContiguousStrides(Shape));
    CoreStorage = std::make_shared<Storage>(Size*itemSize(Type_));
    contiguous = is_contiguous();
}


bool Core::is_contiguous() const {
    int64_t acc = 1;
    for (int64_t d = dim() - 1; d >= 0; --d) {
        if (Stride[d] != acc) return false;
        acc *= Shape[d];
    }
    return true;

}

std::vector<int64_t> Core::getContiguousStrides(std::vector<int64_t> &shape) {
    std::vector<int64_t> Stride;
    int64_t acc = 1;
    Stride.resize(shape.size());
    for (int64_t d = static_cast<int64_t>(shape.size()) - 1; d >= 0; --d) {
        Stride[d] = acc;
        acc *= shape[d];
    }
    return Stride;
}

void Core::all(float t) {
    switch (Type){

        FORALL_PIR_DTYPES(TYPE_ENTRY_CASE,[&]{
            Piranaha::for_each(Shape,{Stride},{Offset},[&]( const std::vector<int64_t>& ips) {
                auto* buffer = static_cast<concrete_type*>(CoreStorage->data());
                buffer[ips[0]] = t;
            });
        })
    }
}

//
// Created by Sohan Prabhu on 06/08/2026.
//
#include "Pir_Core.hpp"

#include <utility>

using namespace Piranha;


Core::Core(std::shared_ptr<Storage> Storage_, std::vector<int64_t> Shape_, DType Type_) : Shape(std::move(Shape_)), Type(Type_) {
    Size = std::accumulate(Shape.begin(),Shape.end(),int64_t{1},std::multiplies<>());
    int64_t acc = 1;
    for (int64_t d : Shape)
        if (d < 0) throw std::invalid_argument("negative dimension");
    Stride.resize(Shape.size());
    for (int64_t d = static_cast<int64_t>(Shape.size()) - 1; d >= 0; --d) {
        Stride[d] = acc;
        acc *= Shape[d];
    }
    CoreStorage = std::move(Storage_);
}

Core::Core(std::vector<int64_t> Shape_, DType Type_ ) : Shape(std::move(Shape_)), Type(Type_) {
    Size = std::accumulate(Shape.begin(),Shape.end(),int64_t{1},std::multiplies<>());
    int64_t acc = 1;
    for (int64_t d : Shape)
        if (d < 0) throw std::invalid_argument("negative dimension");
    Stride.resize(Shape.size());
    for (int64_t d = static_cast<int64_t>(Shape.size()) - 1; d >= 0; --d) {
        Stride[d] = acc;
        acc *= Shape[d];
    }
    CoreStorage = std::make_shared<Storage>(Size*itemSize(Type_));
}

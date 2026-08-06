//
// Created by Sohan Prabhu on 05/08/2026.
//

#pragma once
#include "Pir_Core.hpp"


namespace  Piranha {
    class Tensor {

    public:

        Tensor(std::vector<int64_t> shape_,DType type_) : Impl(std::make_shared<Core>(std::move(shape_),type_)) {}
        explicit Tensor(std::shared_ptr<Core> A ){Impl = A;}
        Tensor(const Tensor& A ){Impl = A.Impl; }
        Tensor& operator=(const Tensor& A) = default;

        std::vector<int64_t> shape() const { return Impl->shape(); }
        std::vector<int64_t> stride() const {return Impl->stride();}
        int64_t numelm() const {return Impl->numelm();}
        int64_t dim() const {return Impl->dim();}
        DType type() const {return Impl->type();}

        Tensor Reshape(std::vector<int64_t> shape_) const;

    private:
        std::shared_ptr<Core> Impl;
    };
}

//
// Created by Sohan Prabhu on 07/08/2026.
//

#ifndef PIRANHA_PIR_BINOPS_HPP
#define PIRANHA_PIR_BINOPS_HPP

#include <cstdint>
#include "Pir_Tensor.hpp"
#include "Pir_Iterator.hpp"



namespace Piranha {
    // elem wise
    Tensor operator+(const Tensor& a ,const Tensor& b) ;
    Tensor operator*(const Tensor& a ,const Tensor& b) ;
    Tensor operator-(const Tensor& a ,const Tensor& b) ;

    Tensor operator$(const Tensor& a ,const Tensor& b) ; // matmul operator
    Tensor dot(const Tensor& a ,const Tensor& b) ; // dot product
    Tensor tmm(const Tensor& a ,const Tensor& b) ; // matrix multiplication for 2D matrix multiplication
}


#endif //PIRANHA_PIR_BINOPS_HPP
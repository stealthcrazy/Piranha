//
// Created by Sohan Prabhu on 07/08/2026.
//

#include "Pir_binOps.hpp"
#include <iostream>

Piranha::Tensor Piranha::operator*(const Tensor &a, const Tensor &b) {
    DType t = a.type();
    //TODO add type promotion for different tensor types
    std::vector<int64_t> shape = a.shape();
    Tensor r = Tensor(shape,t);
    switch (t){
        FORALL_PIR_DTYPES(TYPE_ENTRY_CASE,[&]{
            auto* buffer_a = static_cast<concrete_type*>(a.Impl->getStorage()->data());
            auto* buffer_b = static_cast<concrete_type*>(b.Impl->getStorage()->data());
            auto* buffer_r = static_cast<concrete_type*>(r.Impl->getStorage()->data());
            Piranaha::for_each(shape,
                {a.stride(),b.stride(),r.stride()},
                {a.offset(),b.offset(),r.offset()},
                [&]( const std::vector<int64_t>& ips) {
                    buffer_r[ips[2]] = buffer_a[ips[0]] * buffer_b[ips[1]];
            });
        })
    }
    return r;

}

Piranha::Tensor Piranha::operator-(const Tensor &a, const Tensor &b) {
    DType t = a.type();
    //TODO add type promotion for different tensor types
    std::vector<int64_t> shape = a.shape();
    Tensor r = Tensor(shape,t);
    switch (t){
        FORALL_PIR_DTYPES(TYPE_ENTRY_CASE,[&]{
            auto* buffer_a = static_cast<concrete_type*>(a.Impl->getStorage()->data());
            auto* buffer_b = static_cast<concrete_type*>(b.Impl->getStorage()->data());
            auto* buffer_r = static_cast<concrete_type*>(r.Impl->getStorage()->data());
            Piranaha::for_each(shape,
                {a.stride(),b.stride(),r.stride()},
                {a.offset(),b.offset(),r.offset()},
                [&]( const std::vector<int64_t>& ips) {
                    buffer_r[ips[2]] = buffer_a[ips[0]] - buffer_b[ips[1]];
            });
        })
    }
    return r;
}

Piranha::Tensor Piranha::operator+(const Tensor& a ,const Tensor& b) {
    DType t = a.type();
    std::vector<int64_t> shape = a.shape();
    Tensor r = Tensor(shape,t);
    switch (t){
        FORALL_PIR_DTYPES(TYPE_ENTRY_CASE,[&]{
            auto* buffer_a = static_cast<concrete_type*>(a.Impl->getStorage()->data());
            auto* buffer_b = static_cast<concrete_type*>(b.Impl->getStorage()->data());
            auto* buffer_r = static_cast<concrete_type*>(r.Impl->getStorage()->data());
            Piranaha::for_each(shape,
                {a.stride(),b.stride(),r.stride()},
                {a.offset(),b.offset(),r.offset()},
                [&]( const std::vector<int64_t>& ips) {
                    buffer_r[ips[2]] = buffer_a[ips[0]] + buffer_b[ips[1]];
            });
        })
    }
    return r;

}


Piranha::Tensor Piranha::dot(const Tensor &a, const Tensor &b) {
    DType t = a.type();
    if ((a.dim() != 1) || (b.dim() != 1) ) throw(std::invalid_argument("Dot product applied on Non-1dim Tensors"));
    if (a.numelm() != b.numelm())  throw(std::invalid_argument("Dot product applied on Mismatch Tensors"));
    if (a.type() != b.type()) throw(std::invalid_argument("Hmm Dot product not supported between operrands"));
    //TODO add type promotion for different tensor types
    Tensor r = Tensor({1},t);
    auto as =  a.stride();
    auto bs =  b.stride();
    switch (t) {
        FORALL_PIR_DTYPES(TYPE_ENTRY_CASE,[&] {
            auto* buffer_a = static_cast<concrete_type*>(a.Impl->getStorage()->data());
            auto* buffer_b = static_cast<concrete_type*>(b.Impl->getStorage()->data());
            auto* buffer_r = static_cast<concrete_type*>(r.Impl->getStorage()->data());
            buffer_r[0] = 0;

            for (int i = 0; i < a.numelm(); i++)
                buffer_r[0]  += buffer_a[(as[0]*i)+a.offset()] * buffer_b[(bs[0]*i)+b.offset()];
        });
    }
    return r;

}


Piranha::Tensor Piranha::tmm(const Tensor &a, const Tensor &b) {
    if ((a.dim() != 2) || (b.dim() != 2) ) throw(std::invalid_argument("Matrix product applied on Non-2dim Tensors"));
    if (a.shape().at(1) != b.shape().at(0))  throw(std::invalid_argument("Matrix product applied on Mismatch -> Must be  n x m & m x p "));
    if (a.type() != b.type()) throw(std::invalid_argument("Hmm Matrix product not supported between operrands"));
    DType t = a.type();
    //TODO add type promotion for different tensor types
    Tensor r = Tensor({a.shape().at(0),b.shape().at(1)},t);
    auto rs = r.stride();
    auto as =  a.stride();
    auto bs = b.stride();

    switch (t) {
        FORALL_PIR_DTYPES(TYPE_ENTRY_CASE,[&] {
            auto* buffer_a = static_cast<concrete_type*>(a.Impl->getStorage()->data());
            auto* buffer_b = static_cast<concrete_type*>(b.Impl->getStorage()->data());
            auto* buffer_r = static_cast<concrete_type*>(r.Impl->getStorage()->data());

            for (int i = 0; i < a.shape().at(0); i++) {
                for (int j = 0 ; j < b.shape().at(1); j++) {
                    for (int k = 0 ; k < b.shape().at(0); k++) {
                        std::cout <<  i<< " " << k  <<  " ," <<  k << " " << j << std::endl;
                        buffer_r[(i*rs[0]) + (j*rs[1] + r.offset())] += buffer_a[(i*as[0]) + (k*as[1] + a.offset())] * buffer_b[(k*bs[0]) + (j*bs[1] + b.offset())];
                    }
                    std::cout << " ---- " << std::endl;
                }
            }

        });
    }
    return r;

}

Piranha::Tensor Piranha::operator$(const Tensor &a, const Tensor &b) {

    if ((a.dim() == 1) && (b.dim() == 1) ) return dot(a,b);
    if ((a.dim() == 2 && (b.dim() == 2))) return tmm(a,b);

}



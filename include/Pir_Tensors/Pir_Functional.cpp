//
// Created by Sohan Prabhu on 28/08/2026.
//

#include "Pir_Functional.hpp"
#include <iostream>

bool Piranha::is_Broadcastable(std::vector<int64_t> &x, std::vector<int64_t> &y) {
    //if (x.size() < y.size()) return false; // can't broadcast y to something small shape
    for (int i = x.size()-1 ; i >= (x.size()-y.size()) ; i-- )
        if ( (x[i] != y[i]) && (x[i] != 1) && (y[i] != 1) ) return false;

    return true;

}


std::vector<int64_t> Piranha::broadcast_shape(std::vector<int64_t> &x, std::vector<int64_t> &y) {
    if (!is_Broadcastable(x,y))throw(std::invalid_argument("y not broadcastable to x. Mismatch "));
    std::vector<int64_t> temp(x.size(),1);
    std::copy(y.begin(),y.end(),temp.begin()+(x.size()-y.size()));

    for (int i = 0 ; i <temp.size(); i++ )
        temp[i] = std::max(x[i],y[i]);


    return temp;
}


Piranha::Tensor Piranha::broadcast_Tensor_to(Tensor x, std::vector<int64_t> shape_ ) {
    std::vector<int64_t> x_shape = x.shape();
    if (!is_Broadcastable(x_shape,shape_))throw(std::invalid_argument("y not broadcastable to x. Mismatch "));
    std::vector<int64_t> stride_ = x.stride();
    for (int i = 0 ; i < shape_.size()-x_shape.size(); i++)
        stride_.insert(stride_.begin(),0);
    std::shared_ptr<Core> shell = std::make_shared<Core>(x.Impl->getStorage(),shape_,stride_,x.type(),x.offset());

    Tensor fresh = Tensor(shell);

    /*
    int64_t t = std::accumulate(shape_.begin(),shape_.begin()+(shape_.size()-x_shape.size()),1,std::multiplies<int64_t>());
    switch(x.type()) {
        FORALL_PIR_DTYPES(TYPE_ENTRY_CASE,[&] {
            auto* buffer_old = static_cast<concrete_type*>(x.Impl->getStorage()->data());
            auto* buffer_new = static_cast<concrete_type*>(fresh.Impl->getStorage()->data());
            int64_t buff_nBytes = x.Impl->getStorage()->getBytes() ;
            int64_t buff_size = buff_nBytes / sizeof(concrete_type);
            for (int i = 0; i < t; i++)
                std::memcpy(buffer_new+(i*buff_size),buffer_old+x.Impl->offset(),buff_nBytes);

        });
    }*/

    return fresh;


}




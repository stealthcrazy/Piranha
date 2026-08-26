//
// Created by Sohan Prabhu on 28/08/2026.
//

#ifndef PIRANHA_PIR_FUNCTIONAL_HPP
#define PIRANHA_PIR_FUNCTIONAL_HPP

#include "Pir_Tensor.hpp"
#include <vector>

namespace Piranha {


    bool is_Broadcastable(std::vector<int64_t> &x, std::vector<int64_t> &y);
    std::vector<int64_t> broadcast_shape(std::vector<int64_t> &x,std::vector<int64_t> &y );
    Tensor broadcast_Tensor_to(Tensor x,std::vector<int64_t> shape_   );









}

#endif //PIRANHA_PIR_FUNCTIONAL_HPP
//
// Created by Sohan Prabhu on 11/08/2026.
//

#ifndef PIRANHA_PIR_ITTERATOR_HPP
#define PIRANHA_PIR_ITTERATOR_HPP

#include <vector>
#include <numeric>
#include <algorithm>


namespace Piranaha {
    template <typename F>
    void for_each(std::vector<int64_t> shape, std::vector<std::vector<int64_t>> stride,
                        std::vector<int64_t> offset,F&& f ) {
        // element wise access for handling non-contiguous and contiguous tensor
        int64_t Size = std::accumulate(shape.begin(),shape.end(),int64_t{1},std::multiplies<>()); // total element count
        int64_t n = offset.size(); // operand count
        int64_t dim = shape.size(); // shape dim


        std::vector<int64_t> ips = offset; // initial positions
        std::vector<int64_t> idx(dim,0); // dimension index counters eg [0 , 0 , 0] -> [ 1 , 0 , 0]
        if (Size == 0) return ;

        for (int i = 0 ; i < Size ; i++) {
            f(ips); // apply the function f on the positions
            for (int d = dim-1 ; d >=0 ; --d) { // walk throught the dimensions
                for (int p = 0; p < n; p++) ips[p] += stride[p][d]; // incr the positions by applying stides
                if (++idx[d] < shape[d]) break; // if the idx counters reach max for current dim then reset dim so next outer dim can be walked
                idx[d] = 0;
                for (int p = 0; p < n; p++) ips[p] -= shape[d]*stride[p][d]; // reseting to walk outer dim
            }
        }
    }
}
#endif //PIRANHA_PIR_ITTERATOR_HPP
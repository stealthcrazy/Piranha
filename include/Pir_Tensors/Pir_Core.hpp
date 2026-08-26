//
// Created by Sohan Prabhu on 05/08/2026.
//

#pragma once
#include <vector>
#include "Pir_Storage.hpp"
#include "Pir_Iterator.hpp"
#include <numeric>
#include <functional>
#include <memory>
#include <algorithm>


#define TYPE_ENTRY_CASE(CTYPE,DTYPE,...)  \
    case DType::DTYPE :                            \
    {                                            \
    using concrete_type = CTYPE;                 \
    __VA_ARGS__();                               \
    break;                                       \
    }                                            \


namespace Piranha {

        class Core {
            friend class Tensor ;
        public:
            Core(std::shared_ptr<Storage> Storage_, std::vector<int64_t> Shape_, std::vector<int64_t> Stride_, DType Type_ , int64_t Offset_);
            Core(std::vector<int64_t> Shape_, DType Type_ );
            const std::vector<int64_t>&  shape() const {return Shape;}
            const std::vector<int64_t>&  stride() const {return Stride;}
            int64_t numelm() const {return Size;}
            int64_t dim() const {return static_cast<int64_t>(Shape.size());}
            DType type() const {return Type;}
            int64_t offset() const {return Offset;}
            static std::vector<int64_t> getContiguousStrides(std::vector<int64_t> &shape);
            std::shared_ptr<Storage> getStorage(){return CoreStorage;}
            bool is_contiguous() const;
            std::shared_ptr<Core> make_contiguous();
            void all(float t) ;
            void raw_dump();




        private:


            std::vector<int64_t> Shape;
            std::vector<int64_t> Stride;
            int64_t Offset = 0;
            int64_t Size = 0;
            DType Type = DType::Float32;
            std::shared_ptr<Storage> CoreStorage;
            bool contiguous;

        };


}

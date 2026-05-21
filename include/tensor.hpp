#ifndef PIRANHA_TENSOR_HPP
#define PIRANHA_TENSOR_HPP

#include <array>
#include <ostream>
#include <string>
#include <cassert>

namespace Piranha {
    template <typename T, size_t ... m>
    class Tensor {
        template <typename U, size_t ... M>
        class TensorCore {
            static constexpr int total = ( M*... );
            std::array<U,total > obj;
            TensorCore() = default;
            TensorCore(std::initializer_list<T> a) : obj{a.begin(),a.end(),obj.begin} {};
            TensorCore(TensorCore&& c) :obj{c.obj} {};
        };
        TensorCore<T,m...> *core;
    public:
        static  constexpr std::array<size_t, sizeof ...(m)> shape = {m...};
        Tensor() = default;
        Tensor(size_t&,std::initializer_list<T> t) {
            if (t.size()!= (m*... )) {
                std::cerr << ">> Mismatch when declaring Tensor ";
                exit(1);
            }
            *core(std::move(t));
        }
        Tensor(TensorCore<T,m...>&& C) : core{C} {};

        auto operator[](size_t index) {
            size_t pos;
            if ( index >= shape[index] ) {
                std::cerr << ">> Index Error " << index << " out of bounds for dim " << shape[index];
                exit(1);
            }

            return Tensor<T,>(core);
        }
        /*
        friend std::ostream& operator<<(std::ostream& os, const Tensor& t) {
            for (int i = 0; i<total;i++) {
                std::cout << core.obj[i] << ",";
            }
            return os;
        }*/
    };

} // namespace Piranha

#endif
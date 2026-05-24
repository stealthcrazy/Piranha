#ifndef PIRANHA_TENSOR_HPP
#define PIRANHA_TENSOR_HPP

#include <array>
#include <ostream>
#include <string>
#include <cassert>
#include <memory>

namespace Piranha {

    template <typename T, size_t m , size_t ... n > // Tensor class acts as proxy for access
    class Tensor {
        template <typename U, size_t ... M> // Tersor Core class -> stores the data in memory
        class TensorCore {
            friend class Tensor;
            static constexpr int total = ( M*... );
            std::array<T,total > obj;
            TensorCore() : obj{0} {}
            TensorCore(std::array<U,total> a) {
                std::copy(a.begin(),a.end(),obj.begin());
            }
            TensorCore(TensorCore&& c)  noexcept :obj{std::move(c.obj)} {};
            T* at(size_t i){return &obj[i];}
            T& valueAt(size_t i ){return obj[i];}

        };
        std::shared_ptr<TensorCore<T,m,n...>> core; // shared ptr for ref counting
        struct Data { // stores accessible data params for Proxy
            T* start;
            size_t depth;
            size_t stride;
        };
        Data c;
        Tensor(T* start, size_t dim , size_t stride, std::shared_ptr<TensorCore<T,m,n...>> C) : core{C} , c{start,dim,stride} {};
    public:
        static  constexpr std::array<size_t, sizeof ...(n)+1> shape = {m,n...};
        static constexpr int size = ( m*...*n );
        Tensor() : core{new TensorCore<T, m, n...>()}, c{core->at(0),  0 , size} {};
        Tensor(std::array<T,size> t): core{new TensorCore<T, m, n...>(t)} , c{core->at(0),  0 , size} {
            if (t.size()!= size) {
                std::cerr << "\n >> Mismatch when declaring Tensor " << std::endl;
                exit(1);
            }
        }
        ~Tensor(){} // destructor


        T& value() {return *c.start;}//returns value
        // start operators on Tensor

        Tensor operator[](size_t index) { // indexing operator
            size_t stride = c.stride/ shape[c.depth];
            if ( index >= shape[c.depth] ) {
                std::cerr << "\n>> Index Error " << index << " out of bounds for dim " << stride +1 << "For Piranha_Tensor@" << core.get() << std::endl;
                exit(1);
            }
            return Tensor((stride * index)+ c.start ,c.depth+1,stride,core); // creates new proxy with updated data
        }


        Tensor operator+(){}
        Tensor operator-(){}
        Tensor inv(){}
        Tensor operator*(){}
        Tensor dot(){}
        Tensor scale(){}
        Tensor reshape(){}
        Tensor transpose(){}

        // end  of operators

        Tensor arange(){}
        Tensor ones(){}
        Tensor diag(){}




        /*
        friend std::ostream& operator<<(std::ostream& os, const Tensor& t) {
            for (int i = 0; i<size;i++) {
                std::cout  << ",";
            }
            return os;
        }*/
    };

} // namespace Piranha

#endif
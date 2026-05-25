#ifndef PIRANHA_TENSOR_HPP
#define PIRANHA_TENSOR_HPP

#include <array>
#include <vector>
#include <ostream>
#include <string>
#include <cassert>
#include <memory>
#include <numeric>
#include <algorithm>

namespace Piranha {

    template <typename T> // Tensor Core class -> stores the data in memory
    class TensorCore {
    public: // make this protected
        std::vector<T> obj;
        TensorCore(std::vector<size_t> dims , std::vector<T> v) {
            const size_t size = std::accumulate(dims.begin(), dims.end(), 1, std::multiplies<size_t>());
            obj =v;
        }
        T* at(size_t i){return &obj[i];}
        T& valueAt(size_t i ){return obj[i];}

    };



    template <typename T> // Tensor class acts as proxy for access
    class Tensor {
        Tensor(T* start, size_t depth , size_t stride, std::shared_ptr<TensorCore<T>> C,std::vector<size_t> dims) : core{C} , c{start,depth,stride} {
            shape = dims;
        };
    public:
        std::shared_ptr<TensorCore<T>> core; // shared ptr for ref counting
        struct Data { // stores accessible data params for Proxy
            T* start;
            size_t depth;
            size_t stride;
        };
        Data c;
        std::vector<size_t> shape;
        size_t size;
        Tensor(std::vector<size_t> dims,  std::vector<T> t): core{new TensorCore<T>(dims,t)}{
            size = std::accumulate(dims.begin(),dims.end(),1,std::multiplies<size_t>());
            if (t.size()!= size) {
                std::cerr << "\n >> Mismatch when declaring Tensor " << std::endl;
                exit(1);
            }
            c = {core->at(0),  0 , size};
            shape = dims;
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

        template <typename U, size_t M , size_t ... N >
        Tensor operator+(Tensor<U> r) {
            if ( ! [](std::is_same<T,U> t){}) {
                std::cerr << "Type Mismatch";
            }
            if (!(std::equal(shape.begin(),shape.end(),r.shape.begin()) & (c.depth == r.c.depth) &  (c.stride == r.c.stride))) {
                std::cerr << "Mismatch in dimensions for Add";
                exit(1);
            }
            std::array<T,c.stride> buff{0};
            for (int i = 0; i< c.stride ; i++ ) {
                buff[i] = core.at(i) + r.core.at(i);
            }

            return Tensor<T>();
        }
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
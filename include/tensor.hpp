#ifndef PIRANHA_TENSOR_HPP
#define PIRANHA_TENSOR_HPP

#include <array>
#include <vector>
#include <ostream>
#include <string>
#include <cassert>
#include <numeric>
#include <algorithm>

namespace Piranha {

    template <typename T> // Tensor Core class -> stores the data in memory
    class TensorCore {
    public: // make this protected
        std::vector<T> obj;
        TensorCore(std::vector<size_t> dims , std::vector<T> v) {
            const size_t size = std::accumulate(dims.begin(), dims.end(), 1, std::multiplies<size_t>());
            obj = std::move(v);
        }
        T* at(size_t i){return &obj[i];}
        T& valueAt(size_t i ){return obj[i];}

    };



    template <typename T> // Tensor class acts as proxy for access
    class Tensor {
        Tensor(T* start,
            size_t stride,
            std::shared_ptr<TensorCore<T>> C,
            std::vector<size_t> dims)
        : core{C} , c{start,stride} {
            shape = dims;
            shape.erase(shape.begin());
            size = std::accumulate(dims.begin(),dims.end(),1,std::multiplies<size_t>());

        };

        std::vector<T> mult(Tensor a , Tensor b) {
            std::vector<T> buff;
            for (int i = 0; i < a.shape[0] ; i++) {
                for (int j = 0; j < b.shape[1]; j++) {
                    T p = 0 ;
                    for  (int k = 0 ; k < b.shape[0]; k++) {
                        p += *a.core->at( i*a.shape[0] + k) * *b.core->at(k*b.shape[0] + j);
                    }
                    buff.push_back(p);
                }
            }
            return buff;
        }
    public:
        std::shared_ptr<TensorCore<T>> core; // shared ptr for ref counting
        struct Data { // stores accessible data params for Proxy
            T* start;
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
            c = {core->at(0), size};
            shape = dims;
        }
        ~Tensor(){} // destructor


        T& value() {return *c.start;}//returns value
        // start operators on Tensor


        Tensor operator[](size_t index) { // indexing operator
            size_t stride = c.stride/ shape.at(0);
            if ( index >= shape.at(0) ) {
                std::cerr << "\n>> Index Error" << index << " out of bounds for dim " << stride +1 << " For Piranha_Tensor@" << core.get() << std::endl;
                exit(1);
            }
            return Tensor((stride * index)+ c.start ,stride,core,shape); // creates new proxy with updated data
        }

        Tensor operator+(Tensor r) {
            if (!(std::equal(shape.begin(),shape.end(),r.shape.begin())  &  (c.stride == r.c.stride))) {
                std::cerr << "Mismatch in dimensions for Add";
                exit(1);
            }
            std::vector<T> buff(c.stride);
            for (int i = 0; i< c.stride ; i++ ) {
                buff.push_back(*(core->at(i)) + *(r.core->at(i)));
            }
            return Tensor<T>(shape,buff);
        }
        Tensor operator-(Tensor r) {
            if (!(std::equal(shape.begin(),shape.end(),r.shape.begin())  &  (c.stride == r.c.stride))) {
                std::cerr << "Mismatch in dimensions for Sub";
                exit(1);
            }
            std::vector<T> buff(c.stride);
            for (int i = 0; i< c.stride ; i++ ) {
                buff.push_back(*(core->at(i)) - *(r.core->at(i)));
            }
            return Tensor<T>(shape,buff);
        }

        Tensor operator*(Tensor r) {
            if (!(std::equal(shape.begin(),shape.end(),r.shape.begin())  &  (c.stride == r.c.stride))) {
                std::cerr << "Mismatch in dimensions for Element-wise Multiplication";
                exit(1);
            }
            std::vector<T> buff(c.stride);
            for (int i = 0; i< c.stride ; i++ ) {
                buff.push_back(*(core->at(i)) * *(r.core->at(i)));
            }
            return Tensor<T>(shape,buff);
        }

        Tensor operator&(Tensor r){ // currently supports 2D & 3D tensors only ( Matmul )
            if (!(std::equal(shape.begin(),shape.end(),r.shape.begin())  &  (c.stride == r.c.stride))) { // needs fixes as in only hard coded to 2D
                std::cerr << "Mismatch in dimensions ";
                exit(1);
            }

            std::vector<size_t> s = shape;
            s[s.size()-2] = r.shape[s.size()-1];
            std::vector<T> buff;
            for (int i  = 0 ; i < 1 ; i++) { // needs fixes as in only hard coded to 2D
                std::vector<T> temp = mult((*this)[i] ,r[i] );
                buff.insert(buff.begin(),std::make_move_iterator(temp.begin()),std::make_move_iterator(temp.end()) );
            }

            return Tensor<T>(s,buff);
        }

        Tensor scale(){}
        Tensor reshape(){}
        Tensor transpose(){}

        // end  of operators

        static Tensor arrange(std::vector<size_t> dims, size_t start , size_t end) {
            size_t size = std::accumulate(dims.begin(),dims.end(),1,std::multiplies<size_t>());
            if (size != end-start) {
                std::cerr << "Hmm !! "; // please change to better debug message
                exit(1);
            }
            std::vector<T> buff;
            for ( int i = 0 ; i < size ; i++ ) {
                buff.push_back(i+start);
            }
            return Tensor(dims,buff);
        }
        static Tensor all(std::vector<size_t> dims, T s) {
                size_t size = std::accumulate(dims.begin(),dims.end(),1,std::multiplies<size_t>());
                std::vector<T> buff;
                for ( int i = 0 ; i < size ; i++ ) {
                    buff.push_back(s);
                }
                return Tensor(dims,buff);
        }
        static Tensor ones(std::vector<size_t> dims){ return Tensor::all(std::move(dims),1);}
        static Tensor zeros(std::vector<size_t> dims){ return Tensor::all(std::move(dims),0);}

        static Tensor diag(std::vector<size_t> dims, T s) {
            size_t size = std::accumulate(dims.begin(),dims.end(),1,std::multiplies<size_t>());
            std::vector<T> buff;
            size_t ndm = dims.size();
            size_t m = dims[ndm-2];
            size_t n = dims[ndm-1];
            for ( int i = 0 ; i < size / (m*n); i++ ) {
                for (int j = 0; j < m; j++) {
                    for (int k = 0; k < n; k++) {
                        if (j == k) {
                            buff.push_back(s);
                        }else {
                            buff.push_back(0);
                        }
                    }
                }
            }
            return Tensor(dims,buff);

        }



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
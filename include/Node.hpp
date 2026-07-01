//
// Created by sohan on 6/2/2026.
//

#ifndef PIRANHA_NODE_H
#define PIRANHA_NODE_H


#include "tensor.hpp"
#include <vector>
#include <ostream>
#include <string>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <memory>
#include <unordered_map>

namespace Piranha{
    template <typename  T>
    class Node {
    public :
        virtual ~Node() = default;
        std::vector<Node<T>> Edges; // Outgoing Edges to  Nodes
        size_t topo_nr = 0; // topological Number for Queue
        //example   for Y = A # B where # is the node operator  A : ∂Y/∂A  and B : ∂Y/∂B are calculated
        virtual void apply_grad(){}; // Applying Gradient Calc to Tensors

    };

    template <typename T>
    class AddN : public Node<T> {
    public:
        std::weak_ptr<Tensor<T>> A;
        std::weak_ptr<Tensor<T>> B;
        AddN(
            std::vector<Node<T>> E,
            std::weak_ptr<Tensor<T>> a,
            std::weak_ptr<Tensor<T>> b
            ) {
            A = a;
            B = b;
            this->Edges = std::move(E);
        }
        void apply_grad(Tensor<T> S ){
            auto As = A.lock();
            auto Bs = B.lock();
            As.get()->grad = std::make_shared<Tensor<T>>(S);
            Bs.get()->grad = std::make_shared<Tensor<T>>( S);
        };

    };

    template <typename T>
    class MultN : public Node<T> {
    public:
        std::weak_ptr<Tensor<T>> A;
        std::weak_ptr<Tensor<T>> B;
        MultN(
            std::vector<Node<T>> E,
            std::weak_ptr<Tensor<T>> a,
            std::weak_ptr<Tensor<T>> b
            )  {
            A = a;
            B = b;
            this->Edges = std::move(E);
        }
        void apply_grad(Tensor<T> S ){
            auto As = A.lock();
            auto Bs = B.lock();
            As.get()->grad = std::make_shared<Tensor<T>>(S & Bs.get()->transpose());
            Bs.get()->grad = std::make_shared<Tensor<T>>( As.get()->transpose() & S );
        };

    };




}





#endif //PIRANHA_NODE_H
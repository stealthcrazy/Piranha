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
        size_t in_nr = 0; // incoming edge count
        std::unordered_map<std::weak_ptr<Tensor<T>>,Tensor<T>> gradMap; // stores Tensor and Associated Gradient for Operation
        //example   for Y = A # B where # is the node operator  A : ∂Y/∂A  and B : ∂Y/∂B are stored in Map
        virtual void apply_grad(){}; // Applying Gradient Calc to Tensors

    };

    template <typename T>
    class AddN : public Node<T> {
    public:
        AddN(
            std::vector<Node<T>> E,
            std::weak_ptr<Tensor<T>> a,
            std::weak_ptr<Tensor<T>> b
            ) {
            this->gradMap = {{a,nullptr},{b,nullptr}};
            this->Edges = std::move(E);
        }
        void apply_grad() override{};

    };

    template <typename T>
    class MultN : public Node<T> {
    public:
        MultN(
            std::vector<Node<T>> E,
            std::weak_ptr<Tensor<T>> a,
            std::weak_ptr<Tensor<T>> b
            )  {
            this->gradMap = {{a,nullptr},{b,nullptr}};
            this->Edges = std::move(E);
        }
        void apply_grad(Tensor<T> S ){


        };

    };




}





#endif //PIRANHA_NODE_H
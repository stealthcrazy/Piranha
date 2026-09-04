//
// Created by Sohan Prabhu on 04/08/2026.
//

#pragma once

#include <cstdlib>
#include <new>

#include "Pir_DTypes.hpp"

namespace Piranha {
    // Storage Backbone of Tensor
    class Storage {
    public:
        explicit Storage(int64_t nbytes) : bytes(nbytes) {
            storage_buffer = malloc(bytes); // allocates bytes
            if (storage_buffer == nullptr){ throw std::bad_alloc();}
        }
        ~Storage() {free(storage_buffer);} // destructor for freeing
        Storage(const Storage& ) = delete; // no copy
        Storage& operator=(const Storage&) = delete; // no copy assignment

        void* data();
        int64_t getBytes();

    private:
        int64_t bytes = 0;
        void* storage_buffer = nullptr;

    };





}
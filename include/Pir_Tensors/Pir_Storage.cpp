//
// Created by Sohan Prabhu on 07/08/2026.
//
#include "Pir_Storage.hpp"

void * Piranha::Storage::data() {
    return storage_buffer;
}

int64_t Piranha::Storage::getBytes() {
    return bytes;
}

//
// Created by Sohan Prabhu on 03/08/2026.
//
#pragma once
#include <cstdint>

// MACRO  definition for all supported types
#define FORALL_PIR_DTYPES(X) \
    X(uint8_t , UInt8) \
    X(uint32_t, UInt32) \
    X(uint64_t, UInt64) \
    X(float, Float32) \
    X(double, Float64) \




namespace Piranha {


    // defining Enum entries for data types
    #define MAKE_ENTRY(CTYPE,NAME) NAME,
    enum class DType : uint8_t {
       FORALL_PIR_DTYPES(MAKE_ENTRY)
    };
    #undef MAKE_ENTRY

    // case matching Macro
    #define GET_SIZE_OF_ENTRY(CTYPE,NAME) case DType::NAME : return sizeof(CTYPE);
    inline int64_t itemSize(DType d) {
        switch (d) {
            FORALL_PIR_DTYPES(GET_SIZE_OF_ENTRY)
        }

        return 0;
    }
    #undef GET_SIZE_OF_ENTRY


}







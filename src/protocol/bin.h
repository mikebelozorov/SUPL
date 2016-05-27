#ifndef BIN_H
#define BIN_H

#include "stdint.h"

#define MAX_SAT     33  // maximum number of prns - max prn is 32 plus prn 0 is 33

// define macro to pack structures correctly with both GCC and MSVC compilers
#ifdef _MSC_VER // using MSVC
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#endif

PACK(
        struct EphemSF
        {
            uint32_t W[8];                // Words 3-10 of Subframes
        });

PACK(
        struct EphemSV
        {
            uint32_t HOW;                // Hand Over Word
            struct EphemSF SF[3];                // Subframes
        });


PACK(
        struct AlmSV
        {
            uint32_t number_week;                // Issue date of Almanac
            uint32_t words[8];            // Words 3-10 of Almanac data for an SV
        });

// Holds Almanac data for all SVs
PACK(
        struct BinAlmanac
        {
            struct AlmSV almsv[MAX_SAT];
        });

PACK(
        struct BinProtocol
        {
            int32_t lat;
            int32_t lon;
            uint32_t position_accuracy;
            uint32_t number_week;
            uint32_t time_of_week;
            uint64_t EphemMask;
            struct BinAlmanac almanac;
        }
);
#endif

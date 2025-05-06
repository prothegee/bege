#ifndef BEGE_BASE_HH
#define BEGE_BASE_HH
#include <cstdint>
#include <vector>

// alias for float as in 32 bits
using float32_t = float;

// alias for double as in 64 bits
using float64_t = double;

/// no int128_t & float128_t, for now

// alias for std::vector<unsigned char> as buffer type
using buffer_t = std::vector<unsigned char>;

// alias for unsigned char
using uchr_t = unsigned char;

#if defined(__GNUC__) || defined(__clang__)
    #define DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
    #define DEPRECATED(msg) __declspec(deprecated(msg))
#else
    #define DEPRECATED(msg)
#endif

#endif // BEGE_BASE_HH

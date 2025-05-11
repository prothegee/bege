#ifndef BEGE_BASE_HH
#define BEGE_BASE_HH
#include <cstdint>
#include <string>
#include <vector>

// alias for char
using chr_t = char;

// alias for bool
using bool_t = bool;

// alias for unsigned char
using uchr_t = unsigned char;

// alias for void type
using void_t = void;

// alias for float as in 32 bits
using float32_t = float;

// alias for double as in 64 bits
using float64_t = double;

/// no int128_t & float128_t, for now

// alias for std::vector<unsigned char> as buffer type
using buffer_t = std::vector<unsigned char>;

#if defined(__GNUC__) || defined(__clang__)
#ifndef DEPRECATED
#define DEPRECATED(msg) __attribute__((deprecated(msg)))
#endif // DEPRECATED

#ifndef PRAGMA_MESSAGE_IMPL
#ifndef PRAGMA_MESSAGE
#define PRAGMA_MESSAGE_IMPL(str) _Pragma(#str)
// compiler independetn message
#define PRAGMA_MESSAGE(msg) PRAGMA_MESSAGE_IMPL(message msg)
#endif // PRAGMA_MESSAGE
#endif // PRAGMA_MESSAGE_IMPL
#elif defined(_MSC_VER)
#ifndef DEPRECATED
#define DEPRECATED(msg) __declspec(deprecated(msg))
#endif // DEPRECATED

#ifndef PRAGMA_MESSAGE
// compiler independetn message
#define PRAGMA_MESSAGE(msg) __pragma(message(msg))
#endif // PRAGMA_MESSAGE
#else
// n/a
#endif

#ifndef INLNSTTC
#define INLNSTTC inline static
#endif // INLNSTTC

#ifndef INLNSTTCCNST
#define INLNSTTCCNST inline static const
#endif // INLNSTTCCNST

#endif // BEGE_BASE_HH

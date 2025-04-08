#ifndef YSTDLIB_WRAPPED_FACADE_HEADERS_BITS_TYPES_TIME_T_HPP
#define YSTDLIB_WRAPPED_FACADE_HEADERS_BITS_TYPES_TIME_T_HPP

// clang-format off
// IWYU pragma: begin_exports
#if defined(__linux__)
#include <bits/types/time_t.h>
#elif defined(__APPLE__)
#include <sys/_types/_time_t.h>
#endif
// IWYU pragma: end_exports
// clang-format on

#endif  // YSTDLIB_WRAPPED_FACADE_HEADERS_BITS_TYPES_TIME_T_HPP

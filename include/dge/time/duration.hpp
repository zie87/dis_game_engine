#ifndef DGE_TIME_DURATION_HPP
#define DGE_TIME_DURATION_HPP

#include <chrono>

namespace dge {

template <typename R, typename P = std::ratio<1>>
using duration = std::chrono::duration<R, P>;

using nanoseconds  = std::chrono::nanoseconds;
using microseconds = std::chrono::microseconds;
using milliseconds = std::chrono::milliseconds;
using seconds      = std::chrono::seconds;
using minutes      = std::chrono::minutes;
using hours        = std::chrono::hours;

}  // namespace dge

#endif  // DGE_TIME_DURATION_HPP

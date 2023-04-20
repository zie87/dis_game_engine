#ifndef DGE_PLATFORM_PS2_THREAD_SLEEP_HPP
#define DGE_PLATFORM_PS2_THREAD_SLEEP_HPP

#include "dge/platform/config.hpp"
#include "dge/time/duration.hpp"

#include <chrono>

#include <timer.h>

namespace dge::detail {

constexpr ::timespec to_timespec(dge::nanoseconds dur) noexcept {
    const auto secs = std::chrono::duration_cast<dge::seconds>(dur);
    dur -= secs;

    return ::timespec{secs.count(), dur.count()};
}

inline void sleep_for_us(pf_tag_ps2, const dge::microseconds sleep_duration) noexcept {
    const auto time = to_timespec(sleep_duration);
    ::nanosleep(&time, nullptr);
}

}  // namespace dge::detail
#endif  // DGE_PLATFORM_PS2_THREAD_SLEEP_HPP

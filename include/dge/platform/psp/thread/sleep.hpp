#ifndef DGE_PLATFORM_PSP_THREAD_SLEEP_HPP
#define DGE_PLATFORM_PSP_THREAD_SLEEP_HPP

#include "dge/platform/config.hpp"
#include "dge/time/duration.hpp"

#include <pspthreadman.h>

namespace dge::detail {

inline void sleep_for_us(pf_tag_psp, const dge::microseconds sleep_duration) noexcept {
    ::sceKernelDelayThread(sleep_duration.count());
}

}  // namespace dge::detail
#endif  // DGE_PLATFORM_PSP_THREAD_SLEEP_HPP

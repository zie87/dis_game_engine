#ifndef DGE_PLATFORM_PSP_THREAD_THREAD_CFG_HPP
#define DGE_PLATFORM_PSP_THREAD_THREAD_CFG_HPP

#include <pspthreadman.h>

#include "dge/platform/base/thread/thread_traits.hpp"
#include "dge/platform/config.hpp"
#include "dge/thread/thread_priority.hpp"

namespace dge::psp {
using thread_priority_t = int;

namespace detail {
static constexpr thread_priority_t thread_prio_low      = 0x6f;
static constexpr thread_priority_t thread_prio_normal   = 0x32;
static constexpr thread_priority_t thread_prio_high     = 0x20;
static constexpr thread_priority_t thread_prio_critical = 0x10;
}  // namespace detail

struct thread_cfg {
    const char* name                = "dge thread";
    thread_priority_t priority      = detail::thread_prio_normal;
    int stack_size                  = 0x8000;
    SceUInt attributes              = PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU;
    SceKernelThreadOptParam* option = nullptr;
};
}  // namespace dge::psp

namespace dge {
[[nodiscard]] inline constexpr auto to_pf_type(pf_tag_psp, thread_priority prio) noexcept -> psp::thread_priority_t {
    switch (prio) {
    case thread_priority::low:
        return psp::detail::thread_prio_low;
    case thread_priority::normal:
        return psp::detail::thread_prio_normal;
    case thread_priority::high:
        return psp::detail::thread_prio_high;
    }
}
}  // namespace dge

namespace dge::traits {
template <>
struct thread_config<::dge::pf_tag_psp> {
    using type = ::dge::psp::thread_cfg;
};
}  // namespace dge::traits

#endif  // DGE_PLATFORM_PSP_THREAD_THREAD_CFG_HPP

#ifndef DGE_PLATFORM_PS2_THREAD_THREAD_CFG_HPP
#define DGE_PLATFORM_PS2_THREAD_THREAD_CFG_HPP

#include "dge/platform/base/thread/thread_traits.hpp"
#include "dge/platform/config.hpp"
#include "dge/thread/thread_priority.hpp"

#include <kernel.h>

namespace dge::ps2 {
using thread_priority_t = int;

namespace detail {
static constexpr thread_priority_t thread_prio_low      = 0x6f;
static constexpr thread_priority_t thread_prio_normal   = 0x32;
static constexpr thread_priority_t thread_prio_high     = 0x20;
static constexpr thread_priority_t thread_prio_critical = 0x10;
}  // namespace detail

struct thread_cfg {
    const char* name           = "dge thread";
    thread_priority_t priority = detail::thread_prio_normal;
    int stack_size             = 0x1800;
    ::u32 attributes           = 0;
};
}  // namespace dge::ps2

namespace dge {
[[nodiscard]] inline constexpr auto to_pf_type(pf_tag_ps2, thread_priority prio) noexcept -> ps2::thread_priority_t {
    switch (prio) {
    case thread_priority::low:
        return ps2::detail::thread_prio_low;
    case thread_priority::normal:
        return ps2::detail::thread_prio_normal;
    case thread_priority::high:
        return ps2::detail::thread_prio_high;
    }
}
}  // namespace dge

namespace dge::traits {
template <>
struct thread_config<::dge::pf_tag_ps2> {
    using type = ::dge::ps2::thread_cfg;
};
}  // namespace dge::traits

#endif  // DGE_PLATFORM_PSP_THREAD_THREAD_CFG_HPP

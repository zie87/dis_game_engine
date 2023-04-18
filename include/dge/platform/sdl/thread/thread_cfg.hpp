#ifndef DGE_PLATFORM_SDL_THREAD_THREAD_CFG_HPP
#define DGE_PLATFORM_SDL_THREAD_THREAD_CFG_HPP

#include <SDL_thread.h>

#include "dge/platform/base/thread/thread_traits.hpp"
#include "dge/platform/config.hpp"
#include "dge/thread/thread_priority.hpp"

namespace dge::sdl {

using thread_priority_t = SDL_ThreadPriority;

namespace detail {
static constexpr thread_priority_t thread_prio_low    = SDL_THREAD_PRIORITY_LOW;
static constexpr thread_priority_t thread_prio_normal = SDL_THREAD_PRIORITY_NORMAL;
static constexpr thread_priority_t thread_prio_high   = SDL_THREAD_PRIORITY_HIGH;
}  // namespace detail

struct thread_cfg {
    const char* name           = "dge thread";
    thread_priority_t priority = detail::thread_prio_normal;
    size_t stack_size          = 0x00;
};
}  // namespace dge::sdl

namespace dge {
[[nodiscard]] inline constexpr auto to_pf_type(pf_tag_sdl, thread_priority prio) noexcept -> sdl::thread_priority_t {
    switch (prio) {
    case thread_priority::low:
        return sdl::detail::thread_prio_low;
    case thread_priority::normal:
        return sdl::detail::thread_prio_normal;
    case thread_priority::high:
        return sdl::detail::thread_prio_high;
    }
}
}  // namespace dge

namespace dge::traits {
template <>
struct thread_config<::dge::pf_tag_sdl> {
    using type = ::dge::sdl::thread_cfg;
};
}  // namespace dge::traits

#endif  // DGE_PLATFORM_PSP_THREAD_THREAD_CFG_HPP

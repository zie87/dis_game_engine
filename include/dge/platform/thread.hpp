#ifndef DEG_PLATFORM_THREAD_HPP
#define DEG_PLATFORM_THREAD_HPP

#include "dge/platform/config.hpp"

#if defined(DGE_PLATFORM_PSP)
#include "dge/platform/psp/thread/thread_cfg.hpp"
#include "dge/platform/psp/thread/thread_policy.hpp"
#include "dge/platform/psp/thread/sleep.hpp"
#elif defined(DGE_PLATFORM_SDL)
#include "dge/platform/sdl/thread/thread_cfg.hpp"
#include "dge/platform/sdl/thread/thread_policy.hpp"
#include "dge/platform/sdl/thread/sleep.hpp"
#endif

#include "dge/platform/base/thread/thread_traits.hpp"
#include "dge/platform/base/thread/base_thread.hpp"

#include "dge/time/duration.hpp"

namespace dge {
using thread_cfg = ::dge::traits::thread_config_t<pf_tag_default>;
using thread     = detail::base_thread<pf_tag_default>;

namespace detail {
inline void sleep_for_us(dge::microseconds time) noexcept { sleep_for_us(pf_tag_default{}, time); }
}  // namespace detail

}  // namespace dge

#endif  // DEG_PLATFORM_THREAD_HPP

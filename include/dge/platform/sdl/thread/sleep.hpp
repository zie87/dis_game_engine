#ifndef DGE_PLATFORM_SDL_THREAD_SLEEP_HPP
#define DGE_PLATFORM_SDL_THREAD_SLEEP_HPP

#include "dge/platform/config.hpp"
#include "dge/time/duration.hpp"

#include <SDL_timer.h>

namespace dge::detail {

inline void sleep_for_us(pf_tag_sdl, const dge::microseconds sleep_duration) noexcept {
    const auto time_ms = std::chrono::duration_cast<dge::milliseconds>(sleep_duration);
    SDL_Delay(time_ms.count());
}

}  // namespace dge::detail
#endif  // DGE_PLATFORM_SDL_THREAD_SLEEP_HPP

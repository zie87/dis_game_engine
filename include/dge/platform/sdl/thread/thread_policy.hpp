#ifndef DGE_PLATFORM_SDL_THREAD_THREAD_POLICY_HPP
#define DGE_PLATFORM_SDL_THREAD_THREAD_POLICY_HPP

#include "dge/platform/base/thread/thread_traits.hpp"
#include "dge/platform/base/thread/thread_proxy.hpp"
#include "dge/platform/sdl/thread/thread_cfg.hpp"
#include "dge/memory/shared_ptr.hpp"

#include <SDL_thread.h>

#include <functional>

namespace dge::traits {
template <>
struct thread_native<::dge::pf_tag_sdl> {
    using type = SDL_Thread*;
};

template <>
struct thread_invalid<::dge::pf_tag_sdl> {
    using type = thread_native_t<::dge::pf_tag_sdl>;

    static constexpr type value = nullptr;
};

}  // namespace dge::traits

namespace dge::sdl {

struct thread_policy {
    using tag_type           = ::dge::pf_tag_sdl;
    using native_handle_type = typename ::dge::traits::thread_native_t<tag_type>;
    using config_type        = typename ::dge::traits::thread_config_t<tag_type>;

    template <typename FUNC_T, typename... ARG_Ts>
    static inline bool create_and_run(const config_type& cfg,
                                      native_handle_type& handle,
                                      FUNC_T&& func,
                                      ARG_Ts&&... args) {
        auto thread_proxy_ptr = ::dge::detail::make_thread_proxy(std::bind(std::forward<FUNC_T>(func), std::forward<ARG_Ts>(args)...));
        return create_thread(cfg, handle, thread_proxy_ptr);
    }

    static inline bool is_joinable(const native_handle_type& handle) noexcept {
        return (handle != ::dge::traits::thread_invalid_v<tag_type>);
    }

    static void join(native_handle_type& handle) noexcept;
    static void detach(native_handle_type& handle) noexcept;

    static unsigned hardware_concurrency() noexcept;

private:
    static bool create_thread(const config_type& cfg,
                              native_handle_type& handle,
                              ::dge::detail::shared_thread_proxy_type thread_proxy_ptr) noexcept;
};

}  // namespace dge::sdl

namespace dge::traits {
template <>
struct thread_policy<::dge::pf_tag_sdl> {
    using type = ::dge::sdl::thread_policy;
};

}  // namespace dge::traits

#endif  // DGE_PLATFORM_SDL_THREAD_THREAD_POLICY_HPP

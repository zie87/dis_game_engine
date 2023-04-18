#include "dge/platform/sdl/thread/thread_policy.hpp"

#if !defined(DGE_PLATFORM_SDL)
#error "sdl thread can only be used for SDL2 builds!"
#endif

#include <SDL_cpuinfo.h>
#include <SDL_thread.h>

namespace dge::sdl {

namespace {

static int execute_thread_routine(void* funct_ptr) {
    auto* base_ptr = static_cast<::dge::detail::thread_proxy_base*>(funct_ptr);

    ::dge::detail::shared_thread_proxy_type local_ptr;
    local_ptr.swap(base_ptr->m_this_ptr);

    local_ptr->run();
    return 0;
}

}  // namespace

bool thread_policy::create_thread(const config_type& cfg,
                                  native_handle_type& handle,
                                  ::dge::detail::shared_thread_proxy_type proxy_ptr) noexcept {
    proxy_ptr->m_this_ptr = proxy_ptr;
    auto* thread = SDL_CreateThreadWithStackSize(execute_thread_routine, cfg.name, cfg.stack_size, proxy_ptr.get());
    if (thread == nullptr) {
        return false;
    }
    handle = thread;
    return true;
}

void thread_policy::join(native_handle_type& handle) noexcept { SDL_WaitThread(handle, nullptr); }
void thread_policy::detach(native_handle_type& handle) noexcept { SDL_DetachThread(handle); }

unsigned thread_policy::hardware_concurrency() noexcept {
    const auto cnt = SDL_GetCPUCount();
    if (cnt < 1) {
        return 1;
    }
    return static_cast<unsigned int>(cnt);
}

}  // namespace dge::sdl

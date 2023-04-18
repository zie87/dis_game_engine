#include "dge/platform/psp/thread/thread_policy.hpp"

#if !defined(DGE_PLATFORM_PSP)
#error "psp thread can only be used for psp!"
#endif

#include <pspthreadman.h>

namespace dge::psp {

namespace {

static int execute_thread_routine([[maybe_unused]] ::SceSize arg_size, void* funct_ptr) {
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

    const auto id = ::sceKernelCreateThread(cfg.name, execute_thread_routine, cfg.priority, cfg.stack_size,
                                            cfg.attributes, cfg.option);
    if (id <= 0) {
        return false;
    }

    const int error_code = ::sceKernelStartThread(id, sizeof(::dge::detail::shared_thread_proxy_type), proxy_ptr.get());
    if (error_code < 0) {
        proxy_ptr->m_this_ptr.reset();
        return false;
    }

    handle = id;
    return true;
}

void thread_policy::join(native_handle_type& handle) noexcept {
    ::sceKernelWaitThreadEnd(handle, nullptr);
    ::sceKernelDeleteThread(handle);
}

void thread_policy::detach(native_handle_type& handle) noexcept { ::sceKernelDeleteThread(handle); }

}  // namespace dge::psp

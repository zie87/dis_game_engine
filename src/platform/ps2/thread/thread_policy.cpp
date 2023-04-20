#include "dge/platform/ps2/thread/thread_policy.hpp"
#include "dge/platform/ps2/thread/sleep.hpp"

#if !defined(DGE_PLATFORM_PS2)
#error "ps2 thread can only be used for ps2!"
#endif

#include <kernel.h>

namespace dge::ps2 {

namespace {

static int execute_thread_routine(void* funct_ptr) {
    auto* base_ptr = static_cast<::dge::detail::thread_proxy_base*>(funct_ptr);

    ::dge::detail::shared_thread_proxy_type local_ptr;
    local_ptr.swap(base_ptr->m_this_ptr);

    local_ptr->run();
    return 0;
}

inline void cleanup_thread(::s32 handle) noexcept {
    ::ee_thread_status_t status{};
    const auto ret = ReferThreadStatus(handle, &status);

    ::ReleaseWaitThread(handle);
    ::TerminateThread(handle);
    ::DeleteThread(handle);

    if (ret > 0) {
        free(status.stack);
    }
}

inline ::ee_thread_t to_ee_thread_t(const thread_cfg& cfg) noexcept {
    ::ee_thread_t ee_cfg{};

    ee_cfg.attr             = cfg.attributes;
    ee_cfg.option           = 0;
    ee_cfg.func             = reinterpret_cast<void*>(&execute_thread_routine);
    ee_cfg.stack            = std::malloc(cfg.stack_size);
    ee_cfg.stack_size       = cfg.stack_size;
    ee_cfg.gp_reg           = &_gp;
    ee_cfg.initial_priority = cfg.priority;

    return ee_cfg;
}

}  // namespace

bool thread_policy::create_thread(const config_type& cfg,
                                  native_handle_type& handle,
                                  ::dge::detail::shared_thread_proxy_type proxy_ptr) noexcept {
    proxy_ptr->m_this_ptr = proxy_ptr;

    auto ee_cfg   = to_ee_thread_t(cfg);
    const auto id = ::CreateThread(&ee_cfg);

    if (id < 0) {
        return false;
    }

    const auto error_code = ::StartThread(id, proxy_ptr.get());
    if (error_code < 0) {
        proxy_ptr->m_this_ptr.reset();
        return false;
    }

    handle = id;
    return true;
}

bool thread_policy::is_joinable(const native_handle_type& handle) noexcept {
    ::ee_thread_status_t thread_status{};
    ::ReferThreadStatus(handle, &thread_status);
    return (handle > 0) && (thread_status.status != THS_DORMANT);
}

void thread_policy::join(native_handle_type& handle) noexcept {
    constexpr auto sleep_time = dge::milliseconds(10);
    while (dge::ps2::thread_policy::is_joinable(handle)) {
        dge::detail::sleep_for_us(pf_tag_ps2{}, sleep_time);
    };
    cleanup_thread(handle);
}

void thread_policy::detach([[maybe_unused]] native_handle_type& handle) noexcept {
    // TODO: currently this will do nothing but we will create a mem leak as
    // soon as the thread is finsihed
}

}  // namespace dge::ps2

#ifndef DGE_PLATFORM_BASE_THREAD_THREAD_PROXY_HPP
#define DGE_PLATFORM_BASE_THREAD_THREAD_PROXY_HPP

#include "dge/memory/shared_ptr.hpp"

namespace dge::detail {
struct thread_proxy_base;
using shared_thread_proxy_type = dge::shared_ptr<thread_proxy_base>;

struct thread_proxy_base {
    inline virtual ~thread_proxy_base() = default;
    virtual void run()                  = 0;

    shared_thread_proxy_type m_this_ptr;
};

template <typename FUNC_T>
struct thread_proxy : public thread_proxy_base {
    FUNC_T function_obj;
    thread_proxy(FUNC_T&& func) : function_obj(std::forward<FUNC_T>(func)) {}
    void run() override { function_obj(); }
};

template <typename FUNC_T>
inline auto make_thread_proxy(FUNC_T&& func) -> dge::shared_ptr<thread_proxy<FUNC_T>> {
    return dge::make_shared<thread_proxy<FUNC_T>>(std::forward<FUNC_T>(func));
}

}  // namespace dge::detail

#endif  // DGE_PLATFORM_BASE_THREAD_THREAD_PROXY_HPP

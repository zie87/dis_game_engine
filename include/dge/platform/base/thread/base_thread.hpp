#ifndef DGE_PLATFORM_BASE_THREAD_BASE_THREAD_HPP
#define DGE_PLATFORM_BASE_THREAD_BASE_THREAD_HPP

#include "dge/platform/base/thread/thread_traits.hpp"

#include <exception>

namespace dge::detail {

template <typename TAG_T>
class base_thread {
public:
    // TODO: thread id is missing
    using tag_type    = TAG_T;
    using policy_type = typename ::dge::traits::thread_policy_t<tag_type>;
    using config_type = typename ::dge::traits::thread_config_t<tag_type>;

    using native_handle_type = typename ::dge::traits::thread_native_t<tag_type>;

    static constexpr native_handle_type invalid = ::dge::traits::thread_invalid_v<TAG_T>;

    base_thread() noexcept : m_thread(invalid) {}

    template <typename FUNC_T, typename... ARG_Ts>
    explicit base_thread(FUNC_T&& func, ARG_Ts&&... args) {
        [[maybe_unused]] const auto result = policy_type::template create_and_run(
            config_type{}, m_thread, std::forward<FUNC_T>(func), std::forward<ARG_Ts>(args)...);
        // TODO: error handling
    }

    template <typename FUNC_T, typename... ARG_Ts>
    explicit base_thread(const config_type& cfg, FUNC_T&& func, ARG_Ts&&... args) {
        [[maybe_unused]] const auto result = policy_type::template create_and_run(
            cfg, m_thread, std::forward<FUNC_T>(func), std::forward<ARG_Ts>(args)...);
        // TODO: error handling
    }

    ~base_thread() {
        if (joinable()) {
            // TODO: replace with a better assertion
            std::terminate();
        }
    }
    base_thread(base_thread&& other) noexcept : m_thread(other.m_thread) { other.m_thread = invalid; }

    inline base_thread& operator=(base_thread&& other) noexcept {
        if (joinable()) {
            // TODO: replace with a better assertion
            std::terminate();
        }
        m_thread       = other.m_thread;
        other.m_thread = invalid;
        return *this;
    }

    base_thread(const base_thread&)                    = delete;
    auto operator=(const base_thread&) -> base_thread& = delete;

    void swap(base_thread& other) noexcept {
        using std::swap;
        swap(m_thread, other.m_thread);
    }

    inline bool joinable() const noexcept { return policy_type::is_joinable(m_thread); }
    inline void join() {
        if (joinable()) {
            policy_type::join(m_thread);
            m_thread = invalid;
        }
    }

    inline void detach() {
        if (joinable()) {
            policy_type::detach(m_thread);
            m_thread = invalid;
        }
    }

    static inline unsigned hardware_concurrency() noexcept { return policy_type::hardware_concurrency(); }

private:
    native_handle_type m_thread = invalid;
};

}  // namespace dge::detail

#endif  // DGE_PLATFORM_BASE_THREAD_BASE_THREAD_HPP

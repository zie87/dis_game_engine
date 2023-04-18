#ifndef DGE_THREAD_THIS_THREAD_HPP
#define DGE_THREAD_THIS_THREAD_HPP

#include "dge/time/duration.hpp"
#include "dge/platform/thread.hpp"

namespace dge::this_thread {

template <typename REP_T, typename PERIOD_T>
void sleep_for(const dge::duration<REP_T, PERIOD_T>& sleep_duration) {
    const auto time = ::std::chrono::duration_cast<::dge::microseconds>(sleep_duration);
    dge::detail::sleep_for_us(time);
}

}  // namespace dge::this_thread

#endif  // DGE_THREAD_THIS_THREAD_HPP

#ifndef DGE_PLATFORM_BASE_THREAD_THREAD_TRAITS_HPP
#define DGE_PLATFORM_BASE_THREAD_THREAD_TRAITS_HPP

namespace dge::traits {

template <typename>
struct thread_id;

template <typename T>
using thread_id_t = typename thread_id<T>::type;

template <typename>
struct thread_native;

template <typename T>
using thread_native_t = typename thread_native<T>::type;

template <typename>
struct thread_invalid;

template <typename T>
inline constexpr auto thread_invalid_v = thread_invalid<T>::value;

template <typename>
struct thread_config;

template <typename T>
using thread_config_t = typename thread_config<T>::type;

template <typename>
struct thread_handle;

template <typename T>
using thread_handle_t = typename thread_handle<T>::type;

template <typename>
struct thread_policy;

template <typename T>
using thread_policy_t = typename thread_policy<T>::type;
}  // namespace dge::traits

#endif  // DGE_PLATFORM_BASE_THREAD_THREAD_TRAITS_HPP

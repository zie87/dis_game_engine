#ifndef DGE_PLATFORM_CONFIG_HPP
#define DGE_PLATFORM_CONFIG_HPP

namespace dge {

struct pf_tag_psp {};
struct pf_tag_sdl {};
struct pf_tag_ps2 {};

#if defined(DGE_PLATFORM_PSP)
using pf_tag_default = pf_tag_psp;;
#elif defined(DGE_PLATFORM_PS2)
using pf_tag_default = pf_tag_ps2;
#elif defined(DGE_PLATFORM_SDL)
using pf_tag_default = pf_tag_sdl;
#endif

}  // namespace dge

#endif  // DGE_PLATFORM_CONFIG_HPP

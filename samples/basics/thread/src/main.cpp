#include <dge/thread/thread.hpp>

#if defined(DGE_PLATFORM_PSP)
#include <pspdebug.h>
#include <pspkernel.h>

/* Define the module info section */
PSP_MODULE_INFO("basicthread", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define LOG pspDebugScreenPrintf
#elif defined(DGE_PLATFORM_PS2)
#include <stdio.h>
#include <tamtypes.h>
#include <sifrpc.h>
#include <debug.h>
#include <unistd.h>

#define LOG scr_printf

#elif defined(DGE_PLATFORM_SDL)
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <cstdio>

#define LOG std::printf
#endif

void first_thread(std::size_t repeations) {
    std::size_t cnt = 0;
    while (cnt++ < repeations) {
        LOG("hello from %s!\n", __FUNCTION__);
        dge::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void second_thread(std::size_t repeations) {
    std::size_t cnt = 0;
    while (cnt++ < repeations) {
        LOG("hello from %s!\n", __FUNCTION__);
        dge::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void run() {
    dge::thread first(first_thread, 5);
    dge::thread second(second_thread, 7);

    LOG("run, first and second now execute concurrently...\n");

    first.join();
    second.join();
}

#if defined(DGE_PLATFORM_PSP)
int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[]) {
    pspDebugScreenInit();
    run();
}
#elif defined(DGE_PLATFORM_PS2)

int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[]) {
    SifInitRpc(0);
    init_scr();
    scr_clear();
    scr_setXY(0, 5);

    run();
}
#elif defined(DGE_PLATFORM_SDL)
int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    run();

    SDL_Quit();
}
#endif

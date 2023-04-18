project(
    'DIS Game Engine',
    ['cpp'],
    version: '0.0.1',
    default_options: ['c_std=c11', 'cpp_std=c++20', 'warning_level=3'],
)

dge_inc_dirs = include_directories('include')
dge_srcs = []
dge_c_args = []
dge_cpp_args = []
dge_link_args = []
dge_dependencies = []


if host_machine.system() == 'psp'
    dge_c_args += ['-DDGE_PLATFORM_PSP', '-D_PSP_FW_VERSION=371']
    dge_cpp_args += dge_c_args

    dge_srcs += ['src/platform/psp/thread/thread_policy.cpp']

    dge_link_args += [
        '-lm',
        '-lpsppower',
        '-lpspmpeg',
        '-lpspaudiocodec',
        '-lpspaudiolib',
        '-lpspaudio',
        '-lpspmp3',
        '-lpspgum',
        '-lpspgu',
        '-lpsprtc',
        '-lstdc++',
        '-lpspfpu',
        '-lpspdebug',
        '-lpspdisplay',
        '-lpspge',
        '-lpspctrl',
        '-lpspnet',
        '-lpspnet_apctl',
    ]

else
    sdl2_dep = dependency('sdl2')
    thread_dep = dependency('threads')

    dge_c_args += ['-DDGE_PLATFORM_SDL']

    if host_machine.system() == 'linux'
        dge_c_args += ['-DDGE_PLATFORM_LINUX']
    elif host_machine.system() == 'windows'
        dge_c_args += ['-DDGE_PLATFORM_WINDOWS']
    endif

    dge_cpp_args += dge_c_args
    dge_dependencies += [sdl2_dep, thread_dep]
    dge_srcs += [
        'src/platform/sdl/thread/thread_policy.cpp',
    ]
endif

dge_lib = library(
    'dge',
    sources: dge_srcs,
    include_directories: dge_inc_dirs,
    c_args: dge_c_args,
    cpp_args: dge_cpp_args,
    link_args: dge_link_args,
    dependencies: dge_dependencies,
)

dge_dep = declare_dependency(
    link_with: dge_lib,
    include_directories: dge_inc_dirs,
    compile_args: [dge_cpp_args],
    link_args: [dge_link_args],
    dependencies: dge_dependencies,
)

subdir('tests')
subdir('samples')

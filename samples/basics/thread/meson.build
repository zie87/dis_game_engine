dge_thread_sample = executable(
    'dge_thread_sample',
    sources: [
        'src/main.cpp',
    ],
    dependencies: [dge_dep],
)

if host_machine.system() == 'psp'
    post_build = meson.get_external_property('post_build_script')
    post_build_script = '@0@'.format(
        find_program(meson.source_root() + '/tools/' + post_build).path(),
    )
    custom_target(
        'dge_thread_post_build',
        input: dge_thread_sample,
        output: 'dge_thread_post_build',
        command: [post_build_script, '@INPUT@', 'thread sample'],
        build_by_default: true,
        depends: [dge_thread_sample],
    )
endif

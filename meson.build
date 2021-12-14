project('asunapixel', 'cpp',
         default_options : 'cpp_std=c++20')

deps = [
    dependency('sfml-all')
]

src = [
    'src/app.cpp',
    'src/canvas.cpp',
    'src/chunk.cpp',
    'src/main.cpp',
    'src/viewport.cpp',

    'src/states/stateManager.cpp',
    'src/states/drawingState.cpp'
]

if host_machine.system() == 'linux'
    if get_option('buildtype').startswith('debug')
        add_project_arguments(['-g', '-DDEBUG'], language : 'cpp')
        add_project_link_arguments(['-lbfd', '-ldl'], language : 'cpp')
    endif
endif

executable('asunapixel', src, dependencies : deps)
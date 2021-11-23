project('asunapixel', 'cpp',
         default_options : 'cpp_std=c++20')

deps = [
	dependency('sfml-all')
]

src = [
	'src/main.cpp',
	'src/app.cpp',
	'src/canvas.cpp',
	'src/chunk.cpp',
	'src/viewport.cpp',

	'src/states/stateManager.cpp',
	'src/states/drawingState.cpp'
]

executable('asunapixel', src, dependencies : deps)
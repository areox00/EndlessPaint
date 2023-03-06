# EndlessPaint
## Old, probably abandoned project.

Attempt to create a simple program where you can paint on infinite canvas with friends.

What I want to implement to achieve finished product:
- [x] Simple drawing
- [ ] Fast chunk system
- [ ] Networking
- [x] Basic GUI

## Compiling
Simplest way is to use my little script to automate this process:
```
./builder.sh -br release
```
or alternatively run these commands:
```
meson build --buildtype=release
ninja -C build
./build/EndlessPaint
```

## Instructions for building on windows:

### Ensure [`msys2`](https://www.msys2.org/) is installed

### Installing needed software
- Go into your msys2 `MSYS2 MinGW x64` terminal
- Update everything with `pacman -Syu`
- Install needed packages with `pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-meson mingw-w64-x86_64-ninja mingw-w64-x86_64-sfml`
- Change the `PATH` environment variable to feature `C:\msys64\mingw64\bin`

### Building the project
- Go into the command line
- Change the directory to the `EndlessPaint`'s one
- Build and run with the builder tool:
	- `./builder -br` in powershell
	- `builder -br` in cmd
- Alternatively build and run on your own:
	- Prebuild with `meson build --buildtype=release`
	- Build with `ninja -C build`
	- If compilation and linking succeeded, run with `./build/EndlessPaint` in powershell or `build\EndlessPaint.exe` in cmd.

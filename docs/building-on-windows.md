# Instructions for building asunapixel on windows.

## Ensure following software is installed:
- [`Python` (with `pip`)](https://www.python.org/downloads/)
- [`msys2`](https://www.msys2.org/)

## Installing needed software
- Go into your msys2 `MSYS2 MinGW x64` terminal
- Update everything with `pacman -Syu`
- Install needed packages with `pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-meson mingw-w64-x86_64-ninja mingw-w64-x86_64-sfml`
- Change the `PATH` environment variable to feature `C:\msys64\mingw64\bin`

## Building the project
- Go into the command line
- Change the directory to the `asunapixel`'s one
- Build and run with the builder tool:
	- `./builer -br` in powershell
	- `builder -br` in cmd
- Alternatively build and run on your own:
	- Prebuild with `meson build --buildtype=release`
	- Build with `ninja -C build`
	- If compilation and linking succeeded, run with `./build/asunapixel` in powershell or `cd build` then `asunapixel.exe` in cmd.

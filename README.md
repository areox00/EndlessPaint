# asunapixel
Attempt to create a simple program where you can paint on infinite canvas with friends.

What I want to implement to achieve finished product:
- [x] Simple drawing
- [ ] Fast chunk system
- [ ] Networking
- [ ] Good UI/UX

## Compiling
Simplest way is to use my little script to automate this process:
```
./builder.sh -br release
```
or alternatively run these commands:
```
meson build --buildtype=release
ninja -C build
./build/asunapixel
```
Instructions for building on windows available here:
[building-on-windows.md](./docs/building-on-windows)
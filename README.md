# asunapixel
Attempt to create a simple program where you can paint on infinite canvas with friends.

What i want to implement to achieve finished product:
- [x] simple drawing
- [ ] fast chunk system
- [ ] networking
- [ ] good ui/ux

## Compiling
Simplest way is to use my little script to automate this process:
```
./builder.sh -br debug
```
or alternatively run these commands:
```
meson build --buildtype=release
ninja -C build
./build/asunapixel
```

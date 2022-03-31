#!/bin/bash

program="EndlessPaint"

build () {
	if [ "$1" = "debug" ] ; then
		meson build --buildtype=debug
		ninja -C build
		return $? 
	elif [ "$1" = "release" ] ; then
		meson build --buildtype=release
		ninja -C build
		return $?
	fi
}

case "$1" in
	"-br")
		build $2 && ./build/${program}
	;;
	"-b" | "build")
		build $2
	;;
	"-r" | "run")
		./build/${program}
	;;
esac
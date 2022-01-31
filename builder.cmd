@echo off
SETLOCAL

@REM In case the user hasn't chosen the build profile
set "param2=%~2"
if "%param2%"=="" set "param2=release"

@REM The switch statement:
goto CASE_%1

@REM User hasn't specified any parameters
:CASE_
	echo Usage:
	echo 	builder -b
	echo 		Builds asunapixel
	echo 	builder -r
	echo 		Runs asunapixel (only if built already)
	echo 	builder -br
	echo 		Builds and then runs asunapixel
	goto END_CASE
:CASE_build
:CASE_-b
	call :build %param2%
	goto END_CASE
:CASE_-br
	call :build %param2%
	cd build
	call asunapixel
	goto END_CASE
:CASE_run
:CASE_-r
	cd build
	call asunapixel
	goto END_CASE
:END_CASE
	exit /B %ERRORLEVEL%

:build
	meson build --buildtype=%~1
	ninja -C build
	exit /B 0
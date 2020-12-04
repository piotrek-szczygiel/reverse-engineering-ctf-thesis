@echo off
rem Download and install raylib_installer_v300.mingw.exe from https://github.com/raysan5/raylib/releases
set RAYLIB_PATH=C:\raylib\raylib
set COMPILER_PATH=C:\raylib\mingw\bin
set CC=%COMPILER_PATH%\gcc
set CFLAGS=%RAYLIB_PATH%\src\raylib.rc.data -static -O0 -std=c99 -mwindows -Wall -Iexternal -DPLATFORM_DESKTOP
set LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm

echo %CC% game.c -o game.exe %CFLAGS% %LDFLAGS%
%CC% game.c -o game.exe %CFLAGS% %LDFLAGS%

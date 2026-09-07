@echo off

set DEVKITARM=C:/devkitpro/devkitARM
set DEVKITPPC=C:/devkitpro/devkitPPC
set DEVKITPRO=C:/devkitpro

set PATH=C:\devkitpro\msys2\usr\bin;%PATH%

make -j8


if %errorlevel% neq 0 (
		color 0c
		echo Build failed!
) else (
		color 0a
		echo Build succeeded.
)

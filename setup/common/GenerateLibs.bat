@echo off

set DEVKITARM=C:/devkitpro/devkitARM
set DEVKITPPC=C:/devkitpro/devkitPPC
set DEVKITPRO=C:/devkitpro

set PATH=C:\devkitpro\msys2\usr\bin;%PATH%
set toBuild=%~dp0..\..\%1

make -C %toBuild%



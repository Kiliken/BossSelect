@echo off

for %%I in ("%CD%") do set "PROJECT_NAME=%%~nxI"

cd emulator

NanoBoyAdvance.exe "../%PROJECT_NAME%.gba"
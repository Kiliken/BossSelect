@echo off


:FileCheck
if exist "%cd%/codeDL.ps1" del codeDL.ps1
if not exist "C:/devkitPro" goto InstallDevKit
if not exist "%cd%/emulator" goto InstallNBA
if exist "%cd%/butano" goto ExitProgram


:SetupProject
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0setup/InstallButano.ps1"
echo Project Setup completed...
pause
exit

:InstallDevKit
echo Installing DevKitPro...
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0setup/InstallDevKit.ps1"
echo Waiting for DevKitPro to finish installing...
pause
goto FileCheck

:InstallNBA
echo Installing NanoBoyAdvance...
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0setup/InstallNBA.ps1"
echo Waiting for NanoBoyAdvance to finish installing...
pause
goto FileCheck

:ExitProgram
echo Project is already installed...
pause
exit

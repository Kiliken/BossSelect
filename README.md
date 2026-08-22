# gba-dev-setup

A minimal, ready-to-go setup script for **Game Boy Advance (GBA)** development. It automates the installation and configuration of the essential toolchain:

* **Compiler/Toolchain**: [devkitPro](https://devkitpro.org/)

* **Engine/Library**: [Butano](https://github.com/GValiente/butano)

* **Emulator**: [NanoBoyAdvance](https://nanoboyadvance.eu)


## Quick Start

1. Right-click inside your target project folder and select **Open in Terminal**.

2. Paste and run the following command:

```powershell
curl.exe -L -o "$(Get-Location)\codeDL.ps1" "https://raw.githubusercontent.com/Kiliken/gba-dev-setup/main/codeDL.ps1"
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "$(Get-Location)\codeDL.ps1"

```

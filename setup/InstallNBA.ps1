
New-Item -Path "$($PSScriptRoot)\..\emulator" -ItemType Directory
New-Item -Path "$($PSScriptRoot)\..\emulator\saves" -ItemType Directory

$nbaDownloadUrl = "https://codeberg.org/nba-emu/NanoBoyAdvance/releases/download/v1.8.3/NanoBoyAdvance-Windows-x64.zip"

$biosDownloadUrl = "https://raw.githubusercontent.com/Nebuleon/ReGBA/refs/heads/master/bios/gba_bios.bin"


# Download
Write-Output "[NanoBoyAdvanceInstall] Downloading NanoBoyAdvance v1.8.3..."
curl.exe -L "$nbaDownloadUrl" -o "$($PSScriptRoot)\nbaEmu.zip" --progress-bar

Write-Output "[NanoBoyAdvanceInstall] Downloading GBA bios file..."
curl.exe -L "$biosDownloadUrl" -o "$($PSScriptRoot)\..\emulator\gba_bios.bin" --progress-bar

# Extract
Add-Type -AssemblyName System.IO.Compression.FileSystem

Write-Output "[NanoBoyAdvanceInstall] Extracting NanoBoyAdvance in $($PSScriptRoot)..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\nbaEmu.zip", "$($PSScriptRoot)\..\emulator")

Copy-Item -Path "$($PSScriptRoot)\common\config.toml" -Destination "$($PSScriptRoot)\..\emulator" -Force

return 0

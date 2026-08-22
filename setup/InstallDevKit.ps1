
$devkitDownloadUrl = "https://downloads.devkitpro.org/msys-2.10.0.1.7z"
$pythonDownloadUrl = "https://github.com/bjia56/portable-python/releases/download/cpython-v3.9.25-build.0/python-full-3.9.25-windows-x86_64.zip"

New-Item -ItemType Directory -Force -Path "C:\devkitPro"

# Download
Write-Output "[devkitInstall] Downloading devkit for GBA..."
curl.exe -L `
    "$devkitDownloadUrl" `
    -o "$($PSScriptRoot)/msys-2.10.0.1.7z" `
    --user-agent "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36" `
    --tlsv1.2 `
    --progress-bar
	
Write-Output "[devkitInstall] Downloading python..."
curl.exe -L "$pythonDownloadUrl" -o "$($PSScriptRoot)\python.zip" --progress-bar

# Extract
Add-Type -AssemblyName System.IO.Compression.FileSystem

Write-Output "[devkitInstall] Extracting devkit in C:\devkitPro..."
tar -xf "$($PSScriptRoot)\msys-2.10.0.1.7z" -C "C:\devkitPro\"

Write-Output "[devkitInstall] Extracting python in C:\devkitPro..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\python.zip", "C:\devkitPro")

Rename-Item -Path "C:\devkitPro\python-full-3.9.25-windows-x86_64" -NewName "python"

# Install
& "C:\devkitPro\msys2\usr\bin\bash.exe" --login -c "exit"
& "C:\devkitPro\msys2\usr\bin\pacman.exe" -Syu --noconfirm
& "C:\devkitPro\msys2\usr\bin\pacman.exe" -S "gba-dev" --noconfirm --needed

robocopy "C:\devkitPro\msys2\opt\devkitpro" "C:\devkitPro" /E

Remove-Item -Path "C:\devkitPro\msys2\opt\devkitpro" -Recurse -Force

return 0

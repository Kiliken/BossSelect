
$ProjectRoot = "$($PSScriptRoot)\.."

New-Item -Path "$($ProjectRoot)\build" -ItemType Directory
New-Item -Path "$($ProjectRoot)\audio" -ItemType Directory
New-Item -Path "$($ProjectRoot)\dmg_audio" -ItemType Directory
New-Item -Path "$($ProjectRoot)\include" -ItemType Directory
New-Item -Path "$($ProjectRoot)\graphics" -ItemType Directory

$butanoDownloadUrl = "https://github.com/GValiente/butano/archive/refs/tags/21.7.1.tar.gz"

# Downloads
if ( -not (Test-Path "$($PSScriptRoot)\butano.tar.gz")){
	Write-Output "[gba-dev-setup] Downloading Butano..."
	curl.exe -L "$butanoDownloadUrl" -o "$($PSScriptRoot)\butano.tar.gz" --progress-bar
}

# Extract
Add-Type -AssemblyName System.IO.Compression.FileSystem

Write-Output "[gba-dev-setup] Extracting Butano..."
tar -xzf "$($PSScriptRoot)\butano.tar.gz" -C "$($PSScriptRoot)"

# Install
Copy-Item -Path "$($PSScriptRoot)\butano-21.7.1\butano" -Destination "$($ProjectRoot)" -Recurse

# Clean Dependencies
Remove-Item -Path "$($PSScriptRoot)\butano-21.7.1" -Recurse -Force

return 0

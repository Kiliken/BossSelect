
$dest = (Get-Location).Path

curl.exe -L "https://github.com/Kiliken/gba-dev-setup/archive/refs/heads/main.tar.gz" -o "$($dest)\main.tar.gz" --progress-bar

tar -xzf "$($dest)\main.tar.gz" -C "$($dest)"

Move-Item "$($dest)\gba-dev-setup-main\*" $PSScriptRoot -Force
Remove-Item "$($dest)\gba-dev-setup-main" -Recurse -Force
Remove-Item "$($dest)\main.tar.gz" -Force
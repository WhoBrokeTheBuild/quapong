<#
==== INSTRUCTIONS ====
Run Powershell CLI as Administrator
Run "Set-ExecutionPolicy Unrestricted"
Shift-Right click on this file, Copy Path
Paste into Powershell CLI and remove quotes to Run
#>

$TEMP_DIR = $env:TEMP
$SDL2_VERSION 		= "2.0.5"
$SDL2_IMAGE_VERSION = "2.0.1"
$SDL2_TTF_VERSION 	= "2.0.14"
$FLATCC_VERSION 	= "0.4.1"
$VC_DIR = "$($Env:VS140COMNTOOLS)..\..\VC\"

Add-Type -AssemblyName System.IO.Compression.FileSystem
function Unzip
{
    param([string]$zipfile, [string]$outpath)

    [System.IO.Compression.ZipFile]::ExtractToDirectory($zipfile, $outpath)
}

Write-Host "Downloading SDL2"
Invoke-WebRequest "https://www.libsdl.org/release/SDL2-devel-$($SDL2_VERSION)-VC.zip" -OutFile "$($TEMP_DIR)\SDL2-$($SDL2_VERSION).zip"
Remove-Item "$($TEMP_DIR)\SDL2-$($SDL2_VERSION)" -Recurse -Force | Out-Null
Unzip "$($TEMP_DIR)\SDL2-$($SDL2_VERSION).zip" "$($TEMP_DIR)\"

Write-Host "Installing SDL2"
Copy-Item "$($TEMP_DIR)\SDL2-$($SDL2_VERSION)\include\*" "$($VC_DIR)\include\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2-$($SDL2_VERSION)\lib\x86\*.lib" "$($VC_DIR)\lib\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2-$($SDL2_VERSION)\lib\x86\*.dll" "$($VC_DIR)\bin\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2-$($SDL2_VERSION)\lib\x64\*.lib" "$($VC_DIR)\lib\amd64\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2-$($SDL2_VERSION)\lib\x64\*.dll" "$($VC_DIR)\bin\amd64\" -Recurse -Force

Write-Host "Downloading SDL2_image"
Invoke-WebRequest "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-$($SDL2_IMAGE_VERSION)-VC.zip" -OutFile "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION).zip"
Remove-Item "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION)" -Recurse -Force | Out-Null
Unzip "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION).zip" "$($TEMP_DIR)\"

Write-Host "Installing SDL2_image"
Copy-Item "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION)\include\*" "$($VC_DIR)\include\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION)\lib\x86\*.lib" "$($VC_DIR)\lib\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION)\lib\x86\*.dll" "$($VC_DIR)\bin\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION)\lib\x64\*.lib" "$($VC_DIR)\lib\amd64\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_image-$($SDL2_IMAGE_VERSION)\lib\x64\*.dll" "$($VC_DIR)\bin\amd64\" -Recurse -Force

Write-Host "Downloading SDL2_ttf"
Invoke-WebRequest "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-$($SDL2_TTF_VERSION)-VC.zip" -OutFile "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION).zip"
Remove-Item "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION)" -Recurse -Force | Out-Null
Unzip "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION).zip" "$($TEMP_DIR)\"

Write-Host "Installing SDL2_ttf"
Copy-Item "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION)\include\*" "$($VC_DIR)\include\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION)\lib\x86\*.lib" "$($VC_DIR)\lib\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION)\lib\x86\*.dll" "$($VC_DIR)\bin\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION)\lib\x64\*.lib" "$($VC_DIR)\lib\amd64\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\SDL2_ttf-$($SDL2_TTF_VERSION)\lib\x64\*.dll" "$($VC_DIR)\bin\amd64\" -Recurse -Force

Write-Host "Cloning FlatCC"
Remove-Item "$($TEMP_DIR)\flatcc" -Recurse -Force | Out-Null
git clone --depth=1 --branch="v$($FLATCC_VERSION)" "https://github.com/dvidelabs/flatcc.git" "$($TEMP_DIR)\flatcc" | Out-Null
New-Item -Type Directory "$($TEMP_DIR)\flatcc\build\x86" | Out-Null
New-Item -Type Directory "$($TEMP_DIR)\flatcc\build\x64" | Out-Null

Write-Host "Building FlatCC x86"
cd "$($TEMP_DIR)\flatcc\build\x86"
cmake -G "Visual Studio 14 2015" ..\.. | Out-Null
cmake --build . --target --config Release | Out-Null
Copy-Item "$($TEMP_DIR)\flatcc\include\*" "$($VC_DIR)\include\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\flatcc\lib\Release\*" "$($VC_DIR)\lib\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\flatcc\bin\Release\*" "$($VC_DIR)\bin\" -Recurse -Force

Write-Host "Building FlatCC x64"
cd "$($TEMP_DIR)\flatcc\build\x64"
cmake -G "Visual Studio 14 2015 Win64" ..\.. | Out-Null
cmake --build . --target --config Release | Out-Null
Copy-Item "$($TEMP_DIR)\flatcc\include\*" "$($VC_DIR)\include\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\flatcc\lib\Release\*" "$($VC_DIR)\lib\amd64\" -Recurse -Force
Copy-Item "$($TEMP_DIR)\flatcc\bin\Release\*" "$($VC_DIR)\bin\amd64\" -Recurse -Force
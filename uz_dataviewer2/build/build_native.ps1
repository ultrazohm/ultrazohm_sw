# Build a native, self-contained UltraZohm Data Viewer executable on Windows.
# Run from the project root in PowerShell:
#
#     .\build\build_native.ps1
#
# Output: dist\uz_dataviewer.exe
$ErrorActionPreference = "Stop"

$here = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
Set-Location $here

python -m pip install --upgrade pip
python -m pip install -r requirements.txt
python -m pip install "pyinstaller>=6.0"

if (Test-Path build\native) { Remove-Item -Recurse -Force build\native }
if (Test-Path dist) { Remove-Item -Recurse -Force dist }

pyinstaller --clean --distpath dist --workpath build\native build\uz_dataviewer.spec

Write-Host ""
Write-Host "Built: $here\dist\uz_dataviewer.exe"

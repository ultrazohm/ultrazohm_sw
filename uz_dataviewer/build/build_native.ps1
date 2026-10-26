# Build a native, self-contained UltraZohm Data Viewer executable on Windows.
# Run from the project root in PowerShell:
#
#     .\build\build_native.ps1
#
# Output: dist\uz_dataviewer.exe
$ErrorActionPreference = "Stop"

$here = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
Set-Location $here

if (-not (Get-Command uv -ErrorAction SilentlyContinue)) {
    throw "uv is required: install it with python -m pip install uv"
}
if (-not $env:UV_PROJECT_ENVIRONMENT) {
    $env:UV_PROJECT_ENVIRONMENT = Join-Path $here ".venv-build"
}
uv sync --locked --extra dev --python 3.12 --no-build-package imgui-bundle
if ($LASTEXITCODE -ne 0) { throw "Dependency installation failed ($LASTEXITCODE)" }

if (Test-Path build\native) { Remove-Item -Recurse -Force build\native }
if (Test-Path dist) { Remove-Item -Recurse -Force dist }

uv run --no-sync python -m PyInstaller --noconfirm --clean --distpath dist --workpath build\native build\uz_dataviewer.spec
if ($LASTEXITCODE -ne 0) { throw "PyInstaller failed ($LASTEXITCODE)" }

Write-Host ""
Write-Host "Built: $here\dist\uz_dataviewer.exe"

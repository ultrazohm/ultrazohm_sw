# Build a self-contained native app for Windows.
# Result: dist\uz-dataviewer\uz-dataviewer.exe
# Run from anywhere:  powershell -ExecutionPolicy Bypass -File packaging\desktop\build.ps1
$ErrorActionPreference = "Stop"

$ProjectRoot = Resolve-Path (Join-Path $PSScriptRoot "..\..")
Set-Location $ProjectRoot

$VenvDir = Join-Path $ProjectRoot ".venv-build"
if (-not (Test-Path $VenvDir)) {
    python -m venv $VenvDir
}
& (Join-Path $VenvDir "Scripts\Activate.ps1")

python -m pip install --upgrade pip
pip install ".[fast,build]"

pyinstaller packaging\desktop\uz_dataviewer.spec --noconfirm --distpath dist --workpath build

Write-Host ""
Write-Host "Done. Run: $ProjectRoot\dist\uz-dataviewer\uz-dataviewer.exe"

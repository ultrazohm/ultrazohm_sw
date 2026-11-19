# The pipeline makes PowerShell wait for the windowed process and forwards output.
# Invoke this script with &, not dot-sourcing, so its exit code returns to the caller.
$ErrorActionPreference = 'Continue'
$PSNativeCommandUseErrorActionPreference = $false
$executable = Join-Path $PSScriptRoot 'ultrazohm-dataviewer.exe'
& $executable --cli @args | ForEach-Object { $_ }
exit $LASTEXITCODE

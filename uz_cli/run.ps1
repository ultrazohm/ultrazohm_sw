# Usage: .\uz_cli\run.ps1 [--wheel PATH | --latest | --local-newest] [--channel stable|testing] [--launch cli|example] [-- CLI_ARGUMENTS...]
# Arguments are forwarded verbatim to setup_uv.py; use its --wheel/--venv options.
$ErrorActionPreference = "Stop"
$forwardedArgs = @($args)

if (-not (Get-Command uv -ErrorAction SilentlyContinue)) {
    throw "uv is required. Install uv and run this script again."
}
$dockerfile = Join-Path $PSScriptRoot "../.devcontainer/Dockerfile"
$matchesFound = [regex]::Matches((Get-Content -Raw $dockerfile), '(?m)^FROM .*python:([0-9][0-9.]*)')
if ($matchesFound.Count -ne 1) {
    throw "Could not determine one Python version from .devcontainer/Dockerfile."
}
$pythonVersion = $matchesFound[0].Groups[1].Value
$previousVenv = $env:VIRTUAL_ENV
$exitCode = 1
try {
    # Ignore a stale environment activated on another host/container.
    Remove-Item Env:VIRTUAL_ENV -ErrorAction SilentlyContinue
    & uv python install $pythonVersion
    if ($LASTEXITCODE -ne 0) { throw "uv could not install Python $pythonVersion." }
    $setupScript = Join-Path $PSScriptRoot "setup_uv.py"
    & uv run --no-project --managed-python --python $pythonVersion $setupScript --python $pythonVersion --examples --launch shell @forwardedArgs
    $exitCode = $LASTEXITCODE
}
finally {
    if ($null -ne $previousVenv) {
        $env:VIRTUAL_ENV = $previousVenv
    } else {
        Remove-Item Env:VIRTUAL_ENV -ErrorAction SilentlyContinue
    }
}
exit $exitCode

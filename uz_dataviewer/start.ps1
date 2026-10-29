# Install uv and runtime dependencies, then launch the native data viewer.
# Launcher options: --launch gui|shell, --use-live, --live-wheel PATH, --live-channel stable|testing.
# Remaining arguments are forwarded to the viewer, including relative file paths.
$ErrorActionPreference = 'Stop'

try {
    $uvCommand = Get-Command uv -CommandType Application -ErrorAction SilentlyContinue
    if ($uvCommand) {
        $uvExecutable = $uvCommand.Source
    } else {
        $uvBinDir = if ($env:UV_UNMANAGED_INSTALL) {
            $env:UV_UNMANAGED_INSTALL
        } elseif ($env:UV_INSTALL_DIR) {
            $env:UV_INSTALL_DIR
        } else {
            Join-Path $HOME '.local\bin'
        }
        $uvExecutable = Join-Path $uvBinDir 'uv.exe'
        if (-not (Test-Path -LiteralPath $uvExecutable -PathType Leaf)) {
            Write-Host 'uv is not installed; installing it from https://astral.sh/uv/install.ps1 ...'
            $previousInstallDir = $env:UV_INSTALL_DIR
            $previousNoModifyPath = $env:UV_NO_MODIFY_PATH
            try {
                $env:UV_INSTALL_DIR = $uvBinDir
                $env:UV_NO_MODIFY_PATH = '1'
                $installer = Invoke-RestMethod -Uri 'https://astral.sh/uv/install.ps1'
                & ([scriptblock]::Create($installer))
            } finally {
                $env:UV_INSTALL_DIR = $previousInstallDir
                $env:UV_NO_MODIFY_PATH = $previousNoModifyPath
            }
            if (-not (Test-Path -LiteralPath $uvExecutable -PathType Leaf)) {
                throw "uv installation failed: no executable found at $uvExecutable."
            }
        }
    }

    $viewerOriginalPath = $env:PATH
    try {
        $env:PATH = (Split-Path -Parent $uvExecutable) + [IO.Path]::PathSeparator + $env:PATH
        & $uvExecutable run --no-project --python '3.12' (Join-Path $PSScriptRoot 'launch.py') @args
        exit $LASTEXITCODE
    } finally {
        $env:PATH = $viewerOriginalPath
    }
} catch {
    [Console]::Error.WriteLine($_.Exception.Message)
    exit 1
}

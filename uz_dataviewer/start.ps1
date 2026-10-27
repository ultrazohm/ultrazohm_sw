# Install uv and runtime dependencies, then launch the native data viewer.
# All arguments are forwarded to the viewer, including relative file paths.
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

    $liveOptions = @()
    $viewerArgs = @()
    for ($i = 0; $i -lt $args.Count; $i++) {
        if ($args[$i] -eq '--live-wheel') {
            if ($i + 1 -ge $args.Count -or -not (Test-Path -LiteralPath $args[$i + 1] -PathType Leaf)) {
                throw '--live-wheel requires a compatible ultrazohm wheel path.'
            }
            $i++
            $liveOptions += @('--with', (Resolve-Path -LiteralPath $args[$i]).Path)
        } else {
            $viewerArgs += $args[$i]
        }
    }
    # Keep the caller's working directory so relative input paths still work.
    & $uvExecutable run --project $PSScriptRoot --python 3.12 --no-build-package imgui-bundle @liveOptions uz-dataviewer @viewerArgs
    exit $LASTEXITCODE
} catch {
    [Console]::Error.WriteLine($_.Exception.Message)
    exit 1
}

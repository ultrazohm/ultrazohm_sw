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

    $launch = "gui"
    $useLive = $false
    $liveOptions = @()
    $viewerArgs = @()
    for ($i = 0; $i -lt $args.Count; $i++) {
        if ($args[$i] -eq '--launch') {
            if ($i + 1 -ge $args.Count -or $args[$i + 1] -notin @('gui', 'shell')) {
                throw '--launch requires gui or shell.'
            }
            $i++
            $launch = $args[$i]
        } elseif ($args[$i] -eq '--use-live') {
            $useLive = $true
        } elseif ($args[$i] -eq '--live-wheel') {
            if ($i + 1 -ge $args.Count -or -not (Test-Path -LiteralPath $args[$i + 1] -PathType Leaf)) {
                throw '--live-wheel requires a compatible ultrazohm wheel path.'
            }
            $i++
            $useLive = $true
            $liveOptions += @('--wheel', (Resolve-Path -LiteralPath $args[$i]).Path)
        } elseif ($args[$i] -eq '--live-channel') {
            if ($i + 1 -ge $args.Count -or $args[$i + 1] -notin @('stable', 'testing')) {
                throw '--live-channel requires stable or testing.'
            }
            $i++
            $useLive = $true
            $liveOptions += @('--channel', $args[$i])
        } else {
            $viewerArgs += $args[$i]
        }
    }
    if ($launch -eq 'shell' -and $viewerArgs.Count -gt 0) {
        throw 'Viewer arguments cannot be used with --launch shell.'
    }
    if ($useLive) {
        & $uvExecutable sync --project $PSScriptRoot --python 3.12 --inexact --no-build-package imgui-bundle
        if ($LASTEXITCODE -ne 0) { throw 'Viewer dependency setup failed.' }
        $viewerVenv = Join-Path $PSScriptRoot '.venv'
        $isWindowsPlatform = [Environment]::OSVersion.Platform -eq [PlatformID]::Win32NT
        $shellName = if ($PSVersionTable.PSEdition -eq 'Core') {
            if ($isWindowsPlatform) { 'pwsh.exe' } else { 'pwsh' }
        } else { 'powershell.exe' }
        $cliShell = Join-Path $PSHOME $shellName
        # The CLI launcher discovers uv through PATH, including after bootstrap.
        $previousPath = $env:PATH
        try {
            $env:PATH = (Split-Path -Parent $uvExecutable) + [IO.Path]::PathSeparator + $env:PATH
            # Isolate the CLI launcher's exit from this viewer launcher's scope.
            & $cliShell -NoProfile -File (Join-Path $PSScriptRoot '../uz_cli/run.ps1') --venv $viewerVenv --launch none --no-examples @liveOptions
            if ($LASTEXITCODE -ne 0) { throw 'UltraZohm backend setup failed.' }
        } finally {
            $env:PATH = $previousPath
        }
        $scripts = if ($isWindowsPlatform) { 'Scripts' } else { 'bin' }
        $pythonName = if ($scripts -eq 'Scripts') { 'python.exe' } else { 'python' }
        $viewerName = if ($scripts -eq 'Scripts') { 'uz-dataviewer.exe' } else { 'uz-dataviewer' }
        $viewerScripts = Join-Path $viewerVenv $scripts
        & (Join-Path $viewerScripts $pythonName) -m uz_dataviewer.check_live
        if ($LASTEXITCODE -ne 0) { throw 'The selected backend is incompatible with live viewing.' }
        if ($launch -eq 'shell') {
            & (Join-Path $viewerScripts $pythonName) -m uz_dataviewer.env_shell
            exit $LASTEXITCODE
        }
        & (Join-Path $viewerScripts $viewerName) --use-live --live-repo (Join-Path $PSScriptRoot '..') @viewerArgs
        exit $LASTEXITCODE
    }
    if ($launch -eq 'shell') {
        & $uvExecutable sync --project $PSScriptRoot --python 3.12 --inexact --no-build-package imgui-bundle
        if ($LASTEXITCODE -ne 0) { throw 'Viewer dependency setup failed.' }
        $pythonRelative = if ([Environment]::OSVersion.Platform -eq [PlatformID]::Win32NT) {
            '.venv/Scripts/python.exe'
        } else { '.venv/bin/python' }
        & (Join-Path $PSScriptRoot $pythonRelative) -m uz_dataviewer.env_shell
        exit $LASTEXITCODE
    }
    # Keep the caller's working directory so relative input paths still work.
    & $uvExecutable run --project $PSScriptRoot --python 3.12 --no-build-package imgui-bundle uz-dataviewer @viewerArgs
    exit $LASTEXITCODE
} catch {
    [Console]::Error.WriteLine($_.Exception.Message)
    exit 1
}

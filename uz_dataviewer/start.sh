#!/usr/bin/env bash
# Install runtime dependencies with uv and launch the native data viewer.
# Usage: start.sh [--launch gui|shell] [--use-live] [--live-wheel PATH] [--live-channel stable|testing] [VIEWER_ARGUMENTS...]
set -euo pipefail

if ! command -v uv >/dev/null 2>&1; then
    UV_BIN_DIR="${UV_UNMANAGED_INSTALL:-${UV_INSTALL_DIR:-$HOME/.local/bin}}"
    if [[ ! -x "$UV_BIN_DIR/uv" ]]; then
        echo "uv is not installed; installing it from https://astral.sh/uv/install.sh ..."
        INSTALLER="$(mktemp)"
        trap 'rm -f -- "$INSTALLER"' EXIT
        if command -v curl >/dev/null 2>&1; then
            curl --fail --location --silent --show-error https://astral.sh/uv/install.sh -o "$INSTALLER"
        elif command -v wget >/dev/null 2>&1; then
            wget -q https://astral.sh/uv/install.sh -O "$INSTALLER"
        else
            echo "Install curl or wget so the launcher can download uv." >&2
            exit 1
        fi
        UV_INSTALL_DIR="$UV_BIN_DIR" UV_NO_MODIFY_PATH=1 sh "$INSTALLER"
        rm -f -- "$INSTALLER"
        trap - EXIT
    fi
    export PATH="$UV_BIN_DIR:$PATH"
    if ! command -v uv >/dev/null 2>&1; then
        echo "uv installation failed: no executable found in $UV_BIN_DIR." >&2
        exit 1
    fi
fi

PROJECT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

LAUNCH=gui
USE_LIVE=false
LIVE_OPTIONS=()
VIEWER_ARGS=()
while [[ $# -gt 0 ]]; do
    if [[ "$1" == "--launch" ]]; then
        if [[ $# -lt 2 || ( "$2" != "gui" && "$2" != "shell" ) ]]; then
            echo '--launch requires gui or shell.' >&2
            exit 1
        fi
        LAUNCH="$2"
        shift 2
    elif [[ "$1" == "--use-live" ]]; then
        USE_LIVE=true
        shift
    elif [[ "$1" == "--live-wheel" ]]; then
        if [[ $# -lt 2 || ! -f "$2" ]]; then
            echo '--live-wheel requires a compatible ultrazohm wheel path.' >&2
            exit 1
        fi
        USE_LIVE=true
        LIVE_OPTIONS+=(--wheel "$(cd -- "$(dirname -- "$2")" && pwd)/$(basename -- "$2")")
        shift 2
    elif [[ "$1" == "--live-channel" ]]; then
        if [[ $# -lt 2 || ( "$2" != "stable" && "$2" != "testing" ) ]]; then
            echo '--live-channel requires stable or testing.' >&2
            exit 1
        fi
        USE_LIVE=true
        LIVE_OPTIONS+=(--channel "$2")
        shift 2
    else
        VIEWER_ARGS+=("$1")
        shift
    fi
done

if [[ "$LAUNCH" == shell && ${#VIEWER_ARGS[@]} -gt 0 ]]; then
    echo 'Viewer arguments cannot be used with --launch shell.' >&2
    exit 1
fi

if "$USE_LIVE"; then
    # Sync first, then install the backend into this same environment. Launch
    # directly afterward so another sync cannot remove the optional backend.
    uv sync --project "$PROJECT_DIR" --python 3.12 --inexact --no-build-package imgui-bundle
    "$PROJECT_DIR/../uz_cli/run.sh" --venv "$PROJECT_DIR/.venv" \
        --launch none --no-examples "${LIVE_OPTIONS[@]}"
    "$PROJECT_DIR/.venv/bin/python" -m uz_dataviewer.check_live
    if [[ "$LAUNCH" == shell ]]; then
        exec "$PROJECT_DIR/.venv/bin/python" -m uz_dataviewer.env_shell
    fi
    exec "$PROJECT_DIR/.venv/bin/uz-dataviewer" --use-live --live-repo "$PROJECT_DIR/.." "${VIEWER_ARGS[@]}"
fi

if [[ "$LAUNCH" == shell ]]; then
    uv sync --project "$PROJECT_DIR" --python 3.12 --inexact --no-build-package imgui-bundle
    exec "$PROJECT_DIR/.venv/bin/python" -m uz_dataviewer.env_shell
fi

# Keep the caller's working directory so relative input paths still work.
# uv creates/reuses .venv and installs the project and its runtime dependencies.
# Use the tested Python version: current imgui-bundle Linux wheels omit 3.10.
# Never fall back to compiling the GUI and its native dependencies on startup.
exec uv run --project "$PROJECT_DIR" --python 3.12 \
    --no-build-package imgui-bundle uz-dataviewer "${VIEWER_ARGS[@]}"

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

# Preserve the caller working directory and every argument.
exec uv run --no-project --python 3.12 "$PROJECT_DIR/launch.py" "$@"

#!/usr/bin/env bash
# Shared bootstrap for user and developer launchers.
set -euo pipefail
PROJECT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
UZ_ENTRY_POINT="$1"
shift
UZ_UV_VERSION="$(cat "$PROJECT_DIR/.uv-version")"
if ! command -v uv >/dev/null 2>&1; then
    UV_BIN_DIR="${UV_UNMANAGED_INSTALL:-${UV_INSTALL_DIR:-$HOME/.local/bin}}"
    if [[ ! -x "$UV_BIN_DIR/uv" ]]; then
        echo "uv is not installed; installing it from https://astral.sh/uv/$UZ_UV_VERSION/install.sh ..."
        INSTALLER="$(mktemp)"
        trap 'rm -f -- "$INSTALLER"' EXIT
        if command -v curl >/dev/null 2>&1; then
            curl --fail --location --silent --show-error https://astral.sh/uv/$UZ_UV_VERSION/install.sh -o "$INSTALLER"
        elif command -v wget >/dev/null 2>&1; then
            wget -q https://astral.sh/uv/$UZ_UV_VERSION/install.sh -O "$INSTALLER"
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

exec uv run --no-project --isolated --python "$(cat "$PROJECT_DIR/.python-version")" "$PROJECT_DIR/$UZ_ENTRY_POINT" "$@"

#!/usr/bin/env bash
# Usage: ./uz_cli/run.sh [--wheel PATH] [--launch cli|example] [-- CLI_ARGUMENTS...]
set -euo pipefail

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
if ! command -v uv >/dev/null 2>&1; then
    echo "uv is required. Install uv and run this script again." >&2
    exit 1
fi
# The devcontainer image is the source of truth for the Python version.
python_version="$(sed -n 's/^FROM .*python:\([0-9][0-9.]*\).*/\1/p' "$script_dir/../.devcontainer/Dockerfile")"
if [[ -z "$python_version" || "$python_version" == *$'\n'* ]]; then
    echo "Could not determine one Python version from .devcontainer/Dockerfile." >&2
    exit 1
fi
# Ignore a stale environment activated on another host/container.
unset VIRTUAL_ENV
uv python install "$python_version"
exec uv run --no-project --managed-python --python "$python_version" \
    "$script_dir/setup_uv.py" --python "$python_version" --examples --launch shell "$@"

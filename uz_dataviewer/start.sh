#!/usr/bin/env bash
# Install runtime dependencies with uv and launch the native data viewer.
set -euo pipefail

if ! command -v uv >/dev/null 2>&1; then
    echo "uv is required. Install it from https://docs.astral.sh/uv/getting-started/installation/ and rerun this script." >&2
    exit 1
fi

PROJECT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

# Keep the caller's working directory so relative input paths still work.
# uv creates/reuses .venv and installs the project and its runtime dependencies.
# Use the tested Python version: current imgui-bundle Linux wheels omit 3.10.
# Never fall back to compiling the GUI and its native dependencies on startup.
exec uv run --project "$PROJECT_DIR" --python 3.12 \
    --no-build-package imgui-bundle uz-dataviewer "$@"

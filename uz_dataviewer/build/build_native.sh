#!/usr/bin/env bash
# Build a native, self-contained UltraZohm Data Viewer executable for the host
# platform (Ubuntu/Linux or macOS). Run from the project root:
#
#     ./build/build_native.sh
#
# Output: dist/uz_dataviewer
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$HERE"

if ! command -v uv >/dev/null 2>&1; then
    echo "uv is required: install it with python -m pip install uv" >&2
    exit 1
fi
export UV_PROJECT_ENVIRONMENT="${UV_PROJECT_ENVIRONMENT:-$HERE/.venv-build}"
uv sync --locked --extra dev --python 3.12 --no-build-package imgui-bundle

rm -rf build/native dist
uv run --no-sync python -m PyInstaller --noconfirm --clean --distpath dist --workpath build/native build/uz_dataviewer.spec

echo
echo "Built: $HERE/dist/uz_dataviewer"

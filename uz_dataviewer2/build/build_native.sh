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

python -m pip install --upgrade pip
python -m pip install -r requirements.txt
python -m pip install "pyinstaller>=6.0"

rm -rf build/native dist
pyinstaller --clean --distpath dist --workpath build/native build/uz_dataviewer.spec

echo
echo "Built: $HERE/dist/uz_dataviewer"

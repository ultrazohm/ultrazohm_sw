#!/usr/bin/env bash
# Build a native, self-contained UltraZohm Scope executable for the host
# platform (Ubuntu/Linux or macOS). Run from the uz_scope2 directory:
#
#     ./build/build_native.sh
#
# Output: dist/uz_scope2
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$HERE"

python -m pip install --upgrade pip
python -m pip install -r requirements.txt
python -m pip install "pyinstaller>=6.0"

rm -rf build/native dist
pyinstaller --clean --distpath dist --workpath build/native build/uz_scope2.spec

echo
echo "Built: $HERE/dist/uz_scope2"

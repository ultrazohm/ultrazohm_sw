#!/usr/bin/env bash
# Build a self-contained native app for Linux (Ubuntu).
# Result: dist/uz-dataviewer/uz-dataviewer
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
cd "${PROJECT_ROOT}"

VENV_DIR="${PROJECT_ROOT}/.venv-build"
if [ ! -d "${VENV_DIR}" ]; then
    python3 -m venv "${VENV_DIR}"
fi
# shellcheck disable=SC1091
source "${VENV_DIR}/bin/activate"
# A globally exported PIP_USER would break installing into the venv.
export PIP_USER=0
unset PYTHONUSERBASE

pip install --upgrade pip
pip install ".[fast,build]"

pyinstaller packaging/desktop/uz_dataviewer.spec --noconfirm --distpath dist --workpath build

echo
echo "Done. Run: ${PROJECT_ROOT}/dist/uz-dataviewer/uz-dataviewer"

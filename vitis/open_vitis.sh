#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE="${SCRIPT_DIR}/workspace"

if ! command -v vitis >/dev/null 2>&1; then
    echo "ERROR: vitis not found on PATH"
    exit 1
fi

if [[ ! -d "${WORKSPACE}" ]]; then
    echo "ERROR: Workspace folder not found: ${WORKSPACE}"
    exit 1
fi

echo
echo "========================================"
echo "Starting Vitis..."
echo "Workspace:"
echo "${WORKSPACE}"
echo "========================================"

cd "${WORKSPACE}"
exec vitis -workspace "${WORKSPACE}"
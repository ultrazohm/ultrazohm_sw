#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE="${SCRIPT_DIR}/workspace"
TCL_SCRIPT="${SCRIPT_DIR}/../tcl_scripts/vitis_generate_UltraZohm_workspace.tcl"
PLACEHOLDER="create_Vitis_workspace_here.txt"

if ! command -v xsct >/dev/null 2>&1; then
    echo "ERROR: xsct not found on PATH"
    exit 1
fi

if [[ ! -f "${TCL_SCRIPT}" ]]; then
    echo "ERROR: TCL script not found: ${TCL_SCRIPT}"
    exit 1
fi

mkdir -p "${WORKSPACE}"

shopt -s nullglob dotglob
unexpected_items=()
for path in "${WORKSPACE}"/*; do
    name="$(basename -- "${path}")"
    if [[ "${name}" != "${PLACEHOLDER}" ]]; then
        unexpected_items+=("${name}")
    fi
done
shopt -u nullglob dotglob

if (( ${#unexpected_items[@]} > 0 )); then
    echo "ERROR: Workspace is not empty."
    echo "       Found unexpected item: ${unexpected_items[0]}"
    echo "       Clear the workspace folder before running this script."
    exit 1
fi

echo
echo "========================================"
echo "Starting XSCT to generate workspace..."
echo "Workspace:"
echo "${WORKSPACE}"
echo "========================================"

cd "${WORKSPACE}"
xsct -eval "setws {${WORKSPACE}}; source {${TCL_SCRIPT}}"

echo
echo "========================================"
echo "Opening Vitis workspace..."
echo "Workspace:"
echo "${WORKSPACE}"
echo "========================================"

exec "${SCRIPT_DIR}/open_vitis.sh"
#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
if (( $# != 0 )); then
    echo "Usage: $0" >&2
    exit 2
fi
command -v xsct >/dev/null || { echo "ERROR: xsct not found on PATH" >&2; exit 1; }
exec xsct -nodisp "${SCRIPT_DIR}/../tcl_scripts/vitis_headless.tcl" build

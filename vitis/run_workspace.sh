#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
if (( $# > 1 )); then
    echo "Usage: $0 [Run_UltraZohm]" >&2
    exit 2
fi
PROFILE="${1:-Run_UltraZohm}"
# Debug profiles need an attached debugger session. Keep selection explicit so
# they can be added here when headless debug session handling is implemented.
if [[ "${PROFILE}" != Run_UltraZohm ]]; then
    echo "ERROR: Unsupported headless profile: ${PROFILE}. Use Run_UltraZohm; use Vitis for Debug profiles." >&2
    exit 2
fi
command -v xsct >/dev/null || { echo "ERROR: xsct not found on PATH" >&2; exit 1; }
exec xsct -nodisp "${SCRIPT_DIR}/../tcl_scripts/vitis_headless.tcl" run "${PROFILE}"

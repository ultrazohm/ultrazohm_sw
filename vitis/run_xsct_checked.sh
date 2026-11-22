#!/usr/bin/env bash
# XSCT can exit successfully without running Tcl; require a fresh receipt.
set -euo pipefail
script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
action="${1:?Firmware action required}"
completion_dir="$(mktemp -d)"
trap 'rm -rf -- "$completion_dir"' EXIT
export UZ_VITIS_COMPLETION="$completion_dir/completed"
flags=(-norlwrap)
if [[ "$action" == open || "$action" == generate-open ]]; then
    flags+=(-nodisp)
fi
"${XSCT:-xsct}" "${flags[@]}" "$script_dir/../tcl_scripts/vitis_headless.tcl" "$@"
if [[ ! -f "$UZ_VITIS_COMPLETION" ]] || [[ "$(cat -- "$UZ_VITIS_COMPLETION")" != "$action" ]]; then
    echo "Vitis $action did not confirm completion; XSCT may have exited before running Tcl." >&2
    exit 1
fi

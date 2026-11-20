#!/usr/bin/env bash
set -euo pipefail

# Resolve the repository independently of the workspace mount path.
cd "$(dirname "${BASH_SOURCE[0]}")/.."

# The mounted .venv belongs to the host and may contain Windows binaries or
# host-only interpreter paths. Install into the container's Python instead.
# Inside the container, run ultrazohm-cli / ultrazohm-dataviewer directly;
# ./uz venv dev can also open a fresh isolated local development shell.
unset VIRTUAL_ENV
wheel_stage="$(mktemp -d)"
trap 'rm -rf -- "$wheel_stage"' EXIT
/usr/local/bin/python ultrazohm_cli/tasks.py wheel --out "$wheel_stage"
wheels=("$wheel_stage"/ultrazohm_cli-*.whl)
if [[ ${#wheels[@]} -ne 1 || ! -f "${wheels[0]}" ]]; then
    echo "Expected exactly one UltraZohm wheel from the container build." >&2
    exit 1
fi
uv export --project ultrazohm_dataviewer --locked --no-dev \
    --no-emit-project --no-emit-package ultrazohm-cli --no-hashes \
    --format requirements.txt --output-file "$wheel_stage/constraints.txt"
uv pip install --system --python /usr/local/bin/python --no-sources \
    --constraint "$wheel_stage/constraints.txt" --only-binary imgui-bundle \
    --reinstall-package ultrazohm-cli \
    "${wheels[0]}" --editable ultrazohm_dataviewer \
    -r requirements.txt -r docs/requirements.txt
uv pip check --system --python /usr/local/bin/python
chmod +x javascope/build.sh javascope/run_with_test_server.sh

# Fail setup visibly if the interpreter cannot load the installed packages.
/usr/local/bin/python - <<'PYTHON'
import sys
from ultrazohm_cli import Acquisition, Client
from ultrazohm_dataviewer import Client as ViewerClient
import polars
import matplotlib

print(f"UltraZohm CLI, Data Viewer and example dependencies ready: {sys.executable}")
print(f"Polars {polars.__version__}; Matplotlib {matplotlib.__version__}")
PYTHON

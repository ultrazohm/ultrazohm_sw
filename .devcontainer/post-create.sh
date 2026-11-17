#!/usr/bin/env bash
set -euo pipefail

# Resolve the repository independently of the workspace mount path.
cd "$(dirname "${BASH_SOURCE[0]}")/.."

# Build the CLI from this checkout after the workspace is mounted.
# Stage this build separately so existing wheels for other hosts cannot be
# selected accidentally. Install exactly the artifact produced by this build.
wheel_stage="$(mktemp -d)"
trap 'rm -rf -- "$wheel_stage"' EXIT
python3 uz_cli/tasks.py wheel --out "$wheel_stage"
wheels=("$wheel_stage"/ultrazohm_cli-*.whl)
if [[ ${#wheels[@]} -ne 1 || ! -f "${wheels[0]}" ]]; then
    echo "Expected exactly one UltraZohm wheel from the container build." >&2
    exit 1
fi
python -m pip install --force-reinstall --no-deps "${wheels[0]}"
python -m pip install "${wheels[0]}[examples]"
python -m pip install -r docs/requirements.txt
chmod +x javascope/build.sh javascope/run_with_test_server.sh

# Fail setup visibly if the interpreter cannot load the installed packages.
python - <<'PYTHON'
import sys
from ultrazohm_cli import Acquisition, Client
import polars
import matplotlib

print(f"UltraZohm Python example dependencies ready: {sys.executable}")
print(f"Polars {polars.__version__}; Matplotlib {matplotlib.__version__}")
PYTHON

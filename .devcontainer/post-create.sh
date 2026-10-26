#!/usr/bin/env bash
set -euo pipefail

# Resolve the repository independently of the workspace mount path.
cd "$(dirname "${BASH_SOURCE[0]}")/.."

# The native extension needs the checked-out sources, so build/install it after
# the workspace is mounted. This also installs the Python example dependencies.
python -m pip install './uz_cli[examples]'
python -m pip install -r docs/requirements.txt
chmod +x javascope/build.sh javascope/run_with_test_server.sh

# Fail setup visibly if the interpreter cannot load the installed packages.
python - <<'PYTHON'
import sys
from ultrazohm import Acquisition, Client
import polars
import matplotlib

print(f"UltraZohm Python example dependencies ready: {sys.executable}")
print(f"Polars {polars.__version__}; Matplotlib {matplotlib.__version__}")
PYTHON

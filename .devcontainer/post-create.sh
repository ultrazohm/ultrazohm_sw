#!/usr/bin/env bash
set -euo pipefail

# Resolve the repository independently of the workspace mount path.
cd "$(dirname "${BASH_SOURCE[0]}")/.."

# Use the same local setup as developers outside the container.
./uz setup local
uv pip install --python .venv/bin/python matplotlib -r docs/requirements.txt
chmod +x javascope/build.sh javascope/run_with_test_server.sh

# Fail setup visibly if the interpreter cannot load the installed packages.
.venv/bin/python - <<'PYTHON'
import sys
from ultrazohm_cli import Acquisition, Client
from uz_dataviewer import Client as ViewerClient
import polars
import matplotlib

print(f"UltraZohm CLI, Data Viewer and example dependencies ready: {sys.executable}")
print(f"Polars {polars.__version__}; Matplotlib {matplotlib.__version__}")
PYTHON

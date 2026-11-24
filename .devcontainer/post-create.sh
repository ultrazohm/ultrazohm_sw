#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")/.."
unset VIRTUAL_ENV
./uz_developer build linux_wheels
uv pip install --python "$UZ_DEVELOPMENT_ENVIRONMENT/bin/python" -r docs/requirements.txt
uv pip check --python "$UZ_DEVELOPMENT_ENVIRONMENT/bin/python"
chmod +x javascope/build.sh javascope/run_with_test_server.sh

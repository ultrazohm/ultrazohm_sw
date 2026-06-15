#!/usr/bin/env bash
# Assemble the static web build (pyodide) into packaging/web/site/.
#
#   ./packaging/web/build_web.sh
#   python -m http.server -d packaging/web/site 8000
#   -> open http://localhost:8000
#
# Steps (per the imgui_bundle pyodide docs):
#   1. build the pure-python wheel of uz_dataviewer
#   2. download the imgui_bundle emscripten (pyodide) wheel
#   3. copy index.html and write a wheel manifest
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
SITE_DIR="${SCRIPT_DIR}/site"
WHEEL_DIR="${SITE_DIR}/wheels"
WHEEL_INDEX_URL="https://imgui-bundle.pages.dev/local_wheels/"

rm -rf "${SITE_DIR}"
mkdir -p "${WHEEL_DIR}"

echo "==> Building uz_dataviewer wheel"
pip wheel "${PROJECT_ROOT}" --no-deps --no-build-isolation -w "${WHEEL_DIR}" \
    || pip wheel "${PROJECT_ROOT}" --no-deps -w "${WHEEL_DIR}"

echo "==> Downloading imgui_bundle emscripten wheel from ${WHEEL_INDEX_URL}"
EMSCRIPTEN_WHEEL="$(curl -fsSL "${WHEEL_INDEX_URL}" | grep -o 'imgui_bundle-[^"<>]*wasm32\.whl' | head -1 || true)"
if [ -z "${EMSCRIPTEN_WHEEL}" ]; then
    echo "ERROR: could not discover the imgui_bundle emscripten wheel."
    echo "Download it manually from ${WHEEL_INDEX_URL} into ${WHEEL_DIR}/"
    exit 1
fi
curl -fsSL -o "${WHEEL_DIR}/${EMSCRIPTEN_WHEEL}" "${WHEEL_INDEX_URL}${EMSCRIPTEN_WHEEL}"

echo "==> Writing manifest and site files"
APP_WHEEL="$(basename "$(ls "${WHEEL_DIR}"/uz_dataviewer-*.whl)")"
cat > "${WHEEL_DIR}/manifest.json" <<JSON
{
    "wheels": [
        "${EMSCRIPTEN_WHEEL}",
        "${APP_WHEEL}"
    ]
}
JSON

cp "${SCRIPT_DIR}/index.html" "${SITE_DIR}/"

# Optional demo data file shown at startup.
if [ -f "${1:-}" ]; then
    cp "$1" "${SITE_DIR}/demo.csv"
    echo "==> Included demo data: $1"
fi

echo
echo "Done. Serve with:  python -m http.server -d ${SITE_DIR} 8000"

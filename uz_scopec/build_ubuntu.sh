#!/usr/bin/env bash
# Build uz_scopec on Ubuntu/Debian: app + tests, Release.
#
# One-time system packages (compiler, CMake, OpenGL/X11/Wayland headers for GLFW):
#   sudo apt-get install -y build-essential cmake ninja-build libgl-dev xorg-dev \
#       libwayland-dev libxkbcommon-dev wayland-protocols
#
# Everything else (GLFW, Dear ImGui, ImPlot, nlohmann_json, doctest) is
# fetched automatically by CMake at configure time.
set -euo pipefail
cd "$(dirname "$0")"

GENERATOR=()
if command -v ninja >/dev/null 2>&1; then GENERATOR=(-G Ninja); fi

cmake -B build -S . "${GENERATOR[@]}" -DCMAKE_BUILD_TYPE=Release "$@"
cmake --build build --parallel
ctest --test-dir build --output-on-failure

echo
echo "Build OK: $(pwd)/build/uz_scopec"
echo "Run:      ./build/uz_scopec [--ip <addr>] [--port <port>] [--connect]"

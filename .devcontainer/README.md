# Application build environment

The `ci` stage supplies the CLI/DataViewer toolchain; `dev` adds firmware, Java and
documentation tools. The Python base image is pinned by digest, and
`build-tools.txt` pins uv, Maturin, Zig, setuptools and wheel. Local Rust wheel
tasks consume the same requirements. Package build-system metadata also pins
the backend needed when installing directly from source.

The CI image tag hashes `Dockerfile`, `build-tools.txt`, and `ci-image-revision`.
Update pins deliberately and increment the revision when rebuilding unchanged
inputs to refresh operating-system packages. APT packages are resolved at image
build time; the image is subsequently reused. This is an explicit refresh policy,
not a claim that separate image rebuilds are byte-for-byte identical.

The application workflow tests installed CLI wheels on Python 3.10, including
configuration, preferences and owned service processes. A separate pinned
manylinux image verifies the Linux wheel on glibc 2.28. Release artifact validation
depends on this compatibility check as well as the existing Linux/Windows tests.
Use workflow dispatch with `publish_prerelease=false` for validation-only runs.

## Developer workflow

Post-create runs `./uz_developer build`, then installs documentation dependencies.
Both wheel-installed applications, Python APIs, development and example dependencies live in
`/opt/ultrazohm/development`, which is on PATH and selected by VS Code.
Run the build command again after source changes, then restart running applications.
`./uz_developer shell` (also `./uz venv dev`) activates this existing environment without rebuilding.
A plain Docker invocation must run `bash .devcontainer/post-create.sh` once.

`./uz_developer verify linux` runs local Linux checks against the built pair.
The shared `ci` stage includes Xvfb, xauth and Mesa; GUI smoke tests start Xvfb
when no display is configured. Interactive GUI use requires host display forwarding.
The repository `.venv` is never used.

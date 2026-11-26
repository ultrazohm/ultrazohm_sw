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

## Extension packaging

The shared `ci` stage also includes Node/npm, Tcl, zstd, Xvfb and Electron system
libraries for extension packaging and tests. Node's source image is digest-pinned.
The reusable image workflow returns an immutable repository digest for CI jobs.
The `dev` stage inherits these tools, so rebuild/reopen the dev container after
Dockerfile changes and run the same Make targets that CI uses:

```sh
make                                      # Package Linux and Windows VSIXs
make extension-build TARGET=linux-x64      # Package one target
make extension-test                       # Linux package + runtime/VS Code tests
```

Run from `ultrazohm-extension/` (or use `make -C ultrazohm-extension` from the
repository root). Make calls the Python build driver directly; it
never launches Docker, detects containers, or installs host tools. VS Code starts
the dev container, and GitHub Actions starts the CI container. Windows developers
use the same commands inside the Linux dev container. Windows execution tests
still require a native Windows runner.

The dev image adds tools and is built locally; sharing a Dockerfile does not
promise byte-identical image rebuilds. To reproduce a CI environment exactly,
start the published digest reported by the CI image job and run the same Make
target inside it. For an unpublished Dockerfile change, a local test is:

```sh
docker build --target ci -t ultrazohm-ci-local .devcontainer
docker run --rm --user "$(id -u):$(id -g)" -e HOME=/tmp \
  -v "$PWD:/work" -w /work/ultrazohm-extension ultrazohm-ci-local make
```

Only this external setup uses Docker. The Make targets assume a prepared
environment. No Docker socket is needed inside the dev or CI container.

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

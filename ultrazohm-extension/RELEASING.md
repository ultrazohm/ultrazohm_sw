# Building and releasing ultrazohm-extension

The supported packages are `ultrazohm-extension-linux-x64-<version>.vsix` and
`ultrazohm-extension-win32-x64-<version>.vsix`. ARM, macOS, browser VS Code and
remote extension hosts are not supported. The extension executes on the local UI
machine. Python and uv are bundled; application packages are downloaded from PyPI
on first use. Vitis remains an external prerequisite for firmware operations.

## CI and testing before a release

Pushes to `feature/vscode-extension`, `main`, `develop`, relevant pull requests,
and manual workflow runs build both native platforms. Matching-path pushes to `main` publish stable releases; pushes to `develop`
publish prereleases after checks pass. Feature-branch pushes and PRs only
validate; manual runs validate unless the explicit prerelease option is selected. Tags are not triggers. Download the two artifacts from the Actions run,
unzip each artifact and select the VSIX matching the test machine.

CI checks JavaScript, launcher and release-tool tests, downloads SHA-256-verified
runtime archives, packages the extension, checks its archive contents and runs
the shipped Python/uv. It exercises PyPI CLI/DataViewer help and dependency
imports in fresh private storage, then launches fixture tasks in the packaged
extension in VS Code 1.93.0 and current stable VS Code. Published-command tests check every exposed command and exercise a real interactive CLI service with fake XSCT, including checkout mismatch, flash success and failure propagation. No automated tests program hardware. Test a real DataViewer GUI, interactive CLI, Python shell,
Vitis setup and firmware operations on suitable test machines before a public
release. Verify recording finalization and reconnect behavior during Flash UZ.

Install with **Extensions: Install from VSIX…** or:

```sh
code --install-extension ultrazohm-extension-linux-x64-0.1.11.vsix
```

Uninstall either earlier prototype (`ultrazohm-local.ultrazohm` or
`ultrazohm-local.ultrazohm-extension`) to avoid duplicate panes. The new ID is
`ZohmControlGmbH.ultrazohm-extension`. Existing `ultrazohm.*`
settings remain valid, but private storage starts fresh. GitHub VSIX installations
receive updates by manually installing a newer VSIX. Keep a previous release for
manual rollback.

## Local build

Use Node 22+ and Python 3.14+ on the target OS. Python 3.12/3.13 also work if
`zstd` is on PATH. These are maintainer requirements, not end-user requirements.
From this directory:

```sh
npm ci
npm run check
npm test
python -m unittest discover -s tools -p 'test_*.py'
python tools/bundle.py --target linux-x64
mkdir -p dist
npm run package -- --target linux-x64 --pre-release --out dist/ultrazohm-extension-linux-x64-0.1.11.vsix
python tools/release.py verify --target linux-x64 --vsix dist/ultrazohm-extension-linux-x64-0.1.11.vsix --extract .package-test --smoke-channel prerelease
```

On Windows replace `linux-x64` with `win32-x64`; create `dist` using PowerShell's
`New-Item -ItemType Directory -Force dist`. Set `UZ_EXTENSION_TEST_PATH` to
`.package-test/extension`, then run `npm run test:host`. Linux CI uses
`xvfb-run -a npm run test:host`. `VSCODE_TEST_VERSION` selects a host version;
`VSCODE_TEST_EXECUTABLE` optionally points to an existing VS Code executable.
Remove `.package-test` before verifying another package. Pass `--replace` when
rebuilding `runtime/`; generated runtimes/caches/VSIXs are ignored by Git.

`runtime-lock.json` pins uv, CPython, source archive hashes and redistribution
notices. To update runtime versions, update those pins, verify upstream hashes,
keep root `.uv-version`/`.python-version` compatible, and rebuild both targets.
The Python full distribution supplies native dependency license notices omitted
from its smaller install archive. Bundled launcher scripts are copied from the
root by `vscode:prepublish`, not maintained separately. PyPI packages remain
floating according to the selected channel; a release receipt records the exact
versions tested, not a permanent application dependency lock.

## Automatic branch releases

The extension follows the CLI/DataViewer branch policy: matching-path pushes to
`main` publish stable releases, and matching-path pushes to `develop` publish
prereleases. Both native platform checks must pass. The existing path filters
limit which pushes start the workflow. PRs and feature-branch pushes build/test only; fork repositories cannot publish.
Manual runs build/test by default, with an explicit prerelease publishing option
for `develop` and `feature/vscode-extension` only.

CI stamps `MAJOR.MINOR.<GITHUB_RUN_NUMBER>` into `package.json` and
`package-lock.json` in the runner checkout only. With the current base this is
`0.1.<run>`. No version-bump commits are needed. Both platforms and publishing
jobs derive the same version, and rerunning a job retains that version. Keep
the workflow filename unchanged so its run-number counter and trust policy
remain valid. The extension's counter is independent of the CLI/viewer counter.

The branch selects the channel; odd/even minor numbers no longer select it.
Marketplace versions are numeric, so prereleases use the same numeric format
with `--pre-release`, rather than Python's `.dev0`. Prerelease users can receive
a newer stable version and remain opted in to later prereleases. The extension's
in-app Python-package channel setting remains independent.

After verification, the GitHub Release job creates
`ultrazohm-extension-v<version>` at the exact build commit automatically, creates
a draft with both VSIXs, `SHA256SUMS` and `release-manifest.json`, then publishes
it. No manually pushed tag or PAT is required. Tags identify releases; they do
not initiate builds. The job rejects missing receipts or altered artifact hashes.

Published assets are never overwritten. Rerun only failed jobs when possible.
If a GitHub draft was left incomplete, inspect/remove that incomplete draft
before retrying its job. Do not rebuild and replace an already published version;
a new matching-path push gets a fresh run number. Checksums detect changed bytes
but are not independent signatures.

## Publish a feature-branch prerelease for testing

In Actions, open **ultrazohm-extension**, choose **Run workflow**, select
`feature/vscode-extension`, and enable **Publish prerelease**. Equivalently:

```sh
gh workflow run ultrazohm-extension.yml \
  --repo ultrazohm/ultrazohm_sw \
  --ref feature/vscode-extension \
  -f publish_prerelease=true
```

This publishes a real prerelease to GitHub Releases and Marketplace after the
same Linux/Windows checks pass. It does not bypass tests or publish a stable
version. Each new dispatch gets a new run-number version. Leaving the option
unchecked only produces test artifacts. Manual publication from `main`, other
feature branches, tags, or forks is not allowed. The same option is available
on `develop`. The workflow must be available on the repository's default branch
for GitHub's manual workflow UI to offer it. Until then, use the CLI command
above: this workflow is already registered by its feature-branch push runs.

## Marketplace publication

The publisher ID is `ZohmControlGmbH`; the extension ID is
`ZohmControlGmbH.ultrazohm-extension`. The registered Trusted Publishing policy
matches repository owner `ultrazohm`, repository `ultrazohm_sw`, and workflow
`ultrazohm-extension.yml`. It has no GitHub environment. No PAT secret is required.

After both native builds pass and the GitHub Release succeeds, the Marketplace
job downloads those same artifacts, verifies the build receipts and hashes, and
publishes both VSIXs with pinned `vsce` using `--oidc`. The branch release rules
above select stable/prerelease. PRs never publish; manual publishing requires the explicit prerelease option.

If Marketplace publishing fails after one platform is accepted, rerun the failed
job: `--skip-duplicate` skips the accepted package and publishes the missing one.
Marketplace availability can lag behind the upload while processing completes.
Changing the repository, workflow filename or adding a GitHub environment also
requires updating the publisher's trust policy.

References: [VS Code publishing](https://code.visualstudio.com/api/working-with-extensions/publishing-extension),
[extension testing](https://code.visualstudio.com/api/working-with-extensions/testing-extension),
[GitHub release CLI](https://cli.github.com/manual/gh_release_create).

## Hardware debugger acceptance

CI uses fake XSCT and exercises the published service, wrapper job selection,
stop receipts, adapter teardown and task guards. It cannot certify JTAG behavior.
Before calling Debug hardware-validated, test on native Linux and Windows with
Vitis and Microsoft C/C++ installed:

1. Open the extension's interactive CLI. Click **Debug** with one UZ connected.
   Confirm both `UltraZohm R5` and `UltraZohm A53` stop in `main`, and that the
   service stays disconnected with recordings finalized.
2. Continue each core explicitly. Confirm firmware operation and reconnect from
   the CLI/DataViewer after both have resumed.
3. Stop each debugger; confirm detach does not reset or reprogram firmware. Run
   **Attach debugger** against the matching ELFs and inspect both cores again.
4. Check a missing JTAG cable, unavailable main symbol, failed build, second
   connected board and an occupied external CLI endpoint. Failures must not be
   reported as a successful Debug handoff.
5. After closing the debugger sessions, run ordinary **Flash UZ**. Confirm it
   follows its existing reconnect behavior and does not stop at main.

Debug supports the default local hw_server layout with one R5 #0 and one A53 #0,
each GDB processor ID 1. Do not operate another debugger or firmware programmer
against that board concurrently.

## Container build workflow

Rebuild/reopen the repository's dev container after Dockerfile changes. From the
`ultrazohm-extension/` directory **inside the container**, use the same targets as Linux CI:

```sh
make                                      # Default: build both VSIXs
make extension-build TARGET=linux-x64
make extension-build TARGET=win32-x64
make extension-test                       # Build and verify Linux
```

Windows developers run these commands inside the Linux dev container as well.
The host needs the dev-container setup; it does not need Node/Python/Make for
these builds. Make itself assumes the tools are already installed and directly
calls `tools/build.py`. It does not start Docker or detect its environment.
VS Code and GitHub Actions manage container startup. See
[the shared image guide](../.devcontainer/README.md) for an explicit `docker run`
example and using an exact published CI image digest.

Builds snapshot current extension sources, root launchers and test fixtures into
separate temporary directories. Local edits are included; source versions,
node_modules and generated runtimes are not modified. Outputs go to
`ultrazohm-extension/dist`; override with `make OUTPUT=/some/output`. Runtime and
npm downloads use `ultrazohm-extension/.build-cache`; override with
`UZ_BUILD_CACHE=/some/cache`. Delete that directory to exercise a cold build.
CI remains correct with empty caches. Network access is required.

`extension-test` packages and verifies Linux, including published-package
contracts and minimum/current stable VS Code host tests under Xvfb. CI calls
this complete target instead of duplicating its steps in YAML. Windows
packaging does not execute Windows binaries inside Linux. Native Windows
verification remains mandatory in CI.

Migration is deliberately staged: Linux CI uses the shared image and build
entry point. The existing native Windows build remains the released Windows
artifact. An additional job builds Windows in Linux and a native Windows job
verifies that VSIX; releases require this check as well. Only after a successful
run should native Windows packaging be removed and the cross-produced artifact
promoted to the release. No claim of Windows validation is made by a local Linux
build alone.

Archive inspection is available as `tools/release.py inspect`; `verify` adds
native runtime checks. Receipts record the builder image when supplied. GitHub
release retries verify existing assets and only fill missing draft assets;
conflicting published assets are rejected. Marketplace uploads reuse tested
VSIXs, then check both targets for up to roughly two minutes. Pending processing
is reported separately and never causes repackaging.

## Release verification and integration checks

Release decisions come from `tools/release.py metadata`. Receipts must match the
current commit and channel and record both minimum/current VS Code host checks.
An unverified rebuild removes any old receipt. Failed isolated builds export
VS Code profiles and the failed command under `dist/diagnostics`; CI uploads
these on failure. The internal design document is excluded from VSIXs.

Linux `make extension-test` also downloads Microsoft C/C++ 1.35.6 and exercises
the real adapter through our proxy against a disposable local gdbserver target.
It checks initialization, launch, foreign-source breakpoint filtering and detach
without terminating the target. This requires gcc, gdb and gdbserver (included
in the shared image) and does not access Vitis or hardware. Native Windows
adapter/hardware acceptance remains separate.

Native Windows packaging remains until the cross-produced VSIX passes native
Windows CI. This migration gate must not be bypassed just to remove duplicate jobs.

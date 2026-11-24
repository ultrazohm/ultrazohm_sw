# Building and releasing ultrazohm-extension

The supported packages are `ultrazohm-extension-linux-x64-<version>.vsix` and
`ultrazohm-extension-win32-x64-<version>.vsix`. ARM, macOS, browser VS Code and
remote extension hosts are not supported. The extension executes on the local UI
machine. Python and uv are bundled; application packages are downloaded from PyPI
on first use. Vitis remains an external prerequisite for firmware operations.

## CI and testing before a release

Pushes to `feature/vscode-extension`, `main`, `develop`, relevant pull requests,
and manual workflow runs build both native platforms. No release is published by
a branch push or manual run. Tagged releases publish to GitHub and then Marketplace. Download the two artifacts from the Actions run,
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

## Publish a GitHub Release

1. Update `package.json` and `package-lock.json` together, and add release notes
   to `CHANGELOG.md`. Use numeric versions. Odd minor versions (such as `0.1.11`)
   are prereleases; even minor versions (such as `0.2.0`) are stable. This policy
   is separate from the application's stable/prerelease selector.
2. Commit and push the release commit. Verify both platform builds and manual
   smoke tests. Review changes to runtime pins and bundled launcher scripts.
3. Explicitly create and push the matching tag:

   ```sh
   git tag -a ultrazohm-extension-v0.1.11 -m 'ultrazohm-extension 0.1.11'
   git push origin ultrazohm-extension-v0.1.11
   ```

The tag workflow rebuilds/tests both targets. It rejects mismatched versions,
missing platform verification receipts and changed artifact hashes. A release
job with narrowly scoped `contents: write` creates a draft, attaches both VSIXs,
`SHA256SUMS` and `release-manifest.json`, then publishes it. No PAT is needed;
it uses the workflow's GitHub token. Checksums detect changed downloads and are
not independent signatures. GitHub organization policy must permit the release
job to use its declared write permission.

The workflow never overwrites published assets. If publication fails after draft
creation, inspect that draft; remove only the incomplete draft before rerunning
the release job, or finish publishing its verified complete assets manually.
Do not reuse published versions or move published tags. Fix with a new version.

## Marketplace publication

The publisher ID is `ZohmControlGmbH`; the extension ID is
`ZohmControlGmbH.ultrazohm-extension`. The registered Trusted Publishing policy
matches repository owner `ultrazohm`, repository `ultrazohm_sw`, and workflow
`ultrazohm-extension.yml`. It has no GitHub environment. No PAT secret is required.

After both native builds pass and the GitHub Release succeeds, the Marketplace
job downloads those same artifacts, verifies the build receipts and hashes, and
publishes both VSIXs with pinned `vsce` using `--oidc`. The existing odd/even minor
version policy selects prerelease/stable. Branch pushes and manual runs cannot
publish. Use the matching version tag described above to trigger publication.

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

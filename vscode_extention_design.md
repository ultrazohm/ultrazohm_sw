# ultrazohm-extension design

Status: prototype 0.1.11 implemented in `ultrazohm-extension/`, on the
`feature/vscode-extension` worktree. This design supersedes earlier proposals;
the original issue remains unchanged at the end.

## Purpose and scope

Provide a clickable frontend to `uz` / `uz.ps1`, with a bundled/local launcher selector. Bundled is the default and supports operation without an UltraZohm checkout.
The CLI, launcher and DataViewer retain application, firmware and device logic.
Application packages come exclusively from PyPI. Local mode takes launcher scripts and requirements from the checkout; bundled mode takes them from the VSIX. A selected checkout supplies firmware sources in either mode.

The VSIX bundles uv and CPython 3.12. Installing the extension requires no separate
Python/uv setup. First use downloads application packages into extension-owned
storage. Vitis remains an external prerequisite for firmware operations.

## Launcher source

`ultrazohm.launcher.source` selects `bundled` (default) or `local`, independently
of the stable/prerelease package channel. The pane exposes this as **Launcher**.
Bundled scripts are copied verbatim from the shared root scripts by
`tools/bundle-launcher.js` during VSIX packaging. Include both platform launchers,
bootstraps, `uz.py`, `uz_shell.py`, `uz_venv.py`, version files and requirements.
Generated `launcher/` is not a second maintained implementation.

Bundled DataViewer and Python-shell actions work without a
checkout, with any trusted local folder open. Omit `--live-repo`/`--repo`
when none is selected. Use the opened folder as cwd and task scope. An empty window shows an instruction to open any local folder, because VS Code global tasks are unsupported. Settings in an empty window save
at user scope. Firmware actions require a checkout and XSCT in both modes. The interactive CLI also requires a checkout because the published CLI generates its channel mapping from firmware sources.

Bundled Python shells use the packaged requirements; local Python shells use
the checkout's requirements. Source changes apply on the next launch; existing
tasks are reused until exited. Both modes use bundled uv/Python and private
storage, and PyPI application packages. Launcher updates in bundled mode require
a rebuilt VSIX; local edits apply immediately on the next launch.

## Workspace selection

A single opened UltraZohm checkout is the default root. **Find ultrazohm_sw directory…**
opens a folder picker and saves `ultrazohm.repository` for the current VS Code
workspace. This explicitly selected root overrides the opened folder, so a user
can keep an unrelated project open. An empty VS Code window opens the picked
checkout; a multi-root workspace requires an explicit selection.

In bundled mode identify a firmware checkout by its `vitis` and `ip_cores` paths. In local mode validate an absolute path containing `uz.py`, `.python-version`, `.uv-version` and the platform launcher; this runtime supports Python 3.12. In local mode the selected
checkout must include the bundled-runtime bootstrap and private-shell changes
from this branch. Do not require a particular directory name or a `.git`
directory: worktrees have a `.git` file. A cancelled/invalid selection preserves
the previous choice.

When a checkout is selected, task working directories, repository arguments, task
identities and shared XSCT preferences use the selected root. Tasks remain
associated with the opened VS Code workspace. Changing the selection does not
retarget applications that are already running.

Support trusted, local filesystem windows on native Linux and Windows. Remote,
WSL, devcontainer, virtual and macOS windows are outside this prototype's scope.
Two worktrees can run in separate VS Code windows with separate settings/tasks.
Acquisition services need different endpoints if both are running.

## Pane and command contract

Use the DataViewer's UZ logo for the dedicated Activity Bar container. Its
placement follows the user's VS Code navigation layout. The sidebar has three separate native collapsible views in this order: **Setup**
(directory picker, launcher source, XSCT, release channel, terminal visibility),
**Software build** (generate, build, Flash UZ, clean/build), and **Control**
(DataViewer, interactive CLI, Python environment). VS Code manages each view’s
collapse state and placement. A toolbar refresh button rechecks prerequisites.

Let `R` be the selected root, `C` the stable/prerelease channel, and `E` the
interactive CLI endpoint (default `127.0.0.1:19740`). Each task runs in `R`.
Linux executes `/bin/bash L/uz`; Windows executes Windows PowerShell with
`-NoProfile -ExecutionPolicy Bypass -File L/uz.ps1`, where `L` is the packaged
launcher directory or `R` according to launcher source. Arguments are passed
separately through `ProcessExecution`, including paths containing spaces.

| Action | Equivalent Linux command | Terminal |
| --- | --- | --- |
| Launch DataViewer | `./uz dataviewer C -- gui --live-repo R` | Visible or hidden according to preference. |
| Open interactive CLI | `./uz cli C -- --endpoint E serve --interactive --repo R` | Always visible. |
| Open Python environment | `./uz venv C` | Always visible activated OS shell. |
| Generate Vitis workspace | `./uz cli C -- generate --local --repo R` | Always visible. |
| Build firmware | `./uz cli C -- build --local --repo R` | Always visible. |
| Flash UZ | Published CLI service firmware API, verified against R | Always visible, after confirmation. |
| Clean and build firmware | `./uz cli C -- build-clean --local --repo R` | Always visible. |

Before CLI/firmware launch, run that published command's `--help` through the
same selected launcher and private runtime. This checks available flags and
prepares any initial package download under a progress notification. Older
published CLI versions already run firmware commands locally and lack
`--local`; omit it for those packages. Supply `serve --xsct` when advertised.
Always prepend the selected XSCT directory to the task PATH. Require `--repo`
support; report incompatible packages instead of guessing their repository.
No Rust/Python application logic is copied into the extension.

## Vitis / XSCT discovery

The picker accepts `settings64.sh` on Linux and `settings64.bat` on Windows,
as well as the existing direct XSCT selection. Persist the setup path in
`ultrazohm.vitis.settingsScript`, a machine-scoped VS Code user setting. It
survives window/application restarts and reboots and applies across workspaces.
Bash sources the Linux script; CMD calls the Windows script. Capture their
resulting environments, discover XSCT on that PATH, and apply the environment
to extension tasks before enforcing private uv/Python/cache settings.

Validate the script and discovered XSCT before saving a picker choice. With a
configured script, its result takes precedence over repository XSCT preferences;
write the resolved XSCT back to the selected checkout's shared tools file when
launching, so published CLI versions use the same tool. No machine-wide PATH
change is made. Missing/failing scripts leave firmware buttons disabled. Cache
the environment per script path and modification time; Refresh forces a reload.
The PATH reset action clears the setup script and selected repository preference.

The following direct XSCT discovery applies when no setup script is selected.


Resolve the saved `xsct` field in `R/artifacts/_user/tools.json`, then PATH if
there is no saved choice. A saved but missing/nonexecutable launcher remains an
error so the user can correct it. Linux requires an executable file; Windows
accepts the `xsct.exe`, `xsct.cmd` or `xsct.bat` launcher.

Click **Vitis / XSCT** to browse to the launcher in the Vitis `bin` directory.
Save the absolute path to the shared tools file while preserving other fields.
Malformed JSON is reported rather than overwritten. The Command Palette action
**ultrazohm-extension: Use XSCT from PATH** clears the saved choice.

Generate/build/build-clean/flash have grey labels/icons and no click command when
XSCT or the repository is unavailable. Their Command Palette entries recheck
these requirements before starting. DataViewer, CLI and Python-shell actions
remain available without Vitis. A file watcher and refresh button recheck the
shared settings. Existence/executability is a launch prerequisite, not a Vitis
version or installation-health check.

## Task and service behavior

Use VS Code tasks for process ownership and output. Separate task identities
exist for DataViewer, interactive CLI, Python shell and firmware, scoped by
selected repository. Generate/build/clean/flash share one firmware slot per checkout.
Pending-start guards prevent rapid-click duplicates; existing task definitions
allow rediscovery after extension reactivation. Repeated clicks reveal the
existing task instead of restarting it. Hidden DataViewer tasks remain hidden
on repeated clicks.

Interactive CLI means `serve --interactive`: the prompt owns the service, and
EOF/Ctrl-C ends it. There is no separate background-service action, client-only
REPL attach, status button or shutdown button. Check the configured loopback
port before starting and again after package preparation. An occupied endpoint
is reported without stopping or replacing any process. This port check does not
assert service identity; the CLI remains responsible for the final bind race.

DataViewer launch does not start or attach a service automatically. Existing
services can be used through DataViewer's own controls. The Python environment
opens Bash/PowerShell, not a CLI prompt, and starts no service.

Application failures stay visible in task output; failed starts can be retried.
A running task does not imply device connection or application readiness.
Closing VS Code follows ordinary task behavior; there is no detachment guarantee
or custom automatic device shutdown on extension deactivation.

## Settings

| Setting | Default | Scope/meaning |
| --- | --- | --- |
| `ultrazohm.launcher.source` | `bundled` | Packaged scripts or `local` checkout scripts. |
| `ultrazohm.repository` | Empty | Use opened folder unless a checkout is explicitly selected. |
| `ultrazohm.dataviewer.channel` | `stable` | Shared package channel for all actions; keep the existing key to preserve saved choices. |
| `ultrazohm.dataviewer.terminal` | `visible` | DataViewer only; `hidden` disables automatic terminal reveal and focus. |
| `ultrazohm.cli.endpoint` | `127.0.0.1:19740` | Interactive CLI service endpoint; loopback IPv4 only. |

Selectors persist in the current folder, workspace settings for multi-root
windows, or user settings when no folder is open. Changes affect future tasks; they do not restart running applications.
Hidden output remains accessible in the Terminal panel, and changing visibility
does not hide an already visible terminal.

The channel passes unchanged to `uz`: stable disallows prereleases; prerelease
allows them. It is neither an exact version pin nor a force-update request.
Package resolution/cache behavior belongs to the launcher. An unavailable
channel produces a launcher error; never silently fall back to another channel.

## Bundled and private runtime

The VSIX contains platform-matched uv and managed CPython 3.12. The launcher
bootstrap accepts `UZ_BUNDLED_RUNTIME` / `UZ_BUNDLED_PYTHON` and executes the
bundled interpreter directly in this mode. Ordinary manual bootstrap behavior
is retained.

Task environment overrides inherited uv/Python environment selections. Python
downloads, registry integration and user-site loading are disabled. uv cache,
tool environments, tool executables and temporary files live under the
extension's global storage. There is no host-wide install, permanent PATH
change or repository `.venv` creation.

`UZ_PRIVATE_SHELL_DIR` makes `uz_shell.py` skip user shell profiles, store shell
history privately and create temporary activation files in private storage.
The private Linux startup file adds a green user/host prompt, blue working directory and `ls --color=auto`. It respects `NO_COLOR`, `TERM=dumb` and nonterminal output; activation retains its environment prefix. This applies only to the extension's shell; normal manual launch behavior stays
unchanged. Arbitrary user commands in that shell are not sandboxed. DataViewer
preferences, recordings and firmware build outputs retain their usual locations.

## Flash UZ

Flash UZ confirms the selected checkout/channel, then uses the published CLI's
service-managed firmware API. It opens an interactive CLI if the configured local
endpoint is unused, or reuses the listening service after checking its reported
repository and firmware availability. Mismatched services are never retargeted.
The CLI owns acquisition shutdown, recording finalization, build/programming and
reconnection. A known device target is preserved; an initially disconnected
service with no target flashes without reconnecting. The flash terminal follows
job logs and reports errors, but closing it does not cancel an accepted job.
The interactive CLI remains available. Older standalone-only CLI versions are
rejected with an instruction to update packages. No application or Tcl changes
are required. Generate/build/clean remain explicit local operations.

CI checks published subcommand flags and the DataViewer GUI repository option.
It exercises local firmware commands and the packaged flash helper against a real
published interactive service and fake XSCT, including wrong-checkout rejection,
successful disconnected flashing and failed-job propagation. No hardware is used.

## Commands without dedicated buttons

| Command/family | Where it remains available / why omitted |
| --- | --- |
| Noninteractive `serve`, `status`, `shutdown` | CLI/DataViewer; only interactive service ownership is exposed in this pane. |
| `./uz install cli/dataviewer C` | Manual root launcher; global user commands are unnecessary for the extension. |
| `./uz venv dev` | Manual root launcher; requires development/build tools and local application source. |
| Firmware jobs/job inspection | CLI/DataViewer; the extension displays task output. |
| Device connection, Enable/Stop, variables, observables, buttons, error reset | Existing CLI prompt and DataViewer controls. |
| Recording and data queries | Existing CLI/DataViewer/APIs. |
| Profiles, channel mapping and header conversion | Existing CLI workflows. |
| Viewer plotting, analysis, export, automation | DataViewer and its API. |
| Advanced service flags/arbitrary arguments and help | Existing terminal workflows. |
| Developer build/check/docs/test commands | `./uz_developer`, not invented `./uz` aliases. |

Omission means no pane button; capabilities are not removed. Manual root-level
commands are the escape hatch for options this frontend does not expose.

## Implementation and verification

The extension uses plain JavaScript and native VS Code APIs: `extension.js`
handles the view, configuration and tasks; `runtime-env.js` builds private
environments; `tools.js` owns shared XSCT preference handling; `service.js`
checks the loopback endpoint; `cli-capabilities.js` probes published CLI help.

Verification covers task argv/cwd/environment, duplicate starts, command
independence, local firmware compatibility with older published CLIs, disabled
XSCT actions, external checkout selection/cancellation, preference persistence,
private shell behavior and occupied endpoint handling. An isolated real VS Code
Extension Host fixture exercises the launcher tasks, task termination, repeated-click
reveal and a selected root with spaces outside the opened folder. Published
prerelease CLI help and a real published-package Python shell were also exercised.
Actual Vitis builds, attached hardware and native Windows execution still need
validation.

## Installation and distribution

The Linux test artifact is
`ultrazohm-extension/dist/ultrazohm-extension-linux-x64-0.1.11.vsix`. Install it with
**Extensions: Install from VSIX…**, or `code --install-extension <vsix>`.
A tester needs no npm or Marketplace account. Open the UZ pane and select this
worktree with **Find ultrazohm_sw directory…** if necessary. Choose a channel published
on PyPI; testing here used prerelease. Windows needs a separate Windows artifact.

For development, run `npm ci`, `npm run check` and `npm test` under
`ultrazohm-extension/` using Node 22+. Bundle matching uv/Python using
`tools/bundle.py` and include their redistribution notices. Then run
`npm run package -- --target linux-x64` (or `win32-x64` on Windows).
Use the supplied `.vscode/launch.json` Extension Development Host configuration
for iteration; no TypeScript compile step is required.

The temporary local identity is `ultrazohm-local.ultrazohm-extension`. Increment extension
versions for shared VSIXs, independently of CLI/DataViewer package versions.
Bundled uv/Python updates require a new VSIX. The in-extension stable/prerelease
choice affects application packages, not extension update channels.

Start distribution with tested platform VSIXs as release attachments. Before
Marketplace publication, establish an UltraZohm-controlled publisher and final
extension ID, validate Windows and Linux packages, runtime licenses and README
assets, and configure publisher access. Upload the tested platform artifacts
through Marketplace publisher management; automate subsequent releases after
publisher access and credentials/trusted publishing are configured. Public
publication, account creation and credential changes are not part of this
implementation.

## Automated extension releases

The extension name and platform artifact prefix are `ultrazohm-extension`.
`.github/workflows/ultrazohm-extension.yml` builds Linux x64 and Windows x64 on
native runners. It runs unit tests, verifies checksum-pinned bundled runtimes
and redistribution notices, smoke-tests published PyPI applications, and runs
fixture tasks in minimum-supported and current stable VS Code hosts.

Branch/PR/manual builds upload downloadable workflow artifacts. Only an explicit
`ultrazohm-extension-v<version>` tag matching `package.json` publishes a GitHub
Release after both platforms pass. It includes both VSIXs, SHA256SUMS and a
runtime/application verification manifest. Odd minor versions are prereleases;
even minor versions are stable. This is independent of the user-selected PyPI
channel. Marketplace publishing is deferred. See
`ultrazohm-extension/RELEASING.md` for installation and release procedures.

## Explicit package updates

Setup includes **Update Python packages**. Normal launches reuse uv's cached
environments. Updating explicitly refreshes CLI, DataViewer and the Python-shell
environment for the selected channel, using bundled uv/Python and private storage.
It uses bundled/local launcher requirements according to the selected source.
A visible task terminal reports progress, resolved versions and errors. Running
UltraZohm tasks must be closed first; new tasks are blocked in this window while
updating. Other windows must be stopped manually. Failures may leave some of the
three environments updated; retry after resolving the reported cause. This does
not update the VSIX, Python or uv, and does not modify application/launcher code.

## Original issue (historical reference)

The agreed design above supersedes the broader proposal below for this prototype.
The original issue text is preserved unchanged, including its obsolete setup
commands and broader acceptance criteria.

<details>
<summary>Issue #976: original title, source, and body</summary>

# UltraZohm VSCode extension

Source: https://github.com/ultrazohm/ultrazohm_sw/issues/976

- https://github.com/ultrazohm/ultrazohm_sw/pull/971 introduces the ultrazohm-cli and repo-level commands that were scattered in individual directories up to today (e.g., generate workspace script)
- More commands will get a repo-root-level alias, such as building the docs or running ceedling
- Commands require the terminal at the moment
- With ultrazohm-cli packaged, we can introduce a VSCode extension that just maps repo-root level commands to buttons in VSCode

Astras Plan for this:
## Proposal

Create a lightweight TypeScript VS Code extension that exposes UltraZohm development and device-control workflows through sidebar buttons and commands. Reuse the existing CLI, bootstrap scripts, and native DataViewer.

## Initial scope

- **Setup/update tools:** select `stable`, `prerelease`, or `local`.
- **Device control:** start or reuse the acquisition service, connect, display status, enable system/control, and send Stop.
- **Recording:** start and stop logging.
- **Firmware:** generate the Vitis workspace, build firmware, and program/run via JTAG.
- **DataViewer:** launch the native application with the current repository selected.
- **Terminal:** open the existing UltraZohm environment shell.

## Technical approach

Reuse the [[existing setup implementation](https://github.com/ultrazohm/ultrazohm_sw/blob/1cb977b2f31b1e6e05ae0f5d0dac0776a034619b/ultrazohm_dataviewer/tools/setup_env.py)](https://github.com/ultrazohm/ultrazohm_sw/blob/1cb977b2f31b1e6e05ae0f5d0dac0776a034619b/ultrazohm_dataviewer/tools/setup_env.py):

- Linux: `./uz setup <source> --app viewer`
- Windows: `.\uz.ps1 setup <source> --app viewer`

This bootstraps uv/Python and prepares both applications in the repository’s `.venv`. Run setup explicitly for installation or updates; ordinary launches must reuse the environment because setup recreates it.

Launch applications through the environment’s Python interpreter using argument arrays:

- Backend: `-m ultrazohm_cli serve --repo <root>`
- Viewer: `-m ultrazohm_dataviewer gui --live-repo <root>`

Use existing CLI commands for actions and JSON responses for status. Capture output and failures in a VS Code output channel. Check service readiness and track whether the extension started or attached to the service.

Initially, users attach the DataViewer through its existing **Existing service → Attach** action.

Firmware operations require Vitis/XSCT. Programming must explicitly coordinate acquisition shutdown and reconnection; the raw CLI programming command does not provide the complete viewer workflow.

For devcontainers, launch the GUI on the desktop and run build/test tasks in the workspace environment. Host and container require separate virtual environments and explicit repository-path handling.

## Acceptance criteria

- [ ] Setup and application launching work on supported Windows and Linux systems.
- [ ] Button actions report progress, output, and errors without blocking VS Code.
- [ ] Existing acquisition services are reused without spawning duplicates.
- [ ] Ordinary launches preserve the prepared environment.
- [ ] DataViewer opens as a native window with the correct repository.
- [ ] Host/container execution locations and environments are handled explicitly.


</details>

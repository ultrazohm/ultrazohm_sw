# ultrazohm-extension

Install the platform VSIX using **Extensions: Install from VSIX…**, then open the **UZ** Activity Bar button. Use a trusted native Linux or Windows window. The navigation button follows your VS Code sidebar placement. The sidebar has three independently collapsible sections, like Explorer’s Outline and Timeline: **Setup** (directory, launcher, XSCT, release channel, terminal), **Software build** (generate, build, flash, debug, attach, clean/build), and **Control** (DataViewer, interactive CLI, Python environment).

Open an UltraZohm checkout directly, or click **Find ultrazohm_sw directory…** to select one while keeping your current folder open. The selection is saved for this VS Code workspace. The selected checkout supplies firmware sources and repository arguments. **Launcher: bundled/local** chooses where the `uz` / `uz.ps1` scripts come from. Bundled is the default and also works with any unrelated local folder open: DataViewer and the Python environment do not require a checkout. Interactive CLI and firmware actions still require one: the published CLI generates its channel mapping from firmware sources. In an empty window, the picker opens the selected checkout. With multiple folders, select the checkout explicitly.

| Control | Behavior |
| --- | --- |
| Launch DataViewer | Open the native viewer with the selected checkout. |
| Open interactive CLI | Open the CLI prompt and its acquisition service in a visible task terminal. Exit/Ctrl-C ends the service. |
| Open Python environment | Open an activated Bash/PowerShell shell with published packages and the checkout's requirements. Type `exit` to close it. |
| Generate Vitis workspace | Run the CLI's local `generate` command. |
| Build firmware | Run the CLI's local `build` command. |
| Clean and build firmware | Run the CLI's local `build-clean` command. |
| Flash UZ | Confirm, then build, program via JTAG and run through the CLI service. |
| Vitis / XSCT | Select `settings64.sh` on Linux or `settings64.bat` on Windows; direct XSCT selection is also supported. |
| Launcher | Use scripts bundled in the VSIX (default), or the selected checkout's scripts. |
| Update Python packages | Refresh CLI, DataViewer and the Python environment for the selected channel, with progress in a visible task terminal. Close running UltraZohm tasks first. |
| Release channel | Choose stable or prerelease for all actions. Stable is the default. |
| Terminal | Choose whether DataViewer automatically shows/focuses its terminal. Other actions always show theirs. |

The setup-script path is stored in the machine-specific VS Code user setting `ultrazohm.vitis.settingsScript`. It survives VS Code restarts and reboots and is shared across workspaces on this machine. The extension sources the script in Bash on Linux or calls it through CMD on Windows, discovers XSCT from the resulting PATH, and applies that environment to its tasks. Private uv/Python settings are reapplied afterward. The script must expose XSCT before a picker selection is saved; a missing/broken configured script disables firmware actions. Refresh rechecks the script.

Firmware buttons are grey and nonclickable until XSCT is found. Without a setup script, detection uses the checkout's saved `artifacts/_user/tools.json` choice, then PATH when no choice is saved. Direct XSCT selection updates this shared file. With a setup script selected, launching an action updates the checkout's saved XSCT path to match the discovered launcher, preserving other preferences. Use **ultrazohm-extension: Use XSCT from PATH** in the Command Palette to clear both the setup script and the selected checkout's saved XSCT choice. The toolbar refresh button rechecks availability. The extension does not install Vitis; finding XSCT does not verify the Vitis version or a successful firmware build.

Repeated clicks reveal an existing task instead of starting another. Generate/build/clean/flash/debug/attach share one task slot per checkout. There is no background-service button or automatic service startup when launching DataViewer. The interactive CLI uses `ultrazohm.cli.endpoint` (default `127.0.0.1:19740`); an occupied port prevents a second start. Separate worktrees can use separate endpoints. Existing services are never stopped or replaced by the extension.

Hidden DataViewer output remains accessible through the Terminal panel. Changing the setting does not hide an already visible terminal. Channel and repository changes apply to subsequent tasks; they do not restart or retarget running applications.

## Flash UZ

Flash UZ uses the published CLI's service API. After confirmation it reuses the configured local endpoint or opens an interactive CLI if none is listening. Before submitting a job, it checks that the service reports the selected checkout and usable XSCT. A service for another checkout is rejected; it is never stopped or retargeted automatically.

The CLI stops acquisition, finalizes recordings, builds and programs via JTAG. An existing device target is reconnected afterward; a newly started disconnected service programs without reconnecting. Logging remains idle and system/control enable are not requested automatically. This does not write persistent flash memory. The visible flash terminal follows job logs and reports failure; closing it does not cancel a job already accepted by the service. The interactive CLI remains open for inspection or reuse.

Flash requires the current service-managed CLI API; use **Update Python packages** if an older CLI is cached. Generate/build/clean still use local CLI operations. DataViewer, CLI application code and existing repository Tcl scripts are unchanged.

## Debug and Attach

Install **Microsoft C/C++** (`ms-vscode.cpptools`) and select your Vitis installation in Setup. The extension discovers Vitis's R5 and A53 GDB executables; optional `ultrazohm.debug.r5Gdb` and `ultrazohm.debug.a53Gdb` settings override those paths. GDB and Vitis are supplied by your Vitis installation, not bundled or downloaded by this extension.

- **Attach debugger** opens independent R5/Baremetal and A53/FreeRTOS sessions for the existing firmware. It does not build, reset or download firmware. Both `vitis/workspace/<application>/Debug/<application>.elf` files must match the firmware running on the board. Attaching may pause the cores; stop acquisition and put the hardware in a safe state first.
- **Debug** submits the same service-managed Flash job as **Flash UZ**, including acquisition shutdown, recording finalization and building. An extension-owned XSCT wrapper intercepts the two application starts, sets a hardware breakpoint at `main`, runs each core to it and verifies the program counter. It then opens both debugger sessions. The service remains disconnected while the cores are stopped. Select **UltraZohm R5** and **UltraZohm A53** in Run and Debug and press **Continue** for each. After both are running, reconnect through the interactive CLI or DataViewer.

Debug requires the interactive CLI opened by this version of the extension. If an external or older service occupies the endpoint, close it yourself and use **Open interactive CLI**, then retry. The extension never replaces a running service. Changing the Vitis selection requires restarting that CLI. Ordinary Flash jobs retain their normal behavior: the wrapper selects only the exact Debug request and service identity. It sources the CLI package's original scripts without modifying them. No CLI or DataViewer application changes are needed.

One locally connected UltraZohm board is supported. The extension uses local `hw_server` ports 3121 (XSCT), 3000 (R5) and 3001 (A53); it checks for exactly one core #0 of each architecture, with the default GDB processor ID 1. Other target layouts are rejected. If necessary it opens **UltraZohm Hardware Server** as a visible task. A small extension-owned adapter forwards to Microsoft C/C++ and forces detach on Stop; its connection commands neither run nor download an application. Disconnecting a debugger uses GDB detach and can resume that core; it does not reset/reflash the board or stop a shared hardware server. Close the server terminal yourself when finished.

Build/flash/package updates are blocked while this window owns UltraZohm debugger sessions. Other VS Code windows, Vitis and external clients are not coordinated; do not program or debug the same board concurrently. If programming or attachment fails, inspect the terminals and any already opened sessions. A core may already be stopped, and successful sessions remain open rather than being automatically detached. Closing the Debug task does not cancel its accepted firmware job; use Attach afterward if needed.

Tests cover the service job, request isolation and breakpoint sequence with fake XSCT. **The dual-core handoff still needs validation on real UltraZohm hardware on Linux and Windows.**

## Runtime and packages

The VSIX bundles uv and CPython 3.12. First use downloads application packages from PyPI. Caches, tool environments, temporary files and extension-launched shell history use extension storage. There is no global uv/Python installation, registry registration, PATH modification or repository `.venv` creation. Local mode requires a checkout with this branch's bundled-runtime bootstrap and private-shell support. Bundled mode includes those scripts in the VSIX. DataViewer preferences and measurements retain their usual locations.

Bundled mode uses its packaged `requirements.txt`; local mode uses the checkout's file. Both currently add `matplotlib>=3.9` alongside DataViewer/CLI dependencies. Changing source affects the next task, not already running tasks.

Normal launches reuse cached packages. **Update Python packages** explicitly checks PyPI, refreshes the three cached environments using private bundled uv/Python, and prints their resolved versions. It uses the chosen launcher’s requirements file without changing its scripts. It does not update the extension, Python or uv. Updates may partially succeed before a failure; fix the reported error and retry. Close UltraZohm tasks in other VS Code windows before updating too. The pane’s Refresh icon only rechecks setup.

The selected channel is passed to the chosen launcher; package resolution and updates remain its responsibility. The minimum CLI contract requires `serve --repo --xsct`, local firmware commands with `--repo --local`, and service-managed flash with `--no-reconnect`. Help checks reject older packages with an Update Python packages instruction; no legacy execution fallback is used.

Application code always comes from PyPI. `venv dev`, user-command installation, device controls, recording and advanced CLI options have no dedicated extension buttons. Use the existing launcher, CLI prompt or DataViewer for these workflows. The private Linux Bash shell provides a green user/host prompt, blue working directory and automatic `ls` colors without loading `~/.bashrc`. It respects `NO_COLOR` and disables colors for `TERM=dumb` or nonterminal output. Environment activation still adds its prefix. The Python shell is an ordinary shell, not a sandbox for commands you type.

## Build and test

Rebuild/reopen the dev container, then run `make` from `ultrazohm-extension/` inside it to package both platforms, or `make extension-test` for Linux verification. Linux CI calls the same Make targets inside the shared image. Make assumes the tools are installed and never launches Docker. See [RELEASING.md](RELEASING.md#container-build-workflow) for Windows and CI migration details.

For a direct native build, use Node 22+ and Python 3.14+ (or Python 3.12 with zstd) in `ultrazohm-extension/` (build tools are not required by extension users):

```sh
npm ci
npm run check
npm test
python -m unittest discover -s tools -p 'test_*.py'
python tools/bundle.py --target linux-x64
npm run package -- --target linux-x64 --pre-release --out ultrazohm-extension-linux-x64-0.1.11.vsix
```

Use `win32-x64` on Windows. `runtime-lock.json` pins upstream downloads and SHA-256 checksums; bundling includes redistribution notices. Pass `--replace` to rebuild an existing generated runtime. `vscode:prepublish` snapshots the shared root launcher scripts and requirements into `launcher/` each time you package.

For development, use `.vscode/launch.json`. `npm run test:host` runs hardware-free task fixtures in an isolated real VS Code window. CI tests the actual packaged extension on Linux and Windows, using both minimum supported and current stable VS Code, and starts published applications with `--help` using the bundled runtime.

See [RELEASING.md](RELEASING.md) in the source repository for CI, automatic branch releases, artifact verification and local testing. Real Vitis builds and attached hardware require manual testing.

When upgrading a local prototype, uninstall `ultrazohm-local.ultrazohm` or `ultrazohm-local.ultrazohm-extension` before installing `ZohmControlGmbH.ultrazohm-extension` to avoid duplicate controls. The `ultrazohm.*` settings remain compatible; the new publisher identity gets fresh private storage. GitHub VSIX updates are installed manually. The publisher is `ZohmControlGmbH`; matching-path pushes to `main` publish stable versions and to `develop` publish prereleases, after both native builds and the GitHub Release succeed. CI assigns `0.1.<run number>` automatically; PRs only validate. Manual runs validate by default; enable `publish_prerelease` on `develop` or `feature/vscode-extension` to publish a tested prerelease.

### Serial terminal (prototype)

The **Serial** section below Control opens the SoM UART in a VS Code terminal. Click **Select serial port…**, choose the UART interface, then **Connect**. Defaults match the UltraZohm guide: 115200 baud, 8 data bits, no parity, 1 stop bit, no flow control. Device name, USB identity, matching mode, baud/framing, flow control, Enter line ending and local echo are clickable in this section. Settings are stored on this machine and survive restarts.

USB identity matching follows a device when its COM/tty number changes. Composite adapters may expose several channels: choose the UART interface, not JTAG. Missing or ambiguous matches prompt for selection; devices without a serial identity use the saved device name. **Device name** also supports manual entry.

pySerial is bundled with the private Python runtime, so serial use needs no package download, other extension, Vitis, CLI service or checkout. The host still needs its USB serial driver and permission to access the port (on Linux, commonly the appropriate device-access group). Close other applications using the same UART. Errors appear in the terminal. Closing the terminal or clicking **Disconnect** releases the port. Unplugging ends the session; reconnect explicitly. Reloading VS Code does not automatically reconnect. Settings can be changed after disconnecting.

This is a text terminal using UTF-8, with local echo off by default. It forwards terminal output and keyboard input; it is not a CLI service console. On hardware, verify both supported adapters' channel identification, firmware output, reconnect after unplugging, and port release alongside JTAG debugging on Linux and Windows.

On first connection, a uniquely identified UltraZohm USB interface **02** (channel C, typically `/dev/ttyUSB2`) is selected automatically. Saved selections take precedence. Multiple adapters or missing interface metadata still require selection.

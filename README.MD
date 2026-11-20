# UltraZohm
*A powerful real-time computation platform for research, development, and rapid-control prototyping of power electronics and drive systems.*

![UltraZohmIMage](https://docs.ultrazohm.com/_images/front_lowres.png)

The UltraZohm is a powerful real-time computation platform for research, development, and rapid-control prototyping of power electronics and drive systems.
Development is driven by researchers for researches to accelerate research by establishing a common control platform.
Having a common platform enables the active research community to focus on publication and results, while the platform development is a shared effort. 

- **High Computational power**: Four ARM A53, two ARM R5, and a large FPGA provided by a Xilinx Zynq UltraScale+ MPSoC.
- **Hard real-time**: Designed to meet modern control systems' timing requirements for power electronics.
- **Open Source**: Platform with no black-boxes and no barriers for your research. Adapt to your needs and use as you like.
- **Modularity**: Extend the platform with your own hardware (adapter cards), IP-Cores and software components.
- **Usability**: Novice friendly with tutorials and existing codebase. Expert friendly with access *to the last bit*.
- **Community**: Connect to other researchers working on the same platform and solve infrastructure problems only once!
- **Documentation**: Comprehensive and ever-growing documentation for the Ultrazohm on [docs.ultrazohm.com](docs.ultrazohm.com).
- **Funded**: Project development is funded by the [BMBF with the research grant KI-Power](https://elektronikforschung.de/projekte/ki-power).

## Getting-started

- How to get an UltraZohm? Please shoot us a Mail at info@ultrazohm.com
- More information on [ultrazohm.com](ultrazohm.com)
- Check the [docs](https://docs.ultrazohm.com/) 

## CLI and Data Viewer

The two applications are `ultrazohm-cli` and `ultrazohm-dataviewer`.
Python imports use `ultrazohm_cli` and `ultrazohm_dataviewer`.
Installing the viewer also installs its matching CLI dependency.

### Python and uv (Linux and Windows)

Until the first stable release is published, select prereleases explicitly.
Run a published application directly:

```sh
uvx --prerelease allow ultrazohm-cli
uvx --prerelease allow ultrazohm-dataviewer
```

For persistent terminal commands:

```sh
uv tool install ultrazohm-cli
# Or install both commands in one environment:
uv tool install --with-executables-from ultrazohm-cli ultrazohm-dataviewer
```

For Python scripts, install into your project's virtual environment:

```sh
pip install ultrazohm-cli
# Or install the viewer and CLI together:
pip install ultrazohm-dataviewer
```

The CLI requires Python 3.10+; the viewer requires Python 3.12+.
Published native CLI wheels support Windows x86-64 and Linux x86-64 (glibc 2.28+).
GUI use requires a desktop display and graphics libraries. No Rust compiler is
needed for published wheels. With uv, use `--python 3.12` to select Python explicitly.
Use `--prerelease allow` to include development releases, or `==VERSION` for an exact release.
A viewer release depends on the CLI with the same version.

### Windows standalone downloads

GitHub releases provide two ZIPs: `ultrazohm-cli-VERSION-windows-x86_64.zip`
and `ultrazohm-dataviewer-VERSION-windows-x86_64.zip`.
Extract the entire archive before running it. Neither needs installed Python or uv.

The CLI ZIP contains `ultrazohm-cli.exe`. The viewer ZIP contains
`ultrazohm-dataviewer.exe`, its runtime files, `ultrazohm-cli.exe`, and the
`ultrazohm-dataviewer.ps1` terminal wrapper. Double-click the viewer executable
for a GUI without a console. From PowerShell:

```powershell
.\ultrazohm-dataviewer.ps1
.\ultrazohm-dataviewer.ps1 --help
.\ultrazohm-dataviewer.ps1 status
```

The wrapper waits for the operation and leaves the calling shell open. With no
arguments it opens the GUI and waits until it closes. Keep the runtime directory
beside the executable. Linux uses the published Python wheels; no standalone
Linux archives are provided. Downloads include `SHA256SUMS`.

### Repository environments

Use `./uz` on Linux or `.\uz.ps1` on Windows. The helper bootstraps uv and the
Python version pinned in `.python-version`. First setup needs internet access;
Linux needs curl or wget for uv bootstrap.

```sh
./uz shell stable --app cli       # published CLI only
./uz shell stable --app viewer    # published viewer and CLI
./uz shell prerelease --app viewer
./uz shell local --app viewer     # editable viewer and locally built CLI
./uz shell                       # reuse the last completed selection
```

On first use the default is `stable` with `--app viewer`. `stable` and `prerelease`
install both selected applications from PyPI. `local` builds the CLI from this
checkout and installs the viewer editable when selected, using locked dependency constraints. Local CLI builds require
Rust and a C/C++ toolchain. Re-run local setup after CLI source changes.

`setup` accepts the same arguments and prepares `.venv` without opening a shell.
Failed setup restores the previous managed environment. If filesystem errors prevent
restoration, setup retains the backup and prints its location for manual recovery.
Successful explicit setup recreates the managed environment, removing stale packages and
editable installs. Reinstall any additional project packages afterward.
Plain `shell` reuses a completed environment while its setup inputs match.
Use `./uz clear_venv` or `.\uz.ps1 clear_venv` to remove the repository `.venv` and reset the saved selection.
Neither command starts an application. Inside the activated shell, run
`ultrazohm-cli`, `ultrazohm-dataviewer`, or `python measurement.py`.
Use `exit` to return to the original shell.

Application installation is independent of firmware selection. For example:

```sh
ultrazohm-cli create-json-from-javascope-h --repo /path/to/ultrazohm_sw --output mapping.json
ultrazohm-dataviewer gui --live-repo /path/to/ultrazohm_sw
```

Vitis operations require a firmware checkout and an external Vitis installation.

### Building and testing

```sh
./uz build cli                 # local CLI wheel
./uz task viewer wheel         # viewer wheel
./uz check cli
./uz check viewer              # tests installed wheels, including live simulation
./uz task cli release-wheel    # portable CLI wheel
```

Windows also supports `.\uz.ps1 build viewer` and `.\uz.ps1 task cli standalone`.
CI builds each release wheel once and uses those wheels for testing and bundling.
`--cli-wheel PATH` and `--viewer-wheel PATH` select candidate wheels for viewer checks
and builds. Paths are relative to the calling terminal.

The devcontainer runs `./uz setup local --app viewer` and installs documentation
and example dependencies. The GUI still needs a display.
See [CLI usage](ultrazohm_cli/README.md) and [viewer usage](ultrazohm_dataviewer/README.md).

## Research 

The primary use of the UltraZohm is the research of modern control algorithms for power electronics and drive systems:

- Model predictive control of electric drives
- Model predictive control of power electronics systems
- Renewable energy systems
- Multilevel converter including Modular Multilevel Converter (MMC)
- Multi-phase motors (m>3)
- Special electric motor designs (e.g., transverse flux machine, synchronous reluctance motor)
- Machine Learning in drive systems

## Documentation

Refer to the [docs](https://docs.ultrazohm.com/) for the documentation of the UltraZohm.

## Contributing

The UltraZohm open source project is maintained by employees of the project coordinator of [KI-Power](https://elektronikforschung.de/projekte/ki-power) [Technische Hochschule Nuremberg](https://www.th-nuernberg.de/einrichtungen-gesamt/in-institute/institut-fuer-leistungselektronische-systeme-elsys/).
Currently, only people associated with the project partners of KI-Power and people with access to an UltraZohm in their lab can contribute to this repository.
If you are interested in joining the UltraZohm community, get in touch with us by E-Mail (info@ultrazohm.com).
We are working on streamlining the contribution process since we aim to welcome contributions of all kinds.

### Repository task ownership

`uz` and `uz.ps1` bootstrap Python and call `uz.py`, which dispatches to the selected project's `tasks.py`.
Installation, shell setup, build helpers, and release checks live in each project's `tools/` directory; their tests live in that project's `tests/` directory.
The viewer owns combined distribution validation because it packages the CLI as a dependency.
`./uz check cli` and `./uz check viewer` run only their respective project checks.
The minimal launcher tests run separately with `python -m unittest test_uz`.

## License

The project is licensed under the Apache 2.0 license. See LICENSE for details.

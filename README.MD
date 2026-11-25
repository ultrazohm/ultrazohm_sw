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

## ultrazohm-cli and DataViewer

The two applications are `ultrazohm-cli` and `ultrazohm-dataviewer`.
Python imports use `ultrazohm_cli` and `ultrazohm_dataviewer`.
Installing the DataViewer also installs its matching ultrazohm-cli dependency.

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

The ultrazohm-cli requires Python 3.10+; the DataViewer requires Python 3.12+.
Published native ultrazohm-cli wheels support Windows x86-64 and Linux x86-64 (glibc 2.28+).
GUI use requires a desktop display and graphics libraries.
No Rust compiler is needed for published wheels.
With uv, use `--python 3.12` to select Python explicitly.
Use `--prerelease allow` to include development releases, or `==VERSION` for an exact release.
A DataViewer release depends on the ultrazohm-cli with the same version.

### Windows standalone downloads

GitHub releases provide two ZIPs: `ultrazohm-cli-VERSION-windows-x86_64.zip` and `ultrazohm-dataviewer-VERSION-windows-x86_64.zip`.
Extract the entire archive before running it.
Neither needs installed Python or uv.

The ultrazohm-cli ZIP contains `ultrazohm-cli.exe`.
The DataViewer ZIP contains `ultrazohm-dataviewer.exe`, its runtime files, `ultrazohm-cli.exe`, and the `ultrazohm-dataviewer.ps1` terminal wrapper.
Double-click the DataViewer executable for a GUI without a console.
From PowerShell:

```powershell
.\ultrazohm-dataviewer.ps1
.\ultrazohm-dataviewer.ps1 --help
.\ultrazohm-dataviewer.ps1 status
```

The wrapper waits for the operation and leaves the calling shell open.
With no arguments it opens the GUI and waits until it closes.
Keep the runtime directory beside the executable.
Linux uses the published Python wheels; no standalone Linux archives are provided.
Downloads include `SHA256SUMS`.

For complete [standalone, launcher, ultrazohm-cli process and Python workflows](docs/source/guide/gui/ultrazohm_dataviewer/ultrazohm_dataviewer_workflows.rst), see the DataViewer tutorials.

### Published applications

Use `./uz` on Ubuntu or `.\uz.ps1` on Windows.
Both bootstrap uv and the Python version pinned in `.python-version` when needed.
First use requires internet access; Ubuntu needs curl or wget to bootstrap uv.

```sh
./uz dataviewer stable
./uz cli prerelease
./uz install dataviewer prerelease
./uz install cli prerelease
./uz venv prerelease
```

The channel is optional and defaults to `stable`.
Stable never silently permits prereleases.
Application arguments follow the channel, for example `./uz dataviewer prerelease -- gui --live-repo /path/to/checkout`.
Applications run through `uv tool run` in isolated cached environments.
`install` uses `uv tool install` to expose the selected application command on your user PATH; follow uv's PATH instructions if needed.
These commands never use or change the repository `.venv`.
DataViewer includes the ultrazohm-cli Python library.

`venv` opens an activated shell with both published libraries and commands in a uv-managed cached environment.
Use `python measurement.py`, `ultrazohm-cli`, or `ultrazohm-dataviewer` there; use `exit` to return.
Multiple shells can share it.
Extra shell dependencies are declared in root `requirements.txt` and installed for all shell modes.
Edit that file instead of manually installing into a cached environment.
It is a dependency list, not an exact version lock.

### Local development

Build the checkout and open its persistent development environment:

```sh
./uz_developer build linux_wheels
./uz_developer shell
ultrazohm-cli
ultrazohm-dataviewer
python measurement.py
```

`build cli` and `build dataviewer` also refresh both applications because their versions must match.
Builds use CI's portable CLI wheel and DataViewer wheel implementations, then install those exact wheels.
Run a build after changes to either application's source or embedded Tcl scripts, and restart running applications.
`./uz venv dev` is an alias for opening the existing development shell; it does not build.
Exiting the shell preserves the environment.

The container owns `/opt/ultrazohm/development`; its PATH and VS Code interpreter use that environment.
Post-create runs the same build command, then adds documentation dependencies.
Outside the container, environments are kept in a per-checkout user cache; `UZ_DEVELOPMENT_ENVIRONMENT` overrides the location.
No repository `.venv` is used. Both wheels, locked development dependencies and root `requirements.txt` example dependencies are installed.
GUI use in the container requires desktop display forwarding; automated GUI checks use the included virtual display.

Application installation is independent of firmware selection.
For example:

```sh
ultrazohm-cli create-json-from-javascope-h --repo /path/to/ultrazohm_sw --output mapping.json
ultrazohm-dataviewer gui --live-repo /path/to/ultrazohm_sw
```

Vitis operations require a firmware checkout and an external Vitis installation.
Firmware commands normally execute through the selected ultrazohm-cli process, on its machine.
Start it with `ultrazohm-cli serve --repo PATH`, then use `build`, `flash`, or the DataViewer's Flash UZ action.
Offline builds require `build --local --repo PATH`.
See [firmware tooling](ultrazohm_cli/README.md) for job progress and lifecycle details.

### Building and testing

```sh
./uz_developer build linux_wheels  # build both wheels and update the development environment
./uz_developer check linux_wheels  # Rust, Python, installed-wheel and GUI checks
./uz_developer check cli
./uz_developer check dataviewer
```

On Windows, use `.\uz_developer.ps1 build windows_bundle` to build/install the pair and create the desktop bundle and native CLI.
Use `.\uz_developer.ps1 check windows_bundle` for bundle smoke checks.
Low-level artifact tasks remain available through `task cli` and `task dataviewer`; these do not update the development environment.
For example, `task cli install` retains the separate uv user-tool installation workflow.
Checks use temporary isolated environments; development installations persist.
CI builds release wheels once and passes those artifacts to tests and Windows bundling.

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

`uz` / `uz.ps1` call `uz.py` for published tools.
`uz_developer` / `uz_developer.ps1` call `uz_developer.py` for local development and dispatch build and test commands to each project's `tasks.py`.
Both bootstrap uv and Python.
Persistent development installation is owned by `uz_venv.py`; `uz_build.py` coordinates shared build outputs; `uz_shell.py` only opens an activated shell.
Project build helpers and release checks remain in each project's `tools/` directory.
Run launcher/environment tests with `python -m unittest test_uz test_uz_developer`.

## C formatting

Run from the repository root:

```sh
make format
make format-check
```

The initial scope is `vitis/software/Baremetal/src/uz/uz_exported_actor`.
Override it explicitly to format another directory, for example:

```sh
make format FORMAT_PATH=vitis/software/Baremetal/src/uz/uz_nn
```

Formatting uses clang-format **19.1.7**, installed in the devcontainer image,
and the root `.clang-format` configuration. `.clang-format-ignore` excludes
generated actor configurations, BSPs, vendor code, and build outputs.
`format-check` changes no files and exits unsuccessfully when formatting is needed.

The style follows the [project coding guidelines](docs/source/software/software_development_guidlines/software_development_guidlines.rst):
opening braces stay on the same line, indentation uses tabs at width 8, and
control-statement bodies use braces. Short function and control-statement bodies
are expanded over multiple lines. Tabs indent blocks; spaces align continuations.
For details not consistently specified by existing code, the shared configuration
chooses `type *name` pointer spacing, at most one consecutive empty line, and no
column limit that forces wrapping of otherwise readable statements. Existing
multiline layouts may remain. Include order, qualifier order, and comment text
are preserved. The C editor settings use the same tab width.

Inside the devcontainer, these commands run directly. From a native terminal,
they start or reuse a separate tooling container using the same devcontainer
configuration, execute the formatter there, and return its exit status. The
container stays running for reuse; the terminal stays native. Docker and either
the Dev Container CLI or Node.js/npx must be available on the host. The npx
fallback uses `@devcontainers/cli@0.90.0`. First use may download dependencies
and build the image. Tooling startup skips post-create tasks, which are not
needed for formatting. Editor containers and their display mounts are left alone.

Rebuild an existing editor devcontainer to install the formatter there. VS Code's
C/C++ formatter uses `/usr/local/bin/clang-format` and the shared configuration.

## License

The project is licensed under the Apache 2.0 license. See LICENSE for details.

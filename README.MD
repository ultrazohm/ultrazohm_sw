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

### Published applications

Use `./uz` on Ubuntu or `.\uz.ps1` on Windows. Both bootstrap uv and the
Python version pinned in `.python-version` when needed. First use requires
internet access; Ubuntu needs curl or wget to bootstrap uv.

```sh
./uz dataviewer stable
./uz cli prerelease
./uz install dataviewer prerelease
./uz install cli prerelease
./uz venv prerelease
```

The channel is optional and defaults to `stable`. Stable never silently permits
prereleases. Application arguments follow the channel, for example
`./uz dataviewer prerelease -- gui --live-repo /path/to/checkout`.
Applications run through `uv tool run` in isolated cached environments.
`install` uses `uv tool install` to expose the selected application command on your
user PATH; follow uv's PATH instructions if needed. These commands never use or
change the repository `.venv`. DataViewer includes the CLI Python library.

`venv` opens an activated shell with both published libraries and commands in a
uv-managed cached environment. Use `python measurement.py`, `ultrazohm-cli`, or
`ultrazohm-dataviewer` there; use `exit` to return. Multiple shells can share it.
This environment is disposable (uv cache cleanup can remove it); use your own
project environment for persistent extra dependencies.

### Local development

Use `./uz_developer` on Ubuntu or `.\uz_developer.ps1` on Windows:

```sh
./uz_developer setup       # explicitly build CLI and install editable viewer
./uz_developer cli         # run the prepared local CLI
./uz_developer dataviewer  # run the prepared local viewer
./uz_developer shell       # open the prepared development shell
./uz_developer status
./uz_developer clear_venv
```

There is one development `.venv` containing both applications. Local setup needs
Rust and a C/C++ toolchain. Launches and shells never install or rebuild anything.
Run setup after CLI or dependency changes; restart the viewer after edits to its
Python sources. Application arguments can follow `--`.
Multiple managed applications and shells may share the environment. Setup and
clear_venv refuse while it is in use, before starting a build. Exit managed shells
(`deactivate` alone does not release their usage lock) before reinstalling.
Explicit setup replaces the environment, so reinstall any additional packages
afterward. Failed installation restores the previous environment; if restoration
fails, the backup is retained and its path is reported.

Host environments are platform-specific and must not be shared with a container.
Inside the dev container, run `ultrazohm-cli`, `ultrazohm-dataviewer`, or `python`
directly. Container creation installs both applications into container Python;
refresh with `bash .devcontainer/post-create.sh`. Host environment commands are
blocked there. The GUI requires display forwarding if run inside the container.

Application installation is independent of firmware selection. For example:

```sh
ultrazohm-cli create-json-from-javascope-h --repo /path/to/ultrazohm_sw --output mapping.json
ultrazohm-dataviewer gui --live-repo /path/to/ultrazohm_sw
```

Vitis operations require a firmware checkout and an external Vitis installation.

### Building and testing

```sh
./uz_developer build cli                 # local CLI wheel
./uz_developer task viewer wheel         # viewer wheel
./uz_developer check cli
./uz_developer check viewer              # tests installed wheels, including live simulation
./uz_developer task cli release-wheel    # portable CLI wheel
```

Windows also supports `.\uz_developer.ps1 build viewer` and `.\uz_developer.ps1 task cli standalone`.
CI builds each release wheel once and uses those wheels for testing and bundling.
`--cli-wheel PATH` and `--viewer-wheel PATH` select candidate wheels for viewer checks
and builds. Paths are relative to the calling terminal.

The devcontainer installs local applications, documentation, and example dependencies
into container Python. The GUI still needs a display.
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

`uz` / `uz.ps1` call `uz.py` for published tools. `uz_developer` /
`uz_developer.ps1` call `uz_developer.py` for local development and dispatch build
and test commands to each project's `tasks.py`. Both bootstrap uv and Python.
Local environment installation is owned by `uz_developer_environment.py`;
`uz_shell.py` only opens an activated shell. Project build helpers and release
checks remain in each project's `tools/` directory.
Run launcher/environment tests with
`python -m unittest test_uz test_uz_developer`.

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

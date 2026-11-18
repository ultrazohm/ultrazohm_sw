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

From the repository root, open one environment containing both applications:

```bash
./uz shell                    # Bash (Linux)
# .\uz.ps1 shell             # Windows PowerShell: same arguments
ultrazohm_cli --help
uz-dataviewer --help
```

The launcher installs missing uv and the Python version in `.python-version`;
no host Python or Make is required. Bash needs `curl` or `wget` to bootstrap uv.
First setup needs internet access. If Windows blocks script execution, use
`powershell -ExecutionPolicy Bypass -File .\uz.ps1 shell`.

`setup` prepares the shared repository `.venv` without opening a shell. `shell`
prepares it if needed and opens an activated child shell; `exit` returns to the
original terminal. Both accept an optional CLI source:

```bash
./uz setup stable             # latest compatible stable CLI wheel from PyPI
./uz setup prerelease         # latest compatible CLI, including development releases
./uz setup local              # build this checkout's CLI (Rust/C++ tools required)
./uz shell local              # setup local, then enter the shell
./uz shell                    # reuse the last setup; stable on first use
```

`release` is an alias for `stable`. The viewer always runs from this checkout
(editable installation); other runtime dependencies come from its lockfile.
Published CLI versions must satisfy the viewer's minimum version. Missing
compatible wheels fail setup instead of triggering a native build or switching
channels. If stable setup reports no compatible release, use `./uz setup prerelease`
or `./uz setup local`. Explicit `setup` refreshes the selected installation; plain `shell`
reuses it until setup inputs change. After Rust changes, rerun `./uz setup local`.
Neither setup nor shell starts an application. To activate the existing environment
in the current terminal instead, use `source .venv/bin/activate` in Bash or
`.\.venv\Scripts\Activate.ps1` in PowerShell.

Builds and checks use the same interface locally and in CI, without entering the shell:

```bash
./uz build cli                # native wheel in uz_cli/target/wheels
./uz build viewer             # desktop bundle in uz_dataviewer/dist
./uz check cli
./uz check viewer
./uz task cli release-wheel   # portable release wheel
./uz task viewer bundle-smoke
./uz task cli help            # additional project tasks
./uz --help
```

Use `.\uz.ps1` instead of `./uz` in PowerShell. Build/check options are forwarded,
e.g. `./uz check viewer --cli-wheel path/to/cli.whl`. Paths are relative to the
calling terminal. These launchers replace the project Makefiles and viewer
`start.sh`/`start.ps1`; application options now go directly to `uz-dataviewer` or
`ultrazohm_cli`, after setup/activation.

The dev container supplies the native build tools. Its post-create hook runs
`./uz setup local`; both commands and the shared Python environment are available
in new VS Code terminals. Rebuild the container to pick up this configuration.
The viewer GUI still needs a display; the container supports headless testing.

See [CLI usage](uz_cli/README.md) and [viewer usage](uz_dataviewer/README.md).

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

## License

The project is licensed under the Apache 2.0 license. See LICENSE for details.
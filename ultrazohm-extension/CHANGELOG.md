# Changelog

## 0.1.12

- Automatically version and publish tested main/develop pushes as stable/prerelease to Marketplace using GitHub OIDC Trusted Publishing and pinned vsce 4.1.1.

- Set the Marketplace publisher to `ZohmControlGmbH`; uninstall local-publisher prototypes when switching.

- Add Attach debugger for R5 and A53 through Vitis GDB and Microsoft C/C++.
- Add Debug: service-managed Flash with both cores stopped at main before debugger attachment.
- Keep the CLI disconnected while debugging; preserve the existing CLI, DataViewer and repository Tcl sources.
- Test debug-job isolation, Tcl breakpoint sequencing and the published CLI handoff with fake XSCT. Hardware validation remains required.

## 0.1.11

- Adapt Flash UZ to the current CLI service API with interactive startup, checkout validation and job-log following.
- Test published command contracts and real CLI service flashing with fake XSCT on Linux and Windows.

## 0.1.10

- Add Update Python packages to Setup, refreshing the selected PyPI channel using private bundled tooling.

## 0.1.9

- Name the extension and its platform VSIXs consistently `ultrazohm-extension`.
- Provide Setup, Software build and Control views with bundled or local launchers.
- Bundle private uv/Python runtimes for Linux x64 and Windows x64, including notices.
- Add native build, package and VS Code host tests, plus tagged GitHub Releases
  with checksums and runtime/application verification manifests.
- Retain the `ultrazohm.*` settings. Uninstall the previous
  `ultrazohm-local.ultrazohm` prototype before installing this renamed extension.

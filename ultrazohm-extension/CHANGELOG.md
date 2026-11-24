# Changelog

## 0.1.16

- Route Baremetal source breakpoints only to R5 and FreeRTOS source breakpoints only to A53, preventing same-filename collisions such as isr.c. Shared-source breakpoints remain available to both cores.

## 0.1.15

- Accept the final hex-encoded monitor response used by Vitis 2022.2 hw_server during debugger processor discovery.
- Test the captured R5 response, mixed console/final output, and invalid replies.

## 0.1.14

- Correlate Debug task completion by a unique run ID, including reconstructed task events.
- Show debugger attach progress and retain each handoff stage/error in the UltraZohm Debug output channel.

## 0.1.13

- Fix Debug on Vitis 2022.2: use Tcl 8.5-compatible error handling, always clean up temporary breakpoints, and preserve the original failure if cleanup fails too.
- Exercise the programming wrapper with `try` unavailable; also validated locally with Vitis’s Tcl 8.5 interpreter and simulated hardware commands.

## 0.1.12

- Add an explicit manual prerelease publishing option for develop and feature/vscode-extension, keeping all release checks.

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

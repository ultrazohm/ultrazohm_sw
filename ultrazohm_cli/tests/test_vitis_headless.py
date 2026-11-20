"""Execute the real Tcl entry point with stubbed Vitis commands."""

import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


@unittest.skipUnless(os.name == "posix" and shutil.which("make"), "POSIX Make required")
class NativeGuiHandoffTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / "checkout with spaces"
        self.vitis = self.root / "vitis"
        self.workspace = self.vitis / "workspace"
        self.workspace.mkdir(parents=True)
        shutil.copy(ROOT / "vitis/Makefile", self.vitis)
        tools = self.root / "tools with spaces"
        tools.mkdir()
        self.xsct = tools / "xsct"
        self.gui = tools / "vitis"
        self.xsct.write_text(f"#!{sys.executable}\n" + '''import atexit, os, sys
from pathlib import Path
workspace = Path(os.environ['UZ_TEST_WORKSPACE'])
assert sys.argv[1:] == ['-nodisp', '../tcl_scripts/vitis_headless.tcl', 'generate']
(workspace / 'xsct-called').touch()
sys.exit(7) if os.environ.get('UZ_TEST_FAIL') else None
atexit.register(lambda: (workspace / 'xsct-exited').touch())
print('GENERATION_FINISHED', flush=True)
''')
        self.gui.write_text(f"#!{sys.executable}\n" + '''import os, sys
from pathlib import Path
workspace = Path(os.environ['UZ_TEST_WORKSPACE'])
assert sys.argv[1:] == ['-workspace', str(workspace)]
if (workspace / 'xsct-called').exists():
    assert (workspace / 'xsct-exited').exists(), 'GUI started before XSCT exited'
print('GUI_STARTED', flush=True)
''')
        self.xsct.chmod(0o755)
        self.gui.chmod(0o755)
        self.env = {**os.environ, "UZ_TEST_WORKSPACE": str(self.workspace)}
        self.env.pop("UZ_WORKSPACE_ROOT", None)

    def make(self, target, gui=None, fail=False):
        return subprocess.run(
            ["make", "--no-print-directory", "-C", str(self.vitis), target,
             f"XSCT={self.xsct}", f"VITIS={gui or self.gui}"],
            env={**self.env, **({"UZ_TEST_FAIL": "1"} if fail else {})},
            text=True, capture_output=True, timeout=10)

    def test_generate_waits_for_xsct_before_native_gui_with_paths_containing_spaces(self):
        result = self.make("generate-open")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertLess(result.stdout.index("GENERATION_FINISHED"), result.stdout.index("GUI_STARTED"))

    def test_generation_failure_does_not_launch_gui(self):
        result = self.make("generate-open", fail=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertNotIn("GUI_STARTED", result.stdout)

    def test_open_launches_native_gui_without_xsct(self):
        result = self.make("open")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("GUI_STARTED", result.stdout)
        self.assertFalse((self.workspace / "xsct-called").exists())

    def test_missing_gui_is_rejected_before_generation(self):
        result = self.make("generate-open", gui=self.gui.with_name("missing-vitis"))
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("GUI launcher not found", result.stderr)
        self.assertFalse((self.workspace / "xsct-called").exists())

    def test_clean_workspace_preserves_placeholder_and_removes_hidden_and_nested_contents(self):
        placeholder = self.workspace / "create_Vitis_workspace_here.txt"
        placeholder.write_text("Keep this placeholder unchanged.\n")
        for name in ("Baremetal/Debug", ".metadata/.plugins"):
            folder = self.workspace / name
            folder.mkdir(parents=True)
            (folder / "generated.bin").write_bytes(b"generated")
        (self.workspace / "IDE.log").touch()
        outside = self.root / "source.c"
        outside.write_text("keep source\n")
        (self.workspace / "linked-source").symlink_to(outside)
        result = self.make("clean-workspace")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(list(self.workspace.iterdir()), [placeholder])
        self.assertEqual(placeholder.read_text(), "Keep this placeholder unchanged.\n")
        self.assertEqual(outside.read_text(), "keep source\n")

    def test_clean_workspace_rejects_symlinked_workspace(self):
        self.workspace.rmdir()
        outside = self.root / "outside"
        outside.mkdir()
        marker = outside / "keep.txt"
        marker.write_text("keep")
        self.workspace.symlink_to(outside, target_is_directory=True)
        result = self.make("clean-workspace")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("symlinked workspace", result.stderr)
        self.assertEqual(marker.read_text(), "keep")


@unittest.skipUnless(shutil.which("tclsh"), "Tcl interpreter required")
class HeadlessBuildTest(unittest.TestCase):
    def run_build(self, action, config="Debug", fail=False):
        with tempfile.TemporaryDirectory() as tmp:
            repo = Path(tmp)
            scripts = repo / "tcl_scripts"
            scripts.mkdir()
            shutil.copy(ROOT / "tcl_scripts/vitis_headless.tcl", scripts)
            shutil.copy(ROOT / "tcl_scripts/vitis_incremental.tcl", scripts)
            for name in ("UltraZohm", "Baremetal", "FreeRTOS"):
                folder = repo / "vitis/workspace" / name / "Debug"
                folder.mkdir(parents=True)
                (folder / f"{name}.elf").touch()
            harness = scripts / "test.tcl"
            harness.write_text("""set ::env(XILINX_VITIS) /fake/vitis
proc setws {args} {}
proc platform {args} {puts "CALL platform $args"}
proc app {args} {
    puts "CALL app $args"
    if {[lindex $args 0] eq "config" && [llength $args] == 4} {
        return $::config
    }
    if {$::fail && [lindex $args 0] eq "build"} {error "build failed"}
}
proc sysproj {args} {error "Unexpected system project operation"}
set config [lindex $argv 1]
set fail [lindex $argv 2]
set argv [list [lindex $argv 0]]
source [file join [file dirname [info script]] vitis_headless.tcl]
""")
            return subprocess.run(
                ["tclsh", str(harness), action, config, str(int(fail))],
                capture_output=True,
                text=True,
                timeout=10,
            )

    def test_incremental_does_not_force_generation_or_configuration(self):
        result = self.run_build("build")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("changes found, building", result.stdout)
        self.assertNotIn("generate", result.stdout)
        self.assertNotIn("clean", result.stdout)
        self.assertNotIn("build-config Debug", result.stdout)
        for name in ("Baremetal", "FreeRTOS"):
            self.assertEqual(result.stdout.count(f"CALL app build -name {name}"), 1)

    def test_clean_precedes_build(self):
        result = self.run_build("build-clean")
        self.assertEqual(result.returncode, 0, result.stderr)
        for command in (
            "app clean -name Baremetal",
            "app clean -name FreeRTOS",
            "platform clean",
        ):
            self.assertLess(
                result.stdout.index(f"CALL {command}"),
                result.stdout.index("CALL app build"),
            )

    def test_switches_release_to_debug(self):
        result = self.run_build("build", config="Release")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.count("build-config Debug"), 2)

    def test_flash_build_failure_stops_before_programming(self):
        result = self.run_build("flash", fail=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("build failed", result.stderr)
        self.assertNotIn("Missing", result.stderr)
        self.assertNotIn("successfully", result.stdout)

    def test_make_reuse_and_invalidation(self):
        with tempfile.TemporaryDirectory() as tmp:
            script = Path(tmp) / "test.tcl"
            script.write_text("""source [lindex $argv 0]
set root [lindex $argv 1]
set workspace [file join $root workspace]
set scripts [file join $root scripts]
set ::env(XILINX_VITIS) /fake/vitis
proc writefile {path contents} {
    file mkdir [file dirname $path]
    set f [open $path w]; puts $f $contents; close $f
}
proc check {condition} {
    if {![uplevel 1 [list expr $condition]]} {error "Assertion failed: $condition"}
}
foreach app {Baremetal FreeRTOS} {
    writefile [file join $workspace $app Debug makefile] "all:"
}
set header [file join $workspace UltraZohm include header.h]
writefile $header original
set source [file join $root software main.c]
writefile $source original
set stamp [file join $workspace stamp]
set signature [uz_build_signature $workspace $scripts]
check {![uz_can_make $workspace $signature $stamp]}
uz_save_build_signature $stamp $signature
check {[uz_can_make $workspace $signature $stamp]}
# Editing existing source is handled by Make without restarting Vitis.
writefile $source changed-source
check {[uz_can_make $workspace [uz_build_signature $workspace $scripts] $stamp]}
# Adding a source requires new generated Makefiles.
set added [file join $root software new.c]
writefile $added new
check {![uz_can_make $workspace [uz_build_signature $workspace $scripts] $stamp]}
file delete $added
# Missing generated platform outputs must be restored by Vitis.
file delete $header
check {![uz_can_make $workspace [uz_build_signature $workspace $scripts] $stamp]}
writefile $header changed-header
check {![uz_can_make $workspace [uz_build_signature $workspace $scripts] $stamp]}
# Metadata changes and toolchain changes invalidate Makefile reuse.
uz_save_build_signature $stamp [uz_build_signature $workspace $scripts]
writefile [file join $workspace Baremetal .cproject] new-settings
check {![uz_can_make $workspace [uz_build_signature $workspace $scripts] $stamp]}
uz_save_build_signature $stamp [uz_build_signature $workspace $scripts]
set ::env(XILINX_VITIS) /other/vitis
check {![uz_can_make $workspace [uz_build_signature $workspace $scripts] $stamp]}
file delete [file join $workspace Baremetal Debug makefile]
check {![uz_can_make $workspace $signature $stamp]}
""")
            result = subprocess.run(
                [
                    "tclsh",
                    str(script),
                    str(ROOT / "tcl_scripts/vitis_incremental.tcl"),
                    tmp,
                ],
                capture_output=True,
                text=True,
                timeout=10,
            )
            self.assertEqual(result.returncode, 0, result.stderr)

    @unittest.skipUnless(shutil.which("make"), "Make required")
    def test_build_and_flash_report_dependency_changes(self):
        with tempfile.TemporaryDirectory() as tmp:
            repo = Path(tmp)
            scripts = repo / "tcl_scripts"
            scripts.mkdir()
            workspace = repo / "vitis/workspace"
            for name in ("vitis_headless.tcl", "vitis_incremental.tcl"):
                shutil.copy(ROOT / "tcl_scripts" / name, scripts)
            hardware = workspace / "UltraZohm/hw"
            hardware.mkdir(parents=True)
            (hardware / "psu_init.tcl").touch()
            (hardware / "design.bit").touch()
            utility = repo / "tools/scripts/vitis/util"
            utility.mkdir(parents=True)
            for name in ("zynqmp_utils.tcl", "fsbl.tcl"):
                (utility / name).touch()
            (scripts / "vitis_run_freertos_baremetal_fpga.tcl").write_text(
                'puts "PROGRAMMED"'
            )
            for app in ("Baremetal", "FreeRTOS"):
                folder = workspace / app / "Debug"
                folder.mkdir(parents=True)
                (folder / "source.c").write_text("original")
                (folder / "header.h").write_text("original")
                (folder / "makefile").write_text(
                    f".PHONY: all\nall: {app}.elf\n{app}.elf: source.c header.h\n\tcp source.c $@\n"
                )
            harness = scripts / "test.tcl"
            harness.write_text("""set ::env(XILINX_VITIS) [lindex $argv 1]
set argv [list [lindex $argv 0]]
proc setws {args} {}
proc disconnect {} {}
proc app {args} {
    if {[lindex $args 0] eq "config"} {return "Debug"}
    if {[lindex $args 0] eq "build"} {
        exec make -C [file join $::workspace [lindex $args 2] Debug] all
    }
}
source [file join [file dirname [info script]] vitis_headless.tcl]
""")

            def run(action):
                return subprocess.run(
                    ["tclsh", str(harness), action, str(repo / "tools")],
                    capture_output=True,
                    text=True,
                    timeout=10,
                )

            first = run("build")
            self.assertEqual(first.returncode, 0, first.stderr)
            self.assertIn("changes found, building", first.stdout)
            for action in ("build", "flash"):
                unchanged = run(action)
                self.assertEqual(unchanged.returncode, 0, unchanged.stderr)
                self.assertIn("no changes found", unchanged.stdout)
                self.assertEqual("PROGRAMMED" in unchanged.stdout, action == "flash")
            # An updated header must trigger a build even though source names are unchanged.
            import os

            elf = workspace / "Baremetal/Debug/Baremetal.elf"
            (workspace / "Baremetal/Debug/header.h").write_text("updated header")
            os.utime(elf, (1, 1))
            changed = run("flash")
            self.assertEqual(changed.returncode, 0, changed.stderr)
            self.assertIn("changes found, building", changed.stdout)
            self.assertIn("PROGRAMMED", changed.stdout)
            (workspace / "FreeRTOS/Debug/FreeRTOS.elf").unlink()
            missing = run("build")
            self.assertEqual(missing.returncode, 0, missing.stderr)
            self.assertIn("changes found, building", missing.stdout)
            # Dependency-check failures must not be mistaken for an up-to-date build.
            (workspace / "Baremetal/Debug/header.h").unlink()
            failed = run("flash")
            self.assertNotEqual(failed.returncode, 0)
            self.assertNotIn("no changes found", failed.stdout)
            self.assertNotIn("PROGRAMMED", failed.stdout)

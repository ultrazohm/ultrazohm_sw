"""Execute the real Tcl entry point with stubbed Vitis commands."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


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
            harness.write_text('''set ::env(XILINX_VITIS) /fake/vitis
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
''')
            return subprocess.run(["tclsh", str(harness), action, config, str(int(fail))],
                                  capture_output=True, text=True, timeout=10)

    def test_incremental_does_not_force_generation_or_configuration(self):
        result = self.run_build("build")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertNotIn("generate", result.stdout)
        self.assertNotIn("clean", result.stdout)
        self.assertNotIn("build-config Debug", result.stdout)
        for name in ("Baremetal", "FreeRTOS"):
            self.assertEqual(result.stdout.count(f"CALL app build -name {name}"), 1)

    def test_clean_precedes_build(self):
        result = self.run_build("build-clean")
        self.assertEqual(result.returncode, 0, result.stderr)
        for command in ("app clean -name Baremetal", "app clean -name FreeRTOS", "platform clean"):
            self.assertLess(result.stdout.index(f"CALL {command}"),
                            result.stdout.index("CALL app build"))

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
            script.write_text('''source [lindex $argv 0]
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
''')
            result = subprocess.run(["tclsh", str(script),
                                     str(ROOT / "tcl_scripts/vitis_incremental.tcl"), tmp],
                                    capture_output=True, text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stderr)

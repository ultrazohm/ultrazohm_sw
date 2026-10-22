from __future__ import annotations

import argparse
import os
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[4] if "FreeRTOS" in Path(__file__).parts else Path(r"C:\GIT\UltraZohm\software\ultrazohm_sw_ZC_test_2")
STAGE = Path(os.environ.get("FSD_A53_BUILD_DIR", str(Path(tempfile.gettempdir()) / "fsd_a53_benchmark")))
VITIS = Path(os.environ.get("XILINX_VITIS", r"C:\Xilinx\Vitis\2022.2")) / "gnu"


def run(args: list[str]) -> None:
    subprocess.run(args, check=True)


def build(variant: int, r5_only: bool = False) -> None:
    out = STAGE / (f"r5_yang_{variant}" if r5_only else f"variant_{variant}")
    out.mkdir(parents=True, exist_ok=True)
    shared = ROOT / "vitis/software/shared"
    specs = [
        (
            "r5", "Baremetal", "Baremetal_domain", "Baremetal.elf",
            VITIS / "armr5/nt/gcc-arm-none-eabi/bin/armr5-none-eabi-gcc.exe",
            ["-DARMR5", "-Wall", "-O2", "-g3", "-mcpu=cortex-r5",
             "-mfloat-abi=hard", "-mfpu=vfpv3-d16"],
            ["src/main.c", "src/sw/isr.c", "src/sw/javascope.c",
             "src/sw/fsd_a53_benchmark.c"],
            ["-lm", "-Wl,--start-group", "-lxil", "-lgcc", "-lc",
             "-Wl,--end-group"],
        ),
        (
            "a53", "FreeRTOS", "FreeRTOS_domain", "FreeRTOS.elf",
            VITIS / "aarch64/nt/aarch64-none/bin/aarch64-none-elf-gcc.exe",
            ["-Wall", "-O3", "-g3"],
            ["sw/isr.c", "sw/fsd_a53_worker.c",
             "uz/uz_fsd_mpc/uz_fsd_mpc.c",
             "uz/uz_fsd_mpc/uz_fsd_mpc_math.c",
             "uz/uz_fsd_mpc/uz_fsd_mpc_solver.c"],
            ["-lm", "-Wl,--start-group", "-lxil", "-lfreertos",
             "-lgcc", "-lc", "-Wl,--end-group", "-Wl,--start-group",
             "-lxil", "-llwip4", "-lgcc", "-lc", "-Wl,--end-group"],
        ),
    ]
    if r5_only:
        specs = [(
            "r5", "Baremetal", "Baremetal_domain", "Baremetal.elf",
            VITIS / "armr5/nt/gcc-arm-none-eabi/bin/armr5-none-eabi-gcc.exe",
            ["-DARMR5", "-Wall", "-O2", "-g3", "-mcpu=cortex-r5",
             "-mfloat-abi=hard", "-mfpu=vfpv3-d16"],
            ["src/main.c", "src/sw/isr.c", "src/sw/javascope.c",
             "src/sw/fsd_mpc_benchmark.c", "src/sw/fsd_mpc_benchmark_stats.c",
             "src/uz/uz_fsd_mpc/uz_fsd_mpc.c",
             "src/uz/uz_fsd_mpc/uz_fsd_mpc_math.c",
             "src/uz/uz_fsd_mpc/uz_fsd_mpc_solver.c"],
            ["-lm", "-Wl,--start-group", "-lxil", "-lgcc", "-lc",
             "-Wl,--end-group"],
        )]
    for name, project, domain, elf_name, gcc, flags, sources, libs in specs:
        src_root = ROOT / "vitis/software" / project
        bsp = ROOT / "vitis/workspace/UltraZohm/export/UltraZohm/sw/UltraZohm" / domain
        old_obj_root = ROOT / "vitis/workspace" / project / "Debug"
        new_obj_root = out / name
        new_obj_root.mkdir(exist_ok=True)
        replacements: dict[str, Path] = {}
        for rel in sources:
            src = src_root / rel
            obj = new_obj_root / (rel.replace("/", "_").replace(".c", ".o"))
            run([
                str(gcc), *flags, "-std=gnu99",
                f"-DUZ_FSD_A53_BENCHMARK_ENABLE={0 if r5_only else 1}",
                (f"-DUZ_FSD_BENCHMARK_VARIANT={variant}" if r5_only else
                 f"-DUZ_FSD_A53_BENCHMARK_VARIANT={variant}"),
                *(["-DUZ_FSD_YANG_EXPERIMENT_ENABLE=1"] if variant >= 6 else []),
                "-I" + str(shared), "-I" + str(bsp / "bspinclude/include"),
                "-I" + str(src_root), "-I" + str(src_root / "src"),
                "-I" + str(src_root / "src/include"),
                "-c", str(src), "-o", str(obj),
            ])
            workspace_rel = rel if name == "r5" else "src/" + rel
            replacements[workspace_rel.replace(".c", ".o")] = obj
        existing = sorted(old_obj_root.rglob("*.o"))
        objects = []
        replaced = set()
        for obj in existing:
            key = obj.relative_to(old_obj_root).as_posix()
            if key in replacements:
                objects.append(replacements[key])
                replaced.add(key)
            else:
                objects.append(obj)
        for key, obj in replacements.items():
            if key not in replaced:
                objects.append(obj)
        # Source-tree paths such as src/sw/isr.c map to workspace src/sw/isr.o.
        rsp = new_obj_root / "objects.rsp"
        rsp.write_text("\n".join('"' + x.as_posix() + '"' for x in objects), encoding="utf-8")
        link_script = src_root / ("src/lscript.ld" if name == "r5" else "lscript.ld")
        elf = out / elf_name
        run([
            str(gcc), "-Wl,-T," + link_script.as_posix(),
            "-L" + (bsp / "bsplib/lib").as_posix(), *(["-mcpu=cortex-r5",
                "-mfloat-abi=hard", "-mfpu=vfpv3-d16"] if name == "r5" else []),
            "-o", str(elf), "@" + str(rsp), *libs,
        ])
        print(name, variant, elf, elf.stat().st_size, "bytes", flush=True)
    launch = (ROOT / "tcl_scripts/vitis_debug_run_UltraZohm.tcl").read_text(encoding="utf-8")
    launch = launch.replace("cd [getws]", "cd {" + (ROOT / "vitis/workspace").as_posix() + "}")
    if not r5_only:
        launch = launch.replace("dow FreeRTOS/Debug/FreeRTOS.elf", "dow {" + (out / "FreeRTOS.elf").as_posix() + "}")
    launch = launch.replace("dow Baremetal/Debug/Baremetal.elf", "dow {" + (out / "Baremetal.elf").as_posix() + "}")
    (out / "launch.tcl").write_text(
        'set UZ_PROGRAMMING_MODE "RUN"\nset UZ_FPGA_FAST_RESTART_ACTIVATED 0\n' + launch,
        encoding="utf-8",
    )


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("variant", type=int, choices=range(9))
    ap.add_argument("--r5-only", action="store_true")
    args = ap.parse_args()
    build(args.variant, args.r5_only)

###########################################################################
# Copyright 2024 Eyke Liegmann
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and limitations under the License.
#
# vitis_patch_UltraZohm_freertos_bsp.tcl
#
# BACKGROUND
# ----------
# Vitis 2022.2 ships the Cortex-A53 FreeRTOS port (kernel 10.4.6) without a
# definition of portMEMORY_BARRIER.  With -O2 or higher GCC is free to
# reorder memory accesses across the barriers that the scheduler uses to
# protect its task-list manipulation, which causes the APU to freeze after
# minutes of network traffic.
#
# The fix:
#   #define portMEMORY_BARRIER() __asm volatile ( "" ::: "memory" )
#
# This must be injected into the *generated* FreeRTOSConfig.h because
# `bsp regenerate` rewrites the file every time the BSP is rebuilt.
# Run this script once after every `bsp regenerate` on the FreeRTOS domain.
# Both generated copies must be patched:
#   bsp/<cpu>/include/FreeRTOSConfig.h          (used by app compiler)
#   bsp/<cpu>/libsrc/freertos*/src/FreeRTOSConfig.h  (used when rebuilding the kernel itself)
#
# Fixed upstream in embeddedsw >= 2023.1; the guard below makes the patch
# idempotent so it is safe to apply on newer toolchains too.
#
# USAGE
# -----
#   Source this file from vitis_generate_UltraZohm_workspace.tcl or
#   vitis_update_platform.tcl after calling `bsp regenerate` on the
#   FreeRTOS domain:
#
#     source [file join $::uz_vitis_script_dir vitis_patch_UltraZohm_freertos_bsp.tcl]
#     uz_vitis_patch_freertos_bsp
#
###########################################################################

proc uz_vitis_patch_freertos_config_file {filepath} {
    # Read the file.
    set fd [open $filepath r]
    set content [read $fd]
    close $fd

    # Idempotency guard: do nothing if the define is already present.
    if {[string match "*portMEMORY_BARRIER*" $content]} {
        puts "Info (UltraZohm): portMEMORY_BARRIER already present in $filepath — skipping"
        return
    }

    # The define must appear before any code that uses it.  Inject it right
    # after the opening include-guard (#ifndef / #define pair) so it is
    # available for the rest of the header regardless of include order.
    # We look for the #define that closes the include guard.
    set guard_define_re {(#define\s+FREERTOS_CONFIG_H[^\n]*\n)}
    set patch_line "\n/* portMEMORY_BARRIER: compiler memory barrier required by the A53 FreeRTOS port.\n * Without this GCC -O2 can reorder accesses across scheduler list operations,\n * causing the APU to freeze under network load.  Fixed upstream in >= 2023.1.\n */\n#ifndef portMEMORY_BARRIER\n#define portMEMORY_BARRIER() __asm volatile ( \"\" ::: \"memory\" )\n#endif\n"

    # Try to inject after the include-guard #define line.
    if {[regexp -indices $guard_define_re $content match]} {
        set end_of_guard [lindex $match 1]
        set new_content [string range $content 0 $end_of_guard]
        append new_content $patch_line
        append new_content [string range $content [expr {$end_of_guard + 1}] end]
        set content $new_content
        puts "Info (UltraZohm): Injected portMEMORY_BARRIER after include guard in $filepath"
    } else {
        # Fallback: append at end of file (will still compile correctly).
        append content "\n$patch_line\n"
        puts "Warning (UltraZohm): Could not find include guard in $filepath — appended portMEMORY_BARRIER at end of file"
    }

    set fd [open $filepath w]
    puts -nonewline $fd $content
    close $fd
}

proc uz_vitis_patch_freertos_bsp {} {
    set WS_PATH [getws]
    set patched 0

    # Walk the workspace tree looking for all copies of FreeRTOSConfig.h
    # that live under the FreeRTOS domain BSP.  Vitis generates two copies
    # per domain — one in bsp/<cpu>/include/ and one in the freertos libsrc.
    foreach candidate [glob -nocomplain -type f \
            [file join $WS_PATH * * FreeRTOS_domain bsp * include FreeRTOSConfig.h] \
            [file join $WS_PATH * * FreeRTOS_domain bsp * libsrc freertos* src FreeRTOSConfig.h] \
            [file join $WS_PATH * FreeRTOS_domain bsp * include FreeRTOSConfig.h] \
            [file join $WS_PATH * FreeRTOS_domain bsp * libsrc freertos* src FreeRTOSConfig.h] \
        ] {
        puts "Info (UltraZohm): Patching $candidate"
        uz_vitis_patch_freertos_config_file $candidate
        incr patched
    }

    if {$patched == 0} {
        puts "Warning (UltraZohm): uz_vitis_patch_freertos_bsp: no FreeRTOSConfig.h found under $WS_PATH — BSP may not have been regenerated yet."
    } else {
        puts "Info (UltraZohm): portMEMORY_BARRIER patch applied to $patched file(s)."
    }
}

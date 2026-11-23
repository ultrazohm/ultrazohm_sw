###########################################################################
# Copyright 2026 UltraZohm
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
# See the License for the specific language governing permissions and
# limitations under the License.
###########################################################################
#
# Re-insert portMEMORY_BARRIER into the generated FreeRTOSConfig.h. Call AFTER
# every FreeRTOS "bsp regenerate" and BEFORE "platform generate" (which
# rebuilds the kernel library from the header). Shared by
# vitis_generate_UltraZohm_workspace.tcl and vitis_update_platform.tcl so both
# produce an identical, freeze-free BSP.
#
# Why a textual patch (and not a bsp config like the other settings): the
# Xilinx ARM_CA53 FreeRTOS port (Vitis 2022.2 / kernel 10.4.6) does NOT define
# portMEMORY_BARRIER and there is no BSP parameter for it, so the kernel
# default (empty) applies. The kernel needs it as a compiler barrier in
# xTaskResumeAll()'s pending-ready drain loop; without it GCC -O2 hoists the
# list-head load out of the loop and corrupts the kernel task lists whenever
# >= 2 tasks are woken during one scheduler-suspension window -> infinite loop
# in xTaskResumeAll, all interrupts masked, total A53 freeze (stochastic,
# minutes-scale, load-dependent). Fixed upstream in embeddedsw >= 2023.1
# (kernel >= 10.5.1); this proc then finds the define already present and only
# logs.
###########################################################################

proc uz_vitis_patch_freertos_bsp {ws_path} {
  set barrier_define "#define portMEMORY_BARRIER() __asm volatile ( \"\" ::: \"memory\" )"
  set anchor "#define configASSERT"

  # The compiled header (include/) and its libsrc staging copy. Platform name
  # and freertos version dirs are globbed for robustness.
  set bsp [file join $ws_path * psu_cortexa53_0 FreeRTOS_domain bsp psu_cortexa53_0]
  set candidates {}
  foreach pat [list \
        [file join $bsp include FreeRTOSConfig.h] \
        [file join $bsp libsrc freertos10_xilinx_* src FreeRTOSConfig.h] ] {
    foreach f [glob -nocomplain -- $pat] { lappend candidates $f }
  }
  if {[llength $candidates] == 0} {
    puts "Warning (UltraZohm): portMEMORY_BARRIER patch: no FreeRTOSConfig.h under $ws_path"
    return
  }

  foreach f $candidates {
    set fp [open $f r]; set data [read $fp]; close $fp

    if {[string first "portMEMORY_BARRIER" $data] >= 0} {
      puts "Info (UltraZohm): portMEMORY_BARRIER already present in $f"
      continue
    }
    set idx [string first $anchor $data]
    if {$idx < 0} {
      puts "Warning (UltraZohm): portMEMORY_BARRIER anchor not found in $f -- skipped"
      continue
    }
    set head [string range $data 0 [expr {$idx - 1}]]
    set tail [string range $data $idx end]
    set fp [open $f w]; puts -nonewline $fp "$head$barrier_define\n$tail"; close $fp
    puts "Info (UltraZohm): inserted portMEMORY_BARRIER into $f"
  }
}

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
# Insert portMEMORY_BARRIER into the generated FreeRTOSConfig.h of the A53
# FreeRTOS BSP, and check that the kernel library is built with it.
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
# (kernel >= 10.5.1), where the port's portmacro.h defines it; the procs below
# then leave the BSP alone.
#
# Why the checks: "bsp regenerate" writes FreeRTOSConfig.h without the define,
# and a "bsp regenerate" that fails half-way (e.g. on a BSP file locked by
# another process) leaves no FreeRTOSConfig.h to patch at all. Vitis then
# generates the sources later, without the define. That happened once and only
# showed up as a frozen A53 after minutes of network load. Therefore:
#
#   uz_vitis_patch_freertos_bsp ws_path
#       inserts the define into every generated copy (idempotent). Call it
#       after every FreeRTOS "bsp regenerate" and again right before the
#       platform build ("platform generate").
#   uz_vitis_verify_freertos_bsp ws_path
#       call it after the platform build. Stops with an error unless the
#       kernel library and the exported headers were built from the patched
#       header.
#
# A BSP regeneration outside these scripts (e.g. after changing BSP settings
# in the Vitis GUI) is caught when the FreeRTOS application is compiled, see
# vitis/software/FreeRTOS/sw/uz_apu_assert_configuration.c.
###########################################################################

# The FreeRTOS BSP folder(s) of the workspace (normally exactly one).
proc uz_vitis_freertos_bsp_dirs {ws_path} {
  return [glob -nocomplain -types d -- \
      [file join $ws_path * psu_cortexa53_0 FreeRTOS_domain bsp psu_cortexa53_0]]
}

proc uz_vitis_read_text {path} {
  set fp [open $path r]
  set data [read $fp]
  close $fp
  return $data
}

# 1 if the text defines portMEMORY_BARRIER (a mention in a comment does not count).
proc uz_vitis_defines_memory_barrier {text} {
  return [regexp -line {^[ \t]*#[ \t]*define[ \t]+portMEMORY_BARRIER[ \t]*\(} $text]
}

# 1 if the FreeRTOS port of the BSP defines portMEMORY_BARRIER itself.
proc uz_vitis_freertos_port_has_barrier {bsp} {
  foreach f [glob -nocomplain -- [file join $bsp libsrc freertos10_xilinx_* src portmacro.h]] {
    if {[uz_vitis_defines_memory_barrier [uz_vitis_read_text $f]]} {
      return 1
    }
  }
  return 0
}

# The kernel is compiled from the libsrc copy, the BSP build copies it to
# include/. The exported copy that the applications compile against is left to
# "platform generate", which copies it together with the rebuilt library.
proc uz_vitis_freertos_config_headers {bsp} {
  set headers {}
  foreach pat [list \
      [file join $bsp libsrc freertos10_xilinx_* src FreeRTOSConfig.h] \
      [file join $bsp include FreeRTOSConfig.h]] {
    foreach f [glob -nocomplain -- $pat] {
      lappend headers $f
    }
  }
  return $headers
}

proc uz_vitis_patch_freertos_bsp {ws_path} {
  set barrier_define "#define portMEMORY_BARRIER() __asm volatile ( \"\" ::: \"memory\" )"
  set anchor "#define configASSERT"

  set headers {}
  foreach bsp [uz_vitis_freertos_bsp_dirs $ws_path] {
    if {[uz_vitis_freertos_port_has_barrier $bsp]} {
      puts "Info (UltraZohm): the FreeRTOS port in $bsp defines portMEMORY_BARRIER, nothing to patch"
      return
    }
    set headers [concat $headers [uz_vitis_freertos_config_headers $bsp]]
  }
  if {[llength $headers] == 0} {
    # Not fatal here: after a failed "bsp regenerate" Vitis generates the
    # sources later. The call before the platform build patches them, and
    # uz_vitis_verify_freertos_bsp checks the result.
    puts "Warning (UltraZohm): portMEMORY_BARRIER patch: no FreeRTOSConfig.h under $ws_path yet"
    return
  }

  foreach f $headers {
    set data [uz_vitis_read_text $f]
    if {[uz_vitis_defines_memory_barrier $data]} {
      puts "Info (UltraZohm): portMEMORY_BARRIER already present in $f"
      continue
    }
    set idx [string first $anchor $data]
    if {$idx < 0} {
      error "Error (UltraZohm): portMEMORY_BARRIER patch: '$anchor' not found in $f.\
          The generated FreeRTOSConfig.h has changed, adapt tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl."
    }
    set head [string range $data 0 [expr {$idx - 1}]]
    set tail [string range $data $idx end]
    set fp [open $f w]
    puts -nonewline $fp "$head$barrier_define\n$tail"
    close $fp
    puts "Info (UltraZohm): inserted portMEMORY_BARRIER into $f"
  }
}

proc uz_vitis_verify_freertos_bsp {ws_path} {
  set problems {}
  set bsps [uz_vitis_freertos_bsp_dirs $ws_path]
  if {[llength $bsps] == 0} {
    lappend problems "no FreeRTOS BSP under $ws_path"
  }
  foreach bsp $bsps {
    if {[uz_vitis_freertos_port_has_barrier $bsp]} {
      continue
    }
    set src [glob -nocomplain -- [file join $bsp libsrc freertos10_xilinx_* src FreeRTOSConfig.h]]
    if {[llength $src] != 1} {
      lappend problems "expected one FreeRTOSConfig.h in [file join $bsp libsrc], found [llength $src]"
      continue
    }
    set src [lindex $src 0]
    # bsp = <ws>/<platform>/psu_cortexa53_0/FreeRTOS_domain/bsp/psu_cortexa53_0
    set platform_dir [file dirname [file dirname [file dirname [file dirname $bsp]]]]
    set platform [file tail $platform_dir]
    set export [file join $platform_dir export $platform sw $platform FreeRTOS_domain]

    foreach header [list $src \
        [file join $bsp include FreeRTOSConfig.h] \
        [file join $export bspinclude include FreeRTOSConfig.h]] {
      if {![file exists $header]} {
        lappend problems "missing $header"
      } elseif {![uz_vitis_defines_memory_barrier [uz_vitis_read_text $header]]} {
        lappend problems "no portMEMORY_BARRIER in $header"
      }
    }
    # A kernel library built (or exported) before the header got the define
    # still contains the old code.
    foreach lib [list [file join $bsp lib libfreertos.a] \
        [file join $export bsplib lib libfreertos.a]] {
      if {![file exists $lib]} {
        lappend problems "missing $lib"
      } elseif {[file mtime $lib] < [file mtime $src]} {
        lappend problems "$lib was built before $src got the define"
      }
    }
  }
  if {[llength $problems] > 0} {
    set fix [join [list \
        "Fix it in the XSCT console of Vitis:" \
        "  cd \[getws\]" \
        "  source {../../tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl}" \
        "  uz_vitis_patch_freertos_bsp \[getws\]" \
        "  platform generate" \
        "  uz_vitis_verify_freertos_bsp \[getws\]" \
        "and build the FreeRTOS application again."] "\n"]
    error "Error (UltraZohm): the FreeRTOS kernel is not built with portMEMORY_BARRIER,\
        the A53 can freeze under load:\n  [join $problems "\n  "]\n$fix"
  }
  puts "Info (UltraZohm): the FreeRTOS kernel and the exported headers are built with portMEMORY_BARRIER"
}

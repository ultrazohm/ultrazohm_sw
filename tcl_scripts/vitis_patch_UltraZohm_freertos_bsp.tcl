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
# FreeRTOS BSP, and check that the kernel is built with it.
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
#       inserts the define into every generated copy, or replaces an older
#       define (idempotent). Call it after every FreeRTOS "bsp regenerate" and
#       again right before the platform build ("platform generate").
#   uz_vitis_verify_freertos_bsp ws_path
#       call it after the platform build. Stops with an error unless the
#       headers have the define and the kernel library (BSP and exported copy)
#       is compiled with it.
#   uz_vitis_check_freertos_elf ws_path elf
#       call it before the ELF is downloaded to the A53 (see
#       vitis_debug_run_UltraZohm.tcl). Stops with an error unless the kernel
#       linked into the ELF is compiled with the define. If the workspace
#       folder holds the file uz_start_without_memory_barrier.txt, it only
#       warns, so that the UltraZohm can be started anyway.
#
# How the checks see the compiled kernel: next to the define, the patch adds
# one byte in the section .uz_freertos_memory_barrier to every kernel object
# file (not to application objects). The section is not loaded to the target
# (no "a" flag), the linker keeps it in the ELF, and the kernel code is the same
# as with the define alone. So the section in tasks.o of libfreertos.a, or in
# FreeRTOS.elf, shows that the kernel was compiled with the patched header. The
# checks read file contents, not file times: a library or ELF that is merely
# older than a header raises no error.
#
# A BSP regeneration outside these scripts (e.g. after changing BSP settings
# in the Vitis GUI) is caught when the FreeRTOS application is compiled (see
# vitis/software/FreeRTOS/sw/uz_apu_assert_configuration.c), and at the latest
# when the UltraZohm is programmed.
###########################################################################

# Name of the marker section, see above.
proc uz_vitis_barrier_section {} {
  return .uz_freertos_memory_barrier
}

# The define: a compiler barrier (an asm statement with a "memory" clobber, no
# instruction).
proc uz_vitis_barrier_define {} {
  return {#define portMEMORY_BARRIER() __asm volatile ( "" ::: "memory" )}
}

# The lines that the patch inserts into FreeRTOSConfig.h: the define, and one
# byte in the marker section. The kernel sources define
# MPU_WRAPPERS_INCLUDED_FROM_API_FILE before they include FreeRTOS.h, the
# applications do not, so only the kernel objects carry the marker. It is a
# separate asm statement outside of any function: any text inside the barrier's
# asm statement would change how GCC lays out the kernel code.
proc uz_vitis_barrier_block {} {
  return [join [list \
      "/* UltraZohm: see tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl */" \
      [uz_vitis_barrier_define] \
      "#if defined( MPU_WRAPPERS_INCLUDED_FROM_API_FILE ) && !defined( __ASSEMBLER__ )" \
      [format {__asm__ ( ".pushsection %s, \"\"\n\t.byte 1\n\t.popsection" );} \
          [uz_vitis_barrier_section]] \
      "#endif"] "\n"]
}

# A line that defines portMEMORY_BARRIER (a mention in a comment does not count).
proc uz_vitis_barrier_define_re {} {
  return {^[ \t]*#[ \t]*define[ \t]+portMEMORY_BARRIER[ \t]*\(.*$}
}

# The FreeRTOS BSP folder(s) of the workspace (normally exactly one).
proc uz_vitis_freertos_bsp_dirs {ws_path} {
  return [glob -nocomplain -types d -- \
      [file join $ws_path * psu_cortexa53_0 FreeRTOS_domain bsp psu_cortexa53_0]]
}

# bsp = <ws>/<platform>/psu_cortexa53_0/FreeRTOS_domain/bsp/psu_cortexa53_0
proc uz_vitis_freertos_platform_dir {bsp} {
  return [file dirname [file dirname [file dirname [file dirname $bsp]]]]
}

# The exported FreeRTOS domain that the applications compile and link against.
proc uz_vitis_freertos_export_dir {bsp} {
  set platform_dir [uz_vitis_freertos_platform_dir $bsp]
  set platform [file tail $platform_dir]
  return [file join $platform_dir export $platform sw $platform FreeRTOS_domain]
}

proc uz_vitis_read_text {path} {
  set fp [open $path r]
  set data [read $fp]
  close $fp
  return $data
}

proc uz_vitis_read_binary {path} {
  set fp [open $path r]
  fconfigure $fp -translation binary
  set data [read $fp]
  close $fp
  return $data
}

# The lines of the text that define portMEMORY_BARRIER.
proc uz_vitis_barrier_defines {text} {
  return [regexp -all -inline -line [uz_vitis_barrier_define_re] $text]
}

# 1 if the text defines portMEMORY_BARRIER in any way.
proc uz_vitis_defines_memory_barrier {text} {
  return [expr {[llength [uz_vitis_barrier_defines $text]] > 0}]
}

# 1 if the text has the patched block and defines portMEMORY_BARRIER only there.
proc uz_vitis_defines_patched_barrier {text} {
  if {[string first [uz_vitis_barrier_block] $text] < 0} {
    return 0
  }
  foreach line [uz_vitis_barrier_defines $text] {
    if {$line ne [uz_vitis_barrier_define]} {
      return 0
    }
  }
  return 1
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

# The section names of an ELF file given as binary data (64 bit little endian,
# as for the A53).
proc uz_vitis_elf_section_names {data} {
  if {[string range $data 0 3] ne "\177ELF"} {
    error "not an ELF file"
  }
  if {[binary scan $data @4cu@5cu class endian] != 2 || $class != 2 || $endian != 1} {
    error "not a 64 bit little endian ELF file"
  }
  if {[binary scan $data @40w@58su@60su@62su shoff shentsize shnum shstrndx] != 4} {
    error "truncated ELF file"
  }
  if {$shoff == 0} {
    return {}
  }
  # With very many sections the real numbers are in section header 0.
  if {[binary scan $data @[expr {$shoff + 32}]w@[expr {$shoff + 40}]iu size0 link0] != 2} {
    error "truncated ELF file"
  }
  if {$shnum == 0} {
    set shnum $size0
  }
  if {$shstrndx == 0xffff} {
    set shstrndx $link0
  }
  if {[binary scan $data @[expr {$shoff + $shstrndx * $shentsize + 24}]ww stroff strsize] != 2} {
    error "truncated ELF file"
  }
  set strtab [string range $data $stroff [expr {$stroff + $strsize - 1}]]
  set names {}
  for {set i 0} {$i < $shnum} {incr i} {
    if {[binary scan $data @[expr {$shoff + $i * $shentsize}]iu name_off] != 1} {
      error "truncated ELF file"
    }
    set end [string first "\000" $strtab $name_off]
    if {$end < 0} {
      error "corrupt ELF section name table"
    }
    lappend names [string range $strtab $name_off [expr {$end - 1}]]
  }
  return $names
}

# The content of the member 'name' of an ar archive given as binary data (GNU
# format, as the BSP build writes it), or "" if there is no such member.
proc uz_vitis_ar_member {data name} {
  if {[string range $data 0 7] ne "!<arch>\n"} {
    error "not an ar archive"
  }
  set pos 8
  set len [string length $data]
  while {$pos + 60 <= $len} {
    set member [string trimright [string range $data $pos [expr {$pos + 15}]]]
    if {[scan [string range $data [expr {$pos + 48}] [expr {$pos + 57}]] %d size] != 1} {
      error "corrupt ar archive"
    }
    set start [expr {$pos + 60}]
    if {$member eq "$name/"} {
      return [string range $data $start [expr {$start + $size - 1}]]
    }
    # Members start at even offsets.
    set pos [expr {$start + $size + ($size % 2)}]
  }
  return ""
}

proc uz_vitis_has_barrier_section {elf_data} {
  set names [uz_vitis_elf_section_names $elf_data]
  return [expr {[lsearch -exact $names [uz_vitis_barrier_section]] >= 0}]
}

proc uz_vitis_freertos_fix_hint {ws_path} {
  set platform UltraZohm
  set bsps [uz_vitis_freertos_bsp_dirs $ws_path]
  if {[llength $bsps] > 0} {
    set platform [file tail [uz_vitis_freertos_platform_dir [lindex $bsps 0]]]
  }
  # "app clean": the application does not relink when only libfreertos.a changed.
  return [join [list \
      "Fix it in the XSCT console of Vitis:" \
      "  cd \[getws\]" \
      "  source {../../tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl}" \
      "  platform active $platform" \
      "  uz_vitis_patch_freertos_bsp \[getws\]" \
      "  platform generate" \
      "  uz_vitis_verify_freertos_bsp \[getws\]" \
      "  app clean -name FreeRTOS" \
      "  app build -name FreeRTOS"] "\n"]
}

proc uz_vitis_patch_freertos_bsp {ws_path} {
  set block [uz_vitis_barrier_block]
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
    if {[uz_vitis_defines_patched_barrier $data]} {
      puts "Info (UltraZohm): portMEMORY_BARRIER already present in $f"
      continue
    }
    if {[uz_vitis_defines_memory_barrier $data]} {
      # An older version of this patch (only the define): replace it by the
      # block, so that the checks find the marker.
      foreach line [uz_vitis_barrier_defines $data] {
        if {[string index $line end] eq "\\"} {
          error "Error (UltraZohm): portMEMORY_BARRIER patch: multi-line define in $f,\
              adapt tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl."
        }
      }
      # Shrink existing blocks to their define first, so that blocks are never nested.
      set data [string map [list $block [uz_vitis_barrier_define]] $data]
      regsub -all -line [uz_vitis_barrier_define_re] $data [string map {\\ \\\\ & \\&} $block] data
      set action "replaced the portMEMORY_BARRIER define in"
    } else {
      set idx [string first $anchor $data]
      if {$idx < 0} {
        error "Error (UltraZohm): portMEMORY_BARRIER patch: '$anchor' not found in $f.\
            The generated FreeRTOSConfig.h has changed, adapt tcl_scripts/vitis_patch_UltraZohm_freertos_bsp.tcl."
      }
      set data "[string range $data 0 [expr {$idx - 1}]]$block\n[string range $data $idx end]"
      set action "inserted portMEMORY_BARRIER into"
    }
    set fp [open $f w]
    puts -nonewline $fp $data
    close $fp
    puts "Info (UltraZohm): $action $f"
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
    set export [uz_vitis_freertos_export_dir $bsp]

    foreach header [list [lindex $src 0] \
        [file join $bsp include FreeRTOSConfig.h] \
        [file join $export bspinclude include FreeRTOSConfig.h]] {
      if {![file exists $header]} {
        lappend problems "missing $header"
      } elseif {![uz_vitis_defines_patched_barrier [uz_vitis_read_text $header]]} {
        lappend problems "no current portMEMORY_BARRIER define in $header"
      }
    }
    # The library may still hold a kernel compiled before the header got the
    # define, e.g. if the platform was not rebuilt after the patch.
    foreach lib [list [file join $bsp lib libfreertos.a] \
        [file join $export bsplib lib libfreertos.a]] {
      if {![file exists $lib]} {
        lappend problems "missing $lib"
        continue
      }
      if {[catch {
        set tasks [uz_vitis_ar_member [uz_vitis_read_binary $lib] tasks.o]
        if {$tasks eq ""} {
          lappend problems "no tasks.o in $lib"
        } elseif {![uz_vitis_has_barrier_section $tasks]} {
          lappend problems "tasks.o in $lib is compiled without portMEMORY_BARRIER"
        }
      } msg]} {
        lappend problems "cannot read $lib: $msg"
      }
    }
  }
  if {[llength $problems] > 0} {
    set hint [uz_vitis_freertos_fix_hint $ws_path]
    error "Error (UltraZohm): the FreeRTOS kernel is not built with portMEMORY_BARRIER,\
        the A53 can freeze under load:\n  [join $problems "\n  "]\n$hint"
  }
  puts "Info (UltraZohm): the FreeRTOS kernel library and the exported headers\
      are built with portMEMORY_BARRIER"
}

# File in the workspace folder that lets uz_vitis_check_freertos_elf start a
# FreeRTOS.elf without the barrier anyway.
proc uz_vitis_barrier_override_name {} {
  return uz_start_without_memory_barrier.txt
}

# Path of that file, or "" if there is none. Also accepts the name without or
# with a second extension, e.g. "....txt.txt" from the Windows Explorer.
proc uz_vitis_barrier_override {ws_path} {
  set pattern "[file rootname [uz_vitis_barrier_override_name]]*"
  return [lindex [glob -nocomplain -types f -directory $ws_path -- $pattern] 0]
}

proc uz_vitis_check_freertos_elf {ws_path elf} {
  foreach bsp [uz_vitis_freertos_bsp_dirs $ws_path] {
    if {[uz_vitis_freertos_port_has_barrier $bsp]} {
      puts "Info (UltraZohm): the FreeRTOS port defines portMEMORY_BARRIER, no check of $elf needed"
      return
    }
  }
  if {![file exists $elf]} {
    error "Error (UltraZohm): $elf not found, build the FreeRTOS application.\
        The UltraZohm was not programmed."
  }
  if {[catch {uz_vitis_has_barrier_section [uz_vitis_read_binary $elf]} ok]} {
    error "Error (UltraZohm): cannot read $elf: $ok. The UltraZohm was not programmed."
  }
  set override [uz_vitis_barrier_override $ws_path]
  if {!$ok} {
    if {$override ne ""} {
      puts "Warning (UltraZohm): the FreeRTOS kernel in $elf is not built with the\
          portMEMORY_BARRIER patch, the A53 can freeze under load."
      puts "Warning (UltraZohm): starting anyway, because $override exists.\
          Delete it once the workspace is fixed."
      return
    }
    set hint [uz_vitis_freertos_fix_hint $ws_path]
    set start_anyway [file join $ws_path [uz_vitis_barrier_override_name]]
    error "Error (UltraZohm): the FreeRTOS kernel in $elf is not built with the\
        portMEMORY_BARRIER patch (or with an older version of it), the A53 can freeze\
        under load. The UltraZohm was not programmed.\n$hint\nTo start the UltraZohm\
        anyway, create the (empty) file $start_anyway and launch again."
  }
  puts "Info (UltraZohm): the FreeRTOS kernel in $elf is built with portMEMORY_BARRIER"
  if {$override ne ""} {
    puts "Info (UltraZohm): $override is no longer needed, you can delete it."
  }
}

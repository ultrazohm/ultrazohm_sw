###########################################################################
# Copyright 2021 Eyke Liegmann
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
#
# execute in XSCT console in Vitis workspace
#	cd [getws] 
#	source {../../tcl_scripts/vitis_update_platform.tcl}
#
# XSCT Programming Reference
# https://www.xilinx.com/html_docs/xilinx2020_1/vitis_doc/
###########################################################################


proc app_clean {{name *}} {
  set tmplist [app list]
  set tmplist [split $tmplist "\n"]
  set index 0
  foreach element $tmplist {
    if {[catch {
      if {![string match "*==*" $element] && ! [string match "*NAME*" $element]  && ! [string match "" $element]} {
        set tmpname [lindex [split $element " "] 1];
        if {[string match $name $tmpname]} {
          app clean $tmpname
          puts "clean -name $tmpname "
        } else {
          puts "skip $tmpname"
        }
      } else {
        puts "Debug: (UZ) $element"
      }
    } result]} {
      puts "Error:(UZ) Script (app_clean) failed failed at $element with: $result."
    }
    incr index
  }
}

proc app_build {{name *}} {
  set tmplist [app list]
  set tmplist [split $tmplist "\n"]
  set index 0
  foreach element $tmplist {
    if {[catch {
      if {![string match "*==*" $element] && ! [string match "*NAME*" $element]  && ! [string match "" $element]} {
        set tmpname [lindex [split $element " "] 1];
        if {[string match $name $tmpname]} {
          app build $tmpname
          puts "build $tmpname "
        } else {
          puts "skip $tmpname"
        }
      } else {
        puts "Debug: (UZ) $element"
      }
    } result]} {
      puts "Error:(UZ) Script (app_build) failed at $element with: $result."
    }
    incr index
  }
}


proc vitis_main {} {

set WS_PATH [getws]
cd $WS_PATH
cd ..
set FOLDER_PATH [pwd]
cd $WS_PATH

set PLATFORM_NAME 	UltraZohm
set XSA_FOLDER 		$FOLDER_PATH/vivado_exported_xsa

####################################################
puts "Info (UltraZohm): Chose active platform"
platform active $PLATFORM_NAME

####################################################
puts "Info (UltraZohm): Import new xsa hardware file from:"
puts "Info (UltraZohm): $XSA_FOLDER"
if {[catch {set XSA_FILES [glob -join -dir ${XSA_FOLDER} *.xsa]} ]} {puts "Error:(UltraZohm) update of ${PLATFORM_NAME} failed: .xsa does not exist in ${XSA_FOLDER}."}
#
set XSA_FILE [lindex $XSA_FILES 0]
puts "WARNING (UltraZohm): Make sure there is only one xsa file in ${XSA_FOLDER} "
puts "Info (UltraZohm): using {$XSA_FILE}"
platform config -updatehw $XSA_FILE

####################################################
puts "Info (UltraZohm): Regenerate FreeRTOS_domain BSP"
domain active FreeRTOS_domain
# increase heap size of freertos, to fix javascope glitches
# this has to be included in update_platform script, otherwise this setting is overwritten (for some strange reason)
bsp config total_heap_size  200000000
# FPU/NEON context must be saved for ALL tasks (configUSE_TASK_FPU_SUPPORT=2).
# With the default (1), tasks must opt in via vPortTaskUsesFPU() -- nothing does,
# yet on aarch64 GCC uses NEON Q-registers inside ordinary memcpy (FreeRTOS
# queue copies, lwIP pbuf copies, the XCP TX batcher). A task preempted
# mid-memcpy resumed with corrupted Q-registers, eventually corrupting kernel
# lists: observed as an infinite loop in xTaskResumeAll (tasks.c:2250) with
# GIC PMR stuck at 0x90, all interrupts masked, whole A53 frozen (XCP DAQ
# died after minutes). Root-caused 2026-06; cf. XCP_BOTTLENECK_ANALYSIS.md.
bsp config use_task_fpu_support 2
platform write
bsp regenerate

# CRITICAL: patch portMEMORY_BARRIER into the regenerated FreeRTOSConfig.h.
# The Xilinx ARM_CA53 port does not define it, so the kernel default (EMPTY)
# applies. The kernel relies on it as a compiler barrier, e.g. in the
# xTaskResumeAll() pending-ready drain loop: without it, GCC -O2 hoists the
# list-head load out of the loop (verified in disassembly) and the kernel
# lists get corrupted whenever >=2 tasks are woken during one scheduler
# suspension window -> total system freeze. There is no BSP parameter for
# this, hence the textual patch. Cf. XCP_BOTTLENECK_ANALYSIS.md.
set barrier_define "#define portMEMORY_BARRIER() __asm volatile ( \"\" ::: \"memory\" )"
foreach frtos_cfg [glob -nocomplain \
        "*/psu_cortexa53_0/FreeRTOS_domain/bsp/psu_cortexa53_0/include/FreeRTOSConfig.h" \
        "*/psu_cortexa53_0/FreeRTOS_domain/bsp/psu_cortexa53_0/libsrc/freertos10_xilinx_*/src/FreeRTOSConfig.h"] {
    set fp [open $frtos_cfg r]; set cfg_content [read $fp]; close $fp
    if {[string first "portMEMORY_BARRIER" $cfg_content] == -1} {
        set cfg_content [string map [list "#define configASSERT" "$barrier_define\n#define configASSERT"] $cfg_content]
        set fp [open $frtos_cfg w]; puts -nonewline $fp $cfg_content; close $fp
        puts "Info (UltraZohm): patched portMEMORY_BARRIER into $frtos_cfg"
    } else {
        puts "Info (UltraZohm): portMEMORY_BARRIER already present in $frtos_cfg"
    }
}

####################################################
puts "Info (UltraZohm): Regenerate Baremetal_domain BSP"
domain active Baremetal_domain
bsp regenerate

#####################################################
#puts "Info (UltraZohm): Regenerate FSBL_domain BSP"
#domain active FSBL_domain
#bsp regenerate

#####################################################
puts "Info (UltraZohm): generate Platform project"
platform generate

####################################################
#puts "Info (UltraZohm): clean all application projects"
#app_clean
puts "Info (UltraZohm): build all application projects"
app_build

puts "========================================"
puts "Info (UltraZohm): vitis_update_platform.tcl script finished successfully"
puts "========================================"

}

vitis_main

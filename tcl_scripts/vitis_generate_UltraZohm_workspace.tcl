###########################################################################
# Copyright 2021-2023 Eyke Liegmann, Tobias Schindler, Martin Geier
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
#	source {../../tcl_scripts/vitis_generate_UltraZohm_workspace.tcl}
#
# XSCT Programming Reference UG1416
# https://www.xilinx.com/html_docs/xilinx2020_1/vitis_doc/
###########################################################################

### Configuration Parameters (at the moment, most people do not have to change anything here)
## - Supported values and the [default] are listed behind each parameter, e.g.: true, [false]
## - More parameters to come in the future, including the selection of the hardware platform

## uzcfg is global for now (but can easily be localized being a hash table)
global uzcfg

## System-wide Settings
# Hardware platform: [UltraZohm]
set uzcfg(PLATFORM_NAME) 	UltraZohm

### End of the Configuration (i.e., you might not want to change anything after this line ;))


proc app_clean {{name *}} {
  set tmplist [app list]
  set tmplist [split $tmplist "\n"]
  set index 0
  foreach element $tmplist {
    if {[catch {
      if {![string match "*==*" $element] && ! [string match "*NAME*" $element] && ! [string match "" $element]} {
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
      if {![string match "*==*" $element] && ! [string match "*NAME*" $element] && ! [string match "" $element]} {
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

  global uzcfg

  set WS_PATH [getws]
  cd $WS_PATH
  cd ..
  set FOLDER_PATH [pwd]
  cd $WS_PATH

  set PLATFORM_NAME 	$uzcfg(PLATFORM_NAME)
  set XSA_FOLDER 	[file join $FOLDER_PATH vivado_exported_xsa]
  set EXPORT_FOLDER [file join $FOLDER_PATH software]
  set SHARED_FOLDER [file join $EXPORT_FOLDER shared]


  set filename_Baremetal [file join $EXPORT_FOLDER Baremetal/src]
  set filename_FreeRTOS  [file join $EXPORT_FOLDER FreeRTOS]
  set filename_FSBL      [file join $EXPORT_FOLDER FSBL]
  set filename_FSBLelf   [file join $EXPORT_FOLDER BootImage]

  puts "Info (UltraZohm): Path to exports to be imported:"
  puts stdout $EXPORT_FOLDER

  ####################################################
  puts "Info (UltraZohm): create Platform Project"
  if {[catch {set XSA_FILES [glob -join -dir ${XSA_FOLDER} *.xsa]} ]} {puts "Error:(UltraZohm) update of ${PLATFORM_NAME} failed: .xsa does not exist in ${XSA_FOLDER}."}
  #
  set XSA_FILE [lindex $XSA_FILES 0]
  puts "WARNING (UltraZohm): Make sure there is only one xsa file in ${XSA_FOLDER} "
  puts "Info (UltraZohm): using {$XSA_FILE}"

  #create platform
  platform create -name $PLATFORM_NAME -hw $XSA_FILE -no-boot-bsp

  #Domain FreeRTOS A53_0
  ####################################################
  puts "Info (UltraZohm): create FreeRTOS_domain"
  #add freertos domain
  domain create -name FreeRTOS_domain -os freertos10_xilinx -proc psu_cortexa53_0

  puts "Info (UltraZohm): change FreeRTOS BSP settings"
  #add liIP lib to BSP
  bsp setlib -name lwip211

  # get list of configurable parameters for lwip lib
  #bsp listparams -lib lwip211
  bsp config api_mode SOCKET_API
  platform write
  bsp config dhcp_does_arp_check true
  platform write
  bsp config lwip_dhcp true
  platform write
  # increase heap size of freertos, to fix javascope glitches
  bsp config total_heap_size 200000000
  platform write

  puts "Info (UltraZohm): regenerate FreeRTOS BSP"
  #regenerate board support package
  bsp regenerate


  #Domain Baremetal R5_0
  #####################################################
  puts "Info (UltraZohm): create Baremetal_domain"
  #create Baremetal domain
  domain create -name Baremetal_domain -os standalone -proc psu_cortexr5_0
  #save changes
  platform write


  ##Domain FSBL (Standalone) A53_0
  #####################################################
  #puts "Info (UltraZohm): create FSBL_domain"
  ##add FSBL domain
  #domain create -name FSBL_domain -os standalone -proc psu_cortexa53_0
  #
  #puts "Info (UltraZohm): change FSBL BSP settings"
  ##add xilffs lib to BSP
  #bsp setlib -name xilffs
  ##add xilpm lib to BSP
  #bsp setlib -name xilpm
  ##add xilsecure lib to BSP
  #bsp setlib -name xilsecure
  #
  ## get list of configurable parameters for xilffs lib
  ##bsp listparams -lib xilffs
  #bsp config zynqmp_fsbl_bsp true
  #platform write
  #
  #puts "Info (UltraZohm): regenerate FSBL BSP"
  #regenerate board support package
  #bsp regenerate

  #Regenerate platform
  #####################################################
  puts "Info (UltraZohm): generate Platform project"
  platform generate


  #Application Baremetal R5_0
  #####################################################
  puts "Info (UltraZohm): create Baremetal Application"
  # create application
  app create -name Baremetal -template {Empty Application} -platform $PLATFORM_NAME -domain Baremetal_domain

  puts "Info (UltraZohm): import Baremetal Application sources"
  # import sources to baremetal project
  # first the source files are linked
  importsources -name Baremetal -path $filename_Baremetal -soft-link
  # add shared folder
  importsources -name Baremetal -path $SHARED_FOLDER -soft-link
  # link to linker-script instead of copying it
  app config -name Baremetal -set linker-script $filename_Baremetal/lscript.ld

  #add math library to linker option
  app config -name Baremetal -add libraries m


  #Application FreeRTOS A53_0
  ####################################################
  puts "Info (UltraZohm): create FreeRTOS Application"
  #create application
  app create -name FreeRTOS -template {Empty Application} -platform $PLATFORM_NAME -domain FreeRTOS_domain

  puts "Info (UltraZohm): import FreeRTOS Application sources"
  #import sources to freertos project

  puts "Info (UltraZohm): Path to FreeRTOS source files:"
  puts stdout $filename_FreeRTOS

  # first the source files are linked
  importsources -name FreeRTOS -path $filename_FreeRTOS -soft-link
  importsources -name FreeRTOS -path $SHARED_FOLDER -soft-link
  #link to linker-script instead of copying it
  app config -name FreeRTOS -set linker-script $filename_FreeRTOS/lscript.ld

  # add shared folder to build directory
  # this is a bit of hack, since it is not possible to add a compiler directory using the TCL script
  # we have to add it with -I"path" which results in the same
  # but in Vitis in the compiler settings, it is listed under miscellaneous instead of directories
  app config -name Baremetal compiler-misc -I"$SHARED_FOLDER"
  app config -name FreeRTOS compiler-misc -I"$SHARED_FOLDER"

  # set optimization level
  app config -name FreeRTOS -set compiler-optimization {Optimize most (-O3)}
  app config -name Baremetal -set compiler-optimization {Optimize more (-O2)}

  ##Application FSBL (Standalone) A53_0
  #####################################################
  #puts "Info (UltraZohm): create FSBL Application"
  ##create standalone app based on {Zynq MP FSBL}
  #app create -name FSBL -template {Zynq MP FSBL} -platform $PLATFORM_NAME -domain FSBL_domain
  ##app create -name FSBL -template {Empty Application} -platform $PLATFORM_NAME -domain FSBL_domain
  #
  #puts "Path to FSBL:"
  #puts stdout $filename_FSBL
  #
  #puts "Info (UltraZohm): import FSBL Application sources"
  ##import sources to FSBL project
  #importsources -name FSBL -path $filename_FSBL -soft-link
  #importsources -name FSBL -path $filename_FSBL/lscript.ld -linker-script

  puts "Info (UltraZohm): add standard FSBL.elf"
  platform config -remove-boot-bsp
  platform config -fsbl-elf $filename_FSBLelf/FSBL.elf
  platform write

  #Clean all
  ####################################################
  puts "Info (UltraZohm): clean platform and all application projects"
  platform clean
  app_clean
  puts "Info (UltraZohm): build platform and all application projects"
  platform generate
  app_build


  puts "========================================"
  # copy debug files
  set filename_meta [file join $WS_PATH .metadata]
  set filename_plugins [file join $filename_meta .plugins]
  set filename_eclipse [file join $filename_plugins org.eclipse.debug.core]
  set filename_launches [file join $filename_eclipse .launches]
  puts "Info (UltraZohm): Path to launches:"
  puts stdout $filename_launches

  file mkdir $filename_launches
  set DebugBaremetal [file join $EXPORT_FOLDER DebugBaremetal.launch]
  set DebugFreeRTOS [file join $EXPORT_FOLDER DebugFreeRTOS.launch]
  set DebugAll [file join $EXPORT_FOLDER Debug_FreeRTOS_Baremetal_FPGA.launch]
  #     file copy ?-force? ?--? source ?source ...? targetDir
  #file copy -force -- $DebugBaremetal $filename_launches
  file copy -force -- $DebugFreeRTOS $filename_launches
  file copy -force -- $DebugAll $filename_launches
  puts "========================================"
  puts "Info (UltraZohm): debug files copied"
  puts "Info (UltraZohm): debug configurations are visible after restarting Vitis"
  puts "========================================"
  puts "Info (UltraZohm): generate_UltraZohm_workspace.tcl script finished successfully"
  puts "========================================"
}


vitis_main



## useful
# change active domain
# domain list
# domain active []

##list of all os
#repo -os




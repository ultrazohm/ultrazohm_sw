###########################################################################
# Copyright 2021 Eyke Liegmann, Tobias Schindler
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


proc app_clean {{name *}} {
  set tmplist [app list]
  set index 0
  foreach element $tmplist {
	if {$index>2} {
	  if {[string match $name $element]} {
		app clean $element
		puts "clean -name $element "
	  } else {
		puts "skip $element"
	  }
	} else {
	  puts "$element"
	}
	incr index
  }
}

proc app_build {{name *}} {
  set tmplist [app list]
  set index 0
  foreach element $tmplist {
	if {$index>2} {
	  if {[string match $name $element]} {
	  
		if {[catch {
		  app build $element
		} result]} { puts "Error:(TE) build $element failed: $result."}

		puts "build $element "
	  } else {
		puts "skip $element"
	  }
	} else {
	  puts "$element"
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
set EXPORT_FOLDER [file join $FOLDER_PATH software]
puts "Path to exports to be imported:"
puts stdout $EXPORT_FOLDER

####################################################
puts "Info:(UltraZohm) create Platform Project"
if {[catch {set XSA_FILES [glob -join -dir ${XSA_FOLDER} *.xsa]} ]} {puts "Error:(UltraZohm) update of ${PLATFORM_NAME} failed: .xsa does not exist in ${XSA_FOLDER}."}
#
set XSA_FILE [lindex $XSA_FILES 0]
puts "WARNING (UltraZohm): Make sure there is only one xsa file in ${XSA_FOLDER} "
puts "using {$XSA_FILE}"

#create platform 
platform create -name $PLATFORM_NAME -hw $XSA_FILE -no-boot-bsp

#Domain FreeRTOS A53_0
####################################################
puts "Info:(UltraZohm) create FreeRTOS_domain"
#add freertos domain
domain create -name FreeRTOS_domain -os freertos10_xilinx -proc psu_cortexa53_0

puts "Info:(UltraZohm) change FreeRTOS BSP settings"
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
bsp config total_heap_size  20000000
platform write 

puts "Info:(UltraZohm) regenerate FreeRTOS BSP"
#regenerate board support package
bsp regenerate


#Domain Baremetal R5_0
#####################################################
puts "Info:(UltraZohm) create Baremetal_domain"
#create Baremetal domain
domain create -name Baremetal_domain -os standalone -proc psu_cortexr5_0 
#save changes
platform write 


##Domain FSBL (Standalone) A53_0
#####################################################
#puts "Info:(UltraZohm) create FSBL_domain"
##add FSBL domain
#domain create -name FSBL_domain -os standalone -proc psu_cortexa53_0
#
#puts "Info:(UltraZohm) change FSBL BSP settings"
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
#puts "Info:(UltraZohm) regenerate FSBL BSP"
#regenerate board support package
#bsp regenerate

#Regenerate platform
#####################################################
puts "Info:(UltraZohm) generate Platform project"
platform generate


#Application Baremetal R5_0
#####################################################
puts "Info:(UltraZohm) create Baremetal Application"
# application 
app create -name Baremetal -template {Empty Application} -platform $PLATFORM_NAME -domain Baremetal_domain

puts "Info:(UltraZohm) import Baremetal Application sources"
#import sources to baremetal project
# first the c-files are linked
# then the linker script is copied to the folder with a hard copy due to compilation errors otherwise - note that the sequence (first link the file, then copy the linker script is important due to -soft-link deleting the linker script otherwise
importsources -name Baremetal -path $FOLDER_PATH/software/Baremetal/src -soft-link
importsources -name Baremetal -path $FOLDER_PATH/software/Baremetal/src/lscript.ld -linker-script 
#add math library to linker option
app config -name Baremetal -add  libraries m


#Application FreeRTOS A53_0
####################################################
puts "Info:(UltraZohm) create FreeRTOS Application"
#create freertos app based on {FreeRTOS lwIP Echo Server}
#app create -name FreeRTOS -template {FreeRTOS lwIP Echo Server} -platform $PLATFORM_NAME -domain FreeRTOS_domain
app create -name FreeRTOS -template {Empty Application} -platform $PLATFORM_NAME -domain FreeRTOS_domain

puts "Info:(UltraZohm) import FreeRTOS Application sources"
#import sources to freertos project

set filename_FreeRTOS [file join $EXPORT_FOLDER FreeRTOS]
puts "Path to FreeRTOS:"
puts stdout $filename_FreeRTOS

importsources -name FreeRTOS -path $filename_FreeRTOS -soft-link
importsources -name FreeRTOS -path $filename_FreeRTOS/lscript.ld -linker-script

# add shared folder to build directory
app config -name FreeRTOS compiler-misc -I"$FOLDER_PATH/shared"
app config -name Baremetal compiler-misc -I"$FOLDER_PATH/shared"


# set optimization level 
app config -name FreeRTOS -set compiler-optimization {Optimize most (-O3)}
app config -name Baremetal -set compiler-optimization {Optimize more (-O2)}

##Application FSBL (Standalone) A53_0
#####################################################
#puts "Info:(UltraZohm) create FSBL Application"
##create standalone app based on {Zynq MP FSBL}
#app create -name FSBL -template {Zynq MP FSBL} -platform $PLATFORM_NAME -domain FSBL_domain
##app create -name FSBL -template {Empty Application} -platform $PLATFORM_NAME -domain FSBL_domain
#
#set filename_FSBL [file join $EXPORT_FOLDER FSBL]
#puts "Path to FSBL:"
#puts stdout $filename_FSBL
#
#puts "Info:(UltraZohm) import FSBL Application sources"
##import sources to FSBL project
#importsources -name FSBL -path $filename_FSBL -soft-link
#importsources -name FSBL -path $filename_FSBL/lscript.ld -linker-script

puts "Info:(UltraZohm) add standard FSBL.elf"
platform config -remove-boot-bsp
platform config -fsbl-elf $FOLDER_PATH/software/FSBL.elf 
platform write 

#Clean all
####################################################
puts "Info:(UltraZohm) clean platform and all application projects"
platform clean
app_clean
puts "Info:(UltraZohm) build platform and all application projects"
platform generate 
app_build


puts "========================================"
# copy debug files
set filename_meta [file join $WS_PATH .metadata]
set filename_plugins [file join $filename_meta .plugins]
set filename_eclipse [file join $filename_plugins org.eclipse.debug.core]
set filename_launches [file join $filename_eclipse .launches]
puts "Path to launches:"
puts stdout $filename_launches

file mkdir $filename_launches
set DebugBaremetal [file join $EXPORT_FOLDER DebugBaremetal.launch]
set DebugAll [file join $EXPORT_FOLDER Debug_FreeRTOS_Baremetal_FPGA.launch]
#     file copy ?-force? ?--? source ?source ...? targetDir
file copy -force -- $DebugBaremetal $filename_launches
file copy -force -- $DebugAll $filename_launches
puts "========================================"
puts "debug files copied"
puts "========================================"
puts "Info:(UltraZohm) generate_UltraZohm_workspace.tcl script finished successfully"
}


vitis_main



## useful
# change active domain 
# domain list 
# domain active []

##list of all os 
#repo -os 




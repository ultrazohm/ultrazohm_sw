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

####################################################
puts "Info:(UltraZohm) Chose active platform"
platform active $PLATFORM_NAME

####################################################
puts "Info:(UltraZohm) Import new xsa hardware file from:"
puts "$XSA_FOLDER"
if {[catch {set XSA_FILES [glob -join -dir ${XSA_FOLDER} *.xsa]} ]} {puts "Error:(UltraZohm) update of ${PLATFORM_NAME} failed: .xsa does not exist in ${XSA_FOLDER}."}
#
set XSA_FILE [lindex $XSA_FILES 0]
puts "WARNING (UltraZohm): Make sure there is only one xsa file in ${XSA_FOLDER} "
puts "using {$XSA_FILE}"
platform config -updatehw $XSA_FILE

####################################################
puts "Info:(UltraZohm) Regenerate FreeRTOS_domain BSP"
domain active FreeRTOS_domain
# increase heap size of freertos, to fix javascope glitches
# this has to be included in update_platform script, otherwise this setting is overwritten (for some strange reason)
bsp config total_heap_size  200000000
platform write 
bsp regenerate

####################################################
puts "Info:(UltraZohm) Regenerate Baremetal_domain BSP"
domain active Baremetal_domain
bsp regenerate

#####################################################
#puts "Info:(UltraZohm) Regenerate FSBL_domain BSP"
#domain active FSBL_domain
#bsp regenerate

#####################################################
puts "Info:(UltraZohm) generate Platform project"
platform generate

####################################################
#puts "Info:(UltraZohm) clean all application projects"
#app_clean
puts "Info:(UltraZohm) build all application projects"
app_build

}

vitis_main

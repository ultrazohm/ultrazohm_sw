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
#	source {../../tcl_scripts/create_variables.tcl}
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
set SHARED_FOLDER [file join $EXPORT_FOLDER shared]
puts "Path to exports to be imported:"
puts stdout $EXPORT_FOLDER

platform active $PLATFORM_NAME

set filename_FreeRTOS [file join $EXPORT_FOLDER FreeRTOS]
puts "Path to FreeRTOS:"
puts stdout $filename_FreeRTOS

importsources -name FreeRTOS -path $filename_FreeRTOS -soft-link


#Clean all
####################################################
puts "Info:(UltraZohm) clean platform and all application projects"
platform clean
app_clean
puts "Info:(UltraZohm) build platform and all application projects"
platform generate 
app_build



}


vitis_main



## useful
# change active domain 
# domain list 
# domain active []

##list of all os 
#repo -os 




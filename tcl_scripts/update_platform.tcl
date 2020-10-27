####################################################
#
# update_platform.tcl
#
# Copyright (C) 2020 UltraZohm Community, All rights reserved.
#
# Created on: 21.02.2020
#     Author: Eyke Liegmann (EL)
#
# execute in XSCT console in Vitis workspace
#	cd [getws] 
#	source {../export/update_platform.tcl}
#
# XSCT Programming Reference
# https://www.xilinx.com/html_docs/xilinx2019_2/vitis_doc/
####################################################


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
#exec taskkill /IM "rdi_xsct.exe" /F
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
puts "Info:(UltraZohm) Import new xsa hardware file from $XSA_FOLDER"
if {[catch {set xsafiles [glob -join -dir ${XSA_FOLDER} *.xsa]} ]} {puts "Error:(UltraZohm) update of ${PLATFORM_NAME} failed: .xsa does not exist in ${XSA_FOLDER}."}
#
set xsafile [lindex $xsafiles 0]
puts "WARNING (UltraZohm): Make sure there is only one xsa file in ${XSA_FOLDER} "
platform config -updatehw $xsafile

####################################################
puts "Info:(UltraZohm) Regenerate FreeRTOS_domain BSP"
# hier tritt der fehler auf! idee: update xsa von hand, restart vitis und excute tcl
domain active FreeRTOS_domain
bsp regenerate

####################################################
puts "Info:(UltraZohm) Regenerate Baremetal_domain BSP"
domain active Baremetal_domain
bsp regenerate

####################################################
puts "Info:(UltraZohm) Regenerate FSBL_domain BSP"
domain active FSBL_domain
bsp regenerate

#####################################################
puts "Info:(UltraZohm) generate Platform project"
platform generate

#Clean all
####################################################
#puts "Info:(UltraZohm) clean all application projects"
#app_clean
puts "Info:(UltraZohm) build all application projects"
app_build

}

vitis_main

## useful
## change active domain 

# domain list 
# domain active []

##list of all os 

#repo -os 




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
#	source {../../tcl_scripts/vitis_create_vars.tcl}
#
# XSCT Programming Reference
# https://www.xilinx.com/html_docs/xilinx2020_1/vitis_doc/
###########################################################################


set WS_PATH [getws]
cd $WS_PATH
cd ..
set FOLDER_PATH [pwd]
cd $WS_PATH

set FOLDER_PATH [pwd]
cd $WS_PATH

set VITIS_PATH $::env(XILINX_VITIS)
cd $VITIS_PATH

set PLATFORM_NAME 	UltraZohm
set XSA_FOLDER 	[file join $FOLDER_PATH vivado_exported_xsa]
set EXPORT_FOLDER [file join $FOLDER_PATH software]
set SHARED_FOLDER [file join $EXPORT_FOLDER shared]


set filename_Baremetal [file join $EXPORT_FOLDER Baremetal/src]
set filename_FreeRTOS  [file join $EXPORT_FOLDER FreeRTOS]
set filename_FSBL      [file join $EXPORT_FOLDER FSBL]
set filename_FSBLelf   [file join $EXPORT_FOLDER BootImage]


set filename_meta [file join $WS_PATH .metadata]
set filename_plugins [file join $filename_meta .plugins]
set filename_eclipse [file join $filename_plugins org.eclipse.debug.core]
set filename_launches [file join $filename_eclipse .launches]

set DebugBaremetal [file join $EXPORT_FOLDER DebugBaremetal.launch]
set DebugAll [file join $EXPORT_FOLDER Debug_FreeRTOS_Baremetal_FPGA.launch]

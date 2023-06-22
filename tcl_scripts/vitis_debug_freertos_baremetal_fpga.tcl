# TCL Debug scrip for FreeRTOS and BareMetal
#
#Created by Eyke Aufderheide, Dennis Hufnagel 
#
cd [getws]
set PATH_TCL  ../../tcl_scripts
set PROGRAM_FILE [file join $PATH_TCL vitis_program_freertos_baremetal_fpga.tcl]
source $PROGRAM_FILE

uz_program
uz_enable_debug_mode
uz_connect


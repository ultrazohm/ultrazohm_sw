# TCL Debug script for FreeRTOS and BareMetal
# Created by Eyke Aufderheide, Dennis Hufnagel 
# Wrapper for vitis_debug_run_UltraZohm.tcl

set UZ_PROGRAMMING_MODE "DEBUG"  

cd [getws]
source {../../tcl_scripts/vitis_debug_run_UltraZohm.tcl}
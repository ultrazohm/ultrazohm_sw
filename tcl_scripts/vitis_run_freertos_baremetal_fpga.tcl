# TCL Run script for FreeRTOS and BareMetal
# Created by Eyke Aufderheide, Dennis Hufnagel 
# Wrapper for vitis_debug_run_UltraZohm.tcl


# check if UZ was run in DEBUG mode prior to this call
if {[info exists ::UZ_PROGRAMMING_MODE]} {

   if {$UZ_PROGRAMMING_MODE eq "DEBUG"} {
    # catch {bpremove -all}
    # catch {bpdisable -all}
    puts "\n\n======================================================================================================="
    puts "INFO: UZ was run in DEBUG mode prior, try restarting Vitis or terminate hw_server via e.g. Task Manager."
    puts "=======================================================================================================\n\n"
    }
}

set UZ_PROGRAMMING_MODE "RUN" 

cd [getws]
source {../../tcl_scripts/vitis_debug_run_UltraZohm.tcl}
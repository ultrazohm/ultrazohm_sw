# TCL Debug script for FreeRTOS and BareMetal
#Created by Eyke Aufderheide, Dennis Hufnagel 
# call via source {../../tcl_scripts/vitis_debug_run_UltraZohm.tcl}
#
# --- config ---
set BIT_DIR "UltraZohm/hw"          ;# adjust as needed
set XSA_DIR "UltraZohm/hw"          ;# adjust as needed

set VITIS_PATH $::env(XILINX_VITIS)
set VITIS_UTIL_PATH [file join $VITIS_PATH scripts/vitis/util]
set PATH_zynqmp_utils [file join $VITIS_UTIL_PATH zynqmp_utils.tcl]
set PATH_fsbl [file join $VITIS_UTIL_PATH fsbl.tcl]


# Core helper: return the single file matching 'pattern' in 'dir'; error if 0 or >1.
proc _find_one {dir pattern} {
    set dir [file normalize $dir]
    if {![file isdirectory $dir]} { error "Directory not found: $dir" }
    set matches [glob -nocomplain -directory $dir -- $pattern]
    set n [llength $matches]
    if {$n != 1} { error "Expected exactly one $pattern in $dir, found $n: $matches" }
    return [list [file normalize [lindex $matches 0]]]  ;# safe even if path has spaces
}

# Thin wrappers for readability
proc bitstream {dir} { _find_one $dir "*.bit" }
proc xsa       {dir} { _find_one $dir "*.xsa" }

puts "\n\n====================================================="
puts "INFO: UZ_PROGRAMMING_MODE = $UZ_PROGRAMMING_MODE"
puts "=====================================================\n\n"
#####################################################
cd [getws]
connect -url tcp:127.0.0.1:3121
puts "INFO: Connected to target on host '127.0.0.1' and port '3121'."
#####################################################
source $PATH_zynqmp_utils 
puts "INFO: sourcing of '$PATH_zynqmp_utils ' is done."
#####################################################
targets -set -nocase -filter {name =~"APU*"}
puts "INFO: Context for 'APU' is selected."
#####################################################
rst -system
puts "INFO: System reset is completed."
#####################################################
after 3000
targets -set -nocase -filter {name =~"RPU*"}
puts "INFO: Context for 'RPU' is selected."
#####################################################
enable_split_mode
puts "INFO: Split mode is enabled for R5#1."
#####################################################
target 1 
set BIT_FILE [lindex [bitstream $BIT_DIR] 0]
fpga -file $BIT_FILE
puts "INFO: Device configured successfully with $BIT_FILE."
#####################################################
targets -set -nocase -filter {name =~"APU*"}
puts "INFO: Context for 'APU' is selected."
#####################################################
set XSA_FILE [lindex [xsa $XSA_DIR] 0]
# catch {loadhw -hw $XSA_FILE -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs}
catch {loadhw -hw $XSA_FILE}
puts "INFO: Hardware design and registers information is loaded from $XSA_FILE."
#####################################################
configparams force-mem-access 1
puts "INFO: 'configparams force-mem-access 1' command is executed."
#####################################################
targets -set -nocase -filter {name =~"APU*"}
puts "INFO: Context for 'APU' is selected."
#####################################################
source UltraZohm/hw/psu_init.tcl
puts "INFO: sourcing of 'workspace/UltraZohm/hw/psu_init.tcl' is done."
#####################################################
psu_init
puts "INFO:'psu_init' command is executed."
#####################################################
source $PATH_fsbl 
puts "INFO: sourcing of '$PATH_fsbl' is done."
#####################################################
after 1000
psu_ps_pl_isolation_removal
puts "INFO: 'psu_ps_pl_isolation_removal' command is executed."
#####################################################
after 1000
psu_ps_pl_reset_config
puts "INFO: 'psu_ps_pl_reset_config' command is executed."
#####################################################
catch {psu_protection}
puts "INFO: 'catch {psu_protection}' command is executed."
#####################################################
targets -set -nocase -filter {name =~ "*A53*#0"}
puts "INFO: Context for processor 'psu_cortexa53_0' is selected."
#####################################################
rst -processor
puts "INFO: Processor reset is completed for 'psu_cortexa53_0'."
#####################################################
dow FreeRTOS/Debug/FreeRTOS.elf
puts "INFO: The application 'workspace/FreeRTOS/Debug/FreeRTOS.elf' is downloaded to processor 'psu_cortexa53_0'."
#####################################################
targets -set -nocase -filter {name =~ "*R5*#0"}
puts "INFO: Context for processor 'psu_cortexr5_0' is selected."
#####################################################
rst -processor
puts "INFO: Processor reset is completed for 'psu_cortexr5_0'."
#####################################################
catch {XFsbl_TcmEccInit R5_0}
puts "INFO: 'catch {XFsbl_TcmEccInit}' command is executed."
#####################################################
dow Baremetal/Debug/Baremetal.elf
puts "INFO: The application 'workspace/Baremetal/Debug/Baremetal.elf' is downloaded to processor 'psu_cortexr5_0'."
#####################################################
configparams force-mem-access 0
puts "INFO: 'configparams force-mem-access 0' command is executed."
#####################################################
# differentiate between DEBUG and RUN mode
# however: real RUN mode, where breakpoints set in Eclipse GUI are ignored, is not possible with this script
catch {bpremove -all}

if {$UZ_PROGRAMMING_MODE eq "DEBUG"} {
    puts "\n\n==========================================================="
    bpadd -addr &main -enable 0
    puts "INFO: DEBUG mode: added disabled breakpoint at main entry." ; 
    puts "===========================================================\n\n"
} elseif {$UZ_PROGRAMMING_MODE eq "RUN"} {
    catch {bpdisable -all}
    puts "\n\n====================================================================================="
    puts "INFO: RUN mode: new breakpoints are NOT ignored, disable all BPs by pressing CTRL+ALT+B"
    puts "=====================================================================================\n\n"
} else {
    error "Unknown UZ_PROGRAMMING_MODE '$UZ_PROGRAMMING_MODE' (use RUN or DEBUG)."
}
#####################################################
targets -set -nocase -filter {name =~ "*A53*#0"}
con
puts "INFO: connected to 'psu_cortexa53_0'."
#####################################################
targets -set -nocase -filter {name =~ "*R5*#0"}
con
puts "INFO: connected to 'psu_cortexr5_0'."
#####################################################

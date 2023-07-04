# TCL Debug scrip for FreeRTOS and BareMetal
#
#Created by Eyke Aufderheide, Dennis Hufnagel 
set VITIS_PATH $::env(XILINX_VITIS)
set VITIS_UTIL_PATH [file join $VITIS_PATH scripts/vitis/util]
set PATH_zynqmp_utils [file join $VITIS_UTIL_PATH zynqmp_utils.tcl]
set PATH_fsbl [file join $VITIS_UTIL_PATH fsbl.tcl]

set iswindows 0
if {$::tcl_platform(platform) == "windows"} {	   
    set iswindows 1
} else {	   
    set iswindows 0
}
cd [getws]
connect -url tcp:127.0.0.1:3121
puts "INFO: Connected to target on host '127.0.0.1' and port '3121'."
source $PATH_zynqmp_utils 
puts "INFO: sourcing of '$PATH_zynqmp_utils ' is done."
targets -set -nocase -filter {name =~"APU*"}
puts "INFO: Context for 'APU' is selected."
rst -system
puts "INFO: System reset is completed."
after 3000
targets -set -nocase -filter {name =~"RPU*"}
puts "INFO: Context for 'RPU' is selected."
enable_split_mode
puts "INFO: Split mode is enabled for R5#1."
target 1 
fpga -file FreeRTOS/_ide/bitstream/zusys_wrapper.bit
puts "INFO: Device configured successfully with 'workspace/FreeRTOS/_ide/bitstream/zusys_wrapper.bit'."
targets -set -nocase -filter {name =~"APU*"}
puts "INFO: Context for 'APU' is selected."
catch {loadhw -hw UltraZohm/export/UltraZohm/hw/zusys_wrapper.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs}
puts "INFO: Hardware design and registers information is loaded from 'workspace/UltraZohm/export/UltraZohm/zusys_wrapper.xsa'."
configparams force-mem-access 1
puts "INFO: 'configparams force-mem-access 1' command is executed."
targets -set -nocase -filter {name =~"APU*"}
puts "INFO: Context for 'APU' is selected."
source FreeRTOS/_ide/psinit/psu_init.tcl
puts "INFO: sourcing of 'workspace/FreeRTOS/_ide/psinit/psu_init.tcl' is done."
psu_init
puts "INFO:'psu_init' command is executed."
source $PATH_fsbl 
puts "INFO: sourcing of '$PATH_fsbl' is done."
after 1000
psu_ps_pl_isolation_removal
puts "INFO: 'psu_ps_pl_isolation_removal' command is executed."
after 1000
psu_ps_pl_reset_config
puts "INFO: 'psu_ps_pl_reset_config' command is executed."
catch {psu_protection}
puts "INFO: 'catch {psu_protection}' command is executed."
targets -set -nocase -filter {name =~ "*A53*#0"}
puts "INFO: Context for processor 'psu_cortexa53_0' is selected."
rst -processor
puts "INFO: Processor reset is completed for 'psu_cortexa53_0'."
dow FreeRTOS/Debug/FreeRTOS.elf
puts "INFO: The application 'workspace/FreeRTOS/Debug/FreeRTOS.elf' is downloaded to processor 'psu_cortexa53_0'."
targets -set -nocase -filter {name =~ "*R5*#0"}
puts "INFO: Context for processor 'psu_cortexr5_0' is selected."
rst -processor
puts "INFO: Processor reset is completed for 'psu_cortexr5_0'."
catch {XFsbl_TcmEccInit R5_0}
puts "INFO: 'catch {XFsbl_TcmEccInit}' command is executed."
dow Baremetal/Debug/Baremetal.elf
puts "INFO: The application 'workspace/Baremetal/Debug/Baremetal.elf' is downloaded to processor 'psu_cortexr5_0'."
configparams force-mem-access 0
puts "INFO: 'configparams force-mem-access 0' command is executed."
targets -set -nocase -filter {name =~ "*A53*#0"}
con
puts "INFO: connected to 'psu_cortexa53_0'."
targets -set -nocase -filter {name =~ "*R5*#0"}
con
puts "INFO: connected to 'psu_cortexr5_0'."

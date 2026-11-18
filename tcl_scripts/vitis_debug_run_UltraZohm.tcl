# TCL Debug script for FreeRTOS and BareMetal
#Created by Eyke Aufderheide, Dennis Hufnagel 
# call via source {../../tcl_scripts/vitis_debug_run_UltraZohm.tcl}
#
# --- config ---
set BIT_DIR "UltraZohm/hw"          ;# adjust as needed
set XSA_DIR "UltraZohm/hw"          ;# adjust as needed

set ::uz_vitis_script_dir [file dirname [file normalize [info script]]]

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

# Which bitstream the FPGA holds: Vivado writes the build time into the
# USR_ACCESS register of the bitstream (BITSTREAM.CONFIG.USR_ACCESS TIMESTAMP,
# see vivado/constraints/te0808/_i_bitgen.xdc). The value from the .bit file is
# compared with the one read from the FPGA over JTAG.

# USR_ACCESS value in a .bit file, or "" if it has none.
proc uz_bitfile_usr_access {bit_file} {
    set fp [open $bit_file r]
    fconfigure $fp -translation binary
    set data [read $fp 4096]   ;# the configuration header comes first
    close $fp
    # Type 1 packet "write 1 word to AXSS" (= USR_ACCESS), followed by the value.
    set idx [string first [binary format I 0x3001A001] $data]
    # Only in the configuration header, i.e. before the frame data (FDRI write).
    set fdri [string first [binary format I 0x30004000] $data]
    if {$idx < 0 || ($fdri >= 0 && $fdri < $idx) ||
        [binary scan $data @[expr {$idx + 4}]Iu value] != 1} {
        return ""
    }
    return $value
}

# USR_ACCESS value of the FPGA, read over JTAG. Errors if it cannot be read.
proc uz_fpga_usr_access {} {
    set nodes {}
    foreach t [jtag targets -target-properties] {
        # The FPGA itself, not the debug cores (bscan-switch, debug-hub) behind it.
        if {[dict exists $t is_fpga] && [dict get $t is_fpga]
            && [dict get $t level] == 1} {
            lappend nodes [dict get $t target_ctx]
        }
    }
    if {[llength $nodes] != 1} {
        error "expected one FPGA in the JTAG chain, found [llength $nodes]"
    }
    # The same hw_server request that 'fpga -cor0-status' uses for COR0; XSCT
    # has no option for USR_ACCESS.
    set node [lindex $nodes 0]
    set reply [tcf send_command [::xsdb::getcurchan] Xicom_v1.00 getUserAccess s * [list $node]]
    # Reply: error, number of bits, value, field names.
    if {[lindex $reply 0] ne ""} {
        error [lindex $reply 0]
    }
    set value [lindex $reply 2]
    if {[llength $reply] < 3 || ![string is wideinteger -strict $value]} {
        error "unexpected reply: $reply"
    }
    return [expr {$value & 0xFFFFFFFF}]
}

# Build time stored in a USR_ACCESS value.
# Bits: day 31..27, month 26..23, year-2000 22..17, hour 16..12, minute 11..6, second 5..0
proc uz_usr_access_time {value} {
    return [format "%04d-%02d-%02d %02d:%02d:%02d" \
        [expr {2000 + (($value >> 17) & 0x3F)}] [expr {($value >> 23) & 0xF}] \
        [expr {($value >> 27) & 0x1F}] [expr {($value >> 12) & 0x1F}] \
        [expr {($value >> 6) & 0x3F}] [expr {$value & 0x3F}]]
}

# "" if the FPGA holds the bitstream 'bit_file', otherwise why not (or why
# this cannot be confirmed).
proc uz_fpga_holds_bitstream {bit_file} {
    set state [fpga -state]
    if {![string match "*FPGA is configured*" $state]} {
        return $state
    }
    set expected [uz_bitfile_usr_access $bit_file]
    if {$expected eq ""} {
        return "[file tail $bit_file] has no USR_ACCESS build time,\
            cannot tell which bitstream the FPGA holds"
    }
    if {[catch {uz_fpga_usr_access} actual]} {
        return "cannot read USR_ACCESS of the FPGA ($actual)"
    }
    if {$actual != $expected} {
        return "the FPGA holds a bitstream built [uz_usr_access_time $actual],\
            [file tail $bit_file] was built [uz_usr_access_time $expected]"
    }
    return ""
}


puts "\n\n====================================================="
puts "INFO: UZ_PROGRAMMING_MODE = $UZ_PROGRAMMING_MODE"
puts "=====================================================\n\n"
#####################################################
cd [getws]
# Refuse to program a FreeRTOS.elf whose kernel lacks portMEMORY_BARRIER (the
# A53 freezes under load). Runs before the board is touched.
source [file join $::uz_vitis_script_dir vitis_patch_UltraZohm_freertos_bsp.tcl]
uz_vitis_check_freertos_elf [getws] [file join [getws] FreeRTOS Debug FreeRTOS.elf]
#####################################################
connect -url tcp:127.0.0.1:3121
puts "INFO: Connected to target on host '127.0.0.1' and port '3121'."
#####################################################
# default if not set elsewhere
if {![info exists UZ_FPGA_FAST_RESTART_ACTIVATED]} {
    set UZ_FPGA_FAST_RESTART_ACTIVATED 0
}
#####################################################
set UZ_FPGA_FAST_RESTART 0   ;# full PS/PL init + FPGA reprogram
if {$UZ_FPGA_FAST_RESTART_ACTIVATED == 1} {
    # Skip the programming only if the FPGA holds the bitstream of this launch.
    if {[catch {uz_fpga_holds_bitstream [lindex [bitstream $BIT_DIR] 0]} UZ_FPGA_MISMATCH]} {
        set UZ_FPGA_MISMATCH "cannot compare the bitstreams ($UZ_FPGA_MISMATCH)"
    }
    if {$UZ_FPGA_MISMATCH eq ""} {
        puts "INFO: FPGA holds the bitstream of $BIT_DIR and fast restart activated,\
            skipping FPGA programming."
        set UZ_FPGA_FAST_RESTART 1   ;# skip rst/bitstream/psu_init
    } else {
        puts "INFO: Fast restart activated, but $UZ_FPGA_MISMATCH: run full reset of UZ."
    }
} else {
    puts "INFO: [fpga -state], run full reset of UZ."
}
#####################################################
source UltraZohm/hw/psu_init.tcl
source $PATH_zynqmp_utils 
source $PATH_fsbl 
puts "INFO: sourcing of 'workspace/UltraZohm/hw/psu_init.tcl' , '$PATH_zynqmp_utils', and '$PATH_fsbl' is done."
#####################################################
if {$UZ_FPGA_FAST_RESTART == 0} {
    puts "INFO: Full FPGA reprogramming and PS init selected."
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
    # set XSA_FILE [lindex [xsa $XSA_DIR] 0]
    # catch {loadhw -hw $XSA_FILE}
    #puts "INFO: Hardware design and registers information is loaded from $XSA_FILE."
    #####################################################
    configparams force-mem-access 1
    puts "INFO: 'configparams force-mem-access 1' command is executed."
    #####################################################
    targets -set -nocase -filter {name =~"APU*"}
    puts "INFO: Context for 'APU' is selected."
    #####################################################
    psu_init
    puts "INFO:'psu_init' command is executed."
    #####################################################
    after 1000
    psu_ps_pl_isolation_removal
    puts "INFO: 'psu_ps_pl_isolation_removal' command is executed."
    #####################################################
    after 1000 
} else {
    #####################################################
    # # stop axi2tcm 
    # targets -set -nocase -filter {name =~ "*R5*#0"}
    # configparams force-mem-access 1
    # catch {mwr 0x00800F0000 0x0}
    # # todo: stop all interrupts by disabeling their source (in PL) -> tricky in general way via tcl
    #####################################################
    puts "INFO: Fast restart selected: skip FPGA reprogramming and PS init."
    # Stop R5_0
    targets -set -nocase -filter {name =~ "*R5*#0"}
    set return_code_R5  [catch {stop} errMsg_R5]

    # Stop A53_0
    targets -set -nocase -filter {name =~ "*A53*#0"}
    set return_code_A53 [catch {stop} errMsg_A53]

    # error handling - stop throws an error if the core is already stopped
    if { ( $return_code_R5  == 0 || [string match "*Already stopped*" $errMsg_R5] ) &&
        ( $return_code_A53 == 0 || [string match "*Already stopped*" $errMsg_A53] ) } {
        puts "INFO: Stopped processors R5:0 and A53:0."
    } else {
        # Print specific errors for each core if any
        if { $return_code_R5 != 0 && ![string match "*Already stopped*" $errMsg_R5] } {
            puts "ERROR: 'stop' failed on R5_0: $errMsg_R5"
        }
        if { $return_code_A53 != 0 && ![string match "*Already stopped*" $errMsg_A53] } {
            puts "ERROR: 'stop' failed on A53_0: $errMsg_A53"
        }
        error "Stopping one or more processors failed, see log above."
    }
}
#####################################################
set return_code_PL_reset [catch {psu_ps_pl_reset_config} errMsg_PL_reset]

if {$return_code_PL_reset != 0} {
    error "ERROR: psu_ps_pl_reset_config failed (return_code_PL_reset=$return_code_PL_reset): $errMsg_PL_reset"
} else {
    puts "INFO: PL Reset via 'psu_ps_pl_reset_config' successfully."
}
after 1000 
#####################################################
catch {psu_protection}
puts "INFO: 'catch {psu_protection}' command is executed."
#####################################################
targets -set -nocase -filter {name =~ "*A53*#0"}
puts "INFO: Context for processor 'psu_cortexa53_0' is selected."
#####################################################
rst -processor -clear-registers
puts "INFO: Processor reset is completed for 'psu_cortexa53_0'."
#####################################################
dow FreeRTOS/Debug/FreeRTOS.elf
con
puts "INFO: The application 'workspace/FreeRTOS/Debug/FreeRTOS.elf' is downloaded to processor 'psu_cortexa53_0' and started running."
#####################################################
targets -set -nocase -filter {name =~ "*R5*#0"}
puts "INFO: Context for processor 'psu_cortexr5_0' is selected."
#####################################################
# Reset R5 core(s) and clear registers (recommended after power-on / to avoid bootloop warnings)
if {$UZ_FPGA_FAST_RESTART == 1} {
    rst -processor -clear-registers
} else {
    rst -processor
}
puts "INFO: Processor reset is completed for 'psu_cortexr5_0'."
#####################################################
catch {XFsbl_TcmEccInit R5_0}
puts "INFO: 'catch {XFsbl_TcmEccInit}' command is executed."
#####################################################
dow Baremetal/Debug/Baremetal.elf
puts "INFO: The application 'workspace/Baremetal/Debug/Baremetal.elf' is downloaded to processor 'psu_cortexr5_0'."
#####################################################
# configparams force-mem-access 0
# puts "INFO: 'configparams force-mem-access 0' command is executed."
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
# targets -set -nocase -filter {name =~ "*A53*#0"}
# # bpadd -addr &main -enable 1
# con
# puts "INFO: connected to 'psu_cortexa53_0'."
#####################################################
# targets -set -nocase -filter {name =~ "*R5*#0"}
con
puts "INFO: R5 started running."
#####################################################

puts "\n\n========================================================"
puts "INFO: UltraZohm successfully programmed and running."
puts "========================================================\n\n"
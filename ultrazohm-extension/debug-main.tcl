# Extension-owned wrapper. Source the CLI's original Tcl without editing/copying it.
# Intercept only the first con following the two application downloads. Boot/FSBL
# commands retain their original behavior. Fail closed if a future script changes.
namespace eval ::uz_debug {
    variable pending ""
    variable stopped {}
}
rename ::dow ::uz_debug::original_dow
rename ::con ::uz_debug::original_con
rename ::exit ::uz_debug::original_exit
proc ::dow {args} {
    set result [uplevel 1 [list ::uz_debug::original_dow {*}$args]]
    set file [file tail [lindex $args end]]
    if {$file in {FreeRTOS.elf Baremetal.elf}} {
        if {$::uz_debug::pending ne "" || $file in $::uz_debug::stopped} {
            error "Unexpected application download sequence; Debug cancelled"
        }
        set ::uz_debug::pending $file
    }
    return $result
}
proc ::con {args} {
    if {$::uz_debug::pending eq ""} {
        return [uplevel 1 [list ::uz_debug::original_con {*}$args]]
    }
    if {[llength $args]} { error "Unexpected application resume arguments; Debug cancelled" }
    set file $::uz_debug::pending
    set ::uz_debug::pending ""
    set bp [bpadd -addr &main -type hw]
    # Vitis 2022.2 uses Tcl 8.5, which has no try/finally command.
    set code [catch {
        ::uz_debug::original_con -block -timeout 30
        set at_main [dict values [print -dict {((unsigned long)$pc & ~1) == ((unsigned long)&main & ~1)}]]
        if {[llength $at_main] != 1 || [lindex $at_main 0] ni {1 true}} {
            error "$file stopped outside main; Debug cancelled"
        }
    } message options]
    if {$code != 0} { catch {stop} }
    # Always remove our temporary breakpoint. Preserve the original resume/PC
    # failure if cleanup also fails, and do not confirm a stop after either error.
    set cleanup_code [catch {bpremove $bp} cleanup_message cleanup_options]
    if {$code != 0} { return -options $options $message }
    if {$cleanup_code != 0} { return -options $cleanup_options $cleanup_message }
    lappend ::uz_debug::stopped $file
    puts "UltraZohm Debug: $file stopped at main; waiting for VS Code."
}
proc ::exit {{code 0}} {
    if {$code == 0} {
        if {[lsort $::uz_debug::stopped] ne {Baremetal.elf FreeRTOS.elf} || $::uz_debug::pending ne ""} {
            puts stderr "Debug did not stop both applications at main"
            set code 1
        } else {
            set stream [open $::env(UZ_DEBUG_PROOF) w]
            puts $stream $::env(UZ_DEBUG_REQUEST)
            close $stream
        }
    }
    ::uz_debug::original_exit $code
}
source $::env(UZ_DEBUG_ENTRY)
exit 0

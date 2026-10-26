# A fresh Vitis 2022.2 batch session rebuilds platform dependencies even when
# unchanged. Reuse its generated Makefiles while the workspace inputs match.
# Make still checks C/header dependencies on every invocation; this is not an
# ELF cache. File metadata has the same timestamp semantics as Make itself.
proc uz_build_files {directory} {
    set result {}
    foreach path [lsort [glob -nocomplain -directory $directory * .*]] {
        if {[file tail $path] in {. .. .git logs}} { continue }
        if {[file isdirectory $path]} {
            lappend result {*}[uz_build_files $path]
        } elseif {[file isfile $path] && [file extension $path] ne ".log"} {
            lappend result $path
        }
    }
    return $result
}

proc uz_build_signature {workspace script_dir} {
    set signature [list version 1 toolchain $::env(XILINX_VITIS)]
    # Include platform inputs AND outputs: missing BSP headers/libraries must
    # return to Vitis, as must hardware or BSP configuration edits.
    set metadata [uz_build_files [file join $workspace UltraZohm]]
    foreach application {Baremetal FreeRTOS} {
        foreach name {.project .cproject} {
            lappend metadata [file join $workspace $application $name]
        }
        lappend metadata {*}[glob -nocomplain [file join $workspace $application *.prj]]
        foreach path [uz_build_files [file join $workspace $application Debug]] {
            if {[file tail $path] eq "makefile" || [file extension $path] eq ".mk"} {
                lappend metadata $path
            }
        }
    }
    lappend metadata [file join $script_dir vitis_headless.tcl] [file join $script_dir vitis_incremental.tcl]
    foreach path [lsort -unique $metadata] {
        if {[file isfile $path]} {
            lappend signature [list $path [file size $path] [file mtime $path]]
        } else {
            lappend signature [list $path missing]
        }
    }
    # New/deleted source files require CDT to regenerate its source lists.
    # Contents and timestamps are handled by the generated Make dependencies.
    lappend signature sources [uz_build_files [file join $workspace ../software]]
    return $signature
}

proc uz_can_make {workspace signature stamp} {
    foreach application {Baremetal FreeRTOS} {
        if {![file isfile [file join $workspace $application Debug makefile]]} { return 0 }
    }
    if {![file isfile $stamp]} { return 0 }
    set stream [open $stamp r]
    set previous [read $stream]
    close $stream
    return [string equal $signature $previous]
}

proc uz_save_build_signature {stamp signature} {
    set stream [open ${stamp}.tmp w]
    puts -nonewline $stream $signature
    close $stream
    file rename -force ${stamp}.tmp $stamp
}

# Make -q uses the same dependencies as the actual build without running recipes.
# Exit 1 means work is pending; all other failures must stop build/flash.
proc uz_make_needs_build {directory} {
    if {[catch {exec make -q -C $directory all 2>@stderr} message options]} {
        set code [dict get $options -errorcode]
        if {[lindex $code 0] eq "CHILDSTATUS" && [lindex $code 2] == 1} {
            return 1
        }
        return -options $options $message
    }
    return 0
}

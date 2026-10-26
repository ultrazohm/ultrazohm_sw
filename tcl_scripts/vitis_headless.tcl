# Batch entry point for Vitis 2022.2. Pass arguments as argv, not Tcl source text.
set script_dir [file dirname [file normalize [info script]]]
set workspace [file normalize [file join $script_dir ../vitis/workspace]]

# Keep this at global scope: the existing launch wrappers use global variables.
if {[catch {
    set action [lindex $argv 0]
    if {$action ni {build run flash generate generate-open open}} {
        error "Usage: xsct -nodisp vitis_headless.tcl {generate|generate-open|open|build|flash|run} ?Run_UltraZohm?"
    }
    if {$action eq "flash"} { set action run }
    set profile Run_UltraZohm
    if {$action eq "run"} {
        if {[llength $argv] > 2} { error "Expected run or flash with at most one profile" }
        if {[llength $argv] == 2} { set profile [lindex $argv 1] }
        if {$profile ne "Run_UltraZohm"} {
            error "Unsupported headless profile: $profile. Use Vitis for Debug profiles."
        }
    } elseif {[llength $argv] != 1} {
        error "Unexpected arguments for $action"
    }

    # Resolve the GUI before generating anything. auto_execok also handles the
    # Windows batch launcher; expanding a Tcl list preserves paths with spaces.
    if {$action in {open generate-open}} {
        set vitis_launcher [auto_execok vitis]
        if {$vitis_launcher eq ""} { error "vitis not found on PATH" }
    }
    if {$action in {generate generate-open}} {
        # Check before setws: XSCT itself may populate workspace metadata.
        file mkdir $workspace
        foreach path [glob -nocomplain -directory $workspace * .*] {
            set name [file tail $path]
            if {$name in {. ..}} { continue }
            if {$name eq "create_Vitis_workspace_here.txt" && [file isfile $path]} { continue }
            error "Workspace is not empty: $path. Use an empty workspace for generation."
        }
    } elseif {$action eq "open"} {
        if {![file isdirectory $workspace]} { error "Workspace folder not found: $workspace" }
    } else {
        foreach project {UltraZohm Baremetal FreeRTOS} {
            if {![file isdirectory [file join $workspace $project]]} {
                error "Missing project $project. Run the generate action first."
            }
        }
    }
    if {$action ne "open"} { setws $workspace }
    cd $workspace
    # Every programming entry point builds first, including direct XSCT calls.
    # Vitis/make track changed sources and headers; do not clean here.
    if {$action in {build run}} {
        # Launch scripts load Debug/*.elf even in RUN mode.
        foreach application {Baremetal FreeRTOS} {
            app config -name $application build-config Debug
        }
        platform active UltraZohm
        platform generate
        app build -all
        sysproj build -all
        foreach application {Baremetal FreeRTOS} {
            set elf [file join $workspace $application Debug ${application}.elf]
            if {![file isfile $elf]} { error "Build did not produce $elf" }
        }
        puts "UltraZohm platform, applications, and system projects built successfully."
    }
    switch -- $action {
        generate - generate-open {
            source [file join $script_dir vitis_generate_UltraZohm_workspace.tcl]
        }
        run {
            # Use the same wrapper as the corresponding checked-in .launch file.
            # Add future debug profiles here together with debugger session handling.
            switch -- $profile {
                Run_UltraZohm { set launch_script vitis_run_freertos_baremetal_fpga.tcl }
                default { error "Unsupported headless profile: $profile" }
            }
            # Fail before connecting/resetting hardware if build artifacts are missing.
            foreach relative_path {
                Baremetal/Debug/Baremetal.elf FreeRTOS/Debug/FreeRTOS.elf
                UltraZohm/hw/psu_init.tcl
            } {
                if {![file isfile $relative_path]} { error "Missing $relative_path. Build the workspace first." }
            }
            if {[llength [glob -nocomplain UltraZohm/hw/*.bit]] != 1} {
                error "Expected exactly one bitstream in UltraZohm/hw."
            }
            if {![info exists ::env(XILINX_VITIS)]} { error "XILINX_VITIS is not set." }
            foreach utility {zynqmp_utils.tcl fsbl.tcl} {
                set path [file join $::env(XILINX_VITIS) scripts/vitis/util $utility]
                if {![file isfile $path]} { error "Missing Vitis utility: $path" }
            }
            source [file join $script_dir $launch_script]
            disconnect
        }
    }
    if {$action in {open generate-open}} {
        puts "Opening Vitis workspace: $workspace"
        # Return and release XSCT's workspace before the GUI uses it.
        exec {*}$vitis_launcher -workspace $workspace >@stdout 2>@stderr &
    }
} message options]} {
    puts stderr "ERROR: $message"
    puts stderr [dict get $options -errorinfo]
    exit 1
}
exit 0

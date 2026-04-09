# Run this script to auto-generate and adapt the build.tcl and zusys.tcl scripts necessary to create the
# project and block diagram from scratch
# Obs.: run it inside Vivado with the ultrazohm project opened
#
# source update_tcl_scripts_for_vc.tcl
#

# Change current folder to [repo folder]/vivado
cd [get_property DIRECTORY [current_project]]/../

# call write_project_tcl to get basic 
write_project_tcl -no_copy_sources -use_bd_files -force _build.tcl

# open bd_design and call write_bd_tcl
open_bd_design {./project/zusys/zusys.bd}
write_bd_tcl -force ./bd/_zusys.tcl


# Find Python installation von Vivado
if {$::tcl_platform(platform) eq "windows"} {
  # Windows: assume Vivado sets RDI_PYTHON3 and it points to python.exe
  set py_exe [file join $::env(RDI_PYTHON3) python]
} else {
  # Unix: assume PYTHONHOME points to .../python-3.8.3 and executable is in bin/
  set py_exe [file join $::env(PYTHONHOME) bin python]
  if {![file exists $py_exe]} {
    # Some installs may ship "python3" instead of "python"
    set py_exe [file join $::env(PYTHONHOME) bin python3]
  }
}

# Sanity check if Python works
if {[string length $py_exe] == 0} {
  error "Pointer 'py_exe' to Python executable is empty"
}
puts "Checking Python executable: $py_exe"
set python_check [catch {exec -- $py_exe --version 2>@1} msg]
if {$python_check} {
    puts stderr "Python check failed: $msg"
} else {
    puts "Python OK: $msg"
}

# For some reason, the line
# "set_property -name "board_part" -value "trenz.biz:te0808_9eg_1e:part0:3.0" -objects $obj" (line 131)
# of _build.tcl is before the line:
# set_property -name "board_part_repo_paths" -value "[file normalize "$origin_dir/board_files"]" -objects $obj (line 132)
# leading the errors when rebuilding the project.
# Thus, if the vivado version is 2020.1 or 2020.1.1, the lines are swapped.
set vivado_version [version -short]
if {$vivado_version == "2020.1" || $vivado_version == "2020.1.1"} {
	exec $py_exe swap_board_part_line.py
 	puts "Swaps board part line since 2020.1 or 2020.1.1 is used"
}

# run python script to modify the generated output and generate the build.tcl script
exec $py_exe modify_build_script.py

# run python script to modify the generated output and generate the zusys.tcl script
# inside this files is defined the board files path (later we should pass it as argument)
exec $py_exe modify_bd_script.py

puts "Info: update_tcl_scripts_for_vc.tcl completed successfully."

# Further info:
# To fix Python environment conflicts (AMD guidance): temporarily unset PYTHONHOME/PYTHONPATH,
# run Python, then restore both env vars to their initial values. 
# https://support.xilinx.com/s/article/72570?language=en_US

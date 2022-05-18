# Run this script to auto-generate and adapt the build.tcl and zusys.tcl scripts necessary to create the
# project and block diagram from scratch
# Obs.: run it inside Vivado with the ultrazohm project opened

# Change current folder to [repo folder]/vivado
cd [get_property DIRECTORY [current_project]]/../

# call write_project_tcl to get basic 
write_project_tcl -no_copy_sources -use_bd_files -force _build.tcl

# open bd_design and call write_bd_tcl
open_bd_design {./project/zusys/zusys.bd}
write_bd_tcl -force ./bd/_zusys.tcl

# fix python error 
# https://support.xilinx.com/s/article/72570?language=en_US
# On second run, unset returns an error since the env variables are already unset -> ignore the error with catch
catch {unset ::env(PYTHONPATH)}
catch {unset ::env(PYTHONHOME)}

# For some reason, the line
# "set_property -name "board_part" -value "trenz.biz:te0808_9eg_1e:part0:3.0" -objects $obj" (line 131)
# of _build.tcl is before the line:
# set_property -name "board_part_repo_paths" -value "[file normalize "$origin_dir/board_files"]" -objects $obj (line 132)
# leading the errors when rebuilding the project.
# Thus, if the vivado version is 2020.1 or 2020.1.1, the lines are swapped.
set vivado_version [version -short]
if {$vivado_version == "2020.1" || $vivado_version == "2020.1.1"} {
	if { [catch {exec python swap_board_part_line.py} result] } {
		exec python3 swap_board_part_line.py
		puts "Using python3 since python was not found"
	}
 	puts "Swaps board part line since 2020.1 or 2020.1.1 is used"
}

# run python script to modify the generated output and generate the build.tcl script
if { [catch {exec python modify_build_script.py} result] } {
	exec python3 modify_build_script.py
	puts "Using python3 since python was not found"
}
# run python script to modify the generated output and generate the zusys.tcl script
# inside this files is defined the board files path (later we should pass it as argument)
if { [catch {exec python modify_bd_script.py} result] } {
	exec python3 modify_bd_script.py
	puts "Using python3 since python was not found"
}

puts "Updated tcl scripts!"

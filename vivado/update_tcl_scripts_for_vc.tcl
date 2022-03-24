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
unset ::env(PYTHONPATH)
unset ::env(PYTHONHOME)
# run python script to modify the generated output and generate the build.tcl script
exec python3 modify_build_script.py

# run python script to modify the generated output and generate the zusys.tcl script
# inside this files is defined the board files path (later we should pass it as argument)
exec python3 modify_bd_script.py
puts "finished"

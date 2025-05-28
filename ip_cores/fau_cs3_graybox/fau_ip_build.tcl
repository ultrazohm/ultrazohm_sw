set script_dir "[file dirname "[file normalize "[info script]"]"]"

# cleanup previous mess if exists
close_project -quiet
file delete -force "$script_dir/build"

##################################
# General Project Settings
#

# create project
set proj_obj [create_project "graybox" "$script_dir/build"]
set_property "target_language" "VHDL" $proj_obj

# enable xmp libraries (for virtex ultrascale)
set_property "XPM_LIBRARIES" {XPM_CDC XPM_MEMORY XPM_FIFO} $proj_obj

##################################
# Design
#

add_files "board_design_graybox.vhd"

# set toplevel entity
set_property "top" "board_design_graybox" [get_filesets sources_1]
update_compile_order -fileset sources_1

##################################
# IP Creation
#

source "ip.tcl"

# add created ip library
set_property "ip_repo_paths" {"./build/"} $proj_obj
update_ip_catalog


# Creates the vitis workspace
# call on CLI
# xsct ci_generate_vitis_workspace.tcl
setws vitis/workspace
cd [getws]
source {../../tcl_scripts/vitis_generate_UltraZohm_workspace.tcl}

# Updates the platform for the vitis workspace
# call on CLI
# xsct ci_vitis_update_platform.tcl
setws ../vitis/workspace
cd [getws]
source {../../tcl_scripts/vitis_update_platform.tcl}

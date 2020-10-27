open_project ../vivado/project/ultrazohm.xpr
#vivado -source ../vivado/project/ultrazohm.xpr
set msg [check_syntax -fileset sim_1 -return_string]
set ret_val 0
 
if {$msg != ""} {
  set ret_val 1
}
 
puts $msg
exit $ret_val
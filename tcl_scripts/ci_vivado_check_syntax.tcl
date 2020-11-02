open_project vivado/project/ultrazohm.xpr

set return_msg [check_syntax -fileset sources_1 -return_string]
set error_flag 0
 
if {$return_msg != ""} {
  set error_flag 1
}
 
puts $return_msg
exit $error_flag

open_project ../vivado/project/ultrazohm.xpr

open_bd_design ../vivado/zusys/zusys.bd
set return_msg [validate_bd_design]
set error_flag 0
 
if {$return_msg != ""} {
  set error_flag 1
}
 
puts $return_msg
exit $error_flag

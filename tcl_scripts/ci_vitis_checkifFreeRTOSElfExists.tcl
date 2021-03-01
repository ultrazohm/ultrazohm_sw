setws vitis/workspace
cd [getws]
set status [file exists FreeRTOS/Debug/FreeRTOS.elf]
puts $status
# file exists -> status is 0 -> no error. otherwise error
if {$status != 1} {
 puts "Build failed, check log!"
 exit 1
}
# exit 0 means exit without error
exit 0

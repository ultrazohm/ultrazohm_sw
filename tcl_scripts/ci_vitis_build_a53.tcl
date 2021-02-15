# Build all projects
# call on CLI
# xsct ci_build_project.tcl
set status 0
setws vitis/workspace
cd [getws]
set APU_NAME FreeRTOS
app clean $APU_NAME
app build $APU_NAME
cd [getws]
set status [file exists FreeRTOS/Debug/FreeRTOS.elf] # returns 1 if file exists -> no error
puts $status
if {$status != 1} { # file exists -> status is 0 -> no error. otherwise error
 puts "Build failed, check log!"
 exit 1
}
exit 0 # exit 0 means exit without error



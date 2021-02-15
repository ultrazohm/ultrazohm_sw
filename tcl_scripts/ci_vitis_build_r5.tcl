# Build all projects
# call on CLI
# xsct ci_build_project.tcl
set status 0
setws vitis/workspace
cd [getws]
set RPU_NAME Baremetal
app clean $RPU_NAME
app build $RPU_NAME
cd [getws]
set status [file exists Baremetal/Debug/Baremetal.elf] # returns 1 if file exists -> no error
puts $status
# file exists -> status is 0 -> no error. otherwise error
if {$status != 1} {
 puts "Build failed, check log!"
 exit 1
}
# exit 0 means exit without error
exit 0

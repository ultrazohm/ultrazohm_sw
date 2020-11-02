# Build all projects
# call on CLI
# xsct ci_build_project.tcl
setws vitis/workspace
cd [getws]
set RPU_NAME Baremetal
set APU_NAME FreeRTOS
app clean $RPU_NAME
app build $RPU_NAME
app clean $APU_NAME
app build $APU_NAME
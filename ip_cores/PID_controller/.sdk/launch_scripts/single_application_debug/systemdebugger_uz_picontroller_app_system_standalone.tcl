connect -url tcp:127.0.0.1:3121
source C:/Xilinx/Vitis/2020.1/scripts/vitis/util/zynqmp_utils.tcl
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2NC 210308A7A62F" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT2NC-210308A7A62F-24738093-0"}
fpga -file C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_piController_app/_ide/bitstream/uz_piController.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_piController/export/uz_piController/hw/uz_piController.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
set mode [expr [mrd -value 0xFF5E0200] & 0xf]
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_piController/export/uz_piController/sw/uz_piController/boot/fsbl.elf
set bp_52_35_fsbl_bp [bpadd -addr &XFsbl_Exit]
con -block -timeout 60
bpremove $bp_52_35_fsbl_bp
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_piController_app/Debug/uz_piController_app.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A53*#0"}
con

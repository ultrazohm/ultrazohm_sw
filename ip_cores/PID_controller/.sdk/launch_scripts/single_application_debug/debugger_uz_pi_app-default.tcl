connect -url tcp:127.0.0.1:3121
source C:/Xilinx/Vitis/2020.1/scripts/vitis/util/zynqmp_utils.tcl
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2NC 210308AE62E5" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT2NC-210308AE62E5-24738093-0"}
fpga -file C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_pi_app/_ide/bitstream/uz_pi_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_pi_wrapper/export/uz_pi_wrapper/hw/uz_pi_wrapper.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
set mode [expr [mrd -value 0xFF5E0200] & 0xf]
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_pi_wrapper/export/uz_pi_wrapper/sw/uz_pi_wrapper/boot/fsbl.elf
set bp_17_47_fsbl_bp [bpadd -addr &XFsbl_Exit]
con -block -timeout 60
bpremove $bp_17_47_fsbl_bp
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/uz_pi_app/Debug/uz_pi_app.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A53*#0"}
con

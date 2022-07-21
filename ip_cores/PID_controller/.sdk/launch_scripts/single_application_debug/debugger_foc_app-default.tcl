connect -url tcp:127.0.0.1:3121
source C:/Xilinx/Vitis/2020.1/scripts/vitis/util/zynqmp_utils.tcl
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Xilinx HW-Z1-ZCU104 FT4232H 88127A" && level==0 && jtag_device_ctx=="jsn-HW-Z1-ZCU104 FT4232H-88127A-14730093-0"}
fpga -file C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/FOC_app/_ide/bitstream/FOC_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/FOC_wrapper/export/FOC_wrapper/hw/FOC_wrapper.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
set mode [expr [mrd -value 0xFF5E0200] & 0xf]
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/FOC_wrapper/export/FOC_wrapper/sw/FOC_wrapper/boot/fsbl.elf
set bp_6_27_fsbl_bp [bpadd -addr &XFsbl_Exit]
con -block -timeout 60
bpremove $bp_6_27_fsbl_bp
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/ponpr/Documents/ultrazohm_sw/ip_cores/PID_controller/FOC_app/Debug/FOC_app.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A53*#0"}
con

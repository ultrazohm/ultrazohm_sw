vlib work
vlib activehdl

vlib activehdl/xil_defaultlib
vlib activehdl/xpm
vlib activehdl/axi_infrastructure_v1_1_0
vlib activehdl/smartconnect_v1_0
vlib activehdl/axi_protocol_checker_v2_0_1
vlib activehdl/axi_vip_v1_1_1

vmap xil_defaultlib activehdl/xil_defaultlib
vmap xpm activehdl/xpm
vmap axi_infrastructure_v1_1_0 activehdl/axi_infrastructure_v1_1_0
vmap smartconnect_v1_0 activehdl/smartconnect_v1_0
vmap axi_protocol_checker_v2_0_1 activehdl/axi_protocol_checker_v2_0_1
vmap axi_vip_v1_1_1 activehdl/axi_vip_v1_1_1

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work smartconnect_v1_0  -sv2k12 "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/sc_util_v1_0_vl_rfs.sv" \

vlog -work axi_protocol_checker_v2_0_1  -sv2k12 "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/3b24/hdl/axi_protocol_checker_v2_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_axi_vip_0_0/sim/design_1_axi_vip_0_0_pkg.sv" \

vlog -work axi_vip_v1_1_1  -sv2k12 "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/a16a/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_axi_vip_0_0/sim/design_1_axi_vip_0_0.sv" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ipshared/f2a3/hdl/AXI2TCM_v1_0_M00_AXI.vhd" \
"../../../bd/design_1/ipshared/f2a3/hdl/AXI2TCM_v1_0.vhd" \
"../../../bd/design_1/ip/design_1_AXI2TCM_0_0/sim/design_1_AXI2TCM_0_0.vhd" \
"../../../bd/design_1/sim/design_1.vhd" \

vlog -work xil_defaultlib \
"glbl.v"


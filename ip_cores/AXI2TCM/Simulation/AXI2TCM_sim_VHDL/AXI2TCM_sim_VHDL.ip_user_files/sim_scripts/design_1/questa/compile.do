vlib questa_lib/work
vlib questa_lib/msim

vlib questa_lib/msim/xil_defaultlib
vlib questa_lib/msim/xpm
vlib questa_lib/msim/axi_infrastructure_v1_1_0
vlib questa_lib/msim/smartconnect_v1_0
vlib questa_lib/msim/axi_protocol_checker_v2_0_1
vlib questa_lib/msim/axi_vip_v1_1_1

vmap xil_defaultlib questa_lib/msim/xil_defaultlib
vmap xpm questa_lib/msim/xpm
vmap axi_infrastructure_v1_1_0 questa_lib/msim/axi_infrastructure_v1_1_0
vmap smartconnect_v1_0 questa_lib/msim/smartconnect_v1_0
vmap axi_protocol_checker_v2_0_1 questa_lib/msim/axi_protocol_checker_v2_0_1
vmap axi_vip_v1_1_1 questa_lib/msim/axi_vip_v1_1_1

vlog -work xil_defaultlib -64 -sv -L smartconnect_v1_0 -L axi_protocol_checker_v2_0_1 -L axi_vip_v1_1_1 -L xil_defaultlib -L xilinx_vip "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \

vcom -work xpm -64 -93 \
"C:/Xilinx/Vivado/2017.4/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0 -64 "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work smartconnect_v1_0 -64 -sv -L smartconnect_v1_0 -L axi_protocol_checker_v2_0_1 -L axi_vip_v1_1_1 -L xil_defaultlib -L xilinx_vip "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/sc_util_v1_0_vl_rfs.sv" \

vlog -work axi_protocol_checker_v2_0_1 -64 -sv -L smartconnect_v1_0 -L axi_protocol_checker_v2_0_1 -L axi_vip_v1_1_1 -L xil_defaultlib -L xilinx_vip "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/3b24/hdl/axi_protocol_checker_v2_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L smartconnect_v1_0 -L axi_protocol_checker_v2_0_1 -L axi_vip_v1_1_1 -L xil_defaultlib -L xilinx_vip "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_axi_vip_0_0/sim/design_1_axi_vip_0_0_pkg.sv" \

vlog -work axi_vip_v1_1_1 -64 -sv -L smartconnect_v1_0 -L axi_protocol_checker_v2_0_1 -L axi_vip_v1_1_1 -L xil_defaultlib -L xilinx_vip "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/a16a/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -sv -L smartconnect_v1_0 -L axi_protocol_checker_v2_0_1 -L axi_vip_v1_1_1 -L xil_defaultlib -L xilinx_vip "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../AXI2TCM_sim_VHDL.srcs/sources_1/bd/design_1/ipshared/02c8/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2017.4/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_axi_vip_0_0/sim/design_1_axi_vip_0_0.sv" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/design_1/sim/design_1.vhd" \
"../../../bd/design_1/ip/design_1_AXI2TCM_v1_0_0_0/sim/design_1_AXI2TCM_v1_0_0_0.vhd" \

vlog -work xil_defaultlib \
"glbl.v"


vlib work
vmap -c -modelsimini "/modelsim.ini"
vcom  uz_JL_invModel_ideal_src_uz_JL_invModel_ideal_pkg.vhd
vcom  Xilinx/Zynq_UltraScale+/xczu9eg-ffvb1156-1-e/L8/amdfp_mul_single/amdfp_mul_single.vhd
vcom  Xilinx/Zynq_UltraScale+/xczu9eg-ffvb1156-1-e/L11/amdfp_sub_single/amdfp_sub_single.vhd
vcom  uz_JL_invModel_ideal_src_amdfp_mul_single_block.vhd
vcom  uz_JL_invModel_ideal_src_amdfp_sub_single_block.vhd
vcom  uz_JL_invModel_ideal_src_nfp_div_single.vhd
vcom  uz_JL_invModel_ideal_src_nfp_gain_pow2_single.vhd
vcom  uz_JL_invModel_ideal_src_MATLAB_Function.vhd
vcom  uz_JL_invModel_ideal_src_uz_JL_invModel_ideal.vhd
vlog C:/Xilinx/Vivado/2022.2/data/verilog/src/glbl.v
vopt -64 +acc=npr -L unisims_ver -L unimacro_ver -L secureip -L xpm -work work work.uz_JL_invModel_ideal_src_uz_JL_invModel_ideal work.glbl -o uz_JL_invModel_ideal_src_uz_JL_invModel_ideal_opt

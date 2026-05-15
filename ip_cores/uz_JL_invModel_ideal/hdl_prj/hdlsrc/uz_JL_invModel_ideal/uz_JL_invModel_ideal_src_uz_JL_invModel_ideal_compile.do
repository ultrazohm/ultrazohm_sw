vlib work
vmap -c -modelsimini "/modelsim.ini"
vcom  uz_JL_invModel_ideal_src_uz_JL_invModel_ideal_pkg.vhd
vcom  uz_JL_invModel_ideal_src_uz_JL_invModel_ideal_tc.vhd
vcom  uz_JL_invModel_ideal_src_nfp_uminus_single.vhd
vcom  uz_JL_invModel_ideal_src_nfp_gain_pow2_single.vhd
vcom  uz_JL_invModel_ideal_src_nfp_abs_single.vhd
vcom  uz_JL_invModel_ideal_src_uz_JL_invModel_ideal.vhd
vlog C:/Xilinx/Vivado/2022.2/data/verilog/src/glbl.v
vopt -64 +acc=npr -L unisims_ver -L unimacro_ver -L secureip -L xpm -work work work.uz_JL_invModel_ideal_src_uz_JL_invModel_ideal work.glbl -o uz_JL_invModel_ideal_src_uz_JL_invModel_ideal_opt

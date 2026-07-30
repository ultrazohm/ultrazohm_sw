vlib work
vmap -c -modelsimini "/modelsim.ini"
vcom  uz_JL_SDDemod_src_CLk.vhd
vcom  uz_JL_SDDemod_src_Differentierer.vhd
vcom  uz_JL_SDDemod_src_Integratoren.vhd
vcom  uz_JL_SDDemod_src_Sinc3_Filter_U.vhd
vcom  uz_JL_SDDemod_src_Differentierer_block.vhd
vcom  uz_JL_SDDemod_src_Integratoren_block.vhd
vcom  uz_JL_SDDemod_src_Sinc3_Filter_U1.vhd
vcom  uz_JL_SDDemod_src_Differentierer_block1.vhd
vcom  uz_JL_SDDemod_src_Integratoren_block1.vhd
vcom  uz_JL_SDDemod_src_Sinc3_Filter_U2.vhd
vcom  uz_JL_SDDemod_src_Differentierer_block2.vhd
vcom  uz_JL_SDDemod_src_Integratoren_block2.vhd
vcom  uz_JL_SDDemod_src_Sinc3_Filter_U3.vhd
vcom  uz_JL_SDDemod_src_Differentierer_block3.vhd
vcom  uz_JL_SDDemod_src_Integratoren_block3.vhd
vcom  uz_JL_SDDemod_src_Sinc3_Filter_U4.vhd
vcom  uz_JL_SDDemod_src_trigger_sec_edge.vhd
vcom  uz_JL_SDDemod_src_Subsystem.vhd
vcom  uz_JL_SDDemod_src_gen_slow_clk_I.vhd
vcom  uz_JL_SDDemod_src_gen_slow_clk_U.vhd
vcom  uz_JL_SDDemod_src_uz_JL_SDDemodulator.vhd
vlog C:/Xilinx/Vivado/2022.2/data/verilog/src/glbl.v
vopt -64 +acc=npr -L unisims_ver -L unimacro_ver -L secureip -L xpm -work work work.uz_JL_SDDemod_src_uz_JL_SDDemodulator work.glbl -o uz_JL_SDDemod_src_uz_JL_SDDemodulator_opt

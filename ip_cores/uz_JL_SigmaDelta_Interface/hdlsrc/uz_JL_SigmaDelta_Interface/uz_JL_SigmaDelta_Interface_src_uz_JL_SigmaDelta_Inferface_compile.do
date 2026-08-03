vlib work
vmap -c -modelsimini "/modelsim.ini"
vcom  uz_JL_SigmaDelta_Interface_src_uz_JL_SigmaDelta_Inferface_pkg.vhd
vcom  uz_JL_SigmaDelta_Interface_src_CLk.vhd
vcom  uz_JL_SigmaDelta_Interface_src_trigger_sec_edge.vhd
vcom  uz_JL_SigmaDelta_Interface_src_Subsystem.vhd
vcom  uz_JL_SigmaDelta_Interface_src_gen_slow_clk.vhd
vcom  uz_JL_SigmaDelta_Interface_src_Integratoren.vhd
vcom  uz_JL_SigmaDelta_Interface_src_Differentierer.vhd
vcom  uz_JL_SigmaDelta_Interface_src_For_Each_Subsystem.vhd
vcom  uz_JL_SigmaDelta_Interface_src_uz_JL_SigmaDelta_Inferface.vhd
vlog C:/Xilinx/Vivado/2022.2/data/verilog/src/glbl.v
vopt -64 +acc=npr -L unisims_ver -L unimacro_ver -L secureip -L xpm -work work work.uz_JL_SigmaDelta_Interface_src_uz_JL_SigmaDelta_Inferface work.glbl -o uz_JL_SigmaDelta_Interface_src_uz_JL_SigmaDelta_Inferface_opt

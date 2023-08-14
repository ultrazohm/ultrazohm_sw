# aclk {FREQ_HZ 100000000 CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0 PHASE 0.000} aclk1 {FREQ_HZ 10000000 CLK_DOMAIN zusys_clk_wiz_0_0_clk_50MHz PHASE 0.0} aclk2 {FREQ_HZ 50000000 CLK_DOMAIN zusys_clk_wiz_0_0_clk_50MHz PHASE 0.0}
# Clock Domain: zusys_zynq_ultra_ps_e_0_0_pl_clk0
create_clock -name aclk -period 10.000 [get_ports aclk]
# Clock Domain: zusys_clk_wiz_0_0_clk_50MHz
create_clock -name aclk1 -period 100.000 [get_ports aclk1]
# Generated clocks
create_generated_clock -name aclk2 -source [get_ports aclk1] -multiply_by 5 -divide_by 1 [get_ports aclk2]

create_clock -period 10.000 -name IPCORE_CLK -waveform {0.000 5.000} [get_ports IPCORE_CLK]
set_property HD.CLK_SRC BUFGCTRL_X0Y2 [get_ports IPCORE_CLK]

create_clock -period 10.000 -name AXI4_Lite_ACLK -waveform {0.000 5.000} [get_ports AXI4_Lite_ACLK]
set_property HD.CLK_SRC BUFGCTRL_X0Y3 [get_ports AXI4_Lite_ACLK]
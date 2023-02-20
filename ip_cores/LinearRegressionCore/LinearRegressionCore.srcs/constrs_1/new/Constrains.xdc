create_clock -period 10.000 -name clk -waveform {0.000 5.000} [get_ports clk]
set_property HD.CLK_SRC BUFGCTRL_X0Y2 [get_ports clk]
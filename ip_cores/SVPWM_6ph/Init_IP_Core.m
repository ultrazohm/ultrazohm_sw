%%
clc
clear all

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
'C:\Xilinx\Vivado\2022.2\bin\vivado.bat'); % Tells the HDL-Coder which tool for synthesis it should use



%% Parameter PWM
f_FPGA_clk=100e6; %Used FPGA-Clock
T_FPGA_clk=1/f_FPGA_clk;
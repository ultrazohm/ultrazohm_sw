% IP Core PWM and Switching Signal Control
% Author:   Sebastian Wendel & Barnabas Haucke-Korber
% Date:     04.09.2018
% Version:  3.0
% release notes: First Tests
% Changed: Added the use for lower PWM frequencies and the Tri-State
% function

%%
clc
clear all

%hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
% 'C:\Xilinx\Vivado\2017.4\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.


%% Parameter PWM
f_FPGA_clk=100e6; %Used FPGA-Clock
T_FPGA_clk=1/f_FPGA_clk;
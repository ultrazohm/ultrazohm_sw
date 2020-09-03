% IP Core PWM and Switching Signal Control
% Author:   Barnabas Haucke-Korber
% Date:     04.09.2018
% Version:  0.1
% release notes: First Tests

%%
clc
clear all

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2017.4\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.


%% Parameter PWM
f_pwm_clk=100e6;
T_pwm_clk=1/f_pwm_clk;
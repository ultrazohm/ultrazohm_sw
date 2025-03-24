clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;        % IP core clock freq in Hz
t_clock = 1/f_clock;    % IP core sample time in s

f_ADC =50e3;            % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;        % ADC sample time in s

f_plant = 1e6;          % Plant simulation freq in Hz
t_plant = 1/f_plant;    % Plant sample time in s


ssi_encoder_bit_width = 17; 
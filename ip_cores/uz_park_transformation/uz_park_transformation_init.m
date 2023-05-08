clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;    % IP core clock freq in Hz
t_clock = 1/f_clock;     % IP core sample time in s

f_ADC =100e3;       % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;    % ADC sample time in s

freq_Hz = 300;      % Frequency of input signal in Hz
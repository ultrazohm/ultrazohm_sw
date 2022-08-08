clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;    % IP core clock freq in Hz
ts = 1/f_clock;     % IP core sample time in s

f_ADC =100e3;       % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;    % ADC sample time in s

pu_fixdt_type = fixdt(1,18,15); % data type of pu values

% parameters for sine waves
f = 50;     % fundamental frequency
Harmonic_Orders = [3 5 7 9 11 13 15 17 19 21];
                        %3    5    7    9   11   13   15    17   19    21
Harmonic_Amplitudes = [0.00 0.08 0.06 0.00 0.00 0.00 0.000 0.00 0.00 0.000];
% Harmonic_Amplitudes = [  1    1    1    1    1    1    1     1   1      1];
% Harmonic_Amplitudes = [  0    0.1    0.1    0    0    0    0     0   0      0];

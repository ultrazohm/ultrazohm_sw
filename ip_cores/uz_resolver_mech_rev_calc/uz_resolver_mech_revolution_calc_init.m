clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;    % IP core clock freq in Hz
t_clock = 1/f_clock;     % IP core sample time in s

f_ADC =100e3;       % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;    % ADC sample time in s

resolver_polepairs = 3;
machine_polepairs = 5;
f_mech = 500;

theta_el_offset = -4.261607;

rps_max_16bit = 125;
rps_max_14bit = 500;
rps_max_12bit = 1000;
rps_max_10bit = 2500;

bitToRpsFactor_16bit = rps_max_16bit/(2^(16-1));% 0.003814697
bitToRpsFactor_14bit = rps_max_14bit/(2^(14-1));% 0.061035156
bitToRpsFactor_12bit = rps_max_12bit/(2^(12-1));% 0.48828125
bitToRpsFactor_10bit = rps_max_10bit/(2^(10-1));% 4.8828125

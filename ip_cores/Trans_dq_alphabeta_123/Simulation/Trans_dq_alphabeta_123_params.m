hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.
T_mech = 2e-08;    % 50MHz = 2e-08 //Sample time im FPGA Timer0 da sonst negative SLack-Time im System auftritt


% Used FPGA frequency
f_fpga = 100e6; 
f_T_fpga=1/f_fpga;
T_fpga = 1/f_fpga;
% Weitere Frequenzen
f_150MHz = 150e6;   % [Hz] FPGA-Grundfrequenz für 150 MHz
f_100MHz = 100e6;   % [Hz] FPGA-Grundfrequenz für 100 MHz
f_50MHz  = 50e6;     % [Hz] FPGA-Grundfrequenz für 50 MHz
f_25MHz  = 25e6;     % [Hz] FPGA-Grundfrequenz für 25 MHz
f_10MHz  = 10e6;    % [Hz] FPGA-Grundfrequenz für 10 MHz
T_150MHz  = 1/f_150MHz;
T_100MHz  = 1/f_100MHz;
T_50MHz  = 1/f_50MHz;
T_25MHz  = 1/f_25MHz;

f_c = 100000;        % controll frequency in Hz
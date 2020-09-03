% Sebastian Wendel

clc;        % command window löschen 
clear;      % alle Variablen löschen 
close all; % alle Fenster schließen

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2017.4\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.

%hdlsetuptoolpath('ToolName','Xilinx ISE','ToolPath','C:\Xilinx\14.3\ISE_DS\ISE\bin\nt64\ise.exe')
SimulationsDauer = 10; %0.2%0.02


T_mech = 2e-08;    % 50MHz = 2e-08 //Sample time im FPGA Timer0 da sonst negative SLack-Time im System auftritt

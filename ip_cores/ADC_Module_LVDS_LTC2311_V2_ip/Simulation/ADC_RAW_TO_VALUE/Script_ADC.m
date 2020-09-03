% Sebastian Wendel

clc;        % command window löschen 
clear;      % alle Variablen löschen 
close all; % alle Fenster schließen

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2017.4\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.

SimulationsDauer = 10; %0.2%0.02
T_mech = 10e-08;% 10MHz = 10e-08 //Sample time Regelstrecke (Motor) und ADC-Messung

ADC_SET_USER_OFFSET =0; %If False (0), than the flag uses the measured value as offset. If True (1), than the flag uses the falue in ADC_USER_OFFSET.
ADC_USER_OFFSET = (2^15)/2; %ADC RAW value, which can used as offset, e.g., if positive and negative measurements are necessary.
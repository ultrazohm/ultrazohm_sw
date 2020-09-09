%% Init Script for average switching frequency
% Sebastian Wendel
% 23.08.2020
%% 
clc;
clear all;
close all;

%%  *** HDL Coder Settings ***

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat'); % Hierdruch wird dem HDL-Coder gesagt welches Synthesetool er für die HDL-Generierung nutzen soll.

%--------------------------------------------------------------------------
%%  *** Frequenzen und Vorgaben ***

% Abtastfrequenz Messwerte
f_f_a = 100e3;                              %[Hz] Abtastfrequenz neuer Messwerte, wenn f_a > f_c Oversampling
f_T_a = 1/f_f_a;      
% Frequenz CCS-MPC 
f_f_cc=50e3;                                %[Hz] Regelfrequenz CCS-MPC
f_T_cc=1/f_f_cc;
% Frequenz FCS-MPC
f_f_cf = 100e3;                             %[Hz] Regelfrequenz FCS-MPC
f_T_cf = 1/f_f_cf;
% Frequenz FOC
f_foc = 5e3;                               %[Hz] Regelfrequenz FOC
T_foc = 1/f_foc;
% Frequenz PWM
f_pwm = 5e3;                             % [Hz] PWM-Frequenz in Hz, wie schnell taktet die PWM bei deren verwendung, Grundeinstellung 100 kHz
T_pwm = 1/f_pwm;                            %100kHz = 10e-6 %%50kHz = 20e-6; ((10e-6;= "ohne_Continous" )// 125e-6 = 8kHz || 50e-6 = 20kHz PWM Period //Sample time for PWM-modulation
% Frequenz SVM
f_svm = 5e3;                               % [Hz] PWM-Frequenz in Hz, PWM Frequenz von Raumzeigermodulation. Das ist der Wert der für die FOC-PWm genommen wird!
T_svm = 1/f_pwm;                            %100kHz = 10e-6 %%50kHz = 20e-6; 
% Frequenz Umrichter
T_mech = 5e-8;     % [s] Samplezeit zur Aktuellisierung der VSI Steuersignale 5e-8
f_f_mech= 1/T_mech;
% Frequenz Beobachter
f_f_Beo = f_f_cc;                           %[Hz] Regelfrequenz Beobachter
f_T_Beo = 1/f_f_Beo;  
%CPU Frequenz
f_f_cpu = 1.5e6;    % [Hz] Frequenz der CPU, benötigt für Geber Model (Concerto)
f_T_cpu = 1/f_f_cpu;
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

SimulationsDauer = 0.8; %[s]  %0.2%0.02

%% ------------------------------------------------------------------------
%*** Data-Type***%

DataTypeControl18_11 = 'double'; %fixdt(1,18,11);
DataTypeControl24_20 = 'double'; %fixdt(1,24,20);
DataTypeVoltageVectors = fixdt(1,24,12);







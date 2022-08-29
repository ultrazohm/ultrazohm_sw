% Parameterfile for simulation
clc
clear

% Parameters of the 6 Phase PMSM
R_ph = 0.19;            % phase resistance in Ohm
psi_pm = 0.19;          % flux linkage in Vs
L_d = 2e-3;             % d-axis inductance in H
L_q = 6.4e-3;           % q-axis inductance in H
L_x = 3e-3;             % x-axis inductance in H
L_y = L_x;              % y-axis inductance in H
p = 5;                  % number of pole pairs
J = 2.5581e-4;          % rotor inertia 

% Linkvoltage of the 6 Phase 2-level inverter
u_dc = 565;          % dc link voltage

% SampleTime
f_c = 100000; 

% Rate-Trnsition time
Rt = 4e-6;

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');
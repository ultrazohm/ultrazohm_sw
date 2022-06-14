% Parameterfile for simulation

% Brose Power Steering Motor 
R = 0.023;          % phase resistance in Ohm
psiPM = 0.007;      % flux linkage in Vs
Ld = 0.00003;       % d-axis inductance in H
Lq = 0.00005;       % q-axis inductance in H
np = 5;             % number of pole pairs
J = 2.5581e-4;      % rotor inertia 

% controller calculation according to TI instaspin user guide chp. 11
% current controller
Tnd = Ld/R;         % d-axis integral controller reset time
Tnq = Lq/R;         % q-axis integral controller reset time

BW = 400;           % desired closed loop current controller bandwidth in Hz

Kpd = Ld*2*pi*BW;   % d-axis proportional gain
Kpq = Lq*2*pi*BW;   % q-axis proportional gain
% speed controller
d = 10;             % damping factor for speed controller
K = 3/2*np*psiPM/J; % constant factor for speed controller

Kpn = Kpq/(Lq*d*K); % speed controller proportional gain
Tnn = d^2*Lq/Kpq;   % speed controller integral reset time
%resonant controller for dead time compensation (not used)
Kr = 0;
u_dc = 12;          % dc link voltage
C_dc_link = 450e-6; % dc link capacity in F

%simulation and MCU timing configuration
f_MCU = 150e6;      % frequency of microcontroller in Hz
f_sw = 20000;       % switching frequency in Hz
f_c = 100000;        % controll frequency in Hz
f_Simulation = 10e6;% simulation frequency in Hz
PERIOD = 3750;      % max value of PWM counter

%dead time for Hi Lo transitions of switches
T_dead = 1.2e-6;     % dead time in seconds

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




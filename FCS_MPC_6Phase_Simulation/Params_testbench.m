% Parameterfile for simulation
clc
clear

% Brose Power Steering Motor 6ph customized
R_ph = 0.125;    %0.0353;     %0.023;         % phase resistance in Ohm
psi_pm = 0.0048;   %0.039614;   %0.007;         % flux linkage in Vs
L_d = 0.000147;    %0.824e-3;    %0.00003;       % d-axis inductance in H
L_q = 0.000147;   %2.488e-3;    %0.00005;       % q-axis inductance in H
L_x = 0.00005566 ;     %0.2744e-3;    %0.00004;       % x-axis inductance in H
L_y = L_x;                        % y-axis inductance in H
p = 5;            %5;             % number of pole pairs
J = 2.5581e-4;                    % rotor inertia 

% controller calculation according to TI instaspin user guide chp. 11
% current controller
Tnd = L_d/R_ph;         % d-axis integral controller reset time
Tnq = L_q/R_ph;         % q-axis integral controller reset time

BW = 1000;           % desired closed loop current controller bandwidth in Hz

Kpd = L_d*2*pi*BW;   % d-axis proportional gain
Kpq = L_q*2*pi*BW;   % q-axis proportional gain
% speed controller
d = 10;             % damping factor for speed controller
K = 3/2*p*psi_pm/J; % constant factor for speed controller

Kpn = Kpq/(L_q*d*K); % speed controller proportional gain
Tnn = d^2*L_q/Kpq;   % speed controller integral reset time
%resonant controller for dead time compensation (not used)
Kr = 0;

%dc lick
u_dc = 36.0; %270;  %270          % dc link voltage
C_dc_link = 50e-6;  % dc link capacity in F

%simulation and MCU timing configuration
f_MCU = 100e6;      % frequency of microcontroller in Hz
f_sw = 20000;      % switching frequency in Hz
f_c = 100000;        % controll frequency in Hz

f_Simulation = 10e6;% simulation frequency in Hz
PERIOD = 500;      % max value of PWM counter

%dead time for Hi Lo transitions of switches
T_dead = 0.05e-6;    % dead time in seconds

%Mosfet on resistance
RDSon = 1e-10;       % Ohm

% set_param('FOC', 'DecoupledContinuousIntegration', 'on')
% set_param('FOC', 'MinimalZcImpactIntegration', 'on')

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
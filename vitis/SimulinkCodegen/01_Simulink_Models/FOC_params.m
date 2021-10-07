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

Kr = 270;           % gain of resonant controller for dead time comp.

u_dc = 12;          % dc link voltage
C_dc_link = 450e-6; % dc link capacity in F

f_MCU = 150e6;      % frequency of microcontroller in Hz
f_sw = 20000;       % switching frequency in Hz
f_c = 10000;        % controll frequency in Hz
f_Simulation = 10e6;% simulation frequency in Hz
PERIOD = 3750;      % max value of PWM counter

T_dead = 2.0e-6     % dead time in seconds


% set_param('FOC', 'DecoupledContinuousIntegration', 'on')
% set_param('FOC', 'MinimalZcImpactIntegration', 'on')
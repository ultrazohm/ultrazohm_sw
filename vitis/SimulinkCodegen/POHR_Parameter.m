%Script to declare parameters
% Parameter fuer Reihenschaltung der Spulen
zp = 1;                         % Number of polepairs
L_max = 2*1.9957e-3;              % Maximale Induktivitaet H
L_min = 2*0.4699e-3;              % Minimale Induktivitaet H
R = 2*0.044;                      % Ohm Strangwiderstand

% Lookup-Table Inductance
theta_mech = [0 5 85 95 175 180] .* pi/180;
L_table = [L_max L_max L_min L_min L_max L_max];
%diff_L_table = diff(L_table, theta_mech, 1)

n_speed = 3000;                 % rpm
stop_time = 10 * 60/n_speed;


BW =800;
%Kp = 0.002*2*pi*BW;
%Ki = R/0.002;

f_controller = 10000;
T_controller = 1/f_controller;


time_step = T_controller/100;
%f_switchingInverter = 20000;            %Triangle signal frequency
%T_sigma = 0.5/f_switchingInverter + T_controller;
%Kp = (0.002/R)/(2*T_sigma*1/R);
%Ki = R/0.002;

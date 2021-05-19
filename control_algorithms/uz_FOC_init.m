%% initialization script for uz_FOC
clc
clear
% motor parameters - Bühler 201


Reset = 2;

% Simulation für constante Drehzahl
d_omega_mech=(2000/60)*2*pi;%2000rpm


% Controlparameter
f_c=20000;   %Hz UZ-ISR-frequency
t_a = 1/f_c;
d_d_c=16000;                %kHz
d_y_max=1000;                %V
d_y_min=-d_y_max;           %V

% Auslegung des Stromreglers nach Betragsoptimum
d_tau_sigma=2/16000;          %Verzögerungszeit des Zeitdiskreten Systems
Kp_id=4;%d_L_d/(2*d_tau_sigma);
Kp_iq=5;%d_L_q/(2*d_tau_sigma);
Ki_id=6;%d_R_1/(2*d_tau_sigma);
Ki_iq=Ki_id;
Kp_n=2;
Ki_n=3;

%Parameter
n_ref_rpm=2000; %target speed for speedFOC
U_ZK=24; %V

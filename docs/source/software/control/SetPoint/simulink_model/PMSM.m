% % clear;
% % clc;

%% machine parameters

L_d = 0.00045;
L_q = 0.0018;
R_s = 0.27;
p = 4;
Psi_PM = 0.0195;
n_nenn = 2000;
I_nenn = 10;
I_max = 20;
V_DC = 48;
motor_type = 1; %0=SMPMSM (Ld=Lq)  1=IPMSM(Ld=/=Lq)

V_max = V_DC/sqrt(3); % [V] available voltage space vector

PWM_frequency = 10e3;
Ts = 1 / PWM_frequency;

%% controller parameters
tau_sigma = 2*Ts;

K_Pd = L_d/(2*tau_sigma);
K_Pq = L_q/(2*tau_sigma);
K_Id = R_s/(2*tau_sigma);
K_Iq = R_s/(2*tau_sigma);

%% decoupling
decoupling_active = true;

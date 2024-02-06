%% Parameter for simulation of uz_pmsm_model.slx
% This is called by a callback when uz_pmsm_model is opened
% 

% ad1 = 0;
% ad2 = 0;
% ad3 = 0;
% ad4 = 0;
% ad5 = 0;
% ad6 = 0;
% aq1 = 0;
% aq2 = 0;
% aq3 = 0;
% aq4 = 0;
%  aq5 =0;
% aq6 =0;
% Fid1_Giq1 = 0;
% Fid2_Giq2 = 0;
% R_1=0;
% L_d=0;
% L_q=0;
% psi_pm=0;
% polepair=0;

% % Electrical parameters
R_1=0.3;
L_d=0.00045;
L_q=0.002;
psi_pm=0.0194;
polepair=4;

% %DiffrentMotor
% R_1=0.45;
% L_d=0.00175;
% L_q=0.00175;
% psi_pm=0.042;
% polepair=4;

%DiffrentMotor
% R_1=0.085;
% L_d=3.00e-04;
% L_q=3.00e-04;
% psi_pm=0.0075;
% polepair=4.0;

ts=1/5e5; % =2e-6

setpoint_step=4.0;
rpm = 0;
load_torque = 0;

% Controller parameter
ts_regler=1/20e3;
tau_d=L_d/R_1;
tau_q=L_q/R_1;
tau_sum=2*ts_regler;
% Parallel PID
k_p_d=L_d/(2*tau_sum);
k_p_q=L_q/(2*tau_sum);
k_i_d=R_1/(2*tau_sum);
k_i_q=R_1/(2*tau_sum);

% Mechanical parameters
inertia=0.000084;
% inertia=3.24e-05;
friction_coefficient=0.001;
static_friction_torque=0.01;
% 
% % % Mechanical parameters
% % inertia=0;
% % inertia=0.001;
% friction_coefficient=0;
% static_friction_torque=0;

% Simulation settings
simulate_mechanical=true;
simulate_open_loop=true;
simulate_nonlinear_modell=true;

parameter_nachfuerung=false;

praediktion_entkopplung_nonlinear=false;
entkopplung_linear=true;
entkopplung_static=false;
entkopplung_dynamic=false;



% %Stoeraufschaltung
% c0 = 1;
% T0 = tau_sum/10;

% % Import the data from Excel for lookup table
% FluxMapData = readtable('C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model_nonlinear\FluxMapData_2023-05-26_13-07-57.xlsx');
% 
% %Psi_d
% % d_currents in d Axe for lookup table
% d_current_d_Flux = FluxMapData{1,:};
% % q currents in d Axe for lookup table
% q_current_d_Flux = FluxMapData{22:41,1};
% % Output values for lookup table
% Flux_d = FluxMapData{43:62,:}'*(1e-3);
% 
% %Psi_q
% % d currents in q Axe for lookup table
% d_current_q_Flux = FluxMapData{66,:};
% % q currents in q Axe for lookup table
% q_current_q_Flux = FluxMapData{87:106,1};
% % Output values for lookup table
% Flux_q = FluxMapData{108:end,:}'*(1e-3);
% 
% %Ldd, Ldq
% [Ldq,Ldd]=gradient(Flux_d);
% [Lqq,Lqd]=gradient(Flux_q);

% % Import the data from Excel for lookup table
FluxMapData = readtable('FluxMapData_Prototyp_1000rpm');
%Psi_d
% d_currents in d Axe for lookup table
d_current_d_Flux = FluxMapData{1,1:20};
% q currents in d Axe for lookup table
q_current_d_Flux = FluxMapData{22:41,1};
% Output values for lookup table
Flux_d = FluxMapData{43:62,1:20}'*(1e-3);
Flux_d_test = FluxMapData{43:62,1:20}*(1e-3);
%Psi_q
% d currents in q Axe for lookup table
d_current_q_Flux = FluxMapData{66,1:20};
% q currents in q Axe for lookup table
q_current_q_Flux = FluxMapData{87:106,1};
% Output values for lookup table
Flux_q = FluxMapData{108:127,1:20}'*(1e-3);
Flux_q_test = FluxMapData{108:127,1:20}*(1e-3);
%Ldd, Lqq, Ldq=Lqd;
% [Ldq,Ldd]=gradient(Flux_d);
% [Lqq,Lqd]=gradient(Flux_q);

[Ldq,Ldd]=gradient(Flux_d,2.5263,1.6842);
[Lqq,Lqd]=gradient(Flux_q,2.5263,1.6842);

[Ldd_real,Ldq_real]=gradient(Flux_d_test,1.6842,2.5263);
[Lqd_real,Lqq_real]=gradient(Flux_q_test,1.6842,2.5263);

% [Ldd,Ldq]=gradient(Flux_d,1.6842,2.5263);
% [Lqd,Lqq]=gradient(Flux_q,1.6842,2.5263);

% test = polyfit(d_current_d_Flux(:),q_current_d_Flux(:), Flux_d(:), 2);


% %Diffrent LUTs for diffrent Modeldesign 
% %Currents from psi d and psi q 
% psi_d_in_d_current = FluxMapData{131,1:20}.*(1e-3);
% psi_q_in_d_current = FluxMapData{152:171,1}.*(1e-3);
% d_current = FluxMapData{173:192,1:20}';
% % d_Flux_new = FluxMapData{43,:}'*(1e-3);
% % d_Flux_yaxis = FluxMapData{43,:};
% 
% 
% 
% psi_d_in_q_current = FluxMapData{196,1:20}.*(1e-3);
% psi_q_in_q_current = FluxMapData{217:236,1}.*(1e-3);
% q_current = FluxMapData{238:257,1:20}';
% % q_Flux_new = FluxMapData{108:127,1}'*(1e-3);
% % q_Flux_yaxis = FluxMapData{108,:};







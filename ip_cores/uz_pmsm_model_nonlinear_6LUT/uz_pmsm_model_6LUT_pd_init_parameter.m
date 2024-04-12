%% Parameter for simulation of uz_pmsm_model.slx
% This is called by a callback when uz_pmsm_model is opened
% 
% Electrical parameters
R_1=0.3;
L_d=0.00045;
L_q=0.002;
psi_pm=0.0194;
polepair=4;
ts=1/5e5; % =2e-6
% ts=1/10e3; % =2e-6
% Controller parameter
ts_regler=1/10e3;

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
% inertia=0.001;
friction_coefficient=0.001;
static_friction_torque=0.01;

% Simulation settings
simulate_mechanical=false;
simulate_open_loop=true;
simulate_nonlinear_modell=false; %Cant change it yet

parameter_nachfuerung=false;

praediktion_entkopplung_nonlinear=false;
entkopplung_linear=false;
entkopplung_static=false;
entkopplung_dynamic=false;

setpoint_step=10.0;

%% Dennis measurements MA
% % % Import the data from Excel for lookup table
% FluxMapData = readtable('FluxMapData_Prototyp_1000rpm');
% 
% %Currents
% % d_currents in d Axe for lookup table
% id = single(FluxMapData{1,1:20});
% % q currents in d Axe for lookup table
% iq = single(FluxMapData{22:41,1});
% 
% %Psi_d
% % Output values for lookup table
% psid = single(FluxMapData{43:62,1:20}'*(1e-3));
% %Psi_q 
% % Output values for lookup table
% psiq = single(FluxMapData{108:127,1:20}'*(1e-3));
% 
% %Inductances
% [Ldq,Ldd]=gradient(psid,2.5263,1.6842);
% [Lqq,Lqd]=gradient(psiq,2.5263,1.6842);

%% Michi FEM

 id = single(id(1,1:9));
 iq = single(iq(1:33,1));
 psid = psi_d';
 psiq = psi_q';

[Ldq,Ldd]=gradient(psid,0.5,0.5);
[Lqq,Lqd]=gradient(psiq,0.5,0.5);







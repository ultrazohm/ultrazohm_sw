%% Parameter for simulation of uz_pmsm_model.slx
% This is called by a callback when uz_pmsm_model is opened
% 
% Electrical parameters
R_1=0.3;
L_d=0.00045;
L_q=0.002;
psi_pm=0.0194;
polepair=4;
ts=1/5e5; 
rpm1 = 100;
rpm2 = 100;

% Controller parameter
ts_regler=1/25e3;
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
simulate_open_loop=false;
simulate_nonlinear_modell=true;

parameter_nachfuerung=false;

%Only one should be set true
praediktion_entkopplung_nonlinear=true;
entkopplung_linear=false;
entkopplung_static=false;
entkopplung_dynamic=false;

setpoint_step=10.0;



%% extract Lookup table data
%For nonlinear Model to work LUTs have to be implemented
% Import the data from Excel for lookup table
FluxMapData = readtable('FluxMapData_Prototyp_1000rpm');

% Currents
id = FluxMapData{1,1:20};
iq = FluxMapData{22:41,1};
%Psi_d
psi_d_forLUT = FluxMapData{43:62,1:20}'*(1e-3);
psi_d = FluxMapData{43:62,1:20}*(1e-3);
%Psi_q
psi_q_forLUT = FluxMapData{108:127,1:20}'*(1e-3);
psi_q = FluxMapData{108:127,1:20}*(1e-3);

%Inductances
[Ldq,Ldd]=gradient(psi_d,2.5263,1.6842);
[Lqq,Lqd]=gradient(psi_q,2.5263,1.6842);

[Ldd_real,Ldq_real]=gradient(psi_d_forLUT,1.6842,2.5263);
[Lqd_real,Lqq_real]=gradient(psi_q_forLUT,1.6842,2.5263);

figure;
surf(id,iq,psi_d)
figure;
surf(id,iq,psi_q)







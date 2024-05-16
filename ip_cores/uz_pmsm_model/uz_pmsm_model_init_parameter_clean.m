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
simulate_nonlinear_modell=true; %Only set this true if the fitting parameter script ran successfully

parameter_nachfuerung=false;

setpoint_step=10.0;

% Fitting Parameter 
% Initilize the Parameters one time so the model is not 
ad1 = 0;
ad2 = 0;
ad3 = 0;
ad4 = 0;
ad5 = 0;
ad6 = 0;
aq1 = 0;
aq2 = 0;
aq3 = 0;
aq4 = 0;
aq5 =0;
aq6 =0;
Fid1_Giq1 = 0;
Fid2_Giq2 = 0;


%% Parameter for simulation of uz_pmsm_model.slx
% This is called by a callback when uz_pmsm_model is opened

% Electrical parameters
R_1=0.45;
L_d=1.75e-3;
L_q=1.75e-3;
psi_pm=0.042;
polepair=4;
ts=1/2e6;

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
inertia=0.001;
friction_coefficient=0.001;
static_friction_torque=0.01;

% Simulation settings
simulate_mechanical=true;
simulate_open_loop=true;
setpoint_step=10.0;

% Import the data from Excel for lookup table
FluxMapData = readtable('C:\Users\Philipp\ultrazohm\ultrazohm_sw\ip_cores\uz_pmsm_model\FluxMapData_2023-05-26_13-07-57');

%Psi_d
% d_currents in d Axe for lookup table
d_current_in_d_axis = FluxMapData{1,:};
% q currents in d Axe for lookup table
q_current_in_d_axis = FluxMapData{22:41,1};
% Output values for lookup table
d_Flux = FluxMapData{43:62,:};

%Psi_q
% d currents in q Axe for lookup table
d_current_in_q_axis = FluxMapData{66,:};
% q currents in q Axe for lookup table
q_current_in_q_axis = FluxMapData{87:106,1};
% Output values for lookup table
q_Flux = FluxMapData{108:end,:};

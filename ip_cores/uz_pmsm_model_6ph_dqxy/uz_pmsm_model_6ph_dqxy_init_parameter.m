%% Parameter for simulation of uz_pmsm_model.slx
% This is called by a callback when uz_pmsm_model is opened
hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath','C:/Xilinx/Vivado/2022.2/bin')

% Electrical parameters
R_1=2.1;
L_d=30e-3;
L_q=50e-3;
L_x=30e-4;
L_y=50e-4;
psi_pm=0.05;
polepair=2;
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
k_p_x=L_x/(2*tau_sum);
k_p_y=L_y/(2*tau_sum);
k_i_x=R_1/(2*tau_sum);
k_i_y=R_1/(2*tau_sum);

% Mechanical parameters
inertia=0.001;
friction_coefficient=0.001;
static_friction_torque=0.01;

% Simulation settings
simulate_mechanical=true;
simulate_open_loop=true;
setpoint_step=10.0;
%% Parameter for simulation of uz_pmsm_model.slx
% This is called by a callback when uz_pmsm_model is opened

% Electrical parameters
R_1=0.1;
L_d=30e-3;
L_q=50e-3;
L_o1=0.01;     
L_o2=0.01;
L_x1=0.01;
L_y1=0.01;
L_x2=0.01;
L_y2=0.01;
L_zero=0.01;
psi_pm=0.05;
polepair=5;
ts=1/1e6;       % hmm vlt ändern

max_overload = 4.0;

% Natural Sine Wave
amplitude_sine = 1;
frequency_sine = 10;
gamma = pi/9;
tl1 = [1  cos(6*gamma) cos(12*gamma)   cos(gamma)  cos(7*gamma) cos(13*gamma)  cos(2*gamma) cos(8*gamma) cos(14*gamma)];
tl2 = [0  sin(6*gamma) sin(12*gamma)   sin(gamma)  sin(7*gamma) sin(13*gamma)  sin(2*gamma) sin(8*gamma) sin(14*gamma)];
tl3 = [1             1             1 cos(3*gamma)  cos(3*gamma)  cos(3*gamma)  cos(6*gamma) cos(6*gamma)  cos(6*gamma)];
tl4 = [0             0             0 sin(3*gamma)  sin(3*gamma)  sin(3*gamma)  sin(6*gamma) sin(6*gamma)   sin(6*gamma)];
tl5 = [1 cos(12*gamma)  cos(6*gamma) cos(5*gamma) cos(17*gamma) cos(11*gamma) cos(10*gamma) cos(4*gamma) cos(16*gamma)];
tl6 = [0 sin(12*gamma)  sin(6*gamma) sin(5*gamma) sin(17*gamma) sin(11*gamma) sin(10*gamma) sin(4*gamma) sin(16*gamma)];
tl7 = [1  cos(6*gamma) cos(12*gamma) cos(7*gamma) cos(13*gamma)    cos(gamma) cos(14*gamma) cos(2*gamma)  cos(8*gamma)];
tl8 = [0  sin(6*gamma) sin(12*gamma) sin(7*gamma) sin(13*gamma)    sin(gamma) sin(14*gamma) sin(2*gamma)  sin(8*gamma)];
tl9 = [1/2 1/2 1/2 -1/2 -1/2 -1/2 1/2 1/2 1/2];
c = 2/9*cat(1,tl1,tl2,tl3,tl4,tl5,tl6,tl7,tl8,tl9);


% Controller parameter
ts_regler=1/20e3;
tau_d=L_d/R_1;
tau_q=L_q/R_1;
tau_sum=2*ts_regler;
% Parallel PID
k_p_d=100;%L_d/(2*tau_sum);
k_p_q=100;%L_q/(2*tau_sum);
k_i_d=1000;%R_1/(2*tau_sum);
k_i_q=1000;%R_1/(2*tau_sum);

% Mechanical parameters
inertia=0.001;
friction_coefficient=0.001;
static_friction_torque=0.01;

% Simulation settings
simulate_mechanical=true;
simulate_open_loop=true;
setpoint_step=10.0;
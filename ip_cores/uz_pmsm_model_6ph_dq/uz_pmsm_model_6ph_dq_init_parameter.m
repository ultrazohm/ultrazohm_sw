%% Parameter file

%% Simulation Parameters
ts_isr = 1/10000;
ts_pmsm = 1e-6;

%% Electric Parameters
R_1 = 31.3;        % phase resistance in Ohm
psi_pm = 0.072;    % flux linkage in Vs
L_d = 0.46;       % d-axis inductance in H
L_q = 0.46;       % q-axis inductance in H
L_x = 0.08;       %assuming from other papers
L_y = 0.08;
L_z1 = 0.08;
L_z2 = 0.08;

polepair = 3;       % number of pole pairs

%% Transformation Matrix
gamma = pi/6;
tl1 = [1  cos(4*gamma) cos(8*gamma)   cos(1*gamma)  cos(5*gamma) cos(9*gamma)];
tl2 = [0  sin(4*gamma) sin(8*gamma)   sin(1*gamma)  sin(5*gamma) sin(9*gamma)];
tl3 = [1  cos(5*4*gamma) cos(5*8*gamma)   cos(5*1*gamma)  cos(5*5*gamma) cos(5*9*gamma)];
tl4 = [0  sin(5*4*gamma) sin(5*8*gamma)   sin(5*1*gamma)  sin(5*5*gamma) sin(5*9*gamma)];
tl5 = [1  cos(3*4*gamma) cos(3*8*gamma)   cos(3*1*gamma)  cos(3*5*gamma) cos(3*9*gamma)];
tl6 = [0  sin(3*4*gamma) sin(3*8*gamma)   sin(3*1*gamma)  sin(3*5*gamma) sin(3*9*gamma)];
c = 2/6*cat(1,tl1,tl2,tl3,tl4,tl5,tl6);

%% Controller Parameters Parallel PI
tau_d=L_d/R_1;
tau_q=L_q/R_1;
tau_sum=2*ts_isr;
k_p_d=0.5;%L_d/(2*tau_sum);
k_p_q=0.5;%L_q/(2*tau_sum);
k_i_d=50;%R_1/(2*tau_sum);
k_i_q=50;%R_1/(2*tau_sum);

%% Mechanical Parameters
inertia=0.001;
friction_coefficient=0.001;
static_friction_torque=0.001;
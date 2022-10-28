%% Parameter file

%% Simulation Parameters
ts_isr = 1/10000;
ts_pmsm = 1e-6;

%% Electric Parameters
R_1 = 31.3;        % phase resistance in Ohm
psi_pm = 0.072;    % flux linkage in Vs
L_d = 0.46;       % d-axis inductance in H
L_q = 0.46;       % q-axis inductance in H
L_x1 = 0.08;       %assuming from other papers
L_y1 = 0.08;
L_x2 = 0.08;
L_y2 = 0.08;
L_x3 = 0.08;
L_y3 = 0.08;
L_zero = 0.08;
polepair = 3;       % number of pole pairs

%% Transformation Matrix
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
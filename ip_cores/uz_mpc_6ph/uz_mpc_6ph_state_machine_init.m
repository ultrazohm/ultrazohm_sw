clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;        % IP core clock freq in Hz
t_clock = 1/f_clock;    % IP core sample time in s

f_ADC =100e3;           % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;        % ADC sample time in s
Ts = t_ADC;

% amplitude of sinusoidal signal sources
A = 0.1;

% machine parameters
Rs = 0.19;              % Phase resistance in Ohm
psi_pm = 0.19;          % PM flux linkage in Vs
Ld = 20.0e-3;            % d-inductance in H
Lq = 60.4e-3;            % q-inductance in H
Lx = 30.0e-3;            % x-inductance in H
Ly = 30.0e-3;            % y-inductance in H
p = 5;                  % pole pairs

VR = 400;               % Rated eff. line-line voltage in V
IR = 7.071;             % Rated eff. phase current in A
nR = 3000;              % Rated mechanical speed in 1/min

% p.u. base units acc. to T.Geyer, Model predictive control of high power
% converters and industrial drives. Hoboken, NJ, USA: Wiley, 2016, Chapter 2.1.2
VB = sqrt(2/3)*VR; 
IB = sqrt(2)*IR;
omegaB = nR*2*pi()/60*p;
ZB = VB/IB;
LB = ZB/omegaB;
SB = 3/2 *VB*IB;
psiB = VB/omegaB;
TB = psiB*IB;

%pre calculated constants - check results regarding fixd_type_constants!!!
Rs_over_ZB = Rs/ZB;
Ts_times_ZB_over_Ld = Ts*ZB/Ld;
Ts_times_ZB_over_Lq = Ts*ZB/Lq;
Ts_times_ZB_over_Lx = Ts*ZB/Lx;
Ts_times_ZB_over_Ly = Ts*ZB/Ly;
Ld_over_LB = Ld/LB;
Lq_over_LB = Lq/LB;
Ld_minus_Lq_over_LB = (Ld-Lq)/LB;
psi_pm_over_psiB = psi_pm/psiB;

% fixed-point data types 
fixdt_type_dq_currents = fixdt(1,27,16);
fixdt_type_xy_currents = fixdt(1,18,11);
fixdt_type_dqxy_ref_currents = fixdt(1,18,15);
fixdt_type_dqxy_voltages = fixdt(1,27,24);
fixdt_type_angle = fixdt(1,24,20);
fixdt_type_sin_cos = fixdt(1,18,16);
fixdt_type_lambda = fixdt(0,18,17);
fixdt_type_polepairs = fixdt(0,32,0);
fixdt_type_max_current = fixdt(0,18,15);
fixdt_type_constants = fixdt(1,18,15);      % check range!!!
fixdt_type_speed = fixdt(1,18,15);
fixdt_type_voltage = fixdt(1,18,15);
fixdt_type_squared_current_error = fixdt(0,27,22);
fixdt_type_delta_u_costs = fixdt(0,27,24);

% reference values for simulation
fixdt_type_vsd = fixdt(1,18,15);
v_dc = 565.0;
id_ref = 0.0;
iq_ref = 5.0;
ix_ref = 0.0;
iy_ref = 0.0;
n_rpm = 1000.0;
omega_m = n_rpm*pi/30;

lambda_d = 1.0;
lambda_q = 1.0;
lambda_x = 1.0;
lambda_y = 1.0;
lambda_u = 0.0;

% parameters for sine waves
f = n_rpm/60.0*p;     % fundamental frequency
Harmonic_Orders = [3 5 7 9 11 13 15 17 19 21];
                        %3    5    7    9   11   13   15    17   19    21
Harmonic_Amplitudes = [0.00 0.0 0.0 0.00 0.00 0.00 0.000 0.00 0.00 0.000];


%simulation control model motor testbench
RDSon = 0.01;
J = 1e-4;
C_dc_link = 800e-6;

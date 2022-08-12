clear
clc

hdlsetuptoolpath('ToolName','Xilinx Vivado','ToolPath',...
 'C:\Xilinx\Vivado\2020.1\bin\vivado.bat');

f_clock = 100e6;        % IP core clock freq in Hz
t_clock = 1/f_clock;    % IP core sample time in s

f_ADC =100e3;           % ADC interrupt freq in Hz
t_ADC = 1/f_ADC;        % ADC sample time in s
Ts = t_ADC;

% machine parameters
Rs = 0.19;              % Phase resistance in Ohm
psi_pm = 0.19;          % PM flux linkage in Vs
Ld = 2.0e-3;            % d-inductance in H
Lq = 6.4e-3;            % q-inductance in H
Lx = 3.0e-3;            % x-inductance in H
Ly = 3.0e-3;            % y-inductance in H
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
fixdt_type_angle = fixdt(1,24,20);
fixdt_type_sin_cos = fixdt(1,18,16);
fixdt_type_lambda = fixdt(0,18,18);
fixdt_type_polepairs = fixdt(0,32,0);
fixdt_type_max_current = fixdt(0,18,15);
fixdt_type_constants = fixdt(1,18,15);      % check range!!!
fixdt_type_speed = fixdt(1,18,6);
fixdt_type_voltage = fixdt(1,18,15);

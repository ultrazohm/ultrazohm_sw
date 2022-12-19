%Init Script for Parameter Identification Simscape Modell

%Author: Philipp Gebhardt, Dennis Hufnagel
%Date May 2022

%The Script considers the following machine


clc
clear
addpath('subsystem_references','simscape_references','function_references'); 

%Busses needed for connections---------------------------------------------
load('Busses.mat');

% VSD Matrix --------------------------------------------------------------
gamma = pi/6;
tl1 = [1  cos(4*gamma) cos(8*gamma)   cos(1*gamma)  cos(5*gamma) cos(9*gamma)];
tl2 = [0  sin(4*gamma) sin(8*gamma)   sin(1*gamma)  sin(5*gamma) sin(9*gamma)];
tl3 = [1  cos(5*4*gamma) cos(5*8*gamma)   cos(5*1*gamma)  cos(5*5*gamma) cos(5*9*gamma)];
tl4 = [0  sin(5*4*gamma) sin(5*8*gamma)   sin(5*1*gamma)  sin(5*5*gamma) sin(5*9*gamma)];
tl5 = [1  cos(3*4*gamma) cos(3*8*gamma)   cos(3*1*gamma)  cos(3*5*gamma) cos(3*9*gamma)];
tl6 = [0  sin(3*4*gamma) sin(3*8*gamma)   sin(3*1*gamma)  sin(3*5*gamma) sin(3*9*gamma)];
c = 2/6*cat(1,tl1,tl2,tl3,tl4,tl5,tl6);
VSD = single(c);
inv_VSD = single(inv(c));

% Simulation parameters----------------------------------------------------
d_f_hardware= 200000;               % [Hz] simluation freq of hardware
d_f_states = 20000;                 % [Hz] simulation freq of stateflows

%Additional parameters-----------------------------------------------------
d_Rds_on = 0.0061;                  % [Ohm] Rds_on of MOSFETs
V_DC=24;                            % [V] DC link voltage
d_y_max=10;                         % [V] limit of FOC PI-controllers
d_y_min=-d_y_max;                   % [V] limit of FOC PI-controllers
d_i_max=15;                         % [A] limit of SpeedCont. PI-controller
d_i_min=-d_i_max;                   % [A] limit of SpeedCont. PI-controller

%Motor parameters----------------------------------------------------------
% Bühler Typ BLDC_1_25_058_201 
d_I_n =8;                           % [A] rated current
d_V_n = 24;                         % [V] rated voltage
d_n_n = 3200;                       % [1/min] rated speed
d_R_ph_ph = 0.089*2;                % [Ohm] Stator phase to phase resistance
d_L_ph_ph = 0.0003*2;               % [H] connection inductivity phase-phase
d_R_ph = d_R_ph_ph/2;               % [Ohm] Stator phase resitance
d_L_0  = 0.00010;                         % zero-sequence inductivity
d_L_ph = d_L_ph_ph/2;               % [H] Phase to phase inductivity
d_L_d = 0.00031;                    % [H] d-Axes inductivity  
d_L_q = 0.00033;                    % [H] q-Axes inductivity
d_p = 4;                            % Number ofPolepairs
d_J_m = 0.0000165;                  % [kgm^2]inertia
d_psi_pm = 0.0075;                  % [V*s] Permanent-Flux 


d_Kp_id=0.369;                      % [V/A] d-current controller P-Gain
d_Kp_iq=0.369;                      % [V/A] q-current controller P-Gain
d_Kp_n=0.198;                       % [As/rad] speed controller P-Gain
d_Ki_id=162.47;                     % [V/A] d-current controller I-Gain
d_Ki_iq=162.47;                     % [V/A] q-current controller I-Gain
d_Ki_n=1.982;                       % [As/rad] speed controller I-Gain

% Encoder------------------------------------------------------------------
% Kübler TYP 5802
d_incEncoder = 5000;                % Number of increments
d_J_Encoder = 1.8e-26;              % [kgm^2] encoder inertia

% coupling of  Testmotor and encoder---------------------------------------
% RW BK5 300
d_J_Coupling_M_E = 2e-6;        	% [kgm^2*] coupling inertia
d_c_Coupling_M_E = 1500;        	% [Nm/rad] coupling stiffness 

% coupling of Testmotor and loadmachine------------------------------------
% RW BK5 30
d_J_Coupling_M_Ms = 2e-20;      	% [kgm^2*] coupling inertia
d_c_Coupling_M_Ms = 1500;         	% [Nm/rad] coupling stiffness 

% coupling of measuringshaft and loadmachine-------------------------------
% RW BK5 30

d_J_Coupling_Ms_L = 2e-6;        	% [kgm^2*] coupling inertia
d_c_Coupling_Ms_L = 1500;       	% [Nm/rad] coupling stiffness


% measuring shaft----------------------------------------------------------
% simplified as long torsion shaft of one diameter

d_l_Ms=0.5;                                             	% [m] length
d_d_Ms=0.016;                                            	% [m] diameter
d_G_Ms=8*(10^10);                                           % [N/(m^2)] Shear modulus of steel
d_rho_Ms=7860;                                          	% [g/(m^3)] Density of steel
d_J_Ms_M = 0.5*0.5*((0.5*d_d_Ms)^4)*3.14*d_l_Ms*d_rho_Ms;	% [kgm^2] inertia loadside of measuringshaft
d_J_Ms_L =d_J_Ms_M;                                     	% [kgm^2] inertia of motorside of measuringshaft
d_c_Ms = d_G_Ms*3.14*(d_d_Ms^4)/(32*d_l_Ms);               	% [Nm/rad] stiffness of measuringshaft

% Loadmachine--------------------------------------------------------------
d_J_Loadmachine = 18e-6;            % [kgm^2] Loadinertia
d_J_Loaddisc = 0.00000679;       	% [kgm^2] Loadinertia of additional loaddisc

%  Friction----------------------------------------------------------------
d_M_stribeck = 0.02;             	% [Nm] Stribeck Friction Torque
d_v_stribeck = 1e-18;             	% [rad/s] Stribeck speed
d_d_viscous  = 0.0001963;         	% [Nms/rad] Viscous friction torque constant
d_M_coulomb = 0.01056;          	% [Nm] Coloumb Friction Torque


%Simplification as two mass system

d_J_Motorside = d_J_Encoder + d_J_m  + ....
d_J_Coupling_M_E+d_J_Coupling_M_Ms+d_J_Ms_M;    % [kgm^2]Total loadinertia
d_J_Loadside =   d_J_Ms_L+d_J_Loadmachine + .... 
d_J_Coupling_Ms_L;                              % [kgm^2]Total motorinertia
d_c_TMS = d_c_Ms;                               % [Nm/rad] Stiffness of two mass system
d_d_TMS=0.005;   

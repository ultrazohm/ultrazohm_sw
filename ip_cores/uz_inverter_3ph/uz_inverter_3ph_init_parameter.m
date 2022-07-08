%% Parameter for simulation of inverter_model.slx

%% Init
udc = 560; 
pslcontrol = 1;

%% Solver and Model
nonlinear_iterations = 4;
ext_clock = 100e6;  % defined here for ts calculation - not set automatically in IP-core generation!
oversampling = 25;  % defined here for ts calculation - not set automatically in IP-core generation!
ts_inverter=oversampling/ext_clock*nonlinear_iterations;
%% Init parameters
clc
clear
close all
set(0,'defaulttextinterpreter','latex')

uz_pmsm_model_init_parameter;
mdl='uz_pmsm_model';
out=sim(mdl);

%% Plot Simulink
%                         Name                   BlockPath                            
%                         _____________________  ____________________________________ 
%    1  [1x1 Signal]      u_d                    uz_pmsm_model/Data Type Conversion  
%    2  [1x1 Signal]      u_q                    uz_pmsm_model/Data Type Conversion1 
%    3  [1x1 Signal]      i_q_soll               uz_pmsm_model/Data Type Conversion10
%    4  [1x1 Signal]      load_torque            uz_pmsm_model/Data Type Conversion15
%    5  [1x1 Signal]      torque_hdl             uz_pmsm_model/Data Type Conversion5 
%    6  [1x1 Signal]      i_d_hdl                uz_pmsm_model/Data Type Conversion6 
%    7  [1x1 Signal]      i_q_hdl                uz_pmsm_model/Data Type Conversion7 
%    8  [1x1 Signal]      omega_mech_output_hdl  uz_pmsm_model/Data Type Conversion8 
%    9  [1x1 Signal]      i_d_soll               uz_pmsm_model/Data Type Conversion9 
%   10  [1x1 Signal]      ''                     uz_pmsm_model/PID Controller        
%   11  [1x1 Signal]      ''                     uz_pmsm_model/PID Controller1       
%   12  [1x1 Signal]      iq_regler              uz_pmsm_model/Rate Transition11     
%   13  [1x1 Signal]      id_regler              uz_pmsm_model/Rate Transition12     
%   14  [1x1 Signal]      u_q_input              uz_pmsm_model/Step1                 
%   15  [1x1 Signal]      i_d                    uz_pmsm_model/uz_pmsm_model/pmsm   
sim.ud=out.logsout{1}.Values.Data;
sim.uq=out.logsout{2}.Values.Data;
sim.id=out.logsout{6}.Values.Data;
sim.iq=out.logsout{7}.Values.Data;
sim.speed=out.logsout{8}.Values.Data;
sim.time=out.logsout{8}.Values.Time-0.00005;
sim.time=sim.time*1e3-199.8;
sim.id_soll=out.logsout{9}.Values.Data;
sim.id_soll_time=out.logsout{9}.Values.Time*1e3-199.8;
sim.iq_soll=out.logsout{3}.Values.Data;

figure(1)
subplot(2,1,1)
title('Simulation results');
grid on
hold on

plot(sim.time,sim.ud); % u_d input
plot(sim.time,sim.id); % i_d
legend('U_d', 'i_d');

subplot(2,1,2)
grid on
hold on
plot(sim.time,sim.uq); % u_d input
plot(sim.time,sim.id); % i_d
legend('U_q', 'i_q');

%% Plot FPGA version
%
% 1: time
% 2: i_q
% 3: i_d
% 4: speed
% 5: ud
measurements=readmatrix('no_output_delay.csv');
first_nonzero=find(measurements(:,5),1,'first');
first_nonzero=first_nonzero;
time_offset=measurements(first_nonzero,1)-0.2;
measurements(:,1)=measurements(:,1)-time_offset;
measurment.id=measurements(first_nonzero:end,3);
measurment.iq=measurements(first_nonzero:end,2);
measurment.time=measurements(first_nonzero:end,1)*1e3-199.8;
measurment.sollwert=measurements(first_nonzero:end,5);
measurment.speed=measurements(first_nonzero:end,4);
%measurment.uq=-measurment.ud;



%% Matlab2Tikz options
extraaxisoptions = ['y tick label style={/pgf/number format/.cd, fixed,precision=2}'...
    ,',ylabel style={yshift=-0.2cm,font=\small}'...
    ,',xlabel style={font=\small}'...
];
PPI = 600;
%% Compare
close all
figure
grid on
hold on
box on
stairs(sim.id_soll_time,sim.id_soll,'Color', [0 127/255 0]); % u_d input
plot(measurment.time, measurment.id,'rx'); % i_d
plot(sim.time,sim.id,'b'); % i_d

xlabel('Time (ms)');
%ylabel('Current (A)');
xlim([0.199 1.5]);
title('')

cleanfigure('targetResolution',300);
matlab2tikz('id_step.tikz','showInfo', false,   ...
    'width', '\fwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);

figure
grid on
hold on
box on
stairs(sim.id_soll_time,sim.iq_soll,'Color', [0 127/255 0]); % u_d input
plot(sim.time,sim.iq,'b'); % i_d
plot(measurment.time, measurment.iq,'rx'); % i_d
xlabel('Time (ms)');
%ylabel('Current (A)');
xlim([0.199 1.5]);
title('')
%legend('i_d set point', 'i_d sim','i_d meas','i_q set point','i_q sim','i_q meas', 'FontSize', 18,'Location','eastoutside');
%cleanfigure('targetResolution',300);
%matlab2tikz('iq_step.tex','width', '\fwidth' );
cleanfigure('targetResolution',600);
matlab2tikz('iq_step.tikz','showInfo', false,  ...
    'width', '\fwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);

% calculate error
sim_id=timeseries(sim.id,sim.time);
meas_id=timeseries(measurment.id,measurment.time);
[sim_id,meas_id]=synchronize(sim_id,meas_id,'union');

sim_iq=timeseries(sim.iq,sim.time);
meas_iq=timeseries(measurment.iq,measurment.time);
[sim_iq,meas_iq]=synchronize(sim_iq,meas_iq,'union');

sim_omega=timeseries(sim.speed,sim.time);
meas_omega=timeseries(measurment.speed,measurment.time);
[sim_omega,meas_omega]=synchronize(sim_omega,meas_omega,'union');

abs_error_id=( sim_id-meas_id )*1e3;
abs_error_iq=( sim_iq-meas_iq )*1e3;
abs_error_omega=( sim_omega-meas_omega );

figure
plot(abs_error_id,'r');
grid on
hold on
xlabel('Time (ms)');
%ylabel('Current (A)');
plot(abs_error_iq,'b');
%legend('i_d error','i_q error','Location','eastoutside');
xlabel('Time (ms)');
ylabel('');
xlim([0.199 5]);
title('')
%cleanfigure('targetResolution',300);
%matlab2tikz('step_error.tex','width', '\fwidth' );
cleanfigure('targetResolution',600);
matlab2tikz('step_error.tikz','showInfo', false,  ...
    'width', '\fwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);

%saveas(gcf,'referance_ip_core_measurment_comparision','svg');
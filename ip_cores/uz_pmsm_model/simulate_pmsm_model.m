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
%    3  [1x1 Signal]      load_torque            uz_pmsm_model/Data Type Conversion15
%    4  [1x1 Signal]      i_d_hdl                uz_pmsm_model/Demux                 
%    5  [1x1 Signal]      i_q_hdl                uz_pmsm_model/Demux                 
%    6  [1x1 Signal]      omega_mech_output_hdl  uz_pmsm_model/Demux                 
%    7  [1x1 Signal]      torque_hdl             uz_pmsm_model/Demux                 
%    8  [1x1 Signal]      i_d_ref                uz_pmsm_model/PMSM_flux_based       
%    9  [1x1 Signal]      i_q_ref                uz_pmsm_model/PMSM_flux_based       
%   10  [1x1 Signal]      ''                     uz_pmsm_model/Rate Transition7      
%   11  [1x1 Signal]      u_d_input              uz_pmsm_model/Step2                 
%   12  [1x1 Signal]      u_q_input              uz_pmsm_model/Step3                 
%   13  [1x1 Signal]      error_i_d              uz_pmsm_model/Sum                   
%   14  [1x1 Signal]      error_i_q              uz_pmsm_model/Sum1   
sim.ud=out.logsout{1}.Values.Data;
sim.uq=out.logsout{2}.Values.Data;
sim.id=out.logsout{4}.Values.Data;
sim.iq=out.logsout{5}.Values.Data;
sim.speed=out.logsout{6}.Values.Data;
sim.time=out.logsout{1}.Values.Time-0.000001;

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
A=readmatrix('measurment_with_speed.csv');
measurements=A(1:100000,:);
first_nonzero=find(measurements(:,5),1,'first');
first_nonzero=first_nonzero;
time_offset=measurements(first_nonzero,1)-0.2;
measurements(:,1)=measurements(:,1)-time_offset;
measurment.id=measurements(first_nonzero:end,3);
measurment.iq=measurements(first_nonzero:end,2);
measurment.time=measurements(first_nonzero:end,1);
measurment.ud=measurements(first_nonzero:end,5);
measurment.speed=measurements(first_nonzero:end,4);
measurment.uq=-measurment.ud;
%%
figure(2)
subplot(2,1,1)
title('Measured values');
grid on
hold on

plot(measurment.time, measurment.ud); % u_d input
plot(measurment.time, measurment.id); % i_d
legend('U_d', 'i_d');

subplot(2,1,2)
grid on
hold on
plot(measurment.time, measurment.uq); % u_d input
plot(measurment.time, measurment.iq); % i_d
legend('U_q', 'i_q');

%% Compare
figure(3)
subplot(2,3,1)
title('Compare simulation and measurement');
grid on
hold on
plot(sim.time,sim.ud,'LineWidth',3); % u_d input
plot(sim.time,sim.id,'LineWidth',3); % i_d
plot(measurment.time, measurment.ud,'--','LineWidth',3); % u_d input
plot(measurment.time, measurment.id,'--','LineWidth',3); % i_d
legend('U_d sim', 'i_d sim','u_d meas','i_d meas', 'FontSize', 18);
xlim([0.15 2]);
title('Step Response $I_d$', 'FontSize', 20);
xlabel('Time in s', 'FontSize', 18);
ylabel('Current in A, Voltage in V', 'FontSize', 18);

subplot(2,3,2)
grid on
hold on
plot(sim.time,sim.uq,'LineWidth',3); % u_d input
plot(sim.time,sim.iq,'LineWidth',3); % i_d
plot(measurment.time, measurment.uq,'--','LineWidth',3); % u_d input
plot(measurment.time, measurment.iq,'--','LineWidth',3); % i_d
legend('U_q sim', 'i_q sim','u_q meas','i_q meas', 'FontSize', 18);
xlim([0.15 2]);
title('Step Response $I_q$', 'FontSize', 20);
xlabel('Time in s', 'FontSize', 18);
ylabel('Current in A, Voltage in V', 'FontSize', 18);

subplot(2,3,3)
grid on
hold on
plot(sim.time,sim.speed,'LineWidth',3);
plot(measurment.time, measurment.speed,'--','LineWidth',3);
%legend('U_q sim', 'i_q sim','u_q meas','i_q meas');
xlim([0.15 2]);
title('Rotational speed', 'FontSize', 20);
legend('\omega_{mech} sim','\omega_{mech} meas', 'FontSize', 18);
xlabel('Time in s', 'FontSize', 18);
ylabel('Rotational speed in $\frac{1}{s}$', 'FontSize', 18);

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

abs_error_id=( sim_id-meas_id );
abs_error_iq=( sim_iq-meas_iq );
abs_error_omega=( sim_omega-meas_omega );

subplot(2,3,4)
plot(abs_error_id,'LineWidth',3);
grid on
title('Error $I_d$', 'FontSize', 20);
legend('i_d error', 'FontSize', 18);
xlabel('Time in s', 'FontSize', 18);
ylabel('Current in A', 'FontSize', 18);

subplot(2,3,5)
plot(abs_error_iq,'LineWidth',3);
grid on
title('Error $I_q$', 'FontSize', 20);
legend('i_q error', 'FontSize', 18);
xlabel('Time in s', 'FontSize', 18);
ylabel('Current in A', 'FontSize', 18);

subplot(2,3,6)
plot(abs_error_omega,'LineWidth',3);
grid on
title('Rotational speed', 'FontSize', 20);
legend('\omega_{mech} error', 'FontSize', 18);
xlabel('Time in s', 'FontSize', 18);
ylabel('Rotational speed in $\frac{1}{s}$', 'FontSize', 18);
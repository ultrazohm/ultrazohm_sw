%% Init parameters
clc
clear
close all
uz_pmsm_model_init_parameter;
mdl='uz_pmsm_model';
out=sim(mdl);

%% Plot Simulink


%    1  [1x1 Signal]      u_d_input   uz_pmsm_model/Step2        
%    2  [1x1 Signal]      u_q_input   uz_pmsm_model/Step3        
%    3  [1x1 Signal]      i_d         uz_pmsm_model/uz_pmsm_model
%    4  [1x1 Signal]      i_q         uz_pmsm_model/uz_pmsm_model
%    5  [1x1 Signal]      omega_mech  uz_pmsm_model/uz_pmsm_model
%    6  [1x1 Signal]      torque      uz_pmsm_model/uz_pmsm_model
sim.ud=out.logsout{1}.Values.Data;
sim.uq=out.logsout{2}.Values.Data;
sim.id=out.logsout{3}.Values.Data;
sim.iq=out.logsout{4}.Values.Data;
sim.time=out.logsout{1}.Values.Time-0.000001;

figure(1)
subplot(2,1,1)
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
% 4: u_d
A=readmatrix('vector_core.csv');
measurements=A(1:100000,:);
first_nonzero=find(measurements(:,4),1,'first');
first_nonzero=first_nonzero-1;
time_offset=measurements(first_nonzero,1)-0.2;
measurements(:,1)=measurements(:,1)-time_offset;
measurment.id=measurements(first_nonzero:end,3);
measurment.iq=measurements(first_nonzero:end,2);
measurment.time=measurements(first_nonzero:end,1);
measurment.ud=measurements(first_nonzero:end,4);
measurment.uq=-measurment.ud;
%%
figure(2)
subplot(2,1,1)
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
subplot(2,1,1)
grid on
hold on
plot(sim.time,sim.ud); % u_d input
plot(sim.time,sim.id); % i_d
plot(measurment.time, measurment.ud,'x--'); % u_d input
plot(measurment.time, measurment.id,'x--'); % i_d
legend('U_d sim', 'i_d sim','u_d meas','i_d meas');
xlim([0.15 0.5]);

subplot(2,1,2)
grid on
hold on
plot(sim.time,sim.uq); % u_d input
plot(sim.time,sim.iq); % i_d
plot(measurment.time, measurment.uq,'x--'); % u_d input
plot(measurment.time, measurment.iq,'x--'); % i_d
legend('U_q sim', 'i_q sim','u_q meas','i_q meas');
xlim([0.15 0.5]);



%% timeseries

sim_id=timeseries(sim.id,sim.time);
meas_id=timeseries(measurment.id,measurment.time);
[sim_id,meas_id]=synchronize(sim_id,meas_id,'union');
figure
hold on
plot(sim_id,'o');
plot(meas_id,'x');
% difference
abs_error_id=( sim_id-meas_id );
figure
plot(abs_error_id);
title('Error');

%% difference

% 
% one_second_index=find(abs(measurment.time-1.0) < 0.00001);
% meas_one_sec.id=measurment.id(1:one_second_index);
% meas_one_sec.iq=measurment.iq(1:one_second_index);
% time_index_0_15=find(abs(sim.time-0.15) < 0.00001);
% time_index_0_5=find(abs(sim.time-0.5) < 0.00001);
% sim_resampled.id=sim.id(time_index_0_15:time_index_0_5);
% sim_resampled.id= cast(sim_resampled.id,'double');
% fs_sim=1/20e3;
% time_resample=0.15:fs_sim:0.5;
% sim_resampled.id=resample(sim_resampled.id,1,50);
% 
% figure
% hold on
% plot(time_resample,sim_resampled.id);
% plot(sim.time,sim.id,'--');

%%
%diff.id=sim.id-measurment.id;
%diff.iq=sim.iq-measurment.iq;



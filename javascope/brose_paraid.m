clc
clear
%close all

rs=0.029; % 29
psi_pm=0.007;

%log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/brose_paraid_more_current_longer.parquet');
% brose_paraid_low_pass_corrected_400_800_rpm_plus_minus

log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/brose_paraid_1s_steady_state_minus_0_05_theta_shift_low_pass_1750hz_reversed.parquet');
% brose_paraid_minus_1_shift_only_for_measured_v_dq
%log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/brose_paraid_100rpm_long_steady_state.parquet');

%
log=log(log.enable==1,:);
different_speeds=unique(log.pm_speed_rpm_ref);

log=log(log.pm_speed_rpm_ref==different_speeds(4),:);
% data = table2array(log);
% f_sample_in_Hz=10000;
% f_cuttoff_in_Hz=100;
% % Design a low-pass filter (e.g., Butterworth filter)
% Fs = f_sample_in_Hz;  % Sampling frequency (adjust as needed)
% Fc = f_cuttoff_in_Hz;   % Cutoff frequency
% [b, a] = butter(4, Fc / (Fs / 2));  % 4th order low-pass Butterworth
% 
% % Apply the filter column-wise
% filteredData = zeros(size(data));
% for col = 1:size(data, 2)
%     filteredData(:, col) = filtfilt(b, a, data(:, col));  % Zero-phase filtering
% end
% 
% % Convert filtered data back to table
% log = array2table(filteredData, 'VariableNames', log.Properties.VariableNames);



figure
subplot(4,1,1)
plot(log.time,log.dut_vd);
hold on
plot(log.time,log.dut_vd_ref);
legend('vd','vd_ref');

subplot(4,1,2)
plot(log.time,log.dut_vq);
hold on
plot(log.time,log.dut_vq_ref);
legend('vq','vq_ref');

subplot(4,1,3)
plot(log.time,log.dut_id);
hold on
plot(log.time,log.dut_id_set);
legend('id','id_ref');

subplot(4,1,4)
plot(log.time,log.dut_iq);
hold on
plot(log.time,log.dut_iq_set);
legend('iq','iq_ref');
%%
log=log(abs(log.dut_id_set-log.dut_id)<0.1,:); % only steady state
log=log(abs(log.dut_iq_set-log.dut_iq)<0.1,:);

log.omega_el=log.dut_speed_rpm/60*2*pi*5;

log.psi_d=(log.dut_vq-rs*log.dut_iq)./log.omega_el;
log.psi_q=-(log.dut_vd-rs*log.dut_id)./log.omega_el;

[log.operating_point, ~] = findgroups(log.dut_iq_set, log.dut_id_set);


groupedTable = groupsummary(log, 'operating_point', 'mean');
groupedTable=groupedTable(groupedTable.mean_dut_iq_set>=0,:); % only positive q currents for simple testing

%figure
%scatter3(log.dut_iq_set,log.dut_id_set,log.psi_d);
%%

no_d_current=log(log.dut_id_set==0.0,:);
no_q_current=log(log.dut_iq_set<1.0,:);
no_d_current_groupedTable = groupsummary(no_d_current, 'operating_point', 'mean');
no_d_current_groupedTable=no_d_current_groupedTable(no_d_current_groupedTable.mean_dut_iq_set>0,:); % only positive q currents for simple testing
no_q_current_groupedTable = groupsummary(no_q_current, 'operating_point', 'mean');
no_q_current_groupedTable=no_q_current_groupedTable(no_q_current_groupedTable.mean_dut_iq_set>0,:); % only positive q currents for simple testing

figure
plot(no_d_current_groupedTable.mean_dut_iq,no_d_current_groupedTable.mean_psi_q)
title('psi q over q current at id=0')

figure
plot(no_d_current_groupedTable.mean_dut_iq,no_d_current_groupedTable.mean_psi_q./no_d_current_groupedTable.mean_dut_iq)
title('psi q/iq=L_q over q current at id=0')

figure
plot(no_q_current_groupedTable.mean_dut_id,(no_q_current_groupedTable.mean_psi_d)); % 
title('psi d over d current at iq=0.5')

figure
plot(no_q_current_groupedTable.mean_dut_id,(no_q_current_groupedTable.mean_psi_d-psi_pm)./no_q_current_groupedTable.mean_dut_id); % 
title('psi d-psi_pm/id=L_d over q current at iq=0.5')


i_d = groupedTable.mean_dut_id_set;  % x-axis data
i_q = groupedTable.mean_dut_iq_set;  % y-axis data
psi_d = groupedTable.mean_psi_d;      % z-axis data
psi_q = groupedTable.mean_psi_q;      % z-axis data

% Create a grid to interpolate the data for the surface plot
id_lin = linspace(min(i_d), max(i_d), 30);  % Adjust 30 as needed for resolution
iq_lin = linspace(min(i_q), max(i_q), 30);
[Id_grid, Iq_grid] = meshgrid(id_lin, iq_lin);

linearFit_psi_d = fit([i_d, i_q], psi_d, 'poly11');  % 'poly11' fits a linear surface
linearFit_psi_q = fit([i_d, i_q], psi_q, 'poly11');  % 'poly11' fits a linear surface
fitted_l_d=linearFit_psi_d.p10
fitted_psi_pm=linearFit_psi_d.p00
fitted_l_q=linearFit_psi_q.p01
% Evaluate the fitted plane on the grid for plotting
Psi_d_fit = linearFit_psi_d.p00 + linearFit_psi_d.p10 * Id_grid + linearFit_psi_d.p01 * Iq_grid;

%%
figure
scatter3(groupedTable.mean_dut_iq_set,groupedTable.mean_dut_id_set,groupedTable.mean_psi_d,'filled');
title('Psi d')

figure
scatter3(groupedTable.mean_dut_iq_set,groupedTable.mean_dut_id_set,groupedTable.mean_psi_q,'filled');
title('Psi q')

% Plot the scatter plot
figure;
scatter3(i_d, i_q, psi_d, 'filled');
hold on;
% Plot the interpolated surface
% Interpolate the Z values over the grid using scatteredInterpolant
F = scatteredInterpolant(i_d, i_q, psi_d, 'linear', 'none');  % linear interpolation
Psi_d_grid = F(Id_grid, Iq_grid);
surf(Id_grid, Iq_grid, Psi_d_grid, 'EdgeColor', 'none', 'FaceAlpha', 0.5);  % Semi-transparent surface

% Plot the fitted linear surface
surf(Id_grid, Iq_grid, Psi_d_fit, 'EdgeColor', 'none', 'FaceAlpha', 0.3, 'FaceColor', 'r');  % Red semi-transparent plane

% Add labels and a legend
xlabel('mean\_id\_ref (i_d)');
ylabel('mean\_iq\_ref (i_q)');
zlabel('psi\_d');
legend('Data Points', 'Interpolated Surface', 'Fitted Linear Plane');
title('3D Scatter Plot with Interpolated Surface and Linear Fit');

hold off;

%% Plot idinvidual operating points

local_data=log(log.operating_point==100,:);
figure
subplot(6,1,1)
plot(local_data.time,local_data.dut_vd);
hold on
grid on
plot(local_data.time,local_data.dut_vd_ref);
title('vd');
legend('vd','vd ref');

subplot(6,1,2)
plot(local_data.time,local_data.dut_vq);
hold on
grid on
plot(local_data.time,local_data.dut_vq_ref);
title('vq');
legend('vq','vq ref');

subplot(6,1,3)
plot(local_data.time,local_data.dut_id);
hold on
grid on
plot(local_data.time,local_data.dut_id_set);
title('id');

subplot(6,1,4)
plot(local_data.time,local_data.dut_iq);
hold on
grid on
plot(local_data.time,local_data.dut_iq_set);
title('iq');

subplot(6,1,5)
plot(local_data.time,local_data.dut_speed_rpm);
title('speed in rpm');
hold on
grid on

subplot(6,1,6)
plot(local_data.time,local_data.dut_ia);
title('Phase currents');
hold on
grid on
plot(local_data.time,local_data.dut_ib);
plot(local_data.time,local_data.dut_ic);

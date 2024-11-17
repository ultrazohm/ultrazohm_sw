clc
clear
close all

rs=0.15;
psi_pm=0.0075;
pole_pairs=4;

log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/buehler_paraid_400rpm_3.parquet');

log=log(log.enable==1,:);
% log=log((log.dut_id_set)>-0.5,:); % only steady state

log=log(abs(log.dut_id_set-log.dut_id)<0.1,:); % only steady state
log=log(abs(log.dut_iq_set-log.dut_iq)<0.1,:);

log.omega_el=log.dut_speed_rpm/60*2*pi*pole_pairs;

log.psi_d=(log.dut_vq-rs*log.dut_iq)./log.omega_el;
log.psi_q=-(log.dut_vd-rs*log.dut_id)./log.omega_el;

[log.operating_point, ~] = findgroups(log.dut_iq_set, log.dut_id_set);


groupedTable = groupsummary(log, 'operating_point', 'mean');
groupedTable=groupedTable(groupedTable.mean_dut_iq_set>0,:); % only positive q currents for simple testing

%figure
%scatter3(log.dut_iq_set,log.dut_id_set,log.psi_d);
%%

no_d_current=log(log.dut_id_set==0.0,:);
no_q_current=log(log.dut_iq_set==0.0,:);
no_d_current_groupedTable = groupsummary(no_d_current, 'operating_point', 'mean');
no_d_current_groupedTable=no_d_current_groupedTable(no_d_current_groupedTable.mean_dut_iq_set>=0,:); % only positive q currents for simple testing
no_q_current_groupedTable = groupsummary(no_q_current, 'operating_point', 'mean');
no_q_current_groupedTable=no_q_current_groupedTable(no_q_current_groupedTable.mean_dut_iq_set>=0,:); % only positive q currents for simple testing

figure
plot(no_d_current_groupedTable.mean_dut_iq,no_d_current_groupedTable.mean_psi_q)
title('psi q over q current at id=0')

figure
plot(no_d_current_groupedTable.mean_dut_iq,no_d_current_groupedTable.mean_psi_q./no_d_current_groupedTable.mean_dut_iq)
title('psi q/iq=L_q over q current at id=0')

figure
plot(no_q_current_groupedTable.mean_dut_id,(no_q_current_groupedTable.mean_psi_d)); % 
title('psi d over d current at iq=0.0')

figure
plot(no_q_current_groupedTable.mean_dut_id,(no_q_current_groupedTable.mean_psi_d-psi_pm)./no_q_current_groupedTable.mean_dut_id); % 
title('psi d-psi_pm/id=L_d over q current at iq=0.5')

%%
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
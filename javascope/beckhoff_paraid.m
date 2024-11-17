clc
clear
rs=0.5646;

log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/beckhoff_paraid.parquet');
log=log(log.enable==1,:);

log=log(abs(log.dut_id_set-log.dut_id)<0.1,:); % only steady state
log=log(abs(log.dut_iq_set-log.dut_iq)<0.1,:);

log.omega_el=log.dut_speed_rpm/60*2*pi*4;

log.psi_d=(log.dut_vq_ref-rs*log.dut_iq)./log.omega_el;
log.psi_q=-(log.dut_vd_ref-rs*log.dut_id)./log.omega_el;

[log.operating_point, ~] = findgroups(log.dut_iq_set, log.dut_id_set);
groupedTable = groupsummary(log, 'operating_point', 'mean');

groupedTable=groupedTable(groupedTable.mean_dut_iq_set>0,:); % only positive q currents for simple testing

%figure
%scatter3(log.dut_iq_set,log.dut_id_set,log.psi_d);
%%
figure

scatter3(groupedTable.mean_dut_iq_set,groupedTable.mean_dut_id_set,groupedTable.mean_psi_d,'filled');
title('Psi d')

figure

scatter3(groupedTable.mean_dut_iq_set,groupedTable.mean_dut_id_set,groupedTable.mean_psi_q,'filled');
title('Psi q')

%
i_d = groupedTable.mean_dut_id_set;  % x-axis data
i_q = groupedTable.mean_dut_iq_set;  % y-axis data
psi_d = groupedTable.mean_psi_d;      % z-axis data

% Plot the scatter plot
figure;
scatter3(i_d, i_q, psi_d, 'filled');
hold on;

% Create a grid to interpolate the data for the surface plot
id_lin = linspace(min(i_d), max(i_d), 30);  % Adjust 30 as needed for resolution
iq_lin = linspace(min(i_q), max(i_q), 30);
[Id_grid, Iq_grid] = meshgrid(id_lin, iq_lin);

% Interpolate the Z values over the grid using scatteredInterpolant
F = scatteredInterpolant(i_d, i_q, psi_d, 'linear', 'none');  % linear interpolation
Psi_d_grid = F(Id_grid, Iq_grid);

% Plot the interpolated surface
surf(Id_grid, Iq_grid, Psi_d_grid, 'EdgeColor', 'none', 'FaceAlpha', 0.5);  % Semi-transparent surface

% Fit a linear plane to the data using fit
linearFit = fit([i_d, i_q], psi_d, 'poly11');  % 'poly11' fits a linear surface

fitted_l_d=linearFit.p10;
fitted_psi_pm=linearFit.p00;

% Evaluate the fitted plane on the grid for plotting
Psi_d_fit = linearFit.p00 + linearFit.p10 * Id_grid + linearFit.p01 * Iq_grid;

% Plot the fitted linear surface
surf(Id_grid, Iq_grid, Psi_d_fit, 'EdgeColor', 'none', 'FaceAlpha', 0.3, 'FaceColor', 'r');  % Red semi-transparent plane

% Add labels and a legend
xlabel('mean\_id\_ref (i_d)');
ylabel('mean\_iq\_ref (i_q)');
zlabel('psi\_d');
legend('Data Points', 'Interpolated Surface', 'Fitted Linear Plane');
title('3D Scatter Plot with Interpolated Surface and Linear Fit');

hold off;
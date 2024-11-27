clc
clear
close all

rs=0.029;
pole_pairs=5;
number_of_grid_points=30;

%log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/brose_paraid_more_current_longer.parquet');
%log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/ebm_paraid_3200rpm.parquet');
log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/brose_paraid_1s_steady_state_minus_0_05_theta_shift_low_pass_1750hz_reversed.parquet');

log=log(log.enable==1,:);
different_speeds=unique(log.pm_speed_rpm_ref);

log=log(log.pm_speed_rpm_ref==different_speeds(2),:);
%%
log=calculate_psi(log,pole_pairs,rs);
groupedTable=calculate_average_over_operating_points(log);
groupedTable=groupedTable(groupedTable.mean_dut_iq_set>0,:); % only positive q currents for simple testing
[flux_map,fitted]=calculate_flux_map(groupedTable);
plot_measured_flux_map(flux_map);

%%
fem_q=load('Lenkungsmotor_3ph_Psi_q.mat');
fem_flux_map_q=fem_q.row_data;
fem_flux_map_q.Properties.VariableNames={'i_d','i_q','segments','psi_q'};

fem_d=load('Lenkungsmotor_3ph_Psi_d.mat');
fem_flux_map_d=fem_d.row_data;
fem_flux_map_d.Properties.VariableNames={'i_d','i_q','segments','psi_d'};
fem_flux_map_d.psi_q=fem_flux_map_q.psi_q;
fem_flux_map_d=fem_flux_map_d(fem_flux_map_d.i_d<=0.0,:);
fem_flux_map_d=fem_flux_map_d(fem_flux_map_d.i_d>=-10.0,:);
fem_flux_map_d=fem_flux_map_d(fem_flux_map_d.i_q<=11.0,:);
fem_flux_map_d=fem_flux_map_d(fem_flux_map_d.i_q>=-11.0,:);
plot_measured_flux_map(fem_flux_map_d);
measured_fit.psi_d = fit([fem_flux_map_d.i_d, fem_flux_map_d.i_q], fem_flux_map_d.psi_d, 'poly11');  % 'poly11' fits a linear surface
measured_fit.psi_q = fit([fem_flux_map_d.i_d, fem_flux_map_d.i_q], fem_flux_map_d.psi_q, 'poly11');  % 'poly11' fits a linear surface


% 
flux_map.psi_d_fitted=fitted.psi_d(flux_map.i_d,flux_map.i_q);
flux_map.psi_q_fitted=fitted.psi_q(flux_map.i_d,flux_map.i_q);
approx=approximate_flux_map_for_surf(flux_map,fitted);

plot_measured_vs_fitted_flux(flux_map,approx);


% Evaluate the fitted plane on the grid for plotting
% id_lin = linspace(min(i_d), max(i_d), number_of_grid_points);  % Adjust 30 as needed for resolution
% iq_lin = linspace(min(i_q), max(i_q), number_of_grid_points);
% [Id_grid, Iq_grid] = meshgrid(id_lin, iq_lin);
% Psi_d_fit = linearFit_psi_d.p00 + linearFit_psi_d.p10 * Id_grid + linearFit_psi_d.p01 * Iq_grid;
%%

% no_d_current=log(log.dut_id_set==0.0,:);
% no_q_current=log(log.dut_iq_set<1.0,:);
% no_d_current_groupedTable = groupsummary(no_d_current, 'operating_point', 'mean');
% no_d_current_groupedTable=no_d_current_groupedTable(no_d_current_groupedTable.mean_dut_iq_set>0,:); % only positive q currents for simple testing
% no_q_current_groupedTable = groupsummary(no_q_current, 'operating_point', 'mean');
% no_q_current_groupedTable=no_q_current_groupedTable(no_q_current_groupedTable.mean_dut_iq_set>0,:); % only positive q currents for simple testing

%%
% Plot the scatter plot
% figure;
% scatter3(i_d, i_q, psi_d, 'filled');
% hold on;
% % Plot the interpolated surface
% % Interpolate the Z values over the grid using scatteredInterpolant
% F = scatteredInterpolant(i_d, i_q, psi_d, 'linear', 'none');  % linear interpolation
% Psi_d_grid = F(Id_grid, Iq_grid);
% surf(Id_grid, Iq_grid, Psi_d_grid, 'EdgeColor', 'none', 'FaceAlpha', 0.5);  % Semi-transparent surface

% % Plot the fitted linear surface
% surf(Id_grid, Iq_grid, Psi_d_fit, 'EdgeColor', 'none', 'FaceAlpha', 0.3, 'FaceColor', 'r');  % Red semi-transparent plane

% % Add labels and a legend
% xlabel('mean\_id\_ref (i_d)');
% ylabel('mean\_iq\_ref (i_q)');
% zlabel('psi\_d');
% legend('Data Points', 'Interpolated Surface', 'Fitted Linear Plane');
% title('3D Scatter Plot with Interpolated Surface and Linear Fit');

% hold off;

function log=calculate_psi(log,pole_pairs,rs)

log=log(log.enable==1,:);
log=log(abs(log.dut_id_set-log.dut_id)<0.1,:); % only steady state
log=log(abs(log.dut_iq_set-log.dut_iq)<0.1,:);

log.omega_el=log.dut_speed_rpm/60*2*pi*pole_pairs;

log.psi_d_based_on_reference_voltage=(log.dut_vq_ref-rs*log.dut_iq)./log.omega_el;
log.psi_q_based_on_reference_voltage=-(log.dut_vd_ref-rs*log.dut_id)./log.omega_el;

log.psi_d=(log.dut_vq-rs*log.dut_iq)./log.omega_el;
log.psi_q=-(log.dut_vd-rs*log.dut_id)./log.omega_el;
[log.operating_point, ~] = findgroups(log.dut_iq_set, log.dut_id_set);

end

function filtered_log=calculate_average_over_operating_points(log)
filtered_log = groupsummary(log, 'operating_point', 'mean');
end

function [flux_map,fitted]=calculate_flux_map(groupedTable)
flux_map.i_d = groupedTable.mean_dut_id_set;  % x-axis data
flux_map.i_q = groupedTable.mean_dut_iq_set;  % y-axis data
fitted.psi_d = fit([flux_map.i_d, flux_map.i_q], groupedTable.mean_psi_d, 'poly11');  % 'poly11' fits a linear surface
fitted.psi_q = fit([flux_map.i_d, flux_map.i_q], groupedTable.mean_psi_q, 'poly11');  % 'poly11' fits a linear surface
fitted.psi_d_ref_voltage = fit([flux_map.i_d, flux_map.i_q], groupedTable.mean_psi_d_based_on_reference_voltage, 'poly11');  % 'poly11' fits a linear surface
fitted.psi_q_ref_voltage = fit([flux_map.i_d, flux_map.i_q], groupedTable.mean_psi_q_based_on_reference_voltage, 'poly11');  % 'poly11' fits a linear surface
flux_map.psi_d=groupedTable.mean_psi_d;
flux_map.psi_q=groupedTable.mean_psi_q;
flux_map.speed=groupedTable.mean_pm_speed_rpm_ref;
flux_map=struct2table(flux_map);
end

function plot_measured_flux_map(flux_map)


figure
tcl = tiledlayout(2,2);
subtitle('Raw measurement values (averages over steady state)');
nexttile
scatter3(flux_map.i_d,flux_map.i_q,flux_map.psi_d,'filled');
title('psi_d');
ylabel('i_q');
xlabel('i_d');

nexttile
scatter3(flux_map.i_d,flux_map.i_q,flux_map.psi_q,'filled');
title('psi_q');
ylabel('i_q');
xlabel('i_d');

nexttile
for i=1:length(flux_map.i_q)
    map=flux_map(flux_map.i_q==flux_map.i_q(i),:);
    plot(map.i_d,map.psi_d,'x--');
    hold on
    title('psi_d over i_d at different values for i_q')
end

nexttile
for i=1:length(flux_map.i_d)
    map=flux_map(flux_map.i_d==flux_map.i_d(i),:);
    plot(map.i_q,map.psi_q,'x--');
    hold on
    title('psi_q over i_q at different values for i_d')
end
end

function plot_measured_vs_fitted_flux(flux_map,approx)
figure
tcl = tiledlayout(2,2);
nexttile
scatter3(flux_map.i_d,flux_map.i_q,flux_map.psi_d,'filled');
hold on
scatter3(flux_map.i_d,flux_map.i_q,flux_map.psi_d_fitted);
title('psi_d');
ylabel('i_q');
xlabel('i_d');
legend('measured','fitted');

nexttile
scatter3(flux_map.i_d,flux_map.i_q,flux_map.psi_q,'filled');
hold on
scatter3(flux_map.i_d,flux_map.i_q,flux_map.psi_q_fitted);
title('psi_q');
ylabel('i_q');
xlabel('i_d');

nexttile
surf(approx.i_d,approx.i_q,approx.psi_d);
title('psi_d');
ylabel('i_q');
xlabel('i_d');

nexttile
surf(approx.i_d,approx.i_q,approx.psi_q);
title('psi_q');
ylabel('i_q');
xlabel('i_d');
end

function approx=approximate_flux_map_for_surf(flux_map,fitted)
    number_of_grid_points=30;
    id_lin = linspace(min(flux_map.i_d), max(flux_map.i_d), number_of_grid_points);  % Adjust 30 as needed for resolution
    iq_lin = linspace(min(flux_map.i_q), max(flux_map.i_q), number_of_grid_points);
    [approx.i_d, approx.i_q] = meshgrid(id_lin, iq_lin);
    approx.psi_d=fitted.psi_d(approx.i_d,approx.i_q);
    approx.psi_q=fitted.psi_q(approx.i_d,approx.i_q);
end
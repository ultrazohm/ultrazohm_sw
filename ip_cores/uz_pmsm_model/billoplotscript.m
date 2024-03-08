clc;
clear;
close all;

uz_pmsm_model_init_parameter;
LUT_approx_methode2a;
close all;

pgfplots_test = readtable('data_from_javascope_for_plotting/closes_loop_with_adjusted_output_old_to_sim_delay_1A_nonlinear');
pgfplots_test_cut = pgfplots_test(2:2:end, 1:1:2);
% pgfplots_test = pgfplots_test(2:2:end, 1:1:2);

%writetable( pgfplots_test,'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Implementierung\pgfplots_test_mat.csv');
set(0,'defaulttextinterpreter','latex')
%% Simulink Simulation
%Set stop_time
stop_time = 0.002;
simouttest = sim('uz_pmsm_model','StopTime','stop_time');
iq_plot = simouttest.logsout.getElement('i_q_hdl').Values.Data;
timeplot_iq = simouttest.logsout.getElement('i_q_hdl').Values.time;
id_plot = simouttest.logsout.getElement('i_d_hdl').Values.Data;
timeplot_id = simouttest.logsout.getElement('i_d_hdl').Values.time;
sim.iq_soll_value = simouttest.logsout.getElement('i_q_soll').Values.Data;
sim.iq_soll_time = simouttest.logsout.getElement('i_q_soll').Values.time;

kpd_sim = simouttest.logsout.getElement('Kp_d_adap').Values.Data;
kpd_sim_time = simouttest.logsout.getElement('Kp_d_adap').Values.time;
kpq_sim = simouttest.logsout.getElement('Kp_q_adap').Values.Data;
kpq_sim_time = simouttest.logsout.getElement('Kp_q_adap').Values.time;

u_d_static_ent = simouttest.logsout.getElement('u_d_static_ent').Values.Data;
u_d_static_ent = -1*u_d_static_ent;
u_d_static_ent_time = simouttest.logsout.getElement('u_d_static_ent').Values.time;
u_q_static_ent = simouttest.logsout.getElement('u_q_static_ent').Values.Data;
u_q_static_ent_time = simouttest.logsout.getElement('u_q_static_ent').Values.time;

%% PgfPlot Fugaze
setpoint_search = setpoint_step;  %%Hier wird der Wert gesetzt nachdem er später gesucht wird
%Hier werden einfach die Werte aus der csv datei in eine matrix geschrieben
measurement_1_value = pgfplots_test{1:end, 2};
measurement_1_time = pgfplots_test{1:end, 1}; %Channel 1 ist immer die Zeit
measurement_2_value = pgfplots_test{1:end, 3};
measurement_iqsollwert_value = pgfplots_test{1:end, 4}; %Sollte immer gleich bleiben,Des ist der Sprung Der WErt 4 könnte sich unterscheiden je nachdem auf Welchen Kanal ich des schreiben werde

% Es wird ein Zeitschritt ausgewählt auf was die Achse sozusagen verschoben
% werden soll also ist der Sprung bei 0.0 das muss dann immer zu Simulink
% passen
desired_step_time = 0.0;
find_value = max(measurement_iqsollwert_value); %der Dazugehörige maximale Sprung
first_step_index = find(measurement_iqsollwert_value == find_value, 1); %%%% Die  ist der istwert sprung muss eben gleich dem sein was in der excel file ist
time_difference = measurement_1_time(first_step_index-1) - desired_step_time;
global_time_vector = measurement_1_time - time_difference;

%Hier werden die measurement vectoren in den richtigen Zeitbereich gebracht
cil_time = global_time_vector(global_time_vector >= 0 & global_time_vector <= stop_time); %%The Cil time is the global time
measurement_1_value = measurement_1_value(global_time_vector >= 0 & global_time_vector <= stop_time);
measurement_2_value = measurement_2_value(global_time_vector >= 0 & global_time_vector <= stop_time);
measurement_iqsollwert_value = measurement_iqsollwert_value(global_time_vector >= 0 & global_time_vector <= stop_time);


figure;
plot(timeplot_iq,iq_plot, 'LineWidth', 3,'Color', 'blue');
hold on;
% plot(u_q_static_ent_time,u_q_static_ent , 'LineWidth', 3,'Color', 'black');
% hold on;
plot(cil_time,measurement_1_value,'--', 'LineWidth', 3,'Color', 'red');
% hold on;
% plot(cil_time,measurement_2_value,'--', 'LineWidth', 3,'Color', 'green');
% hold on;
% plot(cil_time,measurement_iqsollwert_value,'--', 'LineWidth', 2,'Color', 'cyan');
title('Sprung 1A,nonlinear, mechsys an, normal CC', 'FontSize', 20);
xlabel('Zeit/s', 'FontSize', 18);
ylabel('Strom/A', 'FontSize', 18);
legend('iq_{sim}','iq_{cil}');
%title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
set(gca, 'FontSize', 22);
set(0,'defaulttextinterpreter','latex')


%% Calculate error
sim_iq = timeseries(iq_plot,timeplot_iq);
meas_iq = timeseries(measurement_1_value,cil_time);
[sim_iq,meas_iq]=synchronize(sim_iq,meas_iq,'union');
abs_error_iq = sim_iq-meas_iq;

% sim_id = timeseries(u_d_static_ent,u_d_static_ent_time);
% meas_id = timeseries(measurement_1_value,cil_time);
% [sim_id,meas_id]=synchronize(sim_id,meas_id,'union');
% abs_error_id = sim_id-meas_id;

figure;
plot(abs_error_iq,'LineWidth',3);
% hold on;
% plot(abs_error_id,'LineWidth',3);
% grid on
title('Error', 'FontSize', 20);
legend('i_q error', 'FontSize', 18);
xlabel('Zeit/s', 'FontSize', 18);
ylabel('Strom/A', 'FontSize', 18);
set(gca,'fontsize',20);
set(0,'defaulttextinterpreter','latex')





clc;
clear;
close all;

uz_pmsm_model_init_parameter;
LUT_approx_methode2a;
close all;

pgfplots_test = readtable('data_from_javascope_for_plotting/CC_adaption_8A_lineare_entkopplung_nonlinear_model');
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
sim.id_soll_value = simouttest.logsout.getElement('i_d_soll').Values.Data;
sim.id_soll_time = simouttest.logsout.getElement('i_d_soll').Values.time;

kpd_sim = simouttest.logsout.getElement('Kp_d_adap').Values.Data;
kpd_sim_time = simouttest.logsout.getElement('Kp_d_adap').Values.time;
kpq_sim = simouttest.logsout.getElement('Kp_q_adap').Values.Data;
kpq_sim_time = simouttest.logsout.getElement('Kp_q_adap').Values.time;

psid_sim = simouttest.logsout.getElement('psi_d_approx').Values.Data;
psid_sim_time = simouttest.logsout.getElement('psi_d_approx').Values.time;
psiq_sim = simouttest.logsout.getElement('psi_q_approx').Values.Data;
psiq_sim_time = simouttest.logsout.getElement('psi_q_approx').Values.time;

u_d_static_ent = simouttest.logsout.getElement('u_d_static_ent').Values.Data;
u_d_static_ent = -1*u_d_static_ent;
u_d_static_ent_time = simouttest.logsout.getElement('u_d_static_ent').Values.time;
u_q_static_ent = simouttest.logsout.getElement('u_q_static_ent').Values.Data;
u_q_static_ent_time = simouttest.logsout.getElement('u_q_static_ent').Values.time;

%% PgfPlot Fugaze
setpoint_search = setpoint_step;  %%Hier wird der Wert gesetzt nachdem er später gesucht wird
%Hier werden einfach die Werte aus der csv datei in eine matrix geschrieben
measurement_1_value = pgfplots_test{1:end, 5};
measurement_1_time = pgfplots_test{1:end, 1}; %Channel 1 ist immer die Zeit
measurement_2_value = pgfplots_test{1:end, 6};
measurement_iqsollwert_value = pgfplots_test{1:end, 4}; %Sollte immer gleich bleiben,Des ist der Sprung Der WErt 4 könnte sich unterscheiden je nachdem auf Welchen Kanal ich des schreiben werde

% Es wird ein Zeitschritt ausgewählt auf was die Achse sozusagen verschoben
% werden soll also ist der Sprung bei 0.0 das muss dann immer zu Simulink
% passen
desired_step_time = 0.0005;
find_value = max(measurement_iqsollwert_value); %der Dazugehörige maximale Sprung
first_step_index = find(measurement_iqsollwert_value == find_value, 1); %%%% Die  ist der istwert sprung muss eben gleich dem sein was in der excel file ist
time_difference = measurement_1_time(first_step_index) - desired_step_time;
global_time_vector = measurement_1_time - time_difference;

%Hier werden die measurement vectoren in den richtigen Zeitbereich gebracht
cil_time = global_time_vector(global_time_vector >= 0 & global_time_vector <= stop_time); %%The Cil time is the global time
measurement_1_value = measurement_1_value(global_time_vector >= 0 & global_time_vector <= stop_time);
measurement_2_value = measurement_2_value(global_time_vector >= 0 & global_time_vector <= stop_time);
measurement_iqsollwert_value = measurement_iqsollwert_value(global_time_vector >= 0 & global_time_vector <= stop_time);

%% write to csv

iq_plot = iq_plot(1:20:end);
timeplot_iq = timeplot_iq(1:20:end);
id_plot = id_plot(1:20:end);
timeplot_id = timeplot_id(1:20:end);


% psid_sim = psid_sim(1:20:end);
% psid_sim_time = psid_sim_time(1:20:end);
% psiq_sim = psiq_sim(1:20:end);
% psiq_sim_time = psiq_sim_time(1:20:end);

% psid_sim = psid_sim(1:4:end);
% psid_sim = psid_sim(1:4:end);
% psid_sim_time = psid_sim_time(1:4:end);
% psid_sim_time = psid_sim_time(1:4:end);
% writematrix([psid_sim_time, psid_sim],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Validation\psid_openloop_validation.csv');
% writematrix([psiq_sim_time, psiq_sim],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Validation\psiq_openloop_validation.csv');


%% Entkopplung nach pgf plots exportieren
%%%---------------------------1--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_lineare_entkopplung_1A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_lineare_entkopplung_1A.csv');
% writematrix([sim.iq_soll_time, sim.iq_soll_value],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_lineare_entkopplung_1A_soll.csv');
% writematrix([sim.id_soll_time, sim.id_soll_value],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_lineare_entkopplung_1A_soll.csv');

%%%---------------------------2--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nichtlineare_entkopplung_1A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nichtlineare_entkopplung_1A.csv');
%%%---------------------------3--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_lineare_entkopplung_4A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_lineare_entkopplung_4A.csv');
% writematrix([sim.iq_soll_time, sim.iq_soll_value],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_lineare_entkopplung_4A_soll.csv');
% writematrix([sim.id_soll_time, sim.id_soll_value],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_lineare_entkopplung_4A_soll.csv');
%%%---------------------------4--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nichtlineare_entkopplung_4A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nichtlineare_entkopplung_4A.csv');
%%%---------------------------5--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_lineare_entkopplung_8A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_lineare_entkopplung_8A.csv');
% writematrix([sim.iq_soll_time, sim.iq_soll_value],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_lineare_entkopplung_8A_soll.csv');
% writematrix([sim.id_soll_time, sim.id_soll_value],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_lineare_entkopplung_8A_soll.csv');
%%%---------------------------6--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nichtlineare_entkopplung_8A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nichtlineare_entkopplung_8A.csv');
%% prädiktion nach pgfplots exportieren

% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nlin_entk_prae_aus_1A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nlin_entk_prae_aus_1A.csv');

%%%---------------------------2--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nlin_entk_prae_an_1A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nlin_entk_prae_an_1A.csv');

%%%---------------------------3--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nlin_entk_prae_aus_4A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nlin_entk_prae_aus_4A.csv');

%%%---------------------------4--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nlin_entk_prae_an_4A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nlin_entk_prae_an_4A.csv');
%%%---------------------------5--------------------------------------%%%%%

% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nlin_entk_prae_aus_8A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nlin_entk_prae_aus_8A.csv');

%%%---------------------------6--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_nlin_entk_prae_an_8A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_nlin_entk_prae_an_8A.csv');

%% adaption nach pgfplots exportieren

% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\iq_adap_aus_1A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Entkopplung\id_adap_aus_1A.csv');

%%%---------------------------2--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\iq_adap_an_1A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\id_adap_an_1A.csv');

%%%---------------------------3--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\iq_adap_aus_4A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\id_adap_aus_4A.csv');

%%%---------------------------4--------------------------------------%%%%%
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\iq_adap_an_4A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\id_adap_an_4A.csv');
%%%---------------------------5--------------------------------------%%%%%

% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\iq_adap_aus_8A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\id_adap_aus_8A.csv');

%%%---------------------------6--------------------------------------%%%%%
writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\iq_adap_an_8A.csv');
writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\id_adap_an_8A.csv');



%% dd
% % psid_iq1
% writematrix([d_current, Fluxd_iq1_fitted],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_d_bei_iq1_approx.csv');
% writematrix([d_current, Fluxd_iq1],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_d_bei_iq1_real.csv');
% % psid_id1
% writematrix([q_current, Fluxq_id1_fitted],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_q_bei_id1_approx.csv');
% writematrix([q_current, Fluxq_id1],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_q_bei_id1_real.csv');


%% plotten
figure;
% plot(kpd_sim_time,kpd_sim, 'LineWidth', 3,'Color', 'blue');
% hold on;
plot(kpd_sim_time,kpq_sim, 'LineWidth', 3,'Color', 'red');
hold on;
% plot(sim.iq_soll_time,sim.iq_soll_value,'--', 'LineWidth', 1,'Color', 'green');
% hold on;
% plot(sim.id_soll_time,sim.id_soll_value,'--', 'LineWidth', 1,'Color', 'green');
% hold on;
% plot(cil_time,measurement_1_value,'--', 'LineWidth', 3,'Color', 'cyan');
% hold on;
plot(cil_time,measurement_2_value,'--', 'LineWidth', 3,'Color', 'green');
hold on;
% plot(cil_time,measurement_iqsollwert_value,'--', 'LineWidth', 2,'Color', 'cyan');
% title('Sprung 1A,nonlinear, mechsys an, normal CC', 'FontSize', 20);
xlabel('Zeit/s', 'FontSize', 18);
ylabel('Regelparameter', 'FontSize', 18);
legend('kpq sim','kpq cil');
%title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
set(gca, 'FontSize', 22);
set(0,'defaulttextinterpreter','latex')

% figure;
% % plot(psiq_sim_time,psiq_sim, 'LineWidth', 3,'Color', 'blue');
% % hold on;
% % plot(psid_sim_time,psid_sim, 'LineWidth', 3,'Color', 'red');
% % hold on;
% plot(cil_time,measurement_1_value,'--', 'LineWidth', 3,'Color', 'red');
% hold on;
% plot(cil_time,measurement_2_value,'--', 'LineWidth', 3,'Color', 'green');
% hold on;
% % plot(cil_time,measurement_iqsollwert_value,'--', 'LineWidth', 2,'Color', 'cyan');
% % title('Sprung 1A,nonlinear, mechsys an, normal CC', 'FontSize', 20);
% xlabel('Zeit/s', 'FontSize', 18);
% ylabel('Fluss/Vs', 'FontSize', 18);
% legend('\psi_q','\psi_d');
% %title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
% set(gca, 'FontSize', 22);
% set(0,'defaulttextinterpreter','latex')




%% Calculate error
sim_iq = timeseries(kpq_sim,kpq_sim_time);
meas_iq = timeseries(measurement_2_value,cil_time);
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
ylabel('Fehler', 'FontSize', 18);
set(gca,'fontsize',20);
set(0,'defaulttextinterpreter','latex')







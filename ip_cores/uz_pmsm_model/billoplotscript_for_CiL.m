clc;
clear;
close all;

uz_pmsm_model_init_parameter;
LUT_approx_methode2a;
close all;

% pgfplots_test = readtable('Neue_Plot_funktionen_besserer_Namen/Open_Loop_iq_id_omegamech_mechan');
pgfplots_test = readtable('Neue_Plot_funktionen_besserer_Namen/ClosedLoopMotor1/Closed_Loop_flux_pre_aus_lin_ent_para_aus_iplusminus8A_1250prm');
% pgfplots_test_cut = pgfplots_test(2:2:end, 1:1:2);
% pgfplots_test = pgfplots_test(2:2:end, 1:1:2);



%writetable( pgfplots_test,'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Implementierung\pgfplots_test_mat.csv');
set(0,'defaulttextinterpreter','latex')
%% Simulink Simulation
%Set stop_time
stop_time = 0.006;
simouttest = sim('uz_pmsm_model','StopTime','stop_time');
iq_plot = simouttest.logsout.getElement('i_q_hdl').Values.Data;
timeplot_iq = simouttest.logsout.getElement('i_q_hdl').Values.time;
id_plot = simouttest.logsout.getElement('i_d_hdl').Values.Data;
timeplot_id = simouttest.logsout.getElement('i_d_hdl').Values.time;
sim.iq_soll_value = simouttest.logsout.getElement('i_q_soll').Values.Data;
sim.iq_soll_time = simouttest.logsout.getElement('i_q_soll').Values.time;
sim.id_soll_value = simouttest.logsout.getElement('i_d_soll').Values.Data;
sim.id_soll_time = simouttest.logsout.getElement('i_d_soll').Values.time;

% kpd_sim = simouttest.logsout.getElement('Kp_d_adap').Values.Data;
% kpd_sim_time = simouttest.logsout.getElement('Kp_d_adap').Values.time;
% kpq_sim = simouttest.logsout.getElement('Kp_q_adap').Values.Data;
% kpq_sim_time = simouttest.logsout.getElement('Kp_q_adap').Values.time;

% psid_sim = simouttest.logsout.getElement('psi_d_approx').Values.Data;
% psid_sim_time = simouttest.logsout.getElement('psi_d_approx').Values.time;
% psiq_sim = simouttest.logsout.getElement('psi_q_approx').Values.Data;
% psiq_sim_time = simouttest.logsout.getElement('psi_q_approx').Values.time;

% psid_predic = simouttest.logsout.getElement('psi_d_regler_approx').Values.Data;
% psid_predic_time = simouttest.logsout.getElement('psi_d_regler_approx').Values.time;
% psiq_predic = simouttest.logsout.getElement('psi_q_regler_approx').Values.Data;
% psiq_predic_time = simouttest.logsout.getElement('psi_q_regler_approx').Values.time;

% psid_predic = simouttest.logsout.getElement('fluxd_predic').Values.Data;
% psid_predic_time = simouttest.logsout.getElement('fluxd_predic').Values.time;
% psiq_predic = simouttest.logsout.getElement('fluxq_predic').Values.Data;
% psiq_predic_time = simouttest.logsout.getElement('fluxq_predic').Values.time;

% psid_predic = simouttest.logsout.getElement('Kp_d_adap').Values.Data;
% psid_predic_time = simouttest.logsout.getElement('Kp_d_adap').Values.time;
% psiq_predic = simouttest.logsout.getElement('Kp_q_adap').Values.Data;
% psiq_predic_time = simouttest.logsout.getElement('Kp_q_adap').Values.time;

psid_predic = simouttest.logsout.getElement('ud_ent').Values.Data;
psid_predic = -1*psid_predic;
psid_predic_time = simouttest.logsout.getElement('ud_ent').Values.time;
psiq_predic = simouttest.logsout.getElement('uq_ent').Values.Data;
psiq_predic_time = simouttest.logsout.getElement('uq_ent').Values.time;

% ud_ent = simouttest.logsout.getElement('ud_ent').Values.Data;
% ud_ent = -1*ud_ent;
% ud_ent_time = simouttest.logsout.getElement('ud_ent').Values.time;
% uq_ent = simouttest.logsout.getElement('uq_ent').Values.Data;
% uq_ent_time = simouttest.logsout.getElement('uq_ent').Values.time;

%% PgfPlot Fugaze
setpoint_search = setpoint_step;  %%Hier wird der Wert gesetzt nachdem er später gesucht wird
%Hier werden einfach die Werte aus der csv datei in eine matrix geschrieben
measurement_1_value = pgfplots_test{1:end, 3};
measurement_1_time = pgfplots_test{1:end, 1}; %Channel 1 ist immer die Zeit
measurement_2_value = pgfplots_test{1:end, 4};
measurement_iqsollwert_value = pgfplots_test{1:end, 4}; %Sollte immer gleich bleiben,Des ist der Sprung Der WErt 4 könnte sich unterscheiden je nachdem auf Welchen Kanal ich des schreiben werde

% Es wird ein Zeitschritt ausgewählt auf was die Achse sozusagen verschoben
% werden soll also ist der Sprung bei 0.0 das muss dann immer zu Simulink
% passen
desired_step_time = 0.001;
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

% iq_plot = iq_plot(1:20:end);
% timeplot_iq = timeplot_iq(1:20:end);
% id_plot = id_plot(1:20:end);
% timeplot_id = timeplot_id(1:20:end);


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
% writematrix([timeplot_iq, iq_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\iq_adap_an_8A.csv');
% writematrix([timeplot_id, id_plot],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Adaption\id_adap_an_8A.csv');



%% dd
% % psid_iq1
% writematrix([d_current, Fluxd_iq1_fitted],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_d_bei_iq1_approx.csv');
% writematrix([d_current, Fluxd_iq1],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_d_bei_iq1_real.csv');
% % psid_id1
% writematrix([q_current, Fluxq_id1_fitted],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_q_bei_id1_approx.csv');
% writematrix([q_current, Fluxq_id1],'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Simulation\Flusskarten_approximation\psi_q_bei_id1_real.csv');


%% plotten

%% iq 
figure;
plot(timeplot_iq,iq_plot, 'LineWidth', 3,'Color', 'blue');
hold on;
% plot(timeplot_id,id_plot, 'LineWidth', 3,'Color', 'red');
% hold on;


plot(cil_time,measurement_1_value,'--', 'LineWidth', 3,'Color', 'cyan');
hold on;
plot(sim.iq_soll_time,sim.iq_soll_value,'--', 'LineWidth', 1,'Color', 'green');
hold on;
% plot(cil_time,measurement_2_value,'--', 'LineWidth', 3,'Color', 'green');
% hold on;
xlim([0.0, stop_time]);
% plot(cil_time,measurement_iqsollwert_value,'--', 'LineWidth', 2,'Color', 'cyan');
% title('Sprung 1A,nonlinear, mechsys an, normal CC', 'FontSize', 20);
xlabel('Zeit/s', 'FontSize', 18);
ylabel('Fluss/Vs', 'FontSize', 18);
legend('iq sim','iq cil','iq soll sim');
% legend('psi_q predic sim','psi_d predic sim','psi_q predic cil','psi_d predic cil');
%title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
set(gca, 'FontSize', 22);
set(0,'defaulttextinterpreter','latex')

%% id 
figure;
plot(timeplot_id,id_plot, 'LineWidth', 3,'Color', 'red');
hold on;
plot(cil_time,measurement_2_value,'--', 'LineWidth', 3,'Color', 'green');
hold on;
 plot(sim.id_soll_time,sim.id_soll_value,'--', 'LineWidth', 1,'Color', 'cyan');
% hold on;
xlim([0.0, stop_time]);
% plot(cil_time,measurement_iqsollwert_value,'--', 'LineWidth', 2,'Color', 'cyan');
% title('Sprung 1A,nonlinear, mechsys an, normal CC', 'FontSize', 20);
xlabel('Zeit/s', 'FontSize', 18);
ylabel('Fluss/Vs', 'FontSize', 18);
legend('id sim','id cil','iq soll sim');
% legend('psi_q predic sim','psi_d predic sim','psi_q predic cil','psi_d predic cil');
%title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
set(gca, 'FontSize', 22);
set(0,'defaulttextinterpreter','latex')
 %% uq 
% figure;
% plot(ud_ent_time,uq_ent, 'LineWidth', 3,'Color', 'red');
% hold on;
% plot(cil_time,measurement_1_value,'--', 'LineWidth', 3,'Color', 'green');
% hold on;
% xlim([0.0, stop_time]);
% % plot(cil_time,measurement_iqsollwert_value,'--', 'LineWidth', 2,'Color', 'cyan');
% % title('Sprung 1A,nonlinear, mechsys an, normal CC', 'FontSize', 20);
% xlabel('Zeit/s', 'FontSize', 18);
% ylabel('Fluss/Vs', 'FontSize', 18);
% legend('uq sim','uq cil');
% % legend('psi_q predic sim','psi_d predic sim','psi_q predic cil','psi_d predic cil');
% %title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
% set(gca, 'FontSize', 22);
% set(0,'defaulttextinterpreter','latex')
% %% ud 
% figure;
% plot(ud_ent_time,ud_ent, 'LineWidth', 3,'Color', 'red');
% hold on;
% plot(cil_time,measurement_2_value,'--', 'LineWidth', 3,'Color', 'green');
% hold on;
% xlim([0.0, stop_time]);
% % plot(cil_time,measurement_iqsollwert_value,'--', 'LineWidth', 2,'Color', 'cyan');
% % title('Sprung 1A,nonlinear, mechsys an, normal CC', 'FontSize', 20);
% xlabel('Zeit/s', 'FontSize', 18);
% ylabel('Fluss/Vs', 'FontSize', 18);
% legend('ud sim','ud cil');
% % legend('psi_q predic sim','psi_d predic sim','psi_q predic cil','psi_d predic cil');
% %title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
% set(gca, 'FontSize', 22);
% set(0,'defaulttextinterpreter','latex')

 %% flux prediction
% figure;
% plot(psiq_predic_time,psiq_predic, 'LineWidth', 3,'Color', 'blue');
% hold on;
% plot(psid_predic_time,psid_predic, 'LineWidth', 3,'Color', 'red');
% hold on;
% plot(cil_time,measurement_1_value,'--', 'LineWidth', 3,'Color', 'cyan');
% hold on;
% plot(cil_time,measurement_2_value,'--', 'LineWidth', 3,'Color', 'green');
% hold on;
% xlim([0.0, stop_time]);
% 
% xlabel('Zeit/s', 'FontSize', 18);
% ylabel('Fluss/Vs', 'FontSize', 18);
% legend('uq sim','ud sim','uq cil','ud cil');
% % legend('psi_q predic sim','psi_d predic sim','psi_q predic cil','psi_d predic cil');
% %title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
% set(gca, 'FontSize', 22);
% set(0,'defaulttextinterpreter','latex')


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
%% iq
sim_iq = timeseries(iq_plot,timeplot_iq);
meas_iq = timeseries(measurement_1_value,cil_time);
[sim_iq,meas_iq]=synchronize(sim_iq,meas_iq,'union');
abs_error_iq = sim_iq-meas_iq;

%% id 
sim_id = timeseries(id_plot,timeplot_id);
meas_id = timeseries(measurement_2_value,cil_time);
[sim_id,meas_id]=synchronize(sim_id,meas_id,'union');
abs_error_id = sim_id-meas_id;

%% anythingelse

% sim_iq = timeseries(psiq_predic,psiq_predic_time);
% meas_iq = timeseries(measurement_1_value,cil_time);
% [sim_iq,meas_iq]=synchronize(sim_iq,meas_iq,'union');
% abs_error_iq = sim_iq-meas_iq;
% 
% 
% sim_id = timeseries(psid_predic,psid_predic_time);
% meas_id = timeseries(measurement_2_value,cil_time);
% [sim_id,meas_id]=synchronize(sim_id,meas_id,'union');
% abs_error_id = sim_id-meas_id;

%% plotte error
%% iq error
figure;
plot(abs_error_iq,'LineWidth',3);
xlim([0.0, stop_time]);
 % xlim([0.0, 0.1]);
% hold on;
% plot(abs_error_id,'LineWidth',3);
% grid on
title('Error', 'FontSize', 20);
% legend('i_q error', 'FontSize', 18);
xlabel('Zeit/s', 'FontSize', 18);
ylabel('Fehler q-achse', 'FontSize', 18);
% legend('i_q');
set(gca,'fontsize',20);
set(0,'defaulttextinterpreter','latex')

%% id error
figure;
 % xlim([0.0, 0.1]);
% hold on;
plot(abs_error_id.Time,abs_error_id.Data,'LineWidth',3);
xlim([0.0, stop_time]);
% grid on
title('Error d-achse', 'FontSize', 20);
% legend('i_q error', 'FontSize', 18);
xlabel('Zeit/s', 'FontSize', 18);
ylabel('Fehler', 'FontSize', 18);
% legend('error id');
set(gca,'fontsize',20);
set(0,'defaulttextinterpreter','latex')


%% extrahiere nach pgfplots
% %iq
% time_iq_sim_cut = sim_iq.Time(1:100:end);
% data_iq_sim_cut = sim_iq.Data(1:100:end);
% time_iq_mea_cut = meas_iq.Time(1:100:end);
% data_iq_mea_cut = meas_iq.Data(1:100:end);
% 
% %id
% time_id_sim_cut = sim_id.Time(1:100:end);
% data_id_sim_cut = sim_id.Data(1:100:end);
% time_id_mea_cut = meas_id.Time(1:100:end);
% data_id_mea_cut = meas_id.Data(1:100:end);
% 
% %error iq
% time_iq_error_cut = abs_error_iq.Time(1:100:end);
% data_iq_error_cut = abs_error_iq.Data(1:100:end);
% 
% %error id
% time_id_error_cut = abs_error_id.Time(1:100:end);
% data_id_error_cut = abs_error_id.Data(1:100:end);


%% flux_approximation
% time_psiq_sim_cut = sim_iq.Time(1:4:end);
% data_psiq_sim_cut = sim_iq.Data(1:4:end);
% time_psiq_mea_cut = meas_iq.Time(1:4:end);
% data_psiq_mea_cut = meas_iq.Data(1:4:end);
% 
% %id
% time_psid_sim_cut = sim_id.Time(1:4:end);
% data_psid_sim_cut = sim_id.Data(1:4:end);
% time_psid_mea_cut = meas_id.Time(1:4:end);
% data_psid_mea_cut = meas_id.Data(1:4:end);
% 
% %error iq
% time_psiq_error_cut = abs_error_iq.Time(1:4:end);
% data_psiq_error_cut = abs_error_iq.Data(1:4:end);
% 
% %error id
% time_psid_error_cut = abs_error_id.Time(1:10:end);
% data_psid_error_cut = abs_error_id.Data(1:10:end);

%% Voltage_for decoupling
% time_uq_sim_cut = sim_iq.Time(1:10:end);
% data_uq_sim_cut = sim_iq.Data(1:10:end);
% time_uq_mea_cut = meas_iq.Time(1:10:end);
% data_uq_mea_cut = meas_iq.Data(1:10:end);
% 
% %id
% time_ud_sim_cut = sim_id.Time(1:10:end);
% data_ud_sim_cut = sim_id.Data(1:10:end);
% time_ud_mea_cut = meas_id.Time(1:10:end);
% data_ud_mea_cut = meas_id.Data(1:10:end);
% 
% %error iq
% time_uq_error_cut = abs_error_iq.Time(1:10:end);
% data_uq_error_cut = abs_error_iq.Data(1:10:end);
% 
% %error id
% time_ud_error_cut = abs_error_id.Time(1:10:end);
% data_ud_error_cut = abs_error_id.Data(1:10:end);

% data_iq_soll_cut =meas_id.Data(1:10:end);
% time_iq_soll_cut =meas_id.Time(1:10:end);
% data_iq_lin_cut =meas_iq.Data(1:10:end);
% time_iq_lin_cut =meas_iq.Time(1:10:end);

% sim_iq = timeseries(sim.id_soll_value,sim.id_soll_time);

data_id_soll_cut =-1*meas_id.Data(1:10:end);
time_id_soll_cut =meas_id.Time(1:10:end);
% data_id_soll_cut =sim_iq.Data(1:10:end);
% time_id_soll_cut =sim_iq.Time(1:10:end);
% data_id_lin_cut =meas_iq.Data(1:10:end);
% time_id_lin_cut =meas_iq.Time(1:10:end);






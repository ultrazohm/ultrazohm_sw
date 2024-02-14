close all;
pgfplots_test = readtable('data_from_javascope_for_plotting/closed_loop_linear_1A');
pgfplots_test_cut = pgfplots_test(2:2:end, 1:1:2);
pgfplots_test_cut = pgfplots_test_cut(2:2:end, 1:1:2);
% pgfplots_test = pgfplots_test(2:2:end, 1:1:2);
% pgfplots_test = pgfplots_test(2:2:end, 1:1:2);
% pgfplots_test = pgfplots_test(2:2:end, 1:1:2);
% pgfplots_test = pgfplots_test(2:2:end, 1:1:2);
writetable( pgfplots_test,'C:\Users\Philipp\MARepository\29-03-2023_hufnagel_doelger_regelung_nichtlinearer_pmsm\Grafiken_Implementierung\pgfplots_test_mat.csv');

%% Simulink Simulation
simouttest = sim('uz_pmsm_model','StopTime','0.05');
iq_plot = simouttest.logsout.getElement('i_q_hdl').Values.Data;
timeplot_iq = simouttest.logsout.getElement('i_q_hdl').Values.time;
iq_plot_test = simouttest.logsout.getElement('i_q_soll').Values.Data;
timeplot_iq_test = simouttest.logsout.getElement('i_q_soll').Values.time;

%% PgfPlot Fugaze
setpoint_search = setpoint_step;
test_sprung_ausGui_value = pgfplots_test{1:end, 2};
test_sprung_ausGui_time = pgfplots_test{1:end, 1};
test_iqsoll_ausGui_value = pgfplots_test{1:end, 4};
reference_current_gui = pgfplots_test{1:end, 4}; %%%%% Des ist der Sprung Der WErt 5 könnte sich unterscheiden je nachdem auf Welchen Kanal ich des schreiben werde
desired_step_time = 0.025;
find_value = max(reference_current_gui);
first_step_index = find(reference_current_gui == find_value, 1); %%%% Die 4 ist der istwert sprung muss eben gleich dem sein was in der excel file ist
time_difference = test_sprung_ausGui_time(first_step_index) - desired_step_time;
adjusted_time_vector = test_sprung_ausGui_time - time_difference;
final_adjusted_time_vector = adjusted_time_vector(adjusted_time_vector >= 0 & adjusted_time_vector <= 0.1);
adjusted_value_vector = test_sprung_ausGui_value(adjusted_time_vector >= 0 & adjusted_time_vector <= 0.1);
test_iqsoll_ausGui_value = test_iqsoll_ausGui_value(adjusted_time_vector >= 0 & adjusted_time_vector <= 0.1);

figure;
plot(timeplot_iq,iq_plot, 'LineWidth', 4,'Color', 'blue');
hold on;
plot(timeplot_iq_test,iq_plot_test, 'LineWidth', 4,'Color', 'red');
hold on;
plot(final_adjusted_time_vector,adjusted_value_vector, 'LineWidth', 4,'Color', 'green');
hold on;
plot(final_adjusted_time_vector,test_iqsoll_ausGui_value, 'LineWidth', 4,'Color', 'cyan');
legend('iq_{sim}','iq_{set}','iq_{CiL}','iq_{sollCiL}');
title('Sprungantworten Simulation mit Betragsoptimum Cil mit Tutorialparametern')
set(gca, 'FontSize', 22);

% %% Fehler berechnen
% iq_cil_interpoliert = interp1(iq_plot,timeplot_iq,final_adjusted_time_vector);
% absolute_error = abs(iq_cil_interpoliert - adjusted_value_vector);
% figure;
% plot(final_adjusted_time_vector,absolute_error);




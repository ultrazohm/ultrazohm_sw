%Alles in einem Plot Pfuschen
timevalues_mea = workspace{19}.Values.Time;
timevalues_sol = workspace{1}.Values.Time;
Z_id_voll = workspace{18}.Values.Data;
Z_id_voll = Z_id_voll(1:24000);
Z_iq_voll = workspace{19}.Values.Data;
Z_iq_voll = Z_iq_voll(1:24000);

%Regelparameter
Z_K_p_q_voll = workspace{9}.Values.Data;
Z_K_p_q_voll = Z_K_p_q_voll(1:1250);
Z_K_p_d_voll = workspace{8}.Values.Data;
Z_K_p_d_voll = Z_K_p_d_voll(1:1250);

%test_Z_id_sol = workspace{21}.Values.Data;
% Z_iq_sol = workspace{24}.Values.Data;
%Ztest = length(Z_id_lin);

anzahl_nullen = 12530;
anzahl_einsen = 24000 - anzahl_nullen;

% Erstellen Sie das Array mit Nullen und Einsen
Z_id_sol = [zeros(1, anzahl_nullen), 10*(-ones(1, anzahl_einsen))]';
Z_iq_sol = [zeros(1, anzahl_nullen), 10*ones(1, anzahl_einsen)]';

%xlimvec = length(workspace{19}.Values.Time)
time_vec = linspace(0, 0.048, 24000);
time_vec_regler = linspace(0, 0.050, 1250);

start_index = 12000;
end_index = 15500;

start_index_regler = 600;
end_index_regler = 775;


close all;
%Plot
figure
%iq
subplot(2,1,1);
plot(time_vec,Z_iq_lin,time_vec,Z_iq_sol,time_vec,Z_iq_static,time_vec,Z_iq_prae,time_vec,Z_iq_voll,time_vec,Z_iq_ada,'LineWidth', 4);
%
grid on;
legend('i_{q,lin}', 'i_{q,soll}','i_{q,static}','i_{q,prae}','i_{q,voll}','i_{q,adap}','FontSize', 18);
xlabel('Zeit/s');
ylabel('Strom/A');
title('I_q Sprungantwort Regelkreis');

xlim([time_vec(start_index), time_vec(end_index)]);
ylim(1.2 * get(gca, 'YLim'));


%id
% subplot(2,1,2);
% plot(time_vec,Z_id_lin,time_vec,Z_id_sol,time_vec,Z_id_static,time_vec,Z_id_prae,time_vec,Z_id_ada,'LineWidth', 4);
% %
% grid on;
% %xlim_vec =;
% legend('i_{d,lin}', 'i_{d,soll}','i_{d,static}','i_{d,prae}','i_{d,adap}','FontSize', 18);
% xlabel('Zeit/s');
% ylabel('Strom/A');
% title('I_d Sprungantwort Regelkreis');
% xlim([time_vec(start_index), time_vec(end_index)]);
% ylim(1.2 * get(gca, 'YLim'));
% figure;
subplot(2,1,2);
plot(time_vec_regler,Z_K_p_q,time_vec_regler,Z_K_p_d,time_vec_regler,Z_K_p_q_voll,time_vec_regler,Z_K_p_d_voll,'LineWidth', 4);
%,time_vec_regler,K_p_q_ada,time_vec_regler,K_p_d_ada
grid on;
%xlim_vec =;
legend('Kpq', 'Kpd', 'Kpq_{ada}', 'Kpd_{ada}','FontSize', 18);
xlabel('Zeit/s');
ylabel('K_p');
title('Regelparameter');
xlim([time_vec_regler(start_index_regler), time_vec_regler(end_index_regler)]);
% ylim(1.2 * get(gca, 'YLim'));
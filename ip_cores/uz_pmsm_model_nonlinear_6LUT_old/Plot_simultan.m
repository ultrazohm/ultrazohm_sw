%Alles in einem Plot Pfuschen
timevalues_mea = workspace{20}.Values.Time;
timevalues_sol = workspace{1}.Values.Time;
Z_id_voll = workspace{20}.Values.Data;
Z_id_voll = Z_id_voll(1:24000);
Z_iq_voll = workspace{21}.Values.Data;
Z_iq_voll = Z_iq_voll(1:24000);

%Regelparameter
Z_K_p_q = workspace{9}.Values.Data;
Z_K_p_q = Z_K_p_q(1:1250);
Z_K_p_d = workspace{8}.Values.Data;
Z_K_p_d = Z_K_p_d(1:1250);

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
end_index = 13500;

start_index_regler = 600;
end_index_regler = 775;

%ITAE berechnen
e_id_time = workspace{12}.Values.time;
e_id = workspace{12}.Values.Data;

iae_id = trapz(e_id_time,abs(e_id))

e_iq_time = workspace{13}.Values.time;
e_iq = workspace{13}.Values.Data;

iae_iq = trapz(e_iq_time,abs(e_iq))
close all;
% figure
% plot(e_id)


%Plot
figure;
%iq
subplot(2,1,1);
%,Z_iq_sol,time_vec
%time_vec,Z_id_sol
%,time_vec,Z_iq_ada
plot(time_vec,Z_iq_lin,time_vec,Z_iq_static,time_vec,Z_iq_prae,time_vec,Z_iq_voll,'LineWidth', 4);
%
grid on;
legend('i_{q,lin}','i_{q,static}','i_{q,prae}','i_{q,voll}','FontSize', 18);
xlabel('Zeit/s');
ylabel('Strom/A');
title('I_q Sprungantwort Regelkreis');

% xlim([time_vec(start_index), time_vec(end_index)]);
% ylim(1.2 * get(gca, 'YLim'));

xlim([timevalues_mea(start_index), timevalues_mea(end_index)]);
ylim(1.2 * get(gca, 'YLim'));

%
%id
subplot(2,1,2);
plot(time_vec,Z_id_lin,time_vec,Z_id_static,time_vec,Z_id_prae,time_vec,Z_id_voll,'LineWidth', 4);
%
grid on;
%xlim_vec =;
legend('i_{d,lin}','i_{d,static}','i_{d,prae}','i_{d,voll}','FontSize', 18);
xlabel('Zeit/s');
ylabel('Strom/A');
title('I_d Sprungantwort Regelkreis');
% xlim([time_vec(start_index), time_vec(end_index)]);
% ylim(1.2 * get(gca, 'YLim'));
xlim([timevalues_mea(start_index), timevalues_mea(end_index)]);
ylim(1.2 * get(gca, 'YLim'));


figure;
%,time_vec_regler,Z_K_p_q_voll,time_vec_regler,Z_K_p_d_voll
% subplot(2,1,2);
plot(time_vec_regler,Z_K_p_q,time_vec_regler,Z_K_p_d,'LineWidth', 4);
%,time_vec_regler,K_p_q_ada,time_vec_regler,K_p_d_ada
grid on;
%xlim_vec =;
legend('Kpq_{lin}', 'Kpd_{lin}', 'Kpq_{voll}', 'Kpd_{voll}','FontSize', 18);
xlabel('Zeit/s');
ylabel('K_p');
title('Regelparameter');
xlim([time_vec_regler(start_index_regler), time_vec_regler(end_index_regler)]);
% ylim(1.2 * get(gca, 'YLim'));
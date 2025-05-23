% === Parameter ===
clear all;

Rs = 1;  % Statorwiderstand in Ohm
filename = 'Log_2025-05-22_16-54-47.csv';  % Pfad zur CSV-Datei
% === Daten einlesen ===
data = readtable(filename);
%make_table_from_log(Log_2025-05-22_16-54-47.csv);

% === Relevante Größen extrahieren ===
data(data.CH19__49_n_ref_rc_meas ~= 200, :) = [];

%validRange = abs(data.CH19 - n_target);  % Bereich mit gültigen/stationären Messdaten (Indexbereich)

u_d = data.CH10__26_vd_right;
u_q = data.CH11__27_vq_right;
i_d = data.CH4__10_id_right;
i_q = data.CH5__11_iq_right;
n_rpm = data.CH19__49_n_ref_rc_meas;  % Drehzahl in U/min
omega = 2 * pi * n_rpm / 60; % Umrechnung in rad/s

% === Flussverkettung berechnen ===
psi_d = (u_q - Rs .* i_q) ./ omega;
psi_q = -(u_d - Rs .* i_d) ./ omega;
psi_abs = sqrt(psi_d.^2 + psi_q.^2);

% === Plot: Flusskarte ===
figure;
scatter3(i_d, i_q, psi_q, 20, psi_q, 'filled');
xlabel('i_d [A]');
ylabel('i_q [A]');
zlabel('|\psi_q| / Vs');
title('Flussverkettung |\psi_q| über i_d / i_q');
colorbar;
grid on;
view(45, 30);

figure;
scatter3(i_d, i_q, psi_d, 20, psi_d, 'filled');
xlabel('i_d [A]');
ylabel('i_q [A]');
zlabel('|\psi_d| / Vs');
title('Flussverkettung |\psi_d| über i_d / i_q');
colorbar;
grid on;
view(45, 30);
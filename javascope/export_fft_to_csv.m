function [THD] = export_fft_to_csv(simOutput,filename,range)
% Ausgabe:
%   THD        - Total Harmonic Distortion in Prozent
% Eingaben:
%   simOutput  - Struktur mit dem Zeitverlauf (z. B. Simulink-Ausgabe mit .Time und .Signals.Values)
%   signalName - Name des Signals im simOutput (String)
%   filename   - Name der Ausgabedatei (z. B. 'fft_output.csv')
%   range      - Bereich, für eine Periode bzw. vielfache zum Abtasten

% time = simOutput.(signalName).Time(range);
% signal = simOutput.(signalName).Data(range);
time = simOutput(range,1);
time = table2array(time);
signal = simOutput(range,2);
signal = table2array(signal);
% Sampling-Rate bestimmen
Ts = mean(diff(time));  % Abtastzeit
Fs = Ts/1;           % Abtastfrequenz

% FFT berechnen
N = length(signal);
Y = fft(signal);         % Fourier-Transformation
f = (0:N-1)*(Fs/N);   % Frequenzachse

% Amplitude normieren und nur positive Frequenzen betrachten
Y_mag = abs(Y)/(N/2); 
Y_half = Y_mag(1:N/2);
f_half = f(1:N/2);
[~, idx_max] = max(Y_half(2:end));  % Index des Maximums (ohne DC)
f0 = f_half(idx_max + 1); 
f_half = f(1:N/2)/f0; 

% Plot der Spektralanalyse
% figure;
% plot(f_half, Y_half, 'LineWidth', 1.5);
% xlabel('Ordnung h');
% ylabel('Amplitude');
% title('Frequenzspektrum des Statorstroms');
% grid on;
% fprintf('Erkannte Grundfrequenz: %.2f Hz\n', f0);


% Harmonische als Balkendiagramm
max_order = 20;  % Anzahl der darzustellenden Ordnungen

% Indizes der ganzzahligen Ordnungen (f_half in Ordnungen umgerechnet)
harmonic_orders = 0:max_order;
harmonic_amplitudes = zeros(size(harmonic_orders));

for h = harmonic_orders
    % Finde den Index der Frequenz, die der Ordnung am nächsten ist
    [~, idx] = min(abs(f_half - h));
    harmonic_amplitudes(h+1) = Y_half(idx);
end

harmonic_amplitudes_rel = (harmonic_amplitudes/harmonic_amplitudes(2))*100;

% Balkendiagramm plotten
figure;
bar(harmonic_orders(3:end), harmonic_amplitudes_rel(3:end), 'FaceColor', [0.2 0.6 0.8]);
xlabel('Ordnung h');
ylabel('Amplitude in %');
title('Harmonische des Statorstroms');
grid on;

%Daten in eine Tabelle
T = table(harmonic_orders(3:end)',harmonic_amplitudes_rel(3:end)', 'VariableNames', {'Ordnung', 'Amplitude'});

% CSV schreiben
writetable(T, filename);

fprintf('FFT-Daten wurden in %s gespeichert.\n', filename);

% THD berechnen

A1 = harmonic_amplitudes(2);  % Grundwelle
A_harmonics = harmonic_amplitudes(3:end);  % höhere Ordnungen
THD_num = sqrt(sum(A_harmonics.^2)) / A1;
THD = THD_num * 100;

end
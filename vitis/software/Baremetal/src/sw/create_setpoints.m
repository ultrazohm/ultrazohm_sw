% Anzahl der Werte
n = 50;

% Initialisierung der Arrays
Array1 = rand(n,1);              % Werte [0,1]
Array2 = -rand(n,1);             % Werte [-1,0]
Array3 = -0.2 + 0.4*rand(n,1);   % Werte [-0.2,0.2]
Array4 = -0.2 + 0.4*rand(n,1);   % Werte [-0.2,0.2]

% Überprüfung und Anpassung
for i = 1:n
    gesamt = sqrt(Array1(i)^2 + Array2(i)^2 + Array3(i)^2 + Array4(i)^2);
    
    % Falls größer als 1.5 → Werte skalieren
    if gesamt > 1.5
        faktor = 1.5 / gesamt;
        Array1(i) = Array1(i) * faktor;
        Array2(i) = Array2(i) * faktor;
        Array3(i) = Array3(i) * faktor;
        Array4(i) = Array4(i) * faktor;
    end
end

% In eine Matrix zusammenfassen
%data = [Array1, Array2, Array3, Array4];

% Als CSV speichern
writematrix(Array1', 'iq_setpoints.csv', 'Delimiter', ',');
writematrix(Array2', 'id_setpoints.csv', 'Delimiter', ',');
writematrix(Array3', 'ix_setpoints.csv', 'Delimiter', ',');
writematrix(Array4', 'iy_setpoints.csv', 'Delimiter', ',');

disp('CSV-Datei wurde erfolgreich erstellt.');
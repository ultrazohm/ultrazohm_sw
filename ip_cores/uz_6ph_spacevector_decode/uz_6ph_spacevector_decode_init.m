Ts = 1e-8;

% Deine Daten
output_ar = [
0,0,0,0,0,0;
1,0,0,0,0,0;    
0,1,0,0,0,0;
1,1,0,0,0,0;
0,1,0,0,0,0;
1,0,0,0,0,0;  
0,0,0,0,0,0;

0,0,0,0,0,0;

0,0,0,0,0,1;
1,0,0,0,0,0;    
0,1,0,0,0,0;
1,1,0,0,0,0;
0,1,0,0,0,0;
1,0,0,0,0,0;  
0,0,0,0,0,0;

0,0,0,0,0,1;
1,0,0,0,0,1;    
0,1,0,0,0,1;
1,1,0,0,0,1;
0,1,0,0,0,1;
1,0,0,0,0,1;
0,0,0,0,0,1;

0,0,0,0,0,0;
1,0,0,0,0,0;    
0,1,0,0,0,0;
1,1,0,0,0,0;
0,1,0,0,0,0;
1,0,0,0,0,0;
0,0,0,0,0,0;
];

time_output_ar = [[1:7]*1e-8, [0:6]*1e-8+10e-6, [1:7]*1e-6+20e-6, [1:7]*1e-6+30e-6];

% Sicherstellen: Spaltenvektor
t_events = time_output_ar(:);

% Gesamtsimulationszeit
t_end = max(t_events);

% Diskrete Zeitachse
t = (0:Ts:t_end)';

% Ausgangssignal initialisieren
u = zeros(length(t), size(output_ar,2));

% --- Kernlogik ---
current_idx = 1;

for k = 1:length(t)
    % solange nächstes Event erreicht → Zustand updaten
    while current_idx < length(t_events) && t(k) >= t_events(current_idx)
        current_idx = current_idx + 1;
    end
    
    u(k,:) = output_ar(current_idx,:);
end

figure(1)
clf;
hold on
plot(1:length(u(:,1)),u(:,1))
plot(1:length(u(:,1)),u(:,2))
plot(1:length(u(:,1)),u(:,3))
plot(1:length(u(:,1)),u(:,4))
plot(1:length(u(:,1)),u(:,5))
plot(1:length(u(:,1)),u(:,6))
hold off
grid on

input_data_1 = timeseries(u, t);
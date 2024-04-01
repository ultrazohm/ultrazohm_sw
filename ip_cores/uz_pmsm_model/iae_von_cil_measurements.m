cil_lin_regler_motor1 = readtable('Neue_Plot_funktionen_besserer_Namen/ClosedLoopMotor1/Closed_Loop_flux_pre_aus_lin_ent_para_aus_iplusminus8A_1250prm');
cil_vollausbau_motor1 = readtable('Neue_Plot_funktionen_besserer_Namen/ClosedLoopMotor1/Closed_loop_flux_pre_an_nonlin_ent_para_an_8A_1250rpm');

cil_lin_regler_motor2 = readtable('Neue_Plot_funktionen_besserer_Namen/Motor3/Motor3_linearer_regler_8A_1250rpm');
cil_vollausbau_motor2 = readtable('Neue_Plot_funktionen_besserer_Namen/Motor3/Motor3_vollausbau_8A_1250prm');


setpoint_step = 8.0;
stop_time = 0.006;
desired_step_time = 0.001;


%% PgfPlot Fugaze
setpoint_search = setpoint_step;  %%Hier wird der Wert gesetzt nachdem er später gesucht wird
%Hier werden einfach die Werte aus der csv datei in eine matrix geschrieben
measurement_1_value = cil_vollausbau_motor2{1:end, 2};
measurement_1_time = cil_vollausbau_motor2{1:end, 1}; %Channel 1 ist immer die Zeit
measurement_2_value = cil_vollausbau_motor2{1:end,3};
measurement_iqsollwert_value = cil_vollausbau_motor2{1:end, 4}; %Sollte immer gleich bleiben,Des ist der Sprung Der WErt 4 könnte sich unterscheiden je nachdem auf Welchen Kanal ich des schreiben werde

% Es wird ein Zeitschritt ausgewählt auf was die Achse sozusagen verschoben
% werden soll also ist der Sprung bei 0.0 das muss dann immer zu Simulink
% passen

find_value = max(measurement_iqsollwert_value); %der Dazugehörige maximale Sprung
first_step_index = find(measurement_iqsollwert_value == find_value, 1); %%%% Die  ist der istwert sprung muss eben gleich dem sein was in der excel file ist
time_difference = measurement_1_time(first_step_index) - desired_step_time;
global_time_vector = measurement_1_time - time_difference;

%Hier werden die measurement vectoren in den richtigen Zeitbereich gebracht
cil_time = global_time_vector(global_time_vector >= 0 & global_time_vector <= stop_time); %%The Cil time is the global time
measurement_1_value = measurement_1_value(global_time_vector >= 0 & global_time_vector <= stop_time);
measurement_2_value = measurement_2_value(global_time_vector >= 0 & global_time_vector <= stop_time);
measurement_iqsollwert_value = measurement_iqsollwert_value(global_time_vector >= 0 & global_time_vector <= stop_time);


eq = measurement_iqsollwert_value-measurement_1_value;
ed = (-1*measurement_iqsollwert_value)-measurement_2_value;

iae_q_absolut = abs(eq);
iae_d_absolut = abs(ed);
ise_q_square = (eq).^2;
ise_d_square = (ed).^2;

ISE_d = trapz(cil_time,ise_d_square)*1e3
ISE_q = trapz(cil_time,ise_q_square)*1e3
IAE_d = trapz(cil_time,iae_d_absolut)*1e3
IAE_q = trapz(cil_time,iae_q_absolut)*1e3






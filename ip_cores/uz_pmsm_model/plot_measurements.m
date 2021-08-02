%% Plots the javascope data in the sepecified .csv
clc
close all
clear

A=readmatrix('measurment_with_speed.csv');

measurement.time=A(:,1);
measurement.iq=A(:,2);
measurement.id=A(:,3);
measurement.speed=A(:,4);
measurement.ud=A(:,5);

figure
subplot(4,1,1)
grid on
plot(measurement.time,measurement.ud);
title('U_d');

subplot(4,1,2)
grid on
plot(measurement.time,measurement.iq);
title('I_q');

subplot(4,1,3)
grid on
plot(measurement.time,measurement.id);
title('I_d');

subplot(4,1,4);
grid on
plot(measurement.time,measurement.speed);
title('speed');
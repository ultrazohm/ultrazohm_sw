clear
clc
load('pred_error_compare_sfix27_en24.mat');

d_pred_er_sqrt_100kHz = sqrt(log_100kHz.CH11);
q_pred_er_sqrt_100kHz = sqrt(log_100kHz.CH12);

mean_d_100kHz = mean(d_pred_er_sqrt_100kHz(1:40000))
mean_q_100kHz = mean(q_pred_er_sqrt_100kHz(1:40000))

d_pred_er_sqrt_400kHz = sqrt(log_400kHz.CH11);
q_pred_er_sqrt_400kHz = sqrt(log_400kHz.CH12);

mean_d_400kHz = mean(d_pred_er_sqrt_400kHz(1:40000))
mean_q_400kHz = mean(q_pred_er_sqrt_400kHz(1:40000))


figure
subplot(211)
plot(log_100kHz.time,d_pred_er_sqrt_100kHz);
hold on
plot(log_100kHz.time,q_pred_er_sqrt_100kHz);
title('prediction error - delay compensation sfix27En24 - 100kHz')
ylabel('Current p.u.')
axis([0 4 0 0.08])
grid on
dim = [.5 .6 .3 .3];
str = 'mean values: d: 0.0075, q: 0.0042';
annotation('textbox',dim,'String',str,'FitBoxToText','on')
subplot(212)
plot(log_400kHz.time,d_pred_er_sqrt_400kHz);
hold on
plot(log_400kHz.time,q_pred_er_sqrt_400kHz);
title('prediction error - delay compensation sfix27En24 - 400kHz')
xlabel('Time / s')
ylabel('Current p.u.')
axis([0 4 0 0.08])
grid on
dim = [.5 .13 .3 .3];
str = 'mean values: d: 0.0115, q: 0.0121';
annotation('textbox',dim,'String',str,'FitBoxToText','on')
close all

x_pos_theta0=find(log.time<7.85 & 7.79<log.time);
x_neg_theta0=find(log.time<16.82 & 16.76<log.time);
x_pos_theta1=find(log.time<28.98 & 28.92<log.time);
x_neg_theta1=find(log.time<39.22 & 39.14<log.time);


u_d_pos_norm_0=log.CH6(x_pos_theta0)./log.CH8(x_pos_theta0);
u_q_pos_norm_0=log.CH7(x_pos_theta0)./log.CH8(x_pos_theta0);
u_d_pos_norm_1=log.CH6(x_pos_theta1)./log.CH8(x_pos_theta1);
u_q_pos_norm_1=log.CH7(x_pos_theta1)./log.CH8(x_pos_theta1);

u_d_neg_norm_0=log.CH6(x_neg_theta0)./log.CH8(x_neg_theta0);
u_q_neg_norm_0=log.CH7(x_neg_theta0)./log.CH8(x_neg_theta0);
u_d_neg_norm_1=log.CH6(x_neg_theta1)./log.CH8(x_neg_theta1);
u_q_neg_norm_1=log.CH7(x_neg_theta1)./log.CH8(x_neg_theta1);



figure
subplot(2,2,1)
title('positive non-aligned');
hold on
grid on
plot(log.time(x_pos_theta0),u_d_pos_norm_0);
plot(log.time(x_pos_theta0),u_q_pos_norm_0);

subplot(2,2,3)
title('positive aligned');
hold on
grid on
plot(log.time(x_pos_theta1),u_d_pos_norm_1);
plot(log.time(x_pos_theta1),u_q_pos_norm_1);


subplot(2,2,2)
title('negative non-aligned');
hold on
grid on
plot(log.time(x_neg_theta0),u_d_neg_norm_0);
plot(log.time(x_neg_theta0),u_q_neg_norm_0);

subplot(2,2,4)
title('negative aligned');
hold on
grid on
plot(log.time(x_neg_theta1),u_d_neg_norm_1);
plot(log.time(x_neg_theta1),u_q_neg_norm_1);







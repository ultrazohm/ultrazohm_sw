load('step_response.mat');

lw = 2;

figure
subplot(121)
plot(time(1,:),i_dq_FCS_400kHz(1,:,1),'LineWidth',lw);
hold on
grid on
plot(time(1,:),i_dq_FCS_400kHz(2,:,1),'LineWidth',lw);
plot(time(1,:),i_dq_ref(2,:,1),'LineWidth',lw,'LineStyle','-.','Color','black');
plot(time(1,:),i_dq_FOC_20kHz(1,:,1),'LineWidth',lw);
plot(time(1,:),i_dq_FOC_20kHz(2,:,1),'LineWidth',lw);
title('step-up')
xlabel('Time / s')
ylabel('Current / A')

subplot(122)
plot(time(1,:),i_dq_FCS_400kHz(1,:,2),'LineWidth',lw);
hold on

grid on
plot(time(1,:),i_dq_FCS_400kHz(2,:,2),'LineWidth',lw);
plot(time(1,:),i_dq_ref(2,:,2),'LineWidth',lw,'LineStyle','-.','Color','black');
plot(time(1,:),i_dq_FOC_20kHz(1,:,2),'LineWidth',lw);
plot(time(1,:),i_dq_FOC_20kHz(2,:,2),'LineWidth',lw);
title('step-down')
xlabel('Time / s')
legend('i_d FCS', 'i_q FCS','i_q_,_r_e_f','i_d FOC', 'i_q FOC')

figure
subplot(121)
plot(time(1,:),i_dq_FCS_400kHz(1,:,1),'LineWidth',lw);
hold on
grid on
plot(time(1,:),i_dq_FCS_400kHz(2,:,1),'LineWidth',lw);
plot(time(1,:),i_dq_ref(2,:,1),'LineWidth',lw,'LineStyle','-.','Color','black');
plot(time(1,:),i_dq_FOC_20kHz(1,:,1),'LineWidth',lw);
plot(time(1,:),i_dq_FOC_20kHz(2,:,1),'LineWidth',lw);
title('step-up')
xlabel('Time / s')
ylabel('Current / A')
axis([0.009 0.015 -2 10])

subplot(122)
plot(time(1,:),i_dq_FCS_400kHz(1,:,2),'LineWidth',lw);
hold on

grid on
plot(time(1,:),i_dq_FCS_400kHz(2,:,2),'LineWidth',lw);
plot(time(1,:),i_dq_ref(2,:,2),'LineWidth',lw,'LineStyle','-.','Color','black');
plot(time(1,:),i_dq_FOC_20kHz(1,:,2),'LineWidth',lw);
plot(time(1,:),i_dq_FOC_20kHz(2,:,2),'LineWidth',lw);
title('step-down')
xlabel('Time / s')
legend('i_d FCS', 'i_q FCS','i_q_,_r_e_f','i_d FOC', 'i_q FOC')
axis([0.009 0.011 -2 10])

stepinfo(i_dq_FCS_400kHz(2,:,1),time(1,:),9.0)
stepinfo(i_dq_FOC_20kHz(2,:,1),time(1,:),9.0)
%Plotting Skript
close all;
path('C:\SoSe23\Masterarbeit\MatlabtoTikz\src',path);
%% inductances
% figure;
% set(0,'defaulttextinterpreter','latex');
% % subplot(2,2,1); 
% surf(d_current, q_current, Lqd_real);
% colormap default;
% grid on
% % legend('\omega_{mech} error', 'FontSize', 18);
% xlabel('$i_d/A$', 'FontSize', 18);
% ylabel('$i_q/A$', 'FontSize', 18);
% zlabel('$Lqd/H$', 'FontSize', 18);
% % xlim([0.19 200]);
% set(gca,'fontsize',20);

% subplot(2,2,2); 
% surf(Lqq_real);
% grid on
% % legend('\omega_{mech} error', 'FontSize', 18);
% xlabel('$i_d/A$', 'FontSize', 18);
% ylabel('$i_q/A$', 'FontSize', 18);
% zlabel('$L_{qq}/H$', 'FontSize', 18);
% % xlim([0.19 200]);
% set(gca,'fontsize',20);
% 
% subplot(2,2,3); 
% surf(Ldq_real);
% grid on
% % legend('\omega_{mech} error', 'FontSize', 18);
% xlabel('$i_d/A$', 'FontSize', 18);
% ylabel('$i_q/A$', 'FontSize', 18);
% zlabel('$L_{dq}/H$', 'FontSize', 18);
% % xlim([0.19 200]);
% set(gca,'fontsize',20);
% 
% subplot(2,2,4); 
% surf(Lqd_real);
% grid on
% % legend('\omega_{mech} error', 'FontSize', 18);
% xlabel('$i_d/A$', 'FontSize', 18);
% ylabel('$i_q/A$', 'FontSize', 18);
% zlabel('$L_{qd}/H$', 'FontSize', 18);
% % xlim([0.19 200]);
% set(gca,'fontsize',20);

%% approximation stuff

%% Selfinductance psid
psi_d_self_punkt1 = psi_d_approx(10,:);
psi_d_self_punkt2 = psi_d_approx(1,:);
psi_d_self_punkt1_real = fluxd_real(10,:);
psi_d_self_punkt2_real = fluxd_real(1,:);
figure;
set(0,'defaulttextinterpreter','latex');
% subplot(2,2,1); 
plot(d_current, psi_d_self_punkt1, '--','Color', '#0072BD');
hold on;
plot(d_current, psi_d_self_punkt2, '--','Color', "#D95319");
hold on;
plot(d_current, psi_d_self_punkt1_real,'Color', 'blue');
hold on;
plot(d_current, psi_d_self_punkt2_real,'Color', 'red');
%% Selfinductance psiq
psi_q_self_punkt1 = psi_q_approx(:,10);
psi_q_self_punkt2 = psi_q_approx(:,1);
psi_q_self_punkt1_real = fluxq_real(:,14);
psi_q_self_punkt2_real = fluxq_real(:,10);
figure;
set(0,'defaulttextinterpreter','latex');
% subplot(2,2,1); 
plot(q_current, psi_q_self_punkt1, '--','Color', '#0072BD');
hold on;
plot(q_current, psi_q_self_punkt2, '--','Color', "#D95319");
hold on;
plot(q_current, psi_q_self_punkt1_real,'Color', 'blue');
hold on;
plot(q_current, psi_q_self_punkt2_real,'Color', 'red');

%% Crosscoupling vergleich psid
psi_d_cross_punkt1 = psi_d_approx(:,10);
psi_d_cross_punkt2 = psi_d_approx(:,13);
psi_d_cross_punkt3 = psi_d_approx(:,16);
psi_d_cross_punkt1_real = fluxd_real(:,10);
psi_d_cross_punkt2_real = fluxd_real(:,13);
psi_d_cross_punkt3_real = fluxd_real(:,16);

figure;
set(0,'defaulttextinterpreter','latex');
% subplot(2,2,1); 
plot(q_current, psi_d_cross_punkt1, '--','Color', 'blue');
hold on;
plot(q_current, psi_d_cross_punkt2, '--','Color', 'red');
hold on;
plot(q_current, psi_d_cross_punkt3, '--','Color', 'green');
hold on;
plot(q_current, psi_d_cross_punkt1_real,'Color', 'black');
hold on;
plot(q_current, psi_d_cross_punkt2_real,'Color', 'cyan');
hold on;
plot(q_current, psi_d_cross_punkt3_real,'Color', 'magenta');

colormap default;
grid on
% legend('\omega_{mech} error', 'FontSize', 18);
xlabel('$i_q/A$', 'FontSize', 18);
% ylabel('$i_q/A$', 'FontSize', 18);
zlabel('$psi^d_{cross}/Vs$', 'FontSize', 18);
% xlim([0.19 200]);
set(gca,'fontsize',20);


%% crosscoupling vergleich psiq
psi_q_cross_punkt1 = psi_q_approx(14,:);
psi_q_cross_punkt2 = psi_q_approx(17,:);
psi_q_cross_punkt3 = psi_q_approx(20,:);
crossscheise = psiqself_padded-fluxq_real;
psi_q_cross_punkt1_real = fluxq_real(14,:);
psi_q_cross_punkt2_real = fluxq_real(17,:);
psi_q_cross_punkt3_real = fluxq_real(20,:);
figure;
set(0,'defaulttextinterpreter','latex');
% subplot(2,2,1); 
plot(d_current, psi_q_cross_punkt1,'--','Color', 'blue');
hold on;
plot(d_current, psi_q_cross_punkt2,'--','Color', 'red');
hold on;
plot(d_current, psi_q_cross_punkt3,'--','Color', 'green');
hold on;
plot(d_current, psi_q_cross_punkt1_real,'Color', 'black');
hold on;
plot(d_current, psi_q_cross_punkt2_real,'Color', 'cyan');
hold on;
plot(d_current, psi_q_cross_punkt3_real,'Color', 'magenta');
colormap default;
grid on
% legend('\omega_{mech} error', 'FontSize', 18);
xlabel('$i_d/A$', 'FontSize', 18);
% ylabel('$i_q/A$', 'FontSize', 18);
zlabel('$psi^q_{cross}/Vs$', 'FontSize', 18);
% xlim([0.19 200]);
set(gca,'fontsize',20);
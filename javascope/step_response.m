% plot of signals from 'Log_2024-06-03_16-00-34.csv'

% color definitions
rgb_ia = '#0000ff';
rgb_ib = '#007f00';
rgb_ic = '#ff0000';

rgb_ia2 = '#6666ff';
rgb_ib2 = '#00cc00';
rgb_ic2 = '#ff6666';

% define interval to plot
start_PI = 4753;
start_MPC = 26986;
finish_PI = start_PI+200;
finish_MPC = start_MPC+200;

% make time axis start at zero for every step response
time_PI = log.time(start_PI:finish_PI)-log.time(start_PI);
time_MPC = log.time(start_MPC:finish_MPC)-log.time(start_MPC);

% formatting
lw = 2;
fs = 24;
lw_leg = 2.5;
fs_leg = 18;

figure
subplot(221)
plot(time_PI,log.CH2(start_PI:finish_PI),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(time_PI,log.CH3(start_PI:finish_PI),'Color',rgb_ib,'LineWidth', lw);
plot(time_PI,log.CH4(start_PI:finish_PI),'Color',rgb_ic,'LineWidth', lw);
plot(time_PI,log.CH5(start_PI:finish_PI),'Color',rgb_ia2,'LineWidth', lw);
plot(time_PI,log.CH6(start_PI:finish_PI),'Color',rgb_ib2,'LineWidth', lw);
plot(time_PI,log.CH7(start_PI:finish_PI),'Color',rgb_ic2,'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_a_1','i_b_1','i_c_1','i_a_2','i_b_2','i_c_2');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 0.05 -6 6])
ylabel('i / A')

subplot(222)
plot(time_MPC,log.CH2(start_MPC:finish_MPC),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(time_MPC,log.CH3(start_MPC:finish_MPC),'Color',rgb_ib,'LineWidth', lw);
plot(time_MPC,log.CH4(start_MPC:finish_MPC),'Color',rgb_ic,'LineWidth', lw);
plot(time_MPC,log.CH5(start_MPC:finish_MPC),'Color',rgb_ia2,'LineWidth', lw);
plot(time_MPC,log.CH6(start_MPC:finish_MPC),'Color',rgb_ib2,'LineWidth', lw);
plot(time_MPC,log.CH7(start_MPC:finish_MPC),'Color',rgb_ic2,'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_a_1','i_b_1','i_c_1','i_a_2','i_b_2','i_c_2');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 0.05 -6 6])
ylabel('i / A')

subplot(223)
plot(time_PI,log.CH12(start_PI:finish_PI),'LineWidth', lw);
hold on
plot(time_PI,log.CH13(start_PI:finish_PI),'LineWidth', lw);
plot(time_PI,log.CH18(start_PI:finish_PI),'--','Color','black','LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q','i_{q,ref}');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 0.05 -1 6])
ylabel('i / A')
xlabel('Time /s')

subplot(224)
plot(time_MPC,log.CH12(start_MPC:finish_MPC),'LineWidth', lw);
hold on
plot(time_MPC,log.CH13(start_MPC:finish_MPC),'LineWidth', lw);
plot(time_MPC,log.CH18(start_MPC:finish_MPC),'--','Color','black','LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q','i_{q,ref}');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 0.05 -1 6])
ylabel('i / A')
xlabel('Time /s')
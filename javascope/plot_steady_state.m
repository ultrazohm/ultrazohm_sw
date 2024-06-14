% plot of signals from 'Log_2024-06-03_16-10-15.csv'

% color definitions
rgb_ia = '#0000ff';
rgb_ib = '#007f00';
rgb_ic = '#ff0000';

% define interval to plot
start = 2528;
finish = start+600;

% formatting
lw = 2;
fs = 20;
lw_leg = 2.5;
fs_leg = 18;

figure
subplot(311)
plot(log.time(start:finish),log.CH3(start:finish),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(log.time(start:finish),log.CH4(start:finish),'Color',rgb_ib,'LineWidth', lw);
plot(log.time(start:finish),log.CH5(start:finish),'Color',rgb_ic,'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_a','i_b','i_c');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text')
set(ht,'FontSize',fs_leg);
grid on
axis([0.63 0.78 -5.5 5.5])
ylabel('i / A')
subplot(312)
plot(log.time(start:finish),log.CH9(start:finish),'LineWidth', lw);
hold on
plot(log.time(start:finish),log.CH10(start:finish),'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text')
set(ht,'FontSize',fs_leg);
grid on
axis([0.63 0.78 -0.5 5.5])
ylabel('i / A')
subplot(313)
plot(log.time(start:finish),log.CH6(start:finish),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(log.time(start:finish),log.CH7(start:finish),'Color',rgb_ib,'LineWidth', lw);
plot(log.time(start:finish),log.CH8(start:finish),'Color',rgb_ic,'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('d_a','d_b','d_c');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text')
set(ht,'FontSize',fs_leg);
grid on
axis([0.63 0.78 0.2 0.8])
xlabel('Time / s')
ylabel('Equiv. mod. signal')
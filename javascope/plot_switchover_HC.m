% switchover from non harmonic control to harmonic control
% color definitions
rgb_ia = '#0000ff';
rgb_ib = '#007f00';
rgb_ic = '#ff0000';

rgb_ia2 = '#6666ff';
rgb_ib2 = '#00cc00';
rgb_ic2 = '#ff6666';

if(file_name_log == 'Log_2024-10-25_15-09-33') % PI FOC dqxy R no decoupl.
% define interval to plot
start = 14081;
finish = start+800; %14881
end

if(file_name_log == 'Log_2024-10-25_15-12-49') % IMPLMODMPC
% define interval to plot
start = 14601;
finish = start+800;
end

% make time axis start at zero for every step response
time = log.time(start:finish)-log.time(start);

% formatting
lw = 2;
fs = 24;
lw_leg = 2.5;
fs_leg = 18;

figure
subplot(211)
plot(time,log.CH12(start:finish),'LineWidth', lw);
hold on
plot(time,log.CH13(start:finish),'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 0.1 -1.1 12.5])
ylabel('i / A')
xlabel('Time /s')

subplot(212)
plot(time,log.CH10(start:finish),'LineWidth', lw);
hold on
plot(time,log.CH11(start:finish),'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_x','i_y');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 0.1 -1.1 1.1])
ylabel('i / A')
xlabel('Time /s')
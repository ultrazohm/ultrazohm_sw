% plot of signals from 'Log_2024-06-03_16-00-34.csv'

% color definitions
rgb_ia = '#0000ff';
rgb_ib = '#007f00';
rgb_ic = '#ff0000';

rgb_ia2 = '#6666ff';
rgb_ib2 = '#00cc00';
rgb_ic2 = '#ff6666';

if(file_name_log == 'Log_2024-10-25_14-57-01') % PI FOC dqxy R no decoupl.
% define interval to plot
start_up = 13214;
start_down = 47294;
finish_up = start_up+401;
finish_down = start_down+401;
end

if(file_name_log == 'Log_2024-10-28_16-09-59') % PI FOC dqxy R lin. decoupl.
% define interval to plot
start_up = 13129-80;
start_down = 45006-80;
finish_up = start_up+401;
finish_down = start_down+401;
end

if(file_name_log == 'Log_2024-10-25_15-04-54') % MPC DOB HC
% define interval to plot
start_up = 29180-80;
start_down = 72172-80;
finish_up = start_up+401;
finish_down = start_down+401;
end

% make time axis start at zero for every step response
time_up = log.time(start_up:finish_up)-log.time(start_up);
time_down = log.time(start_down:finish_down)-log.time(start_down);

% formatting
lw = 2;
fs = 24;
lw_leg = 2.5;
fs_leg = 18;

% time axis
t_end_plot_up = time_up(length(time_up));
t_end_plot_down = time_down(length(time_down));

% current axis
i_min = -18.5;
i_max = -i_min;

% duty cycle axis
d_min = -0.1;
d_max = 1.1;

% calc ITAE over the plotted time window
i_ref_up = log.CH9(start_up:finish_up);
i_q_up = log.CH13(start_up:finish_up);
e_q_up = abs(i_ref_up - i_q_up);
ITAE_up = trapz(e_q_up .*time_up)
i_ref_down = log.CH9(start_down:finish_down);
i_q_down = log.CH13(start_down:finish_down);
e_q_down = abs(i_ref_down - i_q_down);
ITAE_down = trapz(e_q_down .*time_down)

figure
subplot(221)
plot(time_up,log.CH14(start_up:finish_up),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(time_up,log.CH15(start_up:finish_up),'Color',rgb_ib,'LineWidth', lw);
plot(time_up,log.CH16(start_up:finish_up),'Color',rgb_ic,'LineWidth', lw);
plot(time_up,log.CH17(start_up:finish_up),'Color',rgb_ia2,'LineWidth', lw);
plot(time_up,log.CH18(start_up:finish_up),'Color',rgb_ib2,'LineWidth', lw);
plot(time_up,log.CH19(start_up:finish_up),'Color',rgb_ic2,'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('d_a_1','d_b_1','d_c_1','d_a_2','d_b_2','d_c_2');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 t_end_plot_up d_min d_max])
ylabel('Mod. signal')

subplot(222)
plot(time_down,log.CH14(start_down:finish_down),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(time_down,log.CH15(start_down:finish_down),'Color',rgb_ib,'LineWidth', lw);
plot(time_down,log.CH16(start_down:finish_down),'Color',rgb_ic,'LineWidth', lw);
plot(time_down,log.CH17(start_down:finish_down),'Color',rgb_ia2,'LineWidth', lw);
plot(time_down,log.CH18(start_down:finish_down),'Color',rgb_ib2,'LineWidth', lw);
plot(time_down,log.CH19(start_down:finish_down),'Color',rgb_ic2,'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('d_a_1','d_b_1','d_c_1','d_a_2','d_b_2','d_c_2');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 t_end_plot_down d_min d_max])
ylabel('Mod. signal')

subplot(223)
plot(time_up,log.CH12(start_up:finish_up),'LineWidth', lw);
hold on
plot(time_up,log.CH13(start_up:finish_up),'LineWidth', lw);
plot(time_up,log.CH9(start_up:finish_up),'--','Color','black','LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q','i_{q,ref}');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 t_end_plot_up i_min/2 i_max])
ylabel('i / A')
xlabel('Time /s')

subplot(224)
plot(time_down,log.CH12(start_down:finish_down),'LineWidth', lw);
hold on
plot(time_down,log.CH13(start_down:finish_down),'LineWidth', lw);
plot(time_down,log.CH9(start_down:finish_down),'--','Color','black','LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q','i_{q,ref}');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 t_end_plot_down i_min/2 i_max])
ylabel('i / A')
xlabel('Time /s')

figure
plot(time_up,log.CH20(start_up:finish_up),'*');
set(gca,'FontSize',fs);
[leg1, hobj, ~, ~] = legend('iterations');
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 t_end_plot_down 0 7])
ylabel('iterations')
xlabel('Time /s')

figure
plot(time_down,log.CH20(start_down:finish_down),'*');
set(gca,'FontSize',fs);
[leg1, hobj, ~, ~] = legend('iterations');
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([0 t_end_plot_down 0 7])
ylabel('iterations')
xlabel('Time /s')

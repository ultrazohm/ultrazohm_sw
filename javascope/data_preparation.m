%% Requirements to the log-file
% electrical rotor angle:                   CH1
% phase current ia1:                        CH2
% phase current ib1:                        CH3
% phase current ic1:                        CH4
% phase current ia1:                        CH5
% phase current ib1:                        CH6
% phase current ic1:                        CH7
% d-current:                                CH12
% q-current:                                CH13
% X-current:                                CH10
% Y-current:                                CH11
% a1 mod signal                             CH14
% b1 mod signal                             CH15
% c1 mod signal                             CH16
% iterations                                CH20

% color definitions
rgb_ia = '#0000ff';
rgb_ib = '#007f00';
rgb_ic = '#ff0000';

rgb_ia2 = '#6666ff';
rgb_ib2 = '#00cc00';
rgb_ic2 = '#ff6666';

% formatting
lw = 2;
fs = 24;
lw_leg = 2.5;
fs_leg = 18;



% current axis
i_min = -12.5;
i_max = -i_min;

num_of_measured_points = 1;
max_num_of_samples_in_this_batch = 64*10;
start=1;
stop=start+max_num_of_samples_in_this_batch;

%% Prepare data structure to store the measured points
time = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
angle_el = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
angle_el_norm = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
i_ph = zeros(6,max_num_of_samples_in_this_batch,num_of_measured_points);
i_dqXY = zeros(4,max_num_of_samples_in_this_batch,num_of_measured_points);
%% Assign data to the prepared structure
data_point_length = stop-start+1



%%
for i=1:num_of_measured_points
    time(i,1:data_point_length(i)) = log.time(start(i):stop(i));
    angle_el(i,1:data_point_length(i)) = log.CH1(start(i):stop(i));
    angle_el_norm = angle_el./(2*pi);
    f_sw_avg(i,1:data_point_length(i)) = log.CH19(start(i):stop(i));
    i_ph(1,1:data_point_length(i),i) = log.CH2(start(i):stop(i))';
    i_ph(2,1:data_point_length(i),i) = log.CH3(start(i):stop(i))';
    i_ph(3,1:data_point_length(i),i) = log.CH4(start(i):stop(i))';
    i_ph(4,1:data_point_length(i),i) = log.CH5(start(i):stop(i))';
    i_ph(5,1:data_point_length(i),i) = log.CH6(start(i):stop(i))';
    i_ph(6,1:data_point_length(i),i) = log.CH7(start(i):stop(i))';
    i_dqXY(1,1:data_point_length(i),i) = log.CH12(start(i):stop(i))';
    i_dqXY(2,1:data_point_length(i),i) = log.CH13(start(i):stop(i))';
    i_dqXY(3,1:data_point_length(i),i) = log.CH10(start(i):stop(i))';
    i_dqXY(4,1:data_point_length(i),i) = log.CH11(start(i):stop(i))';
end

% time axis
t_start = time(1);
t_finish = time(1)+0.08;
%%

for i=1:num_of_measured_points
    figure
    subplot(2,1,1)
    plot(time(i,1:data_point_length(i)),i_ph(1,1:data_point_length(i),i),'Color',rgb_ia,'LineWidth', lw);
    hold on
    plot(time(i,1:data_point_length(i)),i_ph(2,1:data_point_length(i),i),'Color',rgb_ib,'LineWidth', lw);
    plot(time(i,1:data_point_length(i)),i_ph(3,1:data_point_length(i),i),'Color',rgb_ic,'LineWidth', lw); 
    plot(time(i,1:data_point_length(i)),i_ph(4,1:data_point_length(i),i),'Color',rgb_ia2,'LineWidth', lw); 
    plot(time(i,1:data_point_length(i)),i_ph(5,1:data_point_length(i),i),'Color',rgb_ib2,'LineWidth', lw); 
    plot(time(i,1:data_point_length(i)),i_ph(6,1:data_point_length(i),i),'Color',rgb_ic2,'LineWidth', lw);
    set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_a_1','i_b_1','i_c_1','i_a_2','i_b_2','i_c_2');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([t_start t_finish i_min i_max])
ylabel('i / A')
    subplot(2,1,2)
    plot(time(i,1:data_point_length(i)),i_dqXY(1,1:data_point_length(i),i),'LineWidth', lw);
    hold on
    plot(time(i,1:data_point_length(i)),i_dqXY(2,1:data_point_length(i),i),'LineWidth', lw);
    plot(time(i,1:data_point_length(i)),i_dqXY(3,1:data_point_length(i),i),'LineWidth', lw); 
    plot(time(i,1:data_point_length(i)),i_dqXY(4,1:data_point_length(i),i),'LineWidth', lw); 
        set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q','i_X','i_Y');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([t_start t_finish -3.5 i_max])
ylabel('i / A')
xlabel('Time / s')
end

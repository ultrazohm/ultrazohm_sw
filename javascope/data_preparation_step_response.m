%% Requirements to the log-file
% electrical rotor angle:                   CH1
% phase current ia1:                        CH3
% phase current ib1:                        CH4
% phase current ic1:                        CH5
% d-current:                                CH9
% q-current:                                CH10
% q-current ref:                            CH11
% measured average switching frequency:     CH19
% measuring trigger signal:                 CH20

%% Determine the number of measured points (number of rising edges of measuring trigger)
clc
data_sampling_freq_Hz = 1/(log.time(2)-log.time(1))
% variable declaration
k=1;
l=1;
num_of_measured_points=0;
disp('determine number of measured points...');
% evaluate number of measured points (number of rising edges of the
% measure_flag in CH20
for i=2:length(log.CH20)
    if log.CH20(i) == 1 && log.CH20(i-1) == 0
        num_of_measured_points = num_of_measured_points+1;
    end
end
out = ['number of measured points = ', num2str(num_of_measured_points)];
disp(out);
%% Get all indices of the rising and falling edges of the measuring trigger

% variable declaration
idx_rising = zeros(1,num_of_measured_points);
idx_falling = zeros(1,num_of_measured_points);

disp('get indices of rising and falling edges of the measuring trigger variable...')
% extract rising and falling edges of the measuring flag (make sure the
% flag varaible is always assigned to CH20 of the scope variables)
for i=2:length(log.CH20)
    if log.CH20(i) == 1 && log.CH20(i-1) == 0
        idx_rising(k) = int32(log.time(i)*data_sampling_freq_Hz);
        k = k+1;
    end
    if log.CH20(i) == 0 && log.CH20(i-1) == 1
        idx_falling(l) = int32(log.time(i)*data_sampling_freq_Hz);
        l = l+1;
    end
end
disp('indices stored in idx_rising and idx_falling variables');
%% Look for the measuring point with the most data points and its length (They differ in length since the length is dependant on the rotational speed, which slightly varies throughout the measuring procedure)
disp('evaluating maximum number of samples in the measured points...')

start = idx_rising;
stop = idx_falling;

% let's show half of the duration of the captured step respnse before the
% step by calculating kind of pre-trigger
pre_trigger_samples=ceil((stop-start)/2);
data_point_length = stop-start+1+pre_trigger_samples;
start = start-pre_trigger_samples;

max_num_of_samples_in_this_batch = max(stop-start);
out = ['maximum number of samples = ', num2str(max_num_of_samples_in_this_batch)];
disp(out)
%% Prepare data structure to store the measured points


time = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
angle_el = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
angle_el_norm = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
f_sw_avg = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
i_ph = zeros(3,max_num_of_samples_in_this_batch,num_of_measured_points);
i_dqXY = zeros(2,max_num_of_samples_in_this_batch,num_of_measured_points);
i_dq_ref = zeros(2,max_num_of_samples_in_this_batch,num_of_measured_points);
%% Assign data to the prepared structure


for i=1:num_of_measured_points
    time(i,1:data_point_length(i)) = log.time(start(i):stop(i));
    angle_el(i,1:data_point_length(i)) = log.CH1(start(i):stop(i));
    angle_el_norm = angle_el./(2*pi);
    f_sw_avg(i,1:data_point_length(i)) = log.CH19(start(i):stop(i));
    i_ph(1,1:data_point_length(i),i) = log.CH3(start(i):stop(i))';
    i_ph(2,1:data_point_length(i),i) = log.CH4(start(i):stop(i))';
    i_ph(3,1:data_point_length(i),i) = log.CH5(start(i):stop(i))';
%     i_ph(4,1:data_point_length(i),i) = log.CH6(start(i):stop(i))';
%     i_ph(5,1:data_point_length(i),i) = log.CH7(start(i):stop(i))';
%     i_ph(6,1:data_point_length(i),i) = log.CH8(start(i):stop(i))';
    i_dqXY(1,1:data_point_length(i),i) = log.CH9(start(i):stop(i))';
    i_dqXY(2,1:data_point_length(i),i) = log.CH10(start(i):stop(i))';
%     i_dqXY(3,1:data_point_length(i),i) = log.CH11(start(i):stop(i))';
%     i_dqXY(4,1:data_point_length(i),i) = log.CH12(start(i):stop(i))';
    i_dq_ref(2,1:data_point_length(i),i) = log.CH11(start(i):stop(i))';
end

%% let time for every step response start at zero
time(1,:) = time(1,:)-time(1,1);
time(2,:) = time(2,:)-time(2,1);
%%
lw = 2;

figure
subplot(121)
plot(time(1,:),i_dqXY(1,:,1),'LineWidth',lw);
% plot(time(1,:),i_dq_step_FCS_400kHz(1,:,1),'LineWidth',lw);
hold on
grid on
plot(time(1,:),i_dqXY(2,:,1),'LineWidth',lw);
plot(time(1,:),i_dq_ref(2,:,1),'LineWidth',lw,'LineStyle','-.','Color','black');
% plot(time(1,:),i_dq_FCS_400kHz(2,:,1),'LineWidth',lw);
% plot(time(1,:),angle_el(1,:,1),'LineWidth',lw);
title('step-up')
xlabel('Time / s')
ylabel('Current / A')

subplot(122)
plot(time(1,:),i_dqXY(1,:,2),'LineWidth',lw);
% plot(time(1,:),i_dq_FCS_400kHz(1,:,2),'LineWidth',lw);
hold on
grid on
plot(time(1,:),i_dqXY(2,:,2),'LineWidth',lw);
plot(time(1,:),i_dq_ref(2,:,2),'LineWidth',lw,'LineStyle','-.','Color','black');
% plot(time(1,:),i_dq_FCS_400kHz(2,:,2),'LineWidth',lw);
% plot(time(1,:),angle_el(2,:,1),'LineWidth',lw);
title('step-down')
xlabel('Time / s')
legend('i_d', 'i_q','i_q_,_r_e_f')

stepinfo(i_dqXY(2,:,1),time(1,:),9.0)
stepinfo(i_dqXY(2,:,2),time(2,:),0.0)
%% Upsample the data to the sample rate of the LMG
time_1_2121MHz = linspace(0,0.03,36365);

angle_el_1_2121MHz(1,:) = interp1(time(1,:),angle_el(1,:,1),time_1_2121MHz);



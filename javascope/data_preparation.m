%% Requirements to the log-file
% electrical rotor angle:                   CH1
% phase current ia1:                        CH3
% phase current ib1:                        CH4
% phase current ic1:                        CH5
% phase current ia2:                        CH6
% phase current ib2:                        CH7
% phase current ic2:                        CH8
% d-current:                                CH9
% q-current:                                CH10
% X-current:                                CH11
% Y-current:                                CH12
% measured average switching frequency:     CH19
% measuring trigger signal:                 CH20

%% Determine the number of measured points (number of rising edges of measuring trigger)
clc
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
        idx_rising(k) = int32(log.time(i)*1e4);
        k = k+1;
    end
    if log.CH20(i) == 0 && log.CH20(i-1) == 1
        idx_falling(l) = int32(log.time(i)*1e4);
        l = l+1;
    end
end
disp('indices stored in idx_rising and idx_falling variables');
%% Look for the measuring point with the most data points and its length (They differ in length since the length is dependant on the rotational speed, which slightly varies throughout the measuring procedure)
disp('evaluating maximum number of samples in the measured points...')
start = idx_rising;
stop = idx_falling;

max_num_of_samples_in_this_batch = max(stop-start);
out = ['maximum number of samples = ', num2str(max_num_of_samples_in_this_batch)];
disp(out)
%% Prepare data structure to store the measured points
time = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
angle_el = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
angle_el_norm = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
f_sw_avg = zeros(num_of_measured_points,max_num_of_samples_in_this_batch);
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
    i_ph(1,1:data_point_length(i),i) = log.CH3(start(i):stop(i))';
    i_ph(2,1:data_point_length(i),i) = log.CH4(start(i):stop(i))';
    i_ph(3,1:data_point_length(i),i) = log.CH5(start(i):stop(i))';
    i_ph(4,1:data_point_length(i),i) = log.CH6(start(i):stop(i))';
    i_ph(5,1:data_point_length(i),i) = log.CH7(start(i):stop(i))';
    i_ph(6,1:data_point_length(i),i) = log.CH8(start(i):stop(i))';
    i_dqXY(1,1:data_point_length(i),i) = log.CH9(start(i):stop(i))';
    i_dqXY(2,1:data_point_length(i),i) = log.CH10(start(i):stop(i))';
    i_dqXY(3,1:data_point_length(i),i) = log.CH11(start(i):stop(i))';
    i_dqXY(4,1:data_point_length(i),i) = log.CH12(start(i):stop(i))';
end
%%
for i=1:num_of_measured_points
mean_avg_f_sw_over_trigger_period(i) = mean(f_sw_avg(i,2:end));
end
%%

for i=1:num_of_measured_points
    figure
    plot(time(i,1:data_point_length(i)),i_ph(1,1:data_point_length(i),i));
    hold on
    plot(time(i,1:data_point_length(i)),i_ph(2,1:data_point_length(i),i));
    plot(time(i,1:data_point_length(i)),i_ph(3,1:data_point_length(i),i)); 
end

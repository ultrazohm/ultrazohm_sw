clc
clear
close all

eval_name='twister_eval_*.csv';
training_name='export_test_*.csv';

file_list_eval=dir(eval_name);
file_list_training=dir(training_name);


for i=1:length(file_list_eval)
    eval_log{i}=readtable(file_list_eval(i).name);
end

for i=1:length(file_list_training)
    training_log{i}=readtable(file_list_training(i).name);
end

%%
figure

for i=1:length(training_log)
subplot(4,1,1)
    plot(training_log{i}.episode_loss);
hold on
grid on

subplot(4,1,2)
    plot(training_log{i}.cumulative_reward);
hold on
grid on

subplot(4,1,3)
    plot(training_log{i}.global_reward_metric);
hold on
grid on

subplot(4,1,4)
    plot(training_log{i}.epsilon_per_epsiode);
hold on
grid on
end


%%
% figure
% 
% for i=1:length(training_log)
%     plot(eval_log{i}.cumulative_reward);
% hold on
% grid on
% 
% end
% 
% 




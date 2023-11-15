% load log
close all
clear
%% extract all episodes
filename = 'Log_2023-11-15_11-35-48.mat';
load(filename)
TF =ischange (log.CH17);
I = find(TF == 1);

log_new= log(I,:)
% filename = 'Log_2023-11-15_11-35-48.mat';
% load(filename)
% Eval_DQN_train
% filename = 'Log_2023-11-15_11-35-48.mat';
% Eval_DQN_sample
% filename = 'Log_2023-11-15_11-35-48.mat';
% Eval_DQN_eval_step
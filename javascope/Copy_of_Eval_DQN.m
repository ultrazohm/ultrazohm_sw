% load log
close all
clear
%% extract all episodes
filename = 'Log_2023-11-15_08-02-25';
load(filename)
% sprung in den episoden finden und daten unterteilen, hier ist log.CH17
TF = ischange (log.CH17);
I = find(TF == 1);
Array = table2array(log);
for i=1:(length(I)-1)
    looparray{1} = [];
    looparray{1} = Array(I(i):I(i+1),:);
    % get minimums for all rows
    MinVal=min(cell2mat(looparray));
    % get min from episode reward (CH.16 = index 17)
    epreward(i)= MinVal(17);
end
epreward = epreward';
epreward(epreward==0) = [];
grr = zeros(length(epreward),1);
% definiere smoothfactor für grr
smoothfact = 0.7;
% calculate global running reward
for i=1:length(epreward)
    if (i==1)
        grr(1)=epreward(1);
    else
        grr(i)=smoothfact*epreward(i-1)+(1-smoothfact)*epreward(i);
    end
end
%
figure
plot(epreward);
hold on;
grid on;
plot(grr);
% export grr and epreward für pgfplots
x=linspace(1,length(epreward),length(epreward))';
epcsv = [x,epreward];
grcsv = [x,grr];
epT = array2table(epcsv);
epT.Properties.VariableNames(1:2) = {'Episoden','Reward $R_\text{t}$'};
writetable(epT,'DQNV1/epreward.csv');
grrT = array2table(grcsv);
grrT.Properties.VariableNames(1:2) = {'Episoden','Rewardmetrik $G_\text{t}$'};
writetable(grrT,'DQNV1/grreward.csv');

%% werte die letzten episoden aus, performance

%log_new= log(I,:)
% filename = 'Log_2023-11-15_08-02-25';
% load(filename)
% Eval_DQN_train
% filename = 'Log_2023-11-15_08-02-25';
% Eval_DQN_sample
% filename = 'Log_2023-11-15_08-02-25';
% Eval_DQN_eval_step
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
epT.Properties.VariableNames(1:2) = {'Episoden','Reward'};
writetable(epT,'DQNV1/epreward.csv');
grrT = array2table(grcsv);
grrT.Properties.VariableNames(1:2) = {'Episoden','Rewardmetrik'};
writetable(grrT,'DQNV1/grreward.csv');

%% werte die letzten episoden aus, eval step

% true(logical 1) wenn trigger 10
TX = log.CH11==10;
% get all indices
IX = find(TX == 1);
% getevalarray
evalArray=Array(IX(1)-1:end,:);
% cut eval steps into separate arrays
B=diff(evalArray(:,12));
indexstart = find(B>5);
indexend = find(B<-5);
% delete 4th run manual
indexstart(4)=[];
indexend(4)=[];
%% make plots
for i=1:length(indexstart)
figure(i)
plot(evalArray(indexstart(i):indexend(i),6),'DisplayName','StartPosition');
hold on
plot(evalArray(indexstart(i):indexend(i),7),'DisplayName','EndPosition');
hold on
plot(evalArray(indexstart(i):indexend(i),2)*1000,'DisplayName','IstPositon');
hold off
grid on;
legend
xlabel('Zeit')
ylabel('Position in mm')
end
%% export data eval csv

for i=1:length(indexstart)
x = linspace(1,indexend(i)-indexstart(i)+1,indexend(i)-indexstart(i)+1)';
startpos = evalArray(indexstart(i):indexend(i),6);
endpos = evalArray(indexstart(i):indexend(i),7);
istpos = evalArray(indexstart(i):indexend(i),2);  
eval = [x,startpos,endpos,istpos];
% downsample data now
eval= downsample(eval,20);
evalT = array2table(eval);
evalT.Properties.VariableNames(1:4) = {'timesteps','startpos','endpos','istpos'};
writetable(evalT,['DQNV1/evalrun' num2str(i) '.csv']);
end

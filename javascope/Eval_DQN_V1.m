% load log
close all
clear
filename = 'DQNV1_50xpos.mat';
load(filename)

% lösche alle Zeilen, bei denen DQN aktiv ist
whos log
idx = (log.CH11 == 0 | log.CH11 == 1 | log.CH11 == 2 | log.CH11 == 3 | log.CH11 == 5);
log(idx,:) = [];
whos log
figure
plot(log.CH15);
hold on;
grid on;
%ylim([0 1000])

clear log;
load(filename)
% lösche alle Zeilen, außer DQN aktiv
whos log
idx = (log.CH11 == 0 | log.CH11 == 4 | log.CH11 == 2 | log.CH11 == 3 | log.CH11 == 5);
log(idx,:) = [];
whos log
figure
plot(log.CH16);
grid on;
figure
plot(log.CH13);
grid on;
[pks,locs] = findpeaks(-log.CH16);
figure
plot(-pks);
grid on;
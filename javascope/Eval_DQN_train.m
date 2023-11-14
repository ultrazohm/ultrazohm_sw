% load log
load(filename)

% lösche alle Zeilen, bei denen DQN aktiv ist
whos log
idx = (log.CH11 == 0 | log.CH11 == 1 | log.CH11 == 2 | log.CH11 == 3 | log.CH11 == 5);
log(idx,:) = [];
whos log
figure
plot(log.CH15,'DisplayName','Loss');
hold on;
xlabel('Trainingszeit')
ylabel('Loss')
grid on;
legend
clear;
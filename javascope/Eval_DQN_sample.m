load(filename)

idx = (log.CH11 == 0 | log.CH11 == 4 | log.CH11 == 2 | log.CH11 == 3 | log.CH11 == 5);
log(idx,:) = [];
figure
plot(log.CH16,'DisplayName','Episode Reward');
grid on;
xlabel('Trainingszeit')
ylabel('Episoden Reward')
legend
figure
plot(log.CH13,'DisplayName','Epsilon');
xlabel('Trainingszeit')
ylabel('Epsilon')
grid on;
[pks,locs] = findpeaks(-log.CH16);
figure
plot(-pks,'DisplayName','Peaks');
grid on;
xlabel('Epoche')
ylabel('Reward pro Epoche')
legend
clear

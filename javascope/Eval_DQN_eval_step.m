% load log
load(filename)

idx = (log.CH11 ~= 10);
log(idx,:) = [];
figure
plot(log.CH12);
grid on;
figure
% plot(log.CH8)
% hold on;
plot(log.CH5,'DisplayName','StartPosition')
hold on;
plot(log.CH6,'DisplayName','EndPosition')
hold on;
plot(log.CH1,'DisplayName','Schlitten Istposition')
grid on;
xlabel('Zeit')
ylabel('Position in mm')
legend
% plot position error
figure
plot(log.CH7*1000,'DisplayName','Positionsfehler')
xlabel('Zeit')
ylabel('Position in mm')
grid on;
legend
% clear
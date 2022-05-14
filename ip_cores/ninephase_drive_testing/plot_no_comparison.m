f1=figure();

hold on;
subplot(5,1,1);
title('pwm 2khz')
plot(out.abc1.data(:,1));

subplot(5,1,2);
plot(out.abc1.data);

subplot(5,1,3);
plot(out.abc2.data);

subplot(5,1,4);
plot(out.abc3.data);

subplot(5,1,5);
plot(out.subspaces.data);

hold off;
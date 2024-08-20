start = 194;
stop = start + 400 -2;

time = log.time(start:stop);
time = time - time(1);
raw = log.CH1(start:stop);

time_saw = log.time(start:stop)
time_saw = time_saw - time_saw(1);
saw = log.CH2(start:stop)

error = log.CH4(start:stop)

% angle vector based on 4 kHz sampling rate for one mech revolution at 600
% rpm
angle = 0:(2*pi/399):(2*pi-(2*pi/399));
diff = saw-raw;
mean_diff = mean(diff);
diff_no_mean = diff-mean_diff;

% compensation function parameters
a1 = 0.01995;
b1 = 2.037;
c1 = -0.1551;
a2 = 0.01093;
b2 = 0.9117;
c2 = -2.692;
a3 = -0.001842;
b3 = 4.043;
c3 = -0.3086;
a4 = 0.004457;
b4 = 4.781;
c4 = 2.345;
a5 = 0.01335;
b5 = 3.915;
c5 = -6.021;

% angle vector based on 4 kHz sampling rate for one mech revolution at 600
% rpm
x = 0:(2*pi/400):(2*pi-(2*pi/400));
% x = raw;

% compensation function according to curve fit
for i=1:400
y(i,:) = a1*sin(b1*x(i)+c1) + a2*sin(b2*x(i)+c2) + a3*sin(b3*x(i)+c3) + a4*sin(b4*x(i)+c4) + a5*sin(b5*x(i)+c5) - 0.015;
end

compensated = raw+y;

figure
subplot(411)
plot(time,raw)
hold on
plot(time_saw,saw)
subplot(412)
plot(time,diff)
hold on
plot(time,y)
subplot(413)
plot(x,y)
subplot(414)
plot(time,compensated-saw)
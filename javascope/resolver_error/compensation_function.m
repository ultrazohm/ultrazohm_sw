% compensation function parameters
a1 =0.02495;
b1 = 1.984;
c1 = -1.062;
a2 = 0.01855;
b2 = 0.999;
c2 = 2.472;
a3 = 0.008966;
b3 = 3.995;
c3 = 1.804;
a4 = 0.001554;
b4 = 7.968;
c4 = -2.66;

% angle vector based on 4 kHz sampling rate for one mech revolution at 600
% rpm
x = 0:(2*pi/400):(2*pi-(2*pi/400));

% compensation function according to curve fit
for i=1:400
y(i,:) = a1*sin(b1*x(i)+c1) + a2*sin(b2*x(i)+c2) + a3*sin(b3*x(i)+c3) + a4*sin(b4*x(i)+c4);
end
% plot curve fit and original measured error function
figure
plot(x,y)
hold on
plot(x,sig)

compensated_angle = signal+y;
error_remaining = test_signal-compensated_angle;

figure
plot(angle_mech,signal)
hold on
plot(angle_mech,compensated_angle)
plot(angle_mech,error_remaining)
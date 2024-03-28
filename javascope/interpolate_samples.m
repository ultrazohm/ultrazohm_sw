time_10kHz = linspace(0,0.01,100);
time_1_212121MHz = linspace(0,0.01,1.212121e+04);
angle_10kHz = linspace(0,2*pi,100);

% linear interpolation to create sampling points at higher rate
angle_1_212121MHz = interp1(time_10kHz,angle_10kHz,time_1_212121MHz);

figure
plot(time_10kHz,angle_10kHz,'*')
hold on
plot(time_1_212121MHz,angle_1_212121MHz,'+')

% Requirement: log file imported via JS_plot_data.m script
T = 5*(1/50);
fs = 4000;
test_time = (0:1/fs:T-1/fs)';
test_signal = (2*pi*sawtooth(2*pi*50*test_time)*0.5+pi);

%linewidth axes
lwa=1;
%linewidth lines
lw=2;
%Fontsize
fs=24;
% bar width in FFT plot
barWidth = 1.5;

% CHOOSE TIME SEGMENT OF SIGNAL IN THE LOG CHANNEL
start = 205;
stop = start+(20*400)-1; %2400

% CHOOSE LOG CHANNEL TO BE FOURIER TRANSFORMED
time = log.time(start:stop);
signal = log.CH20(start:stop);

% Sawtooth test signal for demonstration
% time = test_time(start:stop);
% signal = test_signal(start:stop);

% determine max frequency that can be obtained from the data
f_max_kHz = 0.001/(2*(time(2)-time(1)))

% do mathworks FFT
F= signal;
Fs = length(time);
T = 1 / Fs;
L = Fs;
d = Fs*(0:(L/2))/L;                             % Zeitvektor
Y = fft(F);                                     % Ausführung FFT, da aber nur ein Input-Argument =  Compute DFT 
P2 = abs(Y/L);                                  % Berechnung zweiseitiges Spektrum
P1 = P2(1:L/2+1,:);                             % Berechnung einseitiges Spektrum
P1(2:end-1) = 2*P1(2:end-1);
FFT_sig=P1;
freq=d.*1/(time(2)-time(1))/Fs;                 % Rückskalieren, wenn die x-Achse beliebig ist

% Find maximum amplitude in spectrum, 
% assuming it is the fundamental of the signal
[FundamentalSignalAmplitude ,VectorNumber] = max(FFT_sig)
%% Plot
figure
subplot(211)
plot(time,signal,'LineWidth',lw);
hold on
plot(time,signal,'LineWidth',lw);
set(gca,'FontSize',fs);
grid on
xlabel('Time / s')
ylabel('signal(t)')
subplot(212)
hBar = bar(freq(1,:)*0.001,FFT_sig(:,1), 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 1.01*f_max_kHz 0 1.2*FundamentalSignalAmplitude]);
xlabel('Frequency / kHz')
ylabel('signal(f)');
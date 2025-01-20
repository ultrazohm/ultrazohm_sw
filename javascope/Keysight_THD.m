%% input raw data
raw_data = scope1;

time = raw_data.xaxis;
ia = raw_data.ia;

TB = 0.24;   % block length of measurement in s

%% prepare data
dt = time(2)-time(1);
fs = 1/dt;  % sampling frequency

no_of_samples = TB/dt;

time = raw_data.xaxis(1:no_of_samples);
time = time + abs(time(1));
signal = raw_data.ia(1:no_of_samples);

figure
plot(time,signal)

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



% Calculate angle of frequency components
phi = angle(Y(1:L/2+1));

% Calculate THD
[FundamentalCurrent ,VectorNumber] = max(FFT_sig) %Find fundamental in vector (assumed that fundamental equals maximum)
FFT_sig_withoutFundamental=FFT_sig;
FFT_sig_withoutFundamental(VectorNumber,:)=0; %Eliminate fundamental in order to calculate THD

% remove dc value
FFT_sig_withoutFundamental(1,:)=0;

%bsxfun() multipliziert den Vektor in jeder spalte/zeile mit sich selbst,
%dadurch erreiche ich, das jeder Wert im urpsrünglichen Vektor quadriert
%wird.
I_squared_Harmonics = sum(bsxfun(@times, FFT_sig_withoutFundamental, FFT_sig_withoutFundamental)); %[A] Respect all harmonics (without the fundamental) 

THD = (sqrt(I_squared_Harmonics)/FundamentalCurrent)*100 %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
%% Plot
%linewidth axes
lwa=1;
%linewidth lines
lw=2;
%Fontsize
fs=24;
% bar width in FFT plot
barWidth = 24.5;

plot_f_max_kHz = 20;

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
hBar = bar(freq(1,:)*0.001,FFT_sig(:,1)/FundamentalCurrent*100, 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 1.01*plot_f_max_kHz 0 1.2*FundamentalCurrent]);
xlabel('Frequency / kHz')
ylabel('signal(f) / %');
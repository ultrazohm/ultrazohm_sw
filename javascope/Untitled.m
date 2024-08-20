figure
plot(fftimplmodmpc1.xaxis,fftimplmodmpc1.ia,'LineWidth',2.0)
hold on
xlabel('Frequency / Hz')
ylabel('Ampl / dB')
axis([0 1000 -100 50])

figure
plot(indvoltdepengLL1200.xaxis+1.0, indvoltdepengLL1200.ua,'LineWidth',1.0)
hold on
plot(indvoltdepengLL1200.xaxis+1.0, indvoltdepengLL1200.ub,'LineWidth',1.0)
xlabel('Time / s')
ylabel('Voltage / V')
axis([0 0.2 -250 250])

% spectrum plot axis
f_max = 1.0; % kHz
THD_max = 10; % per cent 
barWidth = 1.5;

i_nom = 230.0; % for DepEng motor

% formatting
lw = 2;
fs = 24;
lw_leg = 2.5;
fs_leg = 18;



time_cut = indvoltdepengLL1200.xaxis(1:62499)+1;
F= indvoltdepengLL1200.ua(1:62499);

Fs = length(time_cut);
T = 1 / Fs;
L = Fs;
d = Fs*(0:(L/2))/L;                                     % Zeitvektor
Y = fft(F);                                             % Ausführung FFT, da aber nur ein Input-Argument =  Compute DFT 
P2 = abs(Y/L);                                          % Berechnung zweiseitiges Spektrum
P1 = P2(1:L/2+1,:);                                       % Berechnung einseitiges Spektrum
P1(2:end-1) = 2*P1(2:end-1);
FFT_sig=P1;
%freq=d;                                                % Rückskalieren,wenn die x-Achse von 0 bis 1 geht (Sonderfall)
freq=d.*1/(time_cut(2)-time_cut(1))/Fs;                 % Rückskalieren, wenn die x-Achse beliebig ist

% Calculate THD
[FundamentalCurrent ,VectorNumber] = max(FFT_sig) %Find fundamental in vector (assumed that fundamental equals maximum)
FFT_sig_withoutFundamental=FFT_sig;
FFT_sig_withoutFundamental(VectorNumber,:)=0; %Eliminate fundamental in order to calculate THD

% remove dc value
FFT_sig_withoutFundamental(1,:)=0; 


% FFT_sig_withoutFundamental(14,:)=0; 
% FFT_sig_withoutFundamental(28,:)=0; 
% 
% FFT_sig_withoutFundamental(61,:)=0;
% FFT_sig_withoutFundamental(101,:)=0;
% FFT_sig_withoutFundamental(141,:)=0;
% FFT_sig_withoutFundamental(221,:)=0;
% for k= (VectorNumber-15):(VectorNumber+15)
%     FundamentalCurrent = FundamentalCurrent + FFT_sig_withoutFundamental(k);
%     FFT_sig_withoutFundamental(k,:)=0; %Eliminate fundamental in order to calculate THD
% end

% bar(freq(1,:)./freq(1,VectorNumber(1)),FFT_sig_withoutFundamental(:,1)/FundamentalCurrent(1)*100, 'BarWidth',barWidth)
% bar(freq(1,:)./freq(1,VectorNumber(1)),FFT_sig_withoutFundamental(:,1)/mag(1)*100, 'BarWidth',barWidth)
% axis([0 10101 0 0.7]);

%bsxfun() multipliziert den Vektor in jeder spalte/zeile mit sich selbst,
%dadurch erreiche ich, das jeder Wert im urpsrünglichen Vektor quadriert
%wird.
I_squared_Harmonics = sum(bsxfun(@times, FFT_sig_withoutFundamental, FFT_sig_withoutFundamental)) %[A] Respect all harmonics for FCS-MPC (without the fundamental) 
% calculate THD
% THD = (sqrt(I_squared_Harmonics)/FundamentalCurrent)*100 %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
THD_components = (sqrt(I_squared_Harmonics)/FundamentalCurrent)*100; %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
TDD_components = (sqrt(I_squared_Harmonics)/i_nom)*100;
% THD_components(k) = (sqrt(I_squared_Harmonics(k))/mag(k))*100; %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
% TDD_components(k) = (sqrt(I_squared_Harmonics(k))/i_nom)*100;

THD_components
TDD_components

figure
% hBar = bar(freq(1,:)*0.001,FFT_sig_withoutFundamental(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
hBar = bar(freq(1,:)*0.001,FFT_sig(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 f_max 0 THD_max]);
xlabel('Frequency / kHz')
ylabel('u_a_b (f) / %');
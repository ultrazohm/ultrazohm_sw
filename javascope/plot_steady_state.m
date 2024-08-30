% plot of signals from 'Log_2024-07-30_10-51-51.csv'
% electrical rotor angle:                   CH1
% phase current ia1:                        CH2
% phase current ib1:                        CH3
% phase current ic1:                        CH4
% phase current ia1:                        CH5
% phase current ib1:                        CH6
% phase current ic1:                        CH7
% d-current:                                CH12
% q-current:                                CH13
% X-current:                                CH10
% Y-current:                                CH11
% a1 mod signal                             CH14
% b1 mod signal                             CH15
% c1 mod signal                             CH16
% iterations                                CH20

% color definitions
rgb_ia = '#0000ff';
rgb_ib = '#007f00';
rgb_ic = '#ff0000';

rgb_ia2 = '#6666ff';
rgb_ib2 = '#00cc00';
rgb_ic2 = '#ff6666';

% define interval to plot
start = 1;
finish = start+1200;

% time axis
t_start = 0.0;
t_finish = 0.05;

% current axis
i_min = -6.5;
i_max = -i_min;

% spectrum plot axis
f_max = 1.0; % kHz
THD_max = 10; % per cent 
barWidth = 1.5;

i_nom = 10.0; % for DepEng motor

% formatting
lw = 2;
fs = 24;
lw_leg = 2.5;
fs_leg = 18;

% 
i_dq = sqrt(i_dqXY(1,:).^2+i_dqXY(2,:).^2);

%% FFT of phase currents for spectral plot

% for i=2:2
for i=1:num_of_measured_points
    F=i_ph(:,1:data_point_length(i),i)';
    F_id=i_dqXY(1,1:data_point_length(i),i)';
    F_iq=i_dqXY(2,1:data_point_length(i),i)';
% F=i_ph(:,1:800,i)';
%
Fs = length(time);
% Fs = 800;
T = 1 / Fs;
L = Fs;
d = Fs*(0:(L/2))/L;                                     % Zeitvektor
Y = fft(F);                                             % Ausführung FFT, da aber nur ein Input-Argument =  Compute DFT 
Y_id = fft(F_id);
Y_iq = fft(F_iq);
P2 = abs(Y/L);                                          % Berechnung zweiseitiges Spektrum
P1 = P2(1:L/2+1,:);   
P2_id = abs(Y_id/L);                                          % Berechnung zweiseitiges Spektrum
P1_id = P2_id(1:L/2+1,:); % Berechnung einseitiges Spektrum
P2_iq = abs(Y_iq/L);                                          % Berechnung zweiseitiges Spektrum
P1_iq = P2_iq(1:L/2+1,:);                                       % Berechnung einseitiges Spektrum
P1(2:end-1) = 2*P1(2:end-1);
P1_id(2:end-1) = 2*P1_id(2:end-1);
P1_iq(2:end-1) = 2*P1_iq(2:end-1);
FFT_sig=P1;
FFT_sig_id=P1_id;
FFT_sig_iq=P1_iq;
%freq=d;                                                % Rückskalieren,wenn die x-Achse von 0 bis 1 geht (Sonderfall)
freq=d.*1/(time(i,2)-time(i,1))/Fs;                 % Rückskalieren, wenn die x-Achse beliebig ist

% Calculate THD
[FundamentalCurrent ,VectorNumber] = max(FFT_sig) %Find fundamental in vector (assumed that fundamental equals maximum)
FFT_sig_withoutFundamental=FFT_sig;
FFT_sig_withoutFundamental(VectorNumber,:)=0; %Eliminate fundamental in order to calculate THD

% remove dc value
FFT_sig_withoutFundamental(1,:)=0;

% Calculate angle of frequency components
phi = angle(Y(1:L/2+1));

%bsxfun() multipliziert den Vektor in jeder spalte/zeile mit sich selbst,
%dadurch erreiche ich, das jeder Wert im urpsrünglichen Vektor quadriert
%wird.
I_squared_Harmonics = sum(bsxfun(@times, FFT_sig_withoutFundamental, FFT_sig_withoutFundamental)) %[A] Respect all harmonics for FCS-MPC (without the fundamental) 

for k=1:6
THD_components(k) = (sqrt(I_squared_Harmonics(k))/FundamentalCurrent(k))*100; %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
TDD_components(k) = (sqrt(I_squared_Harmonics(k))/i_nom)*100;

end
THD_components
TDD_components
mean(THD_components)
mean(TDD_components)
THD(i) = mean(THD_components)
TDD(i) = mean(TDD_components)

THD
TDD

% THD of d- and q-current
% Calculate THD
[FundamentalCurrent_id ,VectorNumber_id] = max(FFT_sig_id) %Find fundamental in vector (assumed that fundamental equals maximum)
FFT_sig_withoutFundamental_id=FFT_sig_id;
FFT_sig_withoutFundamental_id(VectorNumber_id,:)=0; %Eliminate fundamental in order to calculate THD

% remove dc value
% FFT_sig_withoutFundamental_iq(1,:)=0;

%bsxfun() multipliziert den Vektor in jeder spalte/zeile mit sich selbst,
%dadurch erreiche ich, das jeder Wert im urpsrünglichen Vektor quadriert
%wird.
I_squared_Harmonics_id = sum(bsxfun(@times, FFT_sig_withoutFundamental_id, FFT_sig_withoutFundamental_id)) %[A] Respect all harmonics for FCS-MPC (without the fundamental) 

for k=1:1
THD_components_id(k) = (sqrt(I_squared_Harmonics_id(k))/FundamentalCurrent_id(k))*100; %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
TDD_components_id(k) = (sqrt(I_squared_Harmonics_id(k))/i_nom)*100;

end
THD_components_id
TDD_components_id
mean(THD_components_id)
mean(TDD_components_id)
THD_id(i) = mean(THD_components_id)
TDD_id(i) = mean(TDD_components_id)

THD_id
TDD_id

% Calculate THD
[FundamentalCurrent_iq ,VectorNumber_iq] = max(FFT_sig_iq) %Find fundamental in vector (assumed that fundamental equals maximum)
FFT_sig_withoutFundamental_iq=FFT_sig_iq;
FFT_sig_withoutFundamental_iq(VectorNumber_iq,:)=0; %Eliminate fundamental in order to calculate THD

% remove dc value
% FFT_sig_withoutFundamental_iq(1,:)=0;

%bsxfun() multipliziert den Vektor in jeder spalte/zeile mit sich selbst,
%dadurch erreiche ich, das jeder Wert im urpsrünglichen Vektor quadriert
%wird.
I_squared_Harmonics_iq = sum(bsxfun(@times, FFT_sig_withoutFundamental_iq, FFT_sig_withoutFundamental_iq)) %[A] Respect all harmonics for FCS-MPC (without the fundamental) 

for k=1:1
THD_components_iq(k) = (sqrt(I_squared_Harmonics_iq(k))/FundamentalCurrent_iq(k))*100; %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
TDD_components_iq(k) = (sqrt(I_squared_Harmonics_iq(k))/i_nom)*100;

end
THD_components_iq
TDD_components_iq
mean(THD_components_iq)
mean(TDD_components_iq)
THD_iq(i) = mean(THD_components_iq)
TDD_iq(i) = mean(TDD_components_iq)
end
THD_iq
TDD_iq

%% Figures
figure
subplot(211)
hBar = bar(freq(1,:)*0.001,FFT_sig_id(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 f_max 0 THD_max]);
xlabel('Frequency / kHz')
ylabel('i_d (f) / %');
subplot(212)
hBar = bar(freq(1,:)*0.001,FFT_sig_iq(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 f_max 0 THD_max]);
xlabel('Frequency / kHz')
ylabel('i_q (f) / %');

figure
subplot(311)
plot(log.time(start:finish),i_dq(start:finish))
subplot(312)
plot(log.time(start:finish),i_dqXY(1,start:finish))
hold on
plot(log.time(start:finish),i_dqXY(2,start:finish))
subplot(313)
plot(log.time(start:finish),i_ph(1,start:finish))
%% Figures
figure
subplot(321)
plot(log.time(start:finish),log.CH2(start:finish),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(log.time(start:finish),log.CH3(start:finish),'Color',rgb_ib,'LineWidth', lw);
plot(log.time(start:finish),log.CH4(start:finish),'Color',rgb_ic,'LineWidth', lw);
plot(log.time(start:finish),log.CH5(start:finish),'Color',rgb_ia2,'LineWidth', lw);
plot(log.time(start:finish),log.CH6(start:finish),'Color',rgb_ib2,'LineWidth', lw);
plot(log.time(start:finish),log.CH7(start:finish),'Color',rgb_ic2,'LineWidth', lw);
plot(log.time(start:finish),log.CH1(start:finish));
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_a_1','i_b_1','i_c_1','i_a_2','i_b_2','i_c_2');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([t_start t_finish i_min i_max])
ylabel('i / A')

subplot(323)
plot(log.time(start:finish),log.CH8(start:finish),'LineWidth', lw);
hold on
plot(log.time(start:finish),log.CH9(start:finish),'LineWidth', lw);
plot(log.time(start:finish),log.CH10(start:finish),'LineWidth', lw);
plot(log.time(start:finish),log.CH11(start:finish),'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_\alpha','i_\beta','i_X','i_Y');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([t_start t_finish i_min i_max])
ylabel('i / A')

subplot(322)
plot(log.time(start:finish),log.CH14(start:finish),'Color',rgb_ia,'LineWidth', lw);
hold on
plot(log.time(start:finish),log.CH15(start:finish),'Color',rgb_ib,'LineWidth', lw);
plot(log.time(start:finish),log.CH16(start:finish),'Color',rgb_ic,'LineWidth', lw);
% plot(log.time(start:finish),log.CH17(start:finish),'Color',rgb_ia2,'LineWidth', lw);
% plot(log.time(start:finish),log.CH18(start:finish),'Color',rgb_ib2,'LineWidth', lw);
% plot(log.time(start:finish),log.CH19(start:finish),'Color',rgb_ic2,'LineWidth', lw);
set(gca,'FontSize',fs)
% [leg1, hobj, ~, ~] = legend('d_a_1','d_b_1','d_c_1');
[leg1, hobj, ~, ~] = legend('d_a_1');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([t_start t_finish 0.2 0.8])
% ylabel('Equiv. mod. signal')
ylabel('Mod. signal')

subplot(325)
plot(log.time(start:finish),log.CH12(start:finish),'LineWidth', lw);
hold on
plot(log.time(start:finish),log.CH13(start:finish),'LineWidth', lw);
set(gca,'FontSize',fs)
[leg1, hobj, ~, ~] = legend('i_d','i_q');
% leg1.ItemTokenSize = [10,10];
hl = findobj(hobj,'type','line');
set(hl,'LineWidth',lw_leg);
ht = findobj(hobj,'type','text');
set(ht,'FontSize',fs_leg);
grid on
axis([t_start t_finish i_min i_max])
xlabel('Time / s')
ylabel('i / A')

subplot(324)
plot(log.time(start:finish),log.CH20(start:finish),'*','LineWidth',lw);
hold on
set(gca,'FontSize',fs);
grid on
axis([t_start t_finish 0 5])
xlabel('Time / s')
ylabel('Solver Iterations');

subplot(326)
hBar = bar(freq(1,:)*0.001,FFT_sig_withoutFundamental(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
% hBar = bar(freq(1,:)*0.001,FFT_sig(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 f_max 0 THD_max]);
xlabel('Frequency / kHz')
ylabel('i_a_1 (f) / %');

%% only fft but with angle
figure
subplot(211)
% hBar = bar(freq(1,:)*0.001,FFT_sig_withoutFundamental(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
hBar = bar(freq(1,:)*0.001,FFT_sig(:,1)/FundamentalCurrent(1)*100, 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 f_max 0 THD_max]);
ylabel('i_a_1 (f) / %');
subplot(212)
hBar = bar(freq(1,:)*0.001,phi(1,:), 'BarWidth', barWidth);
set(gca,'FontSize',fs);
grid on
axis([0 f_max -pi pi]);
xlabel('Frequency / kHz')
ylabel('angle (f) / rad');
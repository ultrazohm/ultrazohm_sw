%linewidth axes
lwa=1;
%linewidth lines
lw=2;
%Fontsize
fs=24;

barWidth = 10;

%  signal(:,1) = time;
%  signal(:,2) = ia1;

% % Orgnialsignal ploten
% figure(1)
% set(gcf,'color','white')
% h=subplot(2,1,1);
% pp=plot(signal(:,1),signal(:,2));
% title('Zeitsignal')
% xlabel('Zeit in s')
% ylabel('y(t)') %ylabel('F(x)')
% pp.LineWidth=1;
% h.FontWeight='bold';
% h.FontSize=fs;
% grid on
% set(gca,'FontSize',fs);

% Programm wird unterbrochen und das Keyboard wird wieder freigegeben
% keyboard
% Mit dem Data Cursor können nun der Start- und Endpunkt des zu
% analysierenden Teilsignals festgelegt werden. Dabei ist wichtig zurerst
% den Startpunkt und danach den Endpunkt zu wählen. Danach Rechtsklick auf einen
% der beiden Datapoint und die Option Export Cursor Data to Workspace. Die
% Variable mit 'limits' benennen und Ok drücken. Danach im Command Window
% oben auf 'continue' klicken. Nun wird eine FFT-Analyse auf das
% markierte Teilsignal durchgeführt.

% markiertes Teilsignal in Variable time und F speichern
% time_cut=signal(1:limits(1).DataIndex-limits(2).DataIndex+1,1);
% F=signal(limits(2).DataIndex:limits(1).DataIndex,2);

time_cut = time;


% %Plot des Teilsignals zur Kontrolle
% h=subplot(2,1,2);
% pp=plot(time_cut,F,'r');
% title('Signalausschnitt für Analyse')
% xlabel('Zeit in s')
% ylabel('y(t)')
% h.FontWeight='bold';
% h.FontSize=fs;
% grid on
% set(gca,'FontSize',fs);


%% FFT-Analyse Teilsignal mit fft (dft), da nur ein Argument

for i=1:num_of_measured_points
    F=i_ph(:,1:data_point_length(i),i)';
%
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
%
FFT_sig_withoutFundamental=FFT_sig;             
FFT_sig_withoutFundamental(VectorNumber,:)=0; %Eliminate fundamental in order to calculate THD

%bsxfun() multipliziert den Vektor in jeder spalte/zeile mit sich selbst,
%dadurch erreiche ich, das jeder Wert im urpsrünglichen Vektor quadriert
%wird.
I_squared_Harmonics = sum(bsxfun(@times, FFT_sig_withoutFundamental, FFT_sig_withoutFundamental)) %[A] Respect all harmonics for FCS-MPC (without the fundamental) 
% calculate THD
% THD = (sqrt(I_squared_Harmonics)/FundamentalCurrent)*100 %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
for k=1:6
THD_components(k) = (sqrt(I_squared_Harmonics(k))/FundamentalCurrent(k))*100; %[%] THD in percent -> sqrt((Sum of all the others)^2) / (Fundamental)
end
THD_components;
THD(i) = mean(THD_components);
end
THD
%% Plot trade-off curve
figure
plot(mean_avg_f_sw_over_trigger_period,THD,'*');
xlabel('f_s_w in Hz');
ylabel('THD_i in %');
title('Trade-Off curve');
% axis([0 max(mean_avg_f_sw_over_trigger_period) 0 max(THD)]);
%%
% %% Plot single-sided amplitude spectrum 
% figure(2)
% set(gcf,'color','white')
% h=subplot(1,1,1);
% % ps=stem(freq([abs(U_spec_dat(:,1))+1]),FFT_sig([abs(U_spec_dat(:,1))+1]));
% % ps=stem(freq([abs(F(:,1))+1]),FFT_sig([abs(F(:,1))+1]));
% % ps=stem(freq(1,:),FFT_sig(:,1));
% % ps=bar(freq(1,:)/1000,FFT_sig(:,1));
% ps=bar(freq(1,:),FFT_sig(:,1));
% title('signal spectrum')
% xlabel('f in Hz') %xlabel('\nu []')
% ylabel('|signal(f)|')
% ps.LineWidth=lw;
% axis([0 2000 0 10])
% 
% % set(gca,'yscal','log')
% h.FontWeight='bold';
% h.FontSize=fs;
% grid on
% ax=gca;
% ax.LineWidth=lwa;
% % annotation('textbox',[.8 .4 .1 .5],'String', {['THD: ' num2str(round(THD,2)) ' %'] ['f_{sw}   : x.x kHz'] ['I_{fun}   : xx.x A']},'FitBoxToText', 'on', 'FontSize', 18)
% annotation('textbox',[.8 .4 .1 .5],'String', {['THD: ' num2str(round(THD,2)) ' %'] },'FitBoxToText', 'on', 'FontSize', 18)
% 
% 
% %% Plot single-sided amplitude spectrum, scaled to fundamental current
% figure(20)
% set(gcf,'color','white')
% h=subplot(1,1,1);
% %ps=stem(freq([abs(U_spec_dat(:,1))+1]),FFT_sig([abs(U_spec_dat(:,1))+1]));
% %ps=stem(freq([abs(F(:,1))+1]),FFT_sig([abs(F(:,1))+1]));
% 
% [FundamentalCurrent ,VectorNumber] = max(FFT_sig(:,1)) %Find fundamental in vector
% % ps=stem(freq(1,:),(FFT_sig(:,1)/FundamentalCurrent)*100,'marker','none'); %SW: Scaled to the fundamental (maximum)
% % ps=bar(freq(1,:)/1000,(FFT_sig(:,1)/FundamentalCurrent)*100, 'BarWidth', barWidth);  
% ps=bar(freq(1,:),(FFT_sig(:,1)/FundamentalCurrent)*100, 'BarWidth', barWidth);  
% title('Phase current spectrum, normalized to fundamental current')
% %Leg2=legend('‘N_p = 2’','‘ideal’','location','NorthWest');
% %set(Leg2,'FontSize',24);
% xlab = xlabel('f in Hz'); %xlabel('\nu []')
% ylab = ylabel('|i_{a1}(f)| in %');
% ps.LineWidth=lw;
% 
% axis([0 5000 0 110]);
% 
% % set(gca,'yscal','log')
% h.FontWeight='bold';
% h.FontSize=fs;
% grid on
% ax=gca;
% ax.LineWidth=lwa;
% 
% set(xlab,'FontSize',24);
% set(ylab,'FontSize',24);
% set(gca,'FontSize',24)
% annotation('textbox',[.8 .4 .1 .5],'String', {['THD: ' num2str(round(THD,2)) ' %'] ['f_{sw}   : xx.x kHz'] ['I_{fun}   : x.x p.u.']},'FitBoxToText', 'on', 'FontSize', 18)
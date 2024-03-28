load('FFT_compare_FCS_20kHz.mat');

close all
barWidth = 0.5;
x = 1
y = 1.6

figure
% hBar = bar(freq_FCS_400kHz(1,:),FFT_sig_FCS_400kHz(:,1)/FundamentalCurrent_FCS_400kHz(1)*100, 'BarWidth', barWidth)
hBar = bar(freq_22_400kHz(1,:)*0.001,FFT_sig_without_Fundamental_22_400kHz(:,1)/FundamentalCurrent_22_400kHz(1)*100, 'BarWidth', barWidth)
% set(gca,'XScale','log')
% set(gca,'YScale','log')
% set(gca,'Xtick',0:4); %// adjust manually; values in log scale
% set(gca,'Xticklabel',10.^get(gca,'Xtick')); %// use labels with linear values
grid on
axis([0 x 0 y]);
title('FFT of phase a current without fundamental, FCS 400 kHz')
xlabel('Frequency / kHz')
ylabel('THD_i / %');

figure
% hBar = bar(freq_FCS_100kHz(1,:),FFT_sig_FCS_100kHz(:,1)/FundamentalCurrent_FCS_100kHz(1)*100, 'BarWidth', barWidth)
hBar = bar(freq_22_100kHz(1,:)*0.001,FFT_sig_without_Fundamental_22_100kHz(:,1)/FundamentalCurrent_22_100kHz(1)*100, 'BarWidth', barWidth)
% set(gca,'XScale','log')
% set(gca,'YScale','log')
% set(gca,'Xtick',0:4); %// adjust manually; values in log scale
% set(gca,'Xticklabel',10.^get(gca,'Xtick')); %// use labels with linear values
grid on
axis([0 x 0 y]);
title('FFT of phase a current without fundamental, FCS 100 kHz')
xlabel('Frequency / kHz')
ylabel('THD_i / %');
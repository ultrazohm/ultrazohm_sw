data_uz=tabledata(:,2);
data_simulink=out.abc1.Data(:,1);

[f_uz,fft_uz] = generate_fft(data_uz);
[f_simulink,fft_simulink] = generate_fft(data_simulink);


figure;
plot(f_uz,fft_uz,'r');
hold on;
plot(f_simulink,fft_simulink,'b');
grid on;
xlabel('El. Frequenz');
ylabel('Strom (A)');
xlim([0 300]);
legend('UZ','Simulink');
%title('FFT Simulink i-a1');
hold off;

function [f,fft_out]=generate_fft(data)
Fs = 10000;
dt = 1/Fs;
N = length(data);
t = dt*(0:N-1)';
%figure;
%plot(t,data);
datafft=fft(data);
datafft_abs=abs(datafft/N);
fft_out=datafft_abs(1:N/2+1);
f=Fs*(0:N/2)/N;
end

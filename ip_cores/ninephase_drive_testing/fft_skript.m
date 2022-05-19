data=tabledata(:,2);
N = length(data);
Fs = 20000;
dt = 1/Fs;
t = dt*(0:N-1)';
figure;
plot(t,data);


 datafft=fft(data);
 datafft_abs=abs(datafft/N);
 datafft_abs=datafft_abs(1:N/2+1);
 f=Fs*(0:N/2)/N;
 figure;
 plot(f,datafft_abs)
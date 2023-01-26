function [frequencies,amplitudes,angles] = FFTRecordedVoltage(data,sampletime)
%FFTRecordedVoltage performs FFT
%   Detailed explanation goes here
Y = single(zeros(10000,1));%1000 depends on the size of recorded data!
L = length(data);
Y = fft(data);
tol = single(1e-7);
for i=10000%1000 depends on the size of recorded data!
    if(Y(i)<tol)
        Y(i) = single(0);
    end
end
P2 = abs(Y/L);
amplitudes = P2(1:L/2+1);
amplitudes(2:end-1) = 2*amplitudes(2:end-1);
frequencies = (0:(L/2))/L/sampletime;
angles=angle(Y);
angles=angles(1:L/2+1);
end
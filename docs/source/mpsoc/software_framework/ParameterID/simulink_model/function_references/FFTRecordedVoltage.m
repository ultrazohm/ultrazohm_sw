function [output] = FFTRecordedVoltage(data,sampletime)
%FFTRecordedVoltage performs FFT
%   Detailed explanation goes here
%% fft functionality
Y = single(zeros(10000,1));%1000 depends on the size of recorded data!
L = length(data);
Y = fft(data);
tol = single(1e-7);
for i=1:10000%1000 depends on the size of recorded data!
    if(abs(Y(i))<tol)
        Y(i) = single(0);
    end
end
P2 = abs(Y/L);
output.amplitudes = P2(1:L/2+1);
output.amplitudes(2:end-1) = 2*output.amplitudes(2:end-1);
output.frequencies = (0:(L/2))/L/sampletime;
output.angles=angle(Y);
output.angles=output.angles(1:L/2+1);
end
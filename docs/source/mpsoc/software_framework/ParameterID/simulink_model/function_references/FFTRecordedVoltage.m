function [frequencies,amplitudes,angles] = FFTRecordedVoltage(data,sampletime) %#codegen
%FFTRecordedVoltage performs FFT
%   Detailed explanation goes here
%% init
Y = single(zeros(10000,1));%1000 depends on the size of recorded data!
L = single(length(data));
temp_amplitude = single(zeros(5001,1));
temp_angle = single(zeros(10000,1));
tol = single(1e-7);
frequencies = single(zeros(1,5001));
amplitudes = single(zeros(1,5001));
angles = single(zeros(1,5001));
%% FFT
Y = fft(data);

for i=1:10000%depends on the size of recorded data!
    if(abs(Y(i))<tol)
        Y(i) = single(0);
    end
end
P2 = abs(Y/L);
temp_amplitude = P2(1:L/2+1);
amplitudes(2:end-1) = 2*temp_amplitude(2:end-1);
frequencies = (0:(L/2))/L/sampletime;
temp_angle=angle(Y);
angles=temp_angle(1:L/2+1);
end
function [output] = FFTRecordedVoltage(input,data,sampletime)
%FFTRecordedVoltage performs FFT
%   Detailed explanation goes here
%% carry datatype
output = input;
%% fft functionality
Y = single(zeros(10000,1));%1000 depends on the size of recorded data!
L = length(data);
Y = fft(data);
temp_amplitude = single(zeros(5001,1));
temp_angle = single(zeros(10000,1));
tol = single(1e-7);
for i=1:10000%1000 depends on the size of recorded data!
    if(abs(Y(i))<tol)
        Y(i) = single(0);
    end
end
P2 = abs(Y/L);
temp_amplitude = P2(1:L/2+1);
output.amplitudes(2:end-1) = 2*temp_amplitude(2:end-1);
output.frequencies = (0:(L/2))/L/sampletime;
temp_angle=angle(Y);
output.angles=temp_angle(1:L/2+1);
end
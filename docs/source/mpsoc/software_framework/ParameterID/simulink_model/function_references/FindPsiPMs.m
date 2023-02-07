function [psi_freq,psi_pm,psi_angle] = FindPsiPMs(frequencies,amplitudes,angles) %#codegen
%FindPsiPMs Finds PSI_PMs of higher orders
%   Detailed explanation goes here
%% initialization
order = uint16([1 3 5 7 11]);
ampl = single(zeros(5,1));
index = uint16(zeros(5,1));
ideal_index = uint16(zeros(5,1));
around_val = uint16(15);
range = uint16(zeros(around_val+1,1));
%% find fundamental
[ampl(1),index(1)] = max(amplitudes);
%% find higher order indizes
for i=2:5
    ideal_index = index(1)*order(i);
    %range = [(ideal_index-around_val):1:(ideal_index+around_val)];
    [ampl(i),index(i)] = max(amplitudes(range));
    index(i) = index(i)+ideal_index-around_val-1;
end
%% calculate results
% calculate frequencies to orders
psi_freq = frequencies(index);
% calculate psi magnitude
psi_pm = amplitudes(index)./(psi_freq*2*pi);
% calculate angles
psi_angle = angles(index(1)*order)';
end
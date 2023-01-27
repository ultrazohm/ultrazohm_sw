function [output] = FindPsiPMs(input)
%FindPsiPMs Finds PSI_PMs of higher orders
%   Detailed explanation goes here
%% carry datatype
output = input;
%% find fundamental
[ampl_1,index_1] = max(input.amplitudes);
omega_el1 = 2*pi*input.frequencies(index_1);
%% initialize arrays
order = single([1 3 5 7 11]);
%% calculate results
% calculate frequencies to orders
output.psi_freq = order*input.frequencies(index_1);
% calculate psi magnitude
output.psi_pm = input.amplitudes(index_1*order)./(omega_el1*order);
% calculate angles
output.psi_angle = input.angles(index_1*order)';
end
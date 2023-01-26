function [psi_pm] = FindPsiPMs(frequencies,amplitudes)
%FindPsiPMs Finds PSI_PMs of higher orders
%   Detailed explanation goes here
[ampl_1,index_1] = max(amplitudes);
omega_el1 = 2*pi*frequencies(index_1);
psi_pm = single(zeros(5,1));
psi_pm(1) = ampl_1/omega_el1;%Order: 1st
psi_pm(2) = amplitudes(3*index_1)/(omega_el1*3);%Order: 3rd
psi_pm(3) = amplitudes(5*index_1)/(omega_el1*5);%Order: 5th
psi_pm(4) = amplitudes(7*index_1)/(omega_el1*7);%Order: 7th
psi_pm(5) = amplitudes(11*index_1)/(omega_el1*11);%Order: 11th
end
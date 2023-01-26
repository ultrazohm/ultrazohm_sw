function [psi_pm,psi_freq,angle] = FindPsiPMs(frequencies,amplitudes,angles,compensate,fc)
%FindPsiPMs Finds PSI_PMs of higher orders
%   Detailed explanation goes here
[ampl_1,index_1] = max(amplitudes);
omega_el1 = 2*pi*frequencies(index_1);
%% initialize arrays
psi_pm = single(zeros(5,1));
psi_freq = psi_pm;
angle = psi_pm;
order = single([1;3;5;7;11]);
%% calculate results
% calculate frequencies to orders
psi_freq = order*frequencies(index_1);
% calculate psi magnitude
if(compensate)
    factor = sqrt(1+(2*pi*psi_freq))
    psi_pm = amplitudes(index_1*order)./(omega_el1*order)*factor;
else
    psi_pm = amplitudes(index_1*order)./(omega_el1*order);
end
% calculate angles
if(compensate)
    correction = atan(psi_freq/fc);
    angle = angles(order*index_1) - angles(index_1) + correction;
else
   angle = angles(order*index_1) - angles(index_1);
end
end
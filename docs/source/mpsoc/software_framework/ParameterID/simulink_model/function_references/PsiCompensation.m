function output = PsiCompensation(input,R_series,R_parallel,C) %#codegen
%PsiCompensation compensates the calculated psis for given voltage devider/filter 
%   Detailed explanation goes here
%% set out=in
output = input;
%% calculate complex voltage devider
Xc = 1./(1i*2*pi*C*input.psi_freq);
Z_parallel = Xc*R_parallel./(Xc+R_parallel);
factor = (Z_parallel + R_series) ./ Z_parallel;
%% compensate
output.psi_angle = input.psi_angle + angle(factor);
output.psi_pm = input.psi_pm .* abs(factor);
end
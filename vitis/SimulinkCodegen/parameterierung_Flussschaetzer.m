% PMSM_FOC_Parameter

clear all
clc
close all


% motorparamter aus Herlein
%Mechanik
 J = 49.662e-6;       % Trägheitsmoment Antriebsstrang
% %Elektronik
 Rs = 7.3;          % phase resistance in Ohm
 phi = 0.07;      % flux linkage in Vs
 Ld = 1.626e-3;       % d-axis inductance in H
 Lq = 1.626e-3;
% L0 = Ld;

 p = 1;             % Polpaarzahl
 Uzk = 48 ;  

n_n = 2760; % in rpm

Ts = 1/(2e4);          %Simulationszeitkonstante
fw = 2e4;
Tw = 1/(fw);       % Wechselrichterzeitkonstante
      
Umax = (1/sqrt(3))*Uzk;     %maximal Stellbare Spannung
Ls=1.626e-3;

% % % Motorparameter aus schroeter prototypenmaschine
% %Mechanik
% J = 8.4e-5 ;      % Trägheitsmoment Antriebsstrang
% %Elektronik
% Rs = 0.249;          % phase resistance in Ohm
% phi = 0.023;      % flux linkage in Vs
% Ld = 0.00044;
% Lq = 0.00245;
% L0 = Ld;
% Ls=sqrt((Ld^2+Lq^2)/2);
% p = 1;             % Polpaarzahl
% Uzk = 48 ;  








%Flussschätzer
fHP = 0.1*n_n*(1/60); % muss experimentel bestimmt werden 80Hz ist auf J.Kiel
THP = 1/(2*pi*fHP);
HP = tf([THP 0],[THP 1]);
HPz= c2d(HP,Ts,'tustin');
[Hochnum,Hochdenum] = tfdata(HPz);
HPnum=Hochnum{1,1};
HPdenum=Hochdenum{1,1};






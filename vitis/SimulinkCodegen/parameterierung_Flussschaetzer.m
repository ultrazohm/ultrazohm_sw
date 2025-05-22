% PMSM_FOC_Parameter

clear all
clc
close all


% motorparamter aus Herlein
% R_ph = 7.3;          % phase resistance in Ohm
% phi = 0.07;      % flux linkage in Vs
% L_ph=1.626e-3;
%  Ld = 1.626e-3;       % d-axis inductance in H
%  Lq = 1.626e-3;
% J = 0.0000101;
%  p = 1; 
% n_n = 2760; % in rpm
% Imax = 1.7; %in A
% M0 = 0.211; %in Nm



%Heidrive parameter
R_ph = 0.543;
L_ph=0.00048;
Ld = 0.00113;
Lq = 0.00142;
phi = 0.0169;
p = 3;
J = 0.0000148;
n_n = 3000; % in rpm
Imax = 5; %in A
M0 = 0.5; %in Nm


Uzk = 48; %in V

Rs = 0.5*R_ph; %bei Steinschaltung
Ts = 1/(2e4);          %Simulationszeitkonstante

Tw = 1/(2e4); % Wechselrichterzeitkonstante
fw = 1/Tw;

Umax = (1/sqrt(3))*Uzk;     %maximal Stellbare Spannung

Ls = 0.5*L_ph;







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



fTP = 40;
TTP = 1/(2*pi*fTP);
TP = tf([1 0],[TTP 1]);
TPz= c2d(TP,Ts,'tustin');
[Tiefnum,Tiefdenum] = tfdata(TPz);
TPnum=Tiefnum{1,1};
TPdenum=Tiefdenum{1,1};


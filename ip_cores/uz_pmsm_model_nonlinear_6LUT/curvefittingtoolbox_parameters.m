%Einfach ne Matlab datei um verschiedene flüsse abzuspeichern
close all;
%Psi d Werte Methode1 (altes Paper) 

%Methode1
%Alles hier ist ad1 bis ad12 durchgehen muss also nicht komisch angepasst werden
% 7.4648
% 0.0001
% -15.5451
% -185.5154
% 186.5382
% 0.0000
% 0.0396
% -0.0789
% 0.0046
% -0.0255
% 74.6056
% 6.8989

% 7.4652
% -0.0295
% 74.6805
% 6.1154
% 0.0001
% -15.7773
% -185.5111
% 186.5401
% 0.0000
% 0.0359
% -0.0756
% 32.0874

% Parameter aus der curvefitting Toolbox (bessere Werte für psi d)
ad1 = 7.2940;
ad2 = 0.0001;
ad3 = -15.5992;
ad4 = -186.4725;
ad5 = 187.4853;
ad6 = 0.0000;
ad7 = 0.0205;
ad8 = 0.0187;
ad9 = 0.0247;
ad10 = -0.0291;
ad11 = 73.4312;
ad12 = 5.9081;

%Immernoch methode1
%Parameter für psiq

%Neue bessere Parameter nur mit  den eigentlichen parameter a1-12für psiq
% 0.0045
% 0.0193
% 0.1055
% 0.0373
% 0.1851
% 0.0009
% 0.4494
% 0.1831
% 1.7377
% 0.0093
% -0.1351
% 0.0398

% Das wäre aq1 dann aq10-12 und dann wieder aq2-9
% 0.0041
% -0.0091
% 0.0579
% 0.0043
% 0.1953
% 0.0010
% 43.4183
% -26.1887
% 0.0220
% 0.0091
% -0.0564
% 0.0042

%Nochmal neue Parameter für psiq aus der Curvefittingtoolbox (sind die besten) 
aq1 =0.0041;
aq10 =0.0032;
aq11 =0.6133;
aq12 =0.1467;
aq2 =0.2092;
aq3 =0.0010;
aq4 =28.4940;
aq5 =-24.2348;
aq6 =0.0405;
aq7 =-0.0030;
aq8 =-0.6286;
aq9 =0.1516;

%Methode 2b
% a_d4 = 0.1413;
% a_d5 = 0.4427;
% a_d6 = 1.0908;
% a_d7 = 0.1704;
% 
% a_q4 = 1.3190;
% a_q5 = 0.7707;
% a_q6 = 0.4186;
% a_q7 = 1.0530;
% 
% k1 = 0.0762;
% k2 = 0.0016;
% k3 = -0.0004;
% k4 = -0.0468;


%Methode2b Formeln

%Formeln für die Methode 2b einfach mal aufgeschrieben damit keine Fehler im langen aufschreiben passieren
% F1 = 1-exp(-(a_d4*d_current).^2);
% F2 = 1-exp(-(a_d5*d_current).^2);
% F3 = 1-exp(-(a_d6*d_current).^2);
% F4 = 1-exp(-(a_d7*d_current).^2);
% 
% G1 = 1-exp(-(a_q4*q_current).^2);
% G2 = 1-exp(-(a_q5*q_current).^2);
% G3 = 1-exp(-(a_q6*q_current).^2);
% G4 = 1-exp(-(a_q7*q_current).^2);
% 
% F1_strich = (2*(a_d4.^2)*d_current)*exp(-(a_d4*d_current).^2);
% F2_strich = (2*(a_d5.^2)*d_current)*exp(-(a_d5*d_current).^2);
% F3_strich = (2*(a_d6.^2)*d_current)*exp(-(a_d6*d_current).^2);
% F4_strich = (2*(a_d7.^2)*d_current)*exp(-(a_d7*d_current).^2);
% 
% G1_strich = (2*(a_q4.^2)*q_current)*exp(-(a_q4*q_current).^2);
% G2_strich = (2*(a_q5.^2)*q_current)*exp(-(a_q5*q_current).^2);
% G3_strich = (2*(a_q6.^2)*q_current)*exp(-(a_q6*q_current).^2);
% G3_strich = (2*(a_q7.^2)*q_current)*exp(-(a_q7*q_current).^2);

%Das hier sind die Karten für Methode 2b um das Least Square Problem einzeln zu lösen (x ist d_current y ist qcurrent)

%psid_fitted mit 7 einzelnen gleichungen (war ein versuch die Genauigkeit mit mehr Gleichungen zu erhöhen)
% k1*((2*(a_d4^2)*x)*exp(-(a_d4*x)^2)*(1-exp(-(a_q4*y)^2)))  + ...
% k2*((2*(a_d5^2)*x)*exp(-(a_d5*x)^2)*(1-exp(-(a_q5*y)^2)))  + ...
% k3*((2*(a_d6^2)*x)*exp(-(a_d6*x)^2)*(1-exp(-(a_q6*y)^2)))  + ...
% k4*((2*(a_d7^2)*x)*exp(-(a_d7*x)^2)*(1-exp(-(a_q7*y)^2)))  + ...
% k5*((2*(a_d8^2)*x)*exp(-(a_d8*x)^2)*(1-exp(-(a_q8*y)^2)))  + ...
% k6*((2*(a_d9^2)*x)*exp(-(a_d9*x)^2)*(1-exp(-(a_q9*y)^2)))  + ...
% k7*((2*(a_d10^2)*x)*exp(-(a_d10*x)^2)*(1-exp(-(a_q10*y)^2)));  

%psiq_fitted
%k1*(1-exp(-(a_d4*y)^2))*((2*(a_q4^2)*x)*exp(-(a_q4*x)^2))   +   k2*(1-exp(-(a_d5*y)^2))*((2*(a_q5.^2)*x)*exp(-(a_q5*x)^2)) + k3*(1-exp(-(a_d6*y)^2))*((2*(a_q6^2)*x)*exp(-(a_q6*x)^2))  + k4*(1-exp(-(a_d7*y)^2))*((2*(a_q7^2)*x)*exp(-(a_q7*x)^2));

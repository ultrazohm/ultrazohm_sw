%Fitting_flux_approximation
close all;
%LUT Fitting

%LeastSquare Problems
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt');
d_current = d_current_d_Flux';
q_current = q_current_d_Flux;

%% Selbstinduktivitäten berechnen Gleiche wie bei Methode 2a

% 1. Gleichung Selbstinduktivität Psid
Fluxd_iqnull = Flux_d(:,10);

%Formel aus Paper2 für Methode 2c "Linearen Bereich" 
%fun0=@(ad)Fluxd_iqnull-(ad(1).*tanh(ad(2)*(d_current-ad(3))));

%Mit folgender Formel funktioniert das fitting nicht
%fun0=@(ad)(Fluxd_iqnull-((ad(1).*(tanh(ad(2)*d_current)))+(ad(3).*d_current)));
fun0=@(ad,d_current) ad(1).*tanh(ad(2)*(d_current-ad(3)));

beta1 =  [0.0305;0.0402; -16.4812];
%ad_1 = lsqnonlin(fun0,beta1,[],[],options)
ad_1 = nlinfit(d_current,Fluxd_iqnull,fun0,beta1)
% Fluxd_iqnull_fitted = ((ad_1(1).*(tanh(ad_1(2)*d_current)))+(ad_1(3).*d_current))
Fluxd_iqnull_fitted = ad_1(1).*(tanh(ad_1(2)*(d_current-ad_1(3))));

%Zuweisung der Parameter
ad1 = ad_1(1);
ad2 = ad_1(2);
ad3 = ad_1(3);


% 2. Gleichung Selbstinduktivität Psiq
Fluxq_idnull = Flux_q(15,:)';
fun2=@(aq)(Fluxq_idnull-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current)));

beta2 = [1;1;1];
aq_1 = lsqnonlin(fun2,beta2,[],[],options)
Fluxq_idnull_fitted = ((aq_1(1).*(tanh(aq_1(2)*q_current)))+(aq_1(3).*q_current));

aq1 = aq_1(1);
aq2 = aq_1(2);
aq3 = aq_1(3);


figure;
% Erster Plot
subplot(2,1,1); 
grid on;
plot(d_current, Fluxd_iqnull_fitted, 'DisplayName', 'Fluxd_{idnull}_{fitted}');
hold on;
plot(d_current, Fluxd_iqnull,'*', 'DisplayName', 'Fluxd_{idnull}');
legend('show');

% Zweiter Plot
subplot(2,1,2); 
grid on;

plot(q_current, Fluxq_idnull_fitted  , 'DisplayName', 'Fluxq_{idnull}_{fitted}');
hold on;
plot(q_current, Fluxq_idnull,'*', 'DisplayName', 'Fluxq_{idnull}');
legend('show');

%% Einfach aufgeschrieben um besser kopieren zu können. (kann eigentlich auch gelöscht werden) 
%Nochmal aufgeschrieben um besser rauskopieren zu können
  % %fs
% (1-exp(-(ad4*id)^2))
% (1-exp(-(ad5*id)^2))
% (1-exp(-(ad6*id)^2))
% (1-exp(-(ad7*id)^2))
% 
% %gs
% (1-exp(-(aq4*iq)^2))
% (1-exp(-(aq5*iq)^2))
% (1-exp(-(aq6*iq)^2))
% (1-exp(-(aq7*iq)^2))
% 
% %fstrichs
% ((2*(ad4^2)*id)*exp(-(ad4*id)^2))
% ((2*(ad5^2)*id)*exp(-(ad5*id)^2))
% ((2*(ad6^2)*id)*exp(-(ad6*id)^2))
% ((2*(ad7^2)*id)*exp(-(ad7*id)^2))
% 
% %gstrichs
% ((2*(aq4^2)*iq)*exp(-(aq4*iq)^2))
% ((2*(aq5^2)*iq)*exp(-(aq5*iq)^2))
% ((2*(aq6^2)*iq)*exp(-(aq6*iq)^2))
% ((2*(aq7^2)*iq)*exp(-(aq7*iq)^2))
%
% flux_ges = fluxd_real+fluxq_real;
% 
% cross_ges = psid_cross_real+psiq_cross_real;
% 
% (k1*((2*(ad4^2)*id)*exp(-(ad4*id)^2))*(1-exp(-(aq4*iq)^2)))+...
%     (k2*((2*(ad5^2)*id)*exp(-(ad5*id)^2)) *(1-exp(-(aq5*iq)^2)) )+...
%     (k3*((2*(ad6^2)*id)*exp(-(ad6*id)^2)) *(1-exp(-(aq6*iq)^2))) + ...
%     (k4*((2*(ad7^2)*id)*exp(-(ad7*id)^2)) *(1-exp(-(aq7*iq)^2))) +...
%     (k1*(1-exp(-(ad4*id)^2))*((2*(aq4^2)*iq)*exp(-(aq4*iq)^2))) + ...
%     (k2*(1-exp(-(ad5*id)^2))*((2*(aq5^2)*iq)*exp(-(aq5*iq)^2))) + ...
%     (k3*(1-exp(-(ad6*id)^2))*((2*(aq6^2)*iq)*exp(-(aq6*iq)^2))) + ...
%     (k4*(1-exp(-(ad7*id)^2))*((2*(aq7^2)*iq)*exp(-(aq7*iq)^2))) 

%% Vorbereitung 

%Selbstinduktion Namensgebung
psidself = Fluxd_iqnull_fitted;

psiqself = Fluxq_idnull_fitted;

q_current_T = q_current';

q_current_T = q_current_T';
d_current = d_current';

fluxd_real = Flux_d';
fluxq_real = Flux_q';

%Berechnen der selbsinduktivität
psidself_padded = repmat(Fluxd_iqnull_fitted, 1, 20)';
psiqself_padded = repmat(Fluxq_idnull_fitted, 1, 20);

psid_cross_real = psidself_padded-Flux_d';
psiq_cross_real = psiqself_padded-Flux_q';

%Addieren des Crosscoupling für "simultane berechnung"
komplettes_crosscoupling_real = psid_cross_real + psiq_cross_real;

%Schauen ob auch das richtige wieder rauskommt
flux_d_mit_cross = psidself_padded-psid_cross_real;
flux_q_mit_cross = psiqself_padded-psiq_cross_real;



%% Eigentliches Versuchen der Methode 2b
%AB HIER geht die eigentliche Versucherei für das Simultane los

%% Versuchen das Simultane Problem mit Fminsearch zu lösen
%Für fminsearch
finalef1 =@(f_ad4,f_ad5,f_ad6,f_ad7,f_aq4,f_aq5,f_aq6,f_aq7,f_k1,f_k2,f_k3,f_k4,d_current,q_current_T) psid_cross_real-...
    (f_k1.*((2.*(f_ad4.^2).*d_current).*exp(-(f_ad4.*d_current).^2)*(1-exp(-(f_aq4.*q_current_T).^2)))+... 
    f_k2.*((2.*(f_ad5.^2).*d_current).*exp(-(f_ad5.*d_current).^2)*(1-exp(-(f_aq5*q_current_T).^2)))+...
    f_k3.*((2.*(f_ad6.^2).*d_current).*exp(-(f_ad6.*d_current).^2).*(1-exp(-(f_aq6.*q_current_T).^2)))+...
    f_k4.*((2*(f_ad7.^2).*d_current).*exp(-(f_ad7.*d_current).^2).*(1-exp(-(f_aq7.*q_current_T).^2))));
finalef2 = @(f_ad4,f_ad5,f_ad6,f_ad7,f_aq4,f_aq5,f_aq6,f_aq7,f_k1,f_k2,f_k3,f_k4,d_current,q_current_T) psiq_cross_real-...
    ((f_k1.*(1-exp(-(f_ad4.*d_current).^2)).*((2.*(f_aq4.^2).*q_current_T).*exp(-(f_aq4.*q_current_T).^2)))   +  ...
    (f_k2.*(1-exp(-(f_ad5.*d_current).^2)).*((2.*(f_aq5.^2).*q_current_T).*exp(-(f_aq5.*q_current_T).^2))) + ...
    (f_k3.*(1-exp(-(f_ad6.*d_current).^2)).*((2.*(f_aq6.^2).*q_current_T).*exp(-(f_aq6.*q_current_T).^2)))  + ...
    (f_k4.*(1-exp(-(f_ad7.*d_current).^2)).*((2.*(f_aq7.^2).*q_current_T).*exp(-(f_aq7.*q_current_T).^2)))  );

%2 Verschiedene möglichkeiten
finalecombined = @(a)norm(sqrt((finalef1(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)+...
    (finalef2(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)),"fro").^2;
%finalecombined = @(a,d_current,q_current_T) sqrt((finalef1(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)+(finalef2(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2));

initial_fmin_paper = [ 33.032; 0.029; 0.008; 0.581 ; 0.064; 0.084; 0.202; 0.223; 0.227; 3.567; 0.101; 0.020];
initial_fmin = [1;1;1;1;1;1;1;1;1;1;1;1];
options = optimset('MaxFunEvals',9999);

adq_red = fminsearch(finalecombined, initial_fmin_paper, options);
adq_red = fminsearch(finalecombined, adq_red,options);

%Parameter zuweisung für fminsearch (einkommentieren falls gebraucht) 
% a_d4 = adq_red(2);
% a_d5 = adq_red(5);
% a_d6 = adq_red(8);
% a_d7 = adq_red(11);
% 
% a_q4 = adq_red(3);
% a_q5 = adq_red(6);
% a_q6 = adq_red(9);
% a_q7 = adq_red(12);
% 
% k1 = adq_red(1);
% k2 = adq_red(4);
% k3 = adq_red(7);
% k4 = adq_red(10);

%% Versuchen das Simulatane Problem mit nlinfit zu lösen. 
%nlinfit
%In der Doku steht dass nur eine X-Variable vorgegeben werden muss (müsste eben beide d_current und q_current in einem Array festgehalten werden
%adq_linfit = nlinfit(d_current,q_current_T,psid_cross_real,f2,initial);

%% Versuchen das simultane Problem mit lsqnonlin zu lösen
%lsqnonlin
initial_lsqnonlin = [1;1;1;1;1;1;1;1;1;1;1;1];
initial_lsqnonlin_paper = [ 33.032; 0.029; 0.008; 0.581 ; 0.064; 0.084; 0.202; 0.223; 0.227; 3.567; 0.101; 0.020];

%Einzelne Formeln
% f3_psid = @(a)psid_cross_real-(a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2)))+ ...
%     a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2)))+ ...
%     a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2)))+ ...
%     a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2))));

% f3_psiq = @(a)(a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2)))+ ...
%     a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2)))+ ...
%     a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2)))+ ...
%     a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2))));

%Schritt 2 Die Parameter werden in der Kreuzkopplung gesucht 
f_combined_cross = @(a)sqrt(((psid_cross_real-( (a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2))))+ ...
    (a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2))))+ ...
    (a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2))))+ ...
    (a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2)))   ))).^2)...
    +((psiq_cross_real-(a(1).*((1-exp(-(a(2).*d_current).^2)).*((2.*(a(3).^2).*q_current_T).*exp(-(a(3).*q_current_T).^2)))) +  ... 
    (a(4).*(1-exp(-(a(5).*d_current).^2)).*((2.*(a(6).^2).*q_current_T).*exp(-(a(6).*q_current_T).^2))) + ... 
    (a(7).*(1-exp(-(a(8).*d_current).^2)).*((2.*(a(9).^2).*q_current_T).*exp(-(a(9).*q_current_T).^2)))  + ... 
    (a(10).*((1-exp(-(a(11).*d_current).^2)).*((2.*(a(12).^2).*q_current_T).*exp(-(a(12).*q_current_T).^2))))  ).^2)   );

adq_zwei = lsqnonlin(f_combined_cross,initial_lsqnonlin_paper,[],[],options);

%Schritt 3 die angepassten Parameter aus der Selbstkopplung und der kruezkopplung werden benutzt um die realen werte auszurechnen
f_combined_real = @(a)sqrt(((fluxd_real-(  psidself_padded - ... 
    ((a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2))))+ ...
    (a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2))))+ ...
    (a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2))))+ ...
    (a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2)))))  )  ).^2)...
    +((fluxq_real-( psiqself_padded  - ...
    ((a(1).*(1-exp(-(a(2).*d_current).^2)).*((2.*(a(3).^2).*q_current_T).*exp(-(a(3).*q_current_T).^2))) +  ... 
    (a(4).*(1-exp(-(a(5).*d_current).^2)).*((2.*(a(6).^2).*q_current_T).*exp(-(a(6).*q_current_T).^2))) + ... 
    (a(7).*(1-exp(-(a(8).*d_current).^2)).*((2.*(a(9).^2).*q_current_T).*exp(-(a(9).*q_current_T).^2)))  + ... 
    (a(10).*(1-exp(-(a(11).*d_current).^2)).*((2.*(a(12).^2).*q_current_T).*exp(-(a(12).*q_current_T).^2)) ) ) )  ).^2)   );
initial_combinedreal = [adq_zwei;ad1;ad2;ad3;aq1;aq2;aq3];
adq_zwei = lsqnonlin(f_combined_real,initial_combinedreal ,[],[],options);

%für lsqnonlin
a_d4 = adq_zwei(2);
a_d5 = adq_zwei(5);
a_d6 = adq_zwei(8);
a_d7 = adq_zwei(11);

a_q4 = adq_zwei(3);
a_q5 = adq_zwei(6);
a_q6 = adq_zwei(9);
a_q7 = adq_zwei(12);

k1 = adq_zwei(1);
k2 = adq_zwei(4);
k3 = adq_zwei(7);
k4 = adq_zwei(10);

a_d1 = adq_zwei(13);
a_d2 = adq_zwei(14);
a_d3 = adq_zwei(15);

a_q1 = adq_zwei(16);
a_q2 = adq_zwei(17);
a_q3 = adq_zwei(18);


%% Mit lsqcurvefit
%Mit lsqcurvefit
%Ähnliches Problem wie bei nlinfit in der Doku steht dass nur eine X-Variable vorgegeben werden muss (müsste eben beide d_current und q_current in einem Array festgehalten werden
OPTIONS = optimoptions('lsqcurvefit','Algorithm','levenberg-marquardt');

dq_current = [d_current;q_current_T'];
%adq_red = lsqcurvefit(finalecombined,initial_lsqnonlin_paper, dq_current, matrix,[],[],[],[],[],[],[],OPTIONS)

%Hiermit kommt ein Fehler wegen input arguements
% adq_red = lsqcurvefit(f_combined_cross,initial_lsqnonlin_paper,dq_current,psid_cross_real);



%% Hier wird wieder nur eingesetzt in die 

%Verschiedene Parameter können aus(einkommentiert) werden wie sie gebraucht werden

%Formeln für die Methode 2b
%Nur Kreuzkopplung
psid_cross_approx_m2b = (k1.*(((2.*(a_d4.^2).*d_current).*exp(-(a_d4.*d_current).^2)).*(1-exp(-(a_q4.*q_current_T).^2))))+ ...
    (k2.*(((2.*(a_d5.^2).*d_current).*exp(-(a_d5.*d_current).^2)).*(1-exp(-(a_q5.*q_current_T).^2))))+ ...
    (k3.*(((2.*(a_d6.^2).*d_current).*exp(-(a_d6.*d_current).^2)).*(1-exp(-(a_q6.*q_current_T).^2))))+ ...
    (k4.*(((2*(a_d7.^2).*d_current).*exp(-(a_d7.*d_current).^2)).*(1-exp(-(a_q7.*q_current_T).^2))));
psiq_cross_approx_m2b = (k1.*(1-exp(-(a_d4.*d_current).^2)).*((2.*(a_q4.^2).*q_current_T).*exp(-(a_q4.*q_current_T).^2)))+ ...
    (k2.*(1-exp(-(a_d5.*d_current).^2)).*((2.*(a_q5.^2).*q_current_T).*exp(-(a_q5.*q_current_T).^2))) + ... 
    (k3.*(1-exp(-(a_d6.*d_current).^2)).*((2.*(a_q6.^2).*q_current_T).*exp(-(a_q6.*q_current_T).^2)))  +...
    (k4.*(1-exp(-(a_d7.*d_current).^2)).*((2.*(a_q7.^2).*q_current_T).*exp(-(a_q7.*q_current_T).^2)));

%Berechnen des ganzen Flusses
flux_d_approx_m2b = psidself_padded - psid_cross_approx_m2b;
flux_q_approx_m2b = psiqself_padded - psiq_cross_approx_m2b;

%% Fehler berechnen

%Berechnen des Fehlers in %
fluxd_max = max(fluxd_real, [], 'all');
fluxq_max = max(fluxq_real, [], 'all');


% Error für Methode 2b
ed = ((abs(fluxd_real-flux_d_approx_m2b))/fluxd_max).*100;
eq = ((abs(fluxq_real-flux_q_approx_m2b))/fluxq_max).*100;

%% Plotten
figure;
% 1 Approximierter Fluss_d
subplot(2,1,1); 
grid on;
surf(d_current, q_current, flux_d_approx_m2b);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_dapprox');
legend;

% 2 Echter Fluss_d
subplot(2,1,2);
grid on;
surf(d_current, q_current, fluxd_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_dreal');
legend;

figure;
% 3 Approximierter Fluss_q
subplot(2,1,1); 
grid on;
surf(d_current, q_current, flux_q_approx_m2b);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_qapprox');
legend;

% 4 Echter Fluss_q
subplot(2,1,2);
grid on;
surf(d_current, q_current, fluxq_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_qreal');
legend;

% 5 Error berechnung für die approximierten flüsse
figure;
subplot(2,1,1);
grid on;
subplot(2,1,1);
surf(d_current, q_current, ed);
xlabel('D Current');
ylabel('Q Current');
zlabel('error/%');
title('error psid');
legend;

subplot(2,1,2);
grid on;
surf(d_current, q_current, eq);
xlabel('D Current');
ylabel('Q Current');
zlabel('error/%');
title('error psiq');
legend;


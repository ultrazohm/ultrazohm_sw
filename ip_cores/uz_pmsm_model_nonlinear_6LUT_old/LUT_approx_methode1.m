%Fitting_flux_approximation
close all;
%LUT Fitting

%LeastSquare Problems
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt');
d_current = d_current_d_Flux';
q_current = q_current_d_Flux;

%% Selbstinduktivitäten berechnen

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
subplot(4,1,1); 
grid on;
plot(d_current, Fluxd_iqnull_fitted, 'DisplayName', 'Fluxd_{idnull}_{fitted}');
hold on;
plot(d_current, Fluxd_iqnull,'*', 'DisplayName', 'Fluxd_{idnull}');
legend('show');

% Zweiter Plot
subplot(4,1,2); 
grid on;

plot(q_current, Fluxq_idnull_fitted  , 'DisplayName', 'Fluxq_{idnull}_{fitted}');
hold on;
plot(q_current, Fluxq_idnull,'*', 'DisplayName', 'Fluxq_{idnull}');
legend('show');

%% Werte für die Methode 1 

%Disclaimer: Diese Methode wurde in der Curve Fitting Toolbox ausgeführt. 

%das sind die anderen formeln aus dem "ersten" Paper also das wurde eingefügt in Curvefitting toolbox für Methode1
% ((aq1*tanh(aq2*iq))+(aq3*iq))   *(   (aq4+(aq5/(1+(aq6*(iq^2)))))   *exp(-((aq7+(aq8/(1+(aq9*(iq^2)))))*id)^2)   + (    (    1-((aq4+(aq5/(1+(aq6*(iq^2))))))  )*exp(-((aq10+(aq11/(1+(aq12*(iq^2)))))*id)^2)   )      )
% (ad1*(tanh(ad2*(id-ad3))))    *(   (ad4+(ad5/(1+(ad6*(id^2)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^2)))))*iq)^2)   + (    (    1-((ad4+(ad5/(1+(ad6*(id^2))))))  )*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2)   )      )

%Dann kommen folgende Parameter raus
%Nochmal neue Parameter für psiq aus der Curvefittingtoolbox 
aq1 =0.0041;
aq2 =0.2092;
aq3 =0.0010;
aq4 =28.4940;
aq5 =-24.2348;
aq6 =0.0405;
aq7 =-0.0030;
aq8 =-0.6286;
aq9 =0.1516;
aq10 =0.0032;
aq11 =0.6133;
aq12 =0.1467;

% Parameter aus der curvefitting Toolbox für psid
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

%AB HIER ist nur noch Ausgabe wo die berechneten Parameter eingesetzt werden
%Das sind einfach mal die Werte aus dem Polyfit mit den Polynomen in eine Formel getan
p00= 0.0167;
p10 = 7.8264e-04;
p01 = 1.6049e-05;
p20 = 2.1681e-08;
p11 = -0.0000;
p02 = -3.3394e-05;
p30 = 4.1224e-07;
p21 = -5.0330e-08;
p12 = -7.7794e-07;
p03 = -1.1882e-07;
p40 = 5.1334e-08;
p31 = 3.2042e-08;
p22 = 5.1152e-08;
p13 = -3.3426e-09;
p04 = 3.3261e-08;
p50 =9.4763e-10;
p41 = 1.2311e-09;
p32 = 1.3180e-09;
p23 = -3.0471e-10;
p14 = 1.4475e-09;
p05 = 1.0813e-10;

 fluxd_poly_approx = p00 + (p10.*d_current) +(p01.*q_current_T) +(p20.*(d_current.^2)) +(p02.*(q_current_T.^2)) + (p30.*(d_current.^3))+ (p21.*(d_current.^2).*q_current_T) +(p12.*d_current.*(q_current.^2))+ (p03.*(q_current.^3)) + (p40.*(d_current.^4)) + (p31.*(d_current.^3).*q_current_T)... 
     + (p22.*(d_current.^2).*(q_current_T.^2)) + (p13.*d_current.*q_current_T) +(p04.*(q_current_T.^4)) +(p50.*(d_current.^5)) +(p41.*(d_current.^4).*q_current_T) +(p32.*(d_current.^3).*(q_current.^2)) + (p23.*(d_current.^2).*(q_current.^3)) + (p14.*d_current.*(q_current_T.^4)) + (p05.*(q_current.^5));
 fluxq_poly_approx = 0;


%Das sind die Formeln für Methode 1 um dann einfach die Berechneten Paramet einzusetzen sie dann in Matlab in einer Figure darzustellen 
flux_q_approx_m1 =(  ((aq1*tanh(aq2.*q_current_T))+(aq3.*q_current_T)) ...
     .*(  ( (aq4+(aq5./(1+(aq6.*(q_current_T.^2)))))   .*exp(-((aq7+(aq8./(1+(aq9.*(q_current_T.^2))))).*d_current).^2) ) ...
     +(     (1-((aq4+(aq5./(1+(aq6.*(q_current_T.^2)))))).*exp(-((aq10+(aq11./(1+(aq12.*(q_current_T.^2))))).*d_current).^2))   )      )       );

flux_d_approx_m1 = (ad1.*(tanh(ad2.*(d_current-ad3)))) ...
    .*(   (ad4+(ad5./(1+(ad6.*(d_current.^2)))))   .*exp(-((ad7+(ad8./(1+(ad9.*(d_current.^2))))).*q_current_T).^2) ...
    + (    (    1-((ad4+(ad5./(1+(ad6.*(d_current.^2))))))  ).*exp(-((ad10+(ad11./(1+(ad12.*(d_current.^2))))).*q_current).^2)   )      );


%Berechnen des Fehlers in %
fluxd_max = max(fluxd_real, [], 'all');
fluxq_max = max(fluxq_real, [], 'all');

ed = ((abs(fluxd_real-flux_d_approx_m1))/fluxd_max).*100;
eq = ((abs(fluxq_real-flux_q_approx_m1))/fluxq_max).*100;

%Error für Polyfit
% ed = ((abs(fluxd_real-fluxd_poly_approx))/fluxd_max).*100;
% eq = ((abs(fluxq_real-fluxq_poly_approx))/fluxq_max).*100;



figure;
% 1 Approximierter Fluss_d
subplot(2,1,1); 
grid on;
surf(d_current, q_current, flux_d_approx_m1);
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
surf(d_current, q_current, flux_q_approx_m1);
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


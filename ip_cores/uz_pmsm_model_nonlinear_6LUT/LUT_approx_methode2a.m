%Fitting_flux_approximation
close all;
%LUT Fitting

%LeastSquare Problems
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt');
d_current = d_current_d_Flux';
q_current = q_current_d_Flux;


% 1. Gleichung Selbstinduktivität Psid
Fluxd_iqnull = Flux_d(:,10);

%Formel aus Paper2 für Methode 2c "Linearen Bereich" 
%fun0=@(ad)Fluxd_iqnull-(ad(1).*tanh(ad(2)*(d_current-ad(3))));

%Mit folgender Formel funktioniert das fitting leider nicht (echte daten sind zu linear)
%fun0=@(ad)(Fluxd_iqnull-((ad(1).*(tanh(ad(2)*d_current)))+(ad(3).*d_current)));
fun0=@(ad,d_current) ad(1).*tanh(ad(2)*(d_current-ad(3)));

beta1 =  [0.0305;0.0402; -16.4812];
%ad_1 = lsqnonlin(fun0,beta1,[],[],options)
ad_1 = nlinfit(d_current,Fluxd_iqnull,fun0,beta1);
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

% 3. Gleichung Maximale Induktivität psid bei Iq1
Fluxd_iq1 = Flux_d(:,1);
fun3=@(ad_zwei)Fluxd_iq1-(ad_zwei(1).*(tanh(ad_zwei(2)*(d_current-ad_zwei(3)))))

beta3 =   [0.0305;0.0402; -16.4812];  %Diese 2-D Plots würden in den meisten fällen auch mit "schlechten" Anfangswerten funktionieren
ad_3_6 = lsqnonlin(fun3,beta3,[],[],options)
Fluxd_iq1_fitted = (ad_3_6(1).*(tanh(ad_3_6(2)*(d_current-ad_3_6(3)))));

ad4 = ad_3_6(1);
ad5 = ad_3_6(2);
ad6 = ad_3_6(3);

% 4. Gleichung Maximale Induktivität pisq bei Id1
Fluxq_id1 = Flux_q(14,:)';
fun4=@(aq_zwei)Fluxq_id1-((aq_zwei(1).*(tanh(aq_zwei(2).*q_current)))+(aq_zwei(3).*q_current));

beta4 = [1;1;1];
aq_3_6 = lsqnonlin(fun4,beta4,[],[],options)
Fluxq_id1_fitted = ((aq_3_6(1).*(tanh(aq_3_6(2).*q_current)))+(aq_3_6(3).*q_current));

aq4 = aq_3_6(1);
aq5 = aq_3_6(2);
aq6 = aq_3_6(3);


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

%Dritter Plot
subplot(4,1,3); 
grid on;

plot(d_current, Fluxd_iq1_fitted  , 'DisplayName', 'Fluxd_{iq1}_{fitted}');
hold on;
plot(d_current, Fluxd_iq1,'*', 'DisplayName', 'Fluxd_{iq1}');
legend('show');

% Vierter Plot
subplot(4,1,4); 
grid on;
plot(q_current, Fluxq_id1_fitted  , 'DisplayName', 'Fluxq_{id1}_{fitted}');
hold on;
plot(q_current, Fluxq_id1,'*', 'DisplayName', 'Fluxq_{id1}');
legend('show');


%Maximum Crosscoupling current constants id1 und iq1

%Selbstinduktion (Zuweisung eigentlich nur wegen Namesgebung)
psidself = Fluxd_iqnull_fitted;

psiqself = Fluxq_idnull_fitted;

% psid_s1 = repmat(Fluxd_iq1_fitted, 1, 20);

psid_s1 = Fluxd_iq1_fitted; 

% psiq_s1 = repmat(Fluxq_id1_fitted, 1, 20);

psiq_s1 = Fluxq_id1_fitted;


psi_d_cross_integrated = @(d_current) ad1.*(tanh(ad2*(d_current-ad3))) - (ad4.*(tanh(ad5*(d_current-ad6))));
test = integral(psi_d_cross_integrated,min(d_current),max(d_current))
%dann ist die Kreuzkopplungin diesem Punkt 
psid_cross_s1 = psidself - psid_s1;
psiq_cross_s1 = psiqself - psiq_s1;


%Die beiden werden dann integriert (wieso auch immer) 
%psiid_cross_s1_integrated = (1/2)*(ad3-ad6).*((d_current).^2)+((ad1/ad2).*log(cosh(ad2.*d_current)))-((ad4/ad5).*log(cosh(ad5.*d_current)));
%psiid_cross_s1_integrated = (1/3)*(ad1-ad4).*((d_current).^3)+(1/2)*(ad2-ad5).*((d_current).^2)+(ad3-ad6).*((d_current));

%psiid_cross_s1_integrated = ((ad1./ad2).*(log(cosh(ad2.*(d_current-ad3))))) - (((ad1.*ad4)).*(log(cosh(ad5.*(d_current-ad6)))./ad5));
psiid_cross_s1_integrated = ((ad1./ad2).*(log(cosh(ad2.*(d_current-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current-ad6)))));
psiiq_cross_s1_integrated = ((1/2).*(aq3-aq6).*((q_current).^2))+((aq1./aq2).*log(cosh(aq2.*q_current)))-((aq4./aq5).*log(cosh(aq5.*q_current)));

%Ableitungen
% psid_nachId = (ad1*tanh(ad2*(x-ad3))-(ad4*(tanh(ad5*(x-ad6)))))
% psiq_nachiq = (((1/2)*(aq3-aq6)*((q_current)^2))+((aq1/aq2)*log(cosh(aq2*q_current)))-((aq4/aq5)*log(cosh(aq5*q_current))))


%Berechnen von F(i1)*G(i1) (wie im Paper)

%Das sind die Setpoints aus für 
q_current_set = q_current(1);
d_current_set = d_current(14);

%Für den Faktor setzte ich einfach in der Formel der Integrierten Terme den Set Strom ein 
Fid1_Giq1 = ((1/2).*(aq3-aq6).*((q_current_set).^2))+((aq1./aq2).*log(cosh(aq2.*q_current_set)))-((aq4/aq5).*log(cosh(aq5.*q_current_set)));
%Fid2_Giq2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set-ad3))))) - (((ad1.*ad4)).*(log(cosh(ad5.*(d_current_set-ad6)))./ad5));
Fid2_Giq2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current_set-ad6)))));

%Kreuzkopplung ist dann
psi_d_cross = (1/Fid1_Giq1).*((psid_cross_s1').*(psiiq_cross_s1_integrated));
psi_q_cross = (1/Fid2_Giq2).*((psiq_cross_s1).*(psiid_cross_s1_integrated'));

%Eigeninduktivität noch "padden"
psidself_padded = repmat(Fluxd_iqnull_fitted, 1, 20)';
psiqself_padded = repmat(Fluxq_idnull_fitted, 1, 20);

% psiid_cross_s1_integrated = repmat(psiid_cross_s1_integrated, 20, 1);
% psiiq_cross_s1_integrated = repmat(psiiq_cross_s1_integrated, 1, 20);
%"Fertig Approximierter Fluss
psi_d_approx = psidself_padded - psi_d_cross;
psi_q_approx = psiqself_padded - psi_q_cross;

fluxd_real = Flux_d';
fluxq_real = Flux_q';

%% Berechnung der induktivitäten
% psi_d_cross_s1_abgeleitet = ((ad1.*ad2.*((sech(ad2.*(d_current-ad3))).^2))-(ad4.*ad5.*((sech(ad2.*(d_current-ad3))).^2)));
% psi_dself_abgeleitet = (ad1.*ad2.*((sech(ad2.*(d_current-ad3))).^2));

%Ldd
psi_d_cross_s1_abgeleitet = ((ad1.*ad2.*(1./((cosh(ad2.*(d_current-ad3))).^2)))-(ad4.*ad5.*(1./((cosh(ad5.*(d_current-ad6))).^2))));
psi_dself_abgeleitet = (ad1.*ad2.*(1./((cosh(ad2.*(d_current-ad3))).^2)));

psi_dself_abgeleitet_padded = repmat(psi_dself_abgeleitet, 1, 20)';
psi_dcross_abgeleitet = (1/Fid1_Giq1).*(psi_d_cross_s1_abgeleitet').*(psiiq_cross_s1_integrated);

Ldd_approx_test = psi_dself_abgeleitet_padded - psi_dcross_abgeleitet;


%Ldq
%Bleibt Gleich da nach q Abgeleitet
psi_dq_cross_s1_abgeleitet = psid_cross_s1;

%Wird 0 da nicht abhängig von q
psi_dqself_abgeleitet = 0;
psi_dqself_abgeleitet_padded = repmat(psi_dqself_abgeleitet, 1, 20)';

psiidq_cross_s1_integrated_abgeleitet = psiq_cross_s1; %Wurde ja vorher integriert

%Also ist das eigentlich (1/Fid1_Giq1).*psiid_cross_s1.*psiiq_cross_s1
psi_dqcross_abgeleitet = (1/Fid1_Giq1).*(psi_dq_cross_s1_abgeleitet').*(psiidq_cross_s1_integrated_abgeleitet);

Ldq_approx_test = psi_dqself_abgeleitet_padded  -  psi_dqcross_abgeleitet;


%Lqq
psi_q_cross_s1_abgeleitet = (aq1.*aq2.*(1./((cosh(aq2.*q_current)).^2))+aq3) - (aq4.*aq5.*(1./((cosh(aq5.*q_current)).^2))+aq6);
psi_qself_abgeleitet = (aq1.*aq2.*(1./((cosh(aq2.*q_current)).^2))+aq3);

psi_qself_abgeleitet_padded = repmat(psi_qself_abgeleitet, 1, 20);
psi_qcross_abgeleitet = (1/Fid2_Giq2).*(psi_q_cross_s1_abgeleitet').*(psiid_cross_s1_integrated);

Lqq_approx_test = psi_qself_abgeleitet_padded - psi_qcross_abgeleitet;


%Lqd
%Bleibt Gleich da nach d Abgeleitet
psi_qd_cross_s1_abgeleitet = psiq_cross_s1; 

%Wird 0 da nicht abhängig von d
psi_qdself_abgeleitet = 0;
psi_qdself_abgeleitet_padded = repmat(psi_qdself_abgeleitet, 1, 20);

psiiqd_cross_s1_integrated_abgeleitet = psid_cross_s1; %Wurde ja vorher integriert
 
%Also ist das eigentlich (1/Fid2_Giq2).*psiiq_cross_s1.*psiid_cross_s1
psi_qdcross_abgeleitet = (1/Fid2_Giq2).*(psi_qd_cross_s1_abgeleitet).*(psiiqd_cross_s1_integrated_abgeleitet');
psi_qdcross_abgeleitet = (1/Fid2_Giq2).*(psiq_cross_s1).* (psid_cross_s1');
% psiid_test = diff(psiid_cross_s1_integrated)
% psi_qdcross_abgeleitet   = (1/Fid2_Giq2).*(psiq_cross_s1).*(psiid_test')

Lqd_approx_test = -psi_qdcross_abgeleitet;


%Induktivitäten aus approximiertem Fluss mit Gradienten
[Ldd_approx,Ldq_approx]=gradient(psi_d_approx,1.6842,2.5263);
[Lqd_approx,Lqq_approx]=gradient(psi_q_approx,1.6842,2.5263);

%Induktivitäten aus approximiertem Fluss mit Gradienten (nur als Vergleich für die Simulink Simulation
[Ldq_simu,Ldd_simu]=gradient(psi_d_approx',2.5263,1.6842);
[Lqq_simu,Lqd_simu]=gradient(psi_q_approx',2.5263,1.6842);

%% Error berechung zwischen den Flusskarten
fluxd_max = max(fluxd_real, [], 'all');
fluxq_max = max(fluxq_real, [], 'all');

ed = ((abs(fluxd_real-psi_d_approx))/fluxd_max).*100;
eq = ((abs(fluxq_real-psi_q_approx))/fluxq_max).*100;

Lqq_approx_max = max(Lqq_approx, [], 'all');
ed_L = ((abs(Lqq_approx-Lqq_approx_test))/Lqq_approx_max).*100;

%% Plotten
figure;
% Approximierter Fluss
subplot(2,1,1); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current,psi_d_approx);
xlabel('D Current');
ylabel('Q Current');
zlabel('psi_dapprox');
legend;

% Echter Fluss
subplot(2,1,2); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, fluxd_real);
%surf(X, Y, fluxd_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('psi_qreal');
legend;

figure;
% Approximierter Fluss
subplot(2,1,1); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current,psi_q_approx);
xlabel('D Current');
ylabel('Q Current');
zlabel('psi_{qapprox}');
legend;

% Echter Fluss
subplot(2,1,2); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, fluxq_real);
%surf(X, Y, fluxd_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('psi_{qreal}');
legend;


figure;
% Error psid zwischen approx und echtem Fluss
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, ed);
xlabel('D Current');
ylabel('Q Current');
zlabel('error %');
title('error psid');
legend;

figure;
% Error psiq zwischen approx und echtem Fluss
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, eq);
xlabel('D Current');
ylabel('Q Current');
zlabel('error %');
title('error psiq');
legend;


figure;
% Approximierter Fluss
subplot(2,1,1); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current,Ldd_approx_test);
xlabel('d Current');
ylabel('q Current');
zlabel('L');
title('Mit Gradient');
legend;

% Approximierter Fluss
subplot(2,1,2); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current,Ldd);
xlabel('d Current');
ylabel('q Current');
zlabel('L');
title('Mit Ableitung');
legend;

% Echter Fluss
% subplot(2,1,3); 
figure;
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current,Ldd_simu);
%surf(X, Y, fluxd_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('L');
title('Mit Gradient aus Flusskarte');
legend;
% 
figure;
% Error psiq zwischen approx und echtem Fluss
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, ed_L);
xlabel('D Current');
ylabel('Q Current');
zlabel('error %');
title('error L');
legend;







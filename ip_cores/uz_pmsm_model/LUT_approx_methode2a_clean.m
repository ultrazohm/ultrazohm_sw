%Fitting_flux_approximation

close all;
%% LUT Fitting
%LeastSquare Problems
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt');
d_current = id(1,:);
q_current = iq(:,1);
[~,id_null] = min(abs(d_current))
[~,iq_null] = min(abs(q_current))

id1 = id_null-1;

% [~,id1] = max(abs(id))
% [~,id1] = max(id)
[~,iq1] = max(abs(iq))
iq1 = iq1+2;

%Preparation
%Hier soll mall die Werte für den Fluss gesucht werden

%% Start der eigentlichen Berechnung 

% 1. Self-axis flux linkage d-axis
psi_d_iq_null = psi_d(iq_null,:);
fun0=@(ad) psi_d_iq_null-(ad(1).*tanh(ad(2)*(d_current-ad(3))));
beta1 =  [1;1;1]; %random starting parameters
ad_self = lsqnonlin(fun0,beta1,[],[],options);
%Zuweisung der Parameter
ad1 = ad_self(1);
ad2 = ad_self(2);
ad3 = ad_self(3);

% 2. Self-axis flux linkage q-axis
psi_q_id_null = psi_q(:,id_null);
fun2=@(aq)(psi_q_id_null-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current)));
beta2 = [1;1;1]; %random starting parameters
aq_self = lsqnonlin(fun2,beta2,[],[],options);
aq1 = aq_self(1);
aq2 = aq_self(2);
aq3 = aq_self(3);

% 3. flux linkage d-axis with maximum cross-coupling
psi_d_iq1 = psi_d(iq1,:);
fun3=@(ad_cross)psi_d_iq1-(ad_cross(1).*(tanh(ad_cross(2)*(d_current-ad_cross(3)))));
beta3 = [1;1;1]; %random starting parameters
ad_4_6 = lsqnonlin(fun3,beta3,[],[],options);
ad4 = ad_4_6(1);
ad5 = ad_4_6(2);
ad6 = ad_4_6(3);

% 4. flux linkage q-axis with maximum cross-coupling
psi_q_id1 = psi_q(:,id1);
fun4=@(aq_cross)psi_q_id1-((aq_cross(1).*(tanh(aq_cross(2).*q_current)))+(aq_cross(3).*q_current));
beta4 = [1;1;1]; %random starting parameters
aq_4_6 = lsqnonlin(fun4,beta4,[],[],options);
aq4 = aq_4_6(1);
aq5 = aq_4_6(2);
aq6 = aq_4_6(3);

% get die flux linkages with the calculated parameters
psidself = ad1.*(tanh(ad2*(d_current-ad3)));
psiqself = (aq1.*(tanh(aq2*q_current)))+(aq3.*q_current);
psid_s1 = ad4.*(tanh(ad5*(d_current-ad6))); 
psiq_s1 = (aq4.*(tanh(aq5.*q_current)))+(aq6.*q_current);
% cross coupling in s1
psid_cross_s1 = psidself - psid_s1;
psiq_cross_s1 = psiqself - psiq_s1;

%% Plotten
figure;
% Erster Plot
subplot(4,1,1); 
grid on;
plot(d_current, psidself, 'DisplayName', 'Fluxd_{idnull}_{fitted}');
hold on;
plot(d_current, psi_d_iq_null,'*', 'DisplayName', 'Fluxd_{idnull}');
legend('show');

% Zweiter Plot
subplot(4,1,2); 
grid on;

plot(q_current, psiqself, 'DisplayName', 'Fluxq_{idnull}_{fitted}');
hold on;
plot(q_current, psi_q_id_null,'*', 'DisplayName', 'Fluxq_{idnull}');
legend('show');

%Dritter Plot
subplot(4,1,3); 
grid on;
plot(d_current, psid_s1, 'DisplayName', 'Fluxd_{iq1}_{fitted}');
hold on;
plot(d_current, psi_d_iq1,'*', 'DisplayName', 'Fluxd_{iq1}');
legend('show');

% Vierter Plot
subplot(4,1,4); 
grid on;
plot(q_current, psiq_s1, 'DisplayName', 'Fluxq_{id1}_{fitted}');
hold on;
plot(q_current, psi_q_id1,'*', 'DisplayName', 'Fluxq_{id1}');
legend('show');

%Berechnen von F(i1)*G(i1) (wie im Paper)
%Das sind die Setpoints an denen eben die kreuzkopplung berechnet wird
q_current_set = q_current(1);
d_current_set = d_current(14);

%Für den Faktor setzte ich einfach in der Formel der Integrierten Terme den Set Strom ein 
Fid1_Giq1 = ((1/2).*(aq3-aq6).*((q_current_set).^2))+((aq1./aq2).*log(cosh(aq2.*q_current_set)))-((aq4/aq5).*log(cosh(aq5.*q_current_set)));
%Fid2_Giq2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set-ad3))))) - (((ad1.*ad4)).*(log(cosh(ad5.*(d_current_set-ad6)))./ad5));
Fid2_Giq2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current_set-ad6)))));

%% fitting only to plot the function and see if the fitting worked

d_current = id;
q_current = iq;

%Die beiden werden dann integriert (wieso auch immer) 
psiid_cross_s1_integrated = ((ad1./ad2).*(log(cosh(ad2.*(d_current-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current-ad6)))));
psiiq_cross_s1_integrated = ((1/2).*(aq3-aq6).*((q_current).^2))+((aq1./aq2).*log(cosh(aq2.*q_current)))-((aq4./aq5).*log(cosh(aq5.*q_current)));

%Kreuzkopplung ist dann
psi_d_cross = (1/Fid1_Giq1).*((psid_cross_s1).*(psiiq_cross_s1_integrated));
psi_q_cross = (1/Fid2_Giq2).*((psiq_cross_s1).*(psiid_cross_s1_integrated'));

%Eigeninduktivität noch "padden"
psidself_padded = repmat(psidself, 20, 1);
psiqself_padded = repmat(psiqself, 1, 20);

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

psi_dself_abgeleitet_padded = repmat(psi_dself_abgeleitet, 20, 1);
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
% subplot(1,2,1); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current,psi_d_approx);
xlabel('$$i_{d}$$','Interpreter','Latex');
ylabel('$$i_{q}$$','Interpreter','Latex');
zlabel('$$\hat{\psi}_{d}$$','Interpreter','Latex');
% title('Approximierter Fluss $$\hat{\psi}_{d}$$','Interpreter','Latex');
% legend;

% % Echter Fluss
% subplot(2,1,2); 
% grid on;
% % plot(q_current_q_Flux, Fluxd_iqnull);
% surf(d_current, q_current, fluxd_real);
% %surf(X, Y, fluxd_real);
% xlabel('i_{d}');
% ylabel('i_{q}');
% zlabel('\psi_{d}');
% legend;

% % figure;
% % Approximierter Fluss
% subplot(1,2,2);
% grid on;
% % plot(q_current_q_Flux, Fluxd_iqnull_fitted);
% surf(d_current, q_current,psi_q_approx);
% xlabel('$$i_{d}$$','Interpreter','Latex');
% ylabel('$$i_{q}$$','Interpreter','Latex');
% zlabel('$$\hat{\psi}_{q}$$','Interpreter','Latex');
% % title('Approximierter Fluss $$\hat{\psi}_{q}$$','Interpreter','Latex');
% % legend;
% 
% % Echter Fluss
% subplot(2,1,2); 
% grid on;
% % plot(q_current_q_Flux, Fluxd_iqnull);
% surf(d_current, q_current, fluxq_real);
% %surf(X, Y, fluxd_real);
% xlabel('D Current');
% ylabel('Q Current');
% zlabel('psi_{qreal}');
% title('Fluss \psi_{d}');
% legend;


% figure;
% % Error psid zwischen approx und echtem Fluss
% grid on;
% % plot(q_current_q_Flux, Fluxd_iqnull);
% surf(d_current, q_current, ed);
% xlabel('$$i_{d}/A$$','Interpreter','Latex');
% ylabel('$$i_{q}/A$$','Interpreter','Latex');
% zlabel('$$\varepsilon_d/\%$$','Interpreter','Latex');
% % title('error psid');
% % legend;
% 
figure;
% Error psiq zwischen approx und echtem Fluss
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, eq);
xlabel('$$i_{d}/A$$','Interpreter','Latex');
ylabel('$$i_{q}/A$$','Interpreter','Latex');
zlabel('$$\varepsilon_q/\%$$','Interpreter','Latex');
% title('error psiq');
% legend;
% 
% 
% figure;
% % Approximierter Fluss
% subplot(2,1,1); 
% grid on;
% % plot(q_current_q_Flux, Fluxd_iqnull_fitted);
% surf(d_current, q_current,Ldd_approx_test);
% xlabel('d Current');
% ylabel('q Current');
% zlabel('L');
% title('Mit Gradient');
% legend;

% Approximierter Fluss
figure;
subplot(2,1,1); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current,Lqq_approx_test);
xlabel('d Current');
ylabel('q Current');
zlabel('L');
title('Mit Ableitung');
legend;
% 
% Echter Fluss
subplot(2,1,2); 

grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current,Lqq_approx);
%surf(X, Y, fluxd_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('L');
title('Mit Gradient aus approx. Flusskarte');
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







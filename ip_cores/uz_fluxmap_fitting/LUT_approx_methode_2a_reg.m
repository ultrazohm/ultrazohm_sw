%Fitting_flux_approximation
close all;
%LUT Fitting

%LeastSquare Problems
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt');
d_current = d_current_d_Flux';

d_current_reg1 = [d_current(1:10); zeros(10, 1)];
d_current_reg2 = [d_current(11:20);zeros(10, 1)];
q_current = q_current_d_Flux;
q_current_reg1 = [q_current(1:10);zeros(10,1)];
q_current_reg2 = [q_current(11:20);zeros(10,1)];

d_current_test = FluxMapData{1:20,1:20};
q_current_test = FluxMapData{22:41,1:20};


%% Berechnen der Selbsinduktivitäten und Kreuzkopplungsinduktivitäten
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
Fluxd_iq1_reg1 = Flux_d(:,1);
fun3_reg1=@(ad_reg1_zwei)Fluxd_iq1_reg1-(ad_reg1_zwei(1).*(tanh(ad_reg1_zwei(2)*(d_current-ad_reg1_zwei(3)))))

beta3_reg1 =   [0.0305;0.0402; -16.4812];  %Diese 2-D Plots würden in den meisten fällen auch mit "schlechten" Anfangswerten funktionieren
ad_3_6_reg1 = lsqnonlin(fun3_reg1,beta3_reg1,[],[],options)
Fluxd_iq1_reg1_fitted = (ad_3_6_reg1(1).*(tanh(ad_3_6_reg1(2)*(d_current-ad_3_6_reg1(3)))));

ad4_reg1 = ad_3_6_reg1(1);
ad5_reg1 = ad_3_6_reg1(2);
ad6_reg1 = ad_3_6_reg1(3);

% 3. Gleichung Maximale Induktivität psid bei Iq1
Fluxd_iq1_reg2 = Flux_d(:,20);
fun3_reg2=@(ad_reg2_zwei)Fluxd_iq1_reg2-(ad_reg2_zwei(1).*(tanh(ad_reg2_zwei(2)*(d_current-ad_reg2_zwei(3)))))

beta3_reg2 =   [0.0305;0.0402; -16.4812];  %Diese 2-D Plots würden in den meisten fällen auch mit "schlechten" Anfangswerten funktionieren
ad_3_6_reg2 = lsqnonlin(fun3_reg2,beta3_reg2,[],[],options)
Fluxd_iq1_reg2_fitted = (ad_3_6_reg2(1).*(tanh(ad_3_6_reg2(2)*(d_current-ad_3_6_reg2(3)))));

ad4_reg2 = ad_3_6_reg2(1);
ad5_reg2 = ad_3_6_reg2(2);
ad6_reg2 = ad_3_6_reg2(3);



% 4. Gleichung Maximale Induktivität pisq bei Id1
Fluxq_id1_reg1 = Flux_q(5,:)';
fun4_reg1=@(aq_zwei_reg1)Fluxq_id1_reg1-((aq_zwei_reg1(1).*(tanh(aq_zwei_reg1(2).*q_current)))+(aq_zwei_reg1(3).*q_current));

beta4_reg1 = [1;1;1];
aq_3_6_reg1 = lsqnonlin(fun4_reg1,beta4_reg1,[],[],options)
Fluxq_id1_reg1_fitted = ((aq_3_6_reg1(1).*(tanh(aq_3_6_reg1(2).*q_current)))+(aq_3_6_reg1(3).*q_current));

aq4_reg1 = aq_3_6_reg1(1);
aq5_reg1 = aq_3_6_reg1(2);
aq6_reg1 = aq_3_6_reg1(3);

% 4. Gleichung Maximale Induktivität pisq bei Id1
Fluxq_id1_reg2 = Flux_q(15,:)';
fun4_reg2=@(aq_zwei_reg2)Fluxq_id1_reg2-((aq_zwei_reg2(1).*(tanh(aq_zwei_reg2(2).*q_current)))+(aq_zwei_reg2(3).*q_current));

beta4_reg2 = [1;1;1];
aq_3_6_reg2 = lsqnonlin(fun4_reg2,beta4_reg2,[],[],options)
Fluxq_id1_reg2_fitted = ((aq_3_6_reg2(1).*(tanh(aq_3_6_reg2(2).*q_current)))+(aq_3_6_reg2(3).*q_current));

aq4_reg2 = aq_3_6_reg2(1);
aq5_reg2 = aq_3_6_reg2(2);
aq6_reg2 = aq_3_6_reg2(3);


%% Plotten der Selbsinduktivitäten und Kreuzkopplungsinduktivitäten
figure;
% Erster Plot
subplot(4,1,1); 
grid on;
plot(d_current, Fluxd_iq1_reg1_fitted, 'DisplayName', 'Fluxd_{idnull}_{fitted}');
hold on;
plot(d_current, Fluxd_iq1_reg1,'*', 'DisplayName', 'Fluxd_{idnull}');
legend('show');

% Zweiter Plot
subplot(4,1,2); 
grid on;

plot(d_current, Fluxd_iq1_reg2_fitted  , 'DisplayName', 'Fluxq_{idnull}_{fitted}');
hold on;
plot(d_current, Fluxd_iq1_reg2,'*', 'DisplayName', 'Fluxq_{idnull}');
legend('show');

%Dritter Plot
subplot(4,1,3); 
grid on;

plot(q_current, Fluxq_id1_reg1_fitted  , 'DisplayName', 'Fluxd_{iq1}_{fitted}');
hold on;
plot(q_current, Fluxq_id1_reg1,'*', 'DisplayName', 'Fluxd_{iq1}');
legend('show');

% Vierter Plot
subplot(4,1,4); 
grid on;
plot(q_current, Fluxd_iq1_reg2_fitted  , 'DisplayName', 'Fluxq_{id1}_{fitted}');
hold on;
plot(q_current, Fluxd_iq1_reg2,'*', 'DisplayName', 'Fluxq_{id1}');
legend('show');


%% Vorbereitung 
%Selbstinduktion (Zuweisung eigentlich nur wegen Namesgebung)
psidself = Fluxd_iqnull_fitted;

psiqself = Fluxq_idnull_fitted;

psid_s1_reg1 = Fluxd_iq1_reg1_fitted; 
psid_s1_reg2 = Fluxd_iq1_reg2_fitted; 

psiq_s1_reg1 = Fluxq_id1_reg1_fitted;
psiq_s1_reg2 = Fluxq_id1_reg2_fitted;

fluxd_real = Flux_d';
fluxq_real = Flux_q';

%% Berechnen der Methode 2a
%Maximum Crosscoupling current constants id1 und iq1

%% Region 1

%dann ist die Kreuzkopplungin diesem Punkt 
psid_cross_s1_reg1 = psidself - psid_s1_reg1;
psiq_cross_s1_reg1 = psiqself - psiq_s1_reg1;

%Die beiden werden dann integriert (wieso auch immer) 
%psiid_cross_s1_integrated = (1/2)*(ad3-ad6).*((d_current).^2)+((ad1/ad2).*log(cosh(ad2.*d_current)))-((ad4/ad5).*log(cosh(ad5.*d_current)));
%psiid_cross_s1_integrated = (1/3)*(ad1-ad4).*((d_current).^3)+(1/2)*(ad2-ad5).*((d_current).^2)+(ad3-ad6).*((d_current));

psiid_cross_s1_integrated_reg1 = ((ad1./ad2).*(log(cosh(ad2.*(d_current-ad3))))) - (((ad1.*ad4_reg1)).*(log(cosh(ad5_reg1.*(d_current-ad6_reg1)))./ad5_reg1));
psiiq_cross_s1_integrated_reg1 = ((1/2).*(aq3-aq6_reg1).*((q_current).^2))+((aq1./aq2).*log(cosh(aq2.*q_current)))-((aq4_reg1./aq5_reg1).*log(cosh(aq5_reg1.*q_current)));

% psiid_cross_s1_integrated_reg1 = [psiid_cross_s1_integrated_reg1(1:10); zeros(10, 1)];
% psiiq_cross_s1_integrated_reg1 = [psiiq_cross_s1_integrated_reg1(1:10); zeros(10, 1)];
%Berechnen von F(i1)*G(i1) (wie im Paper)

%Das sind die Setpoints kann mit gespielt werden um Ergebnis zu verändern müssen oben dann auch geändert werden.  
q_current_set_reg1 = q_current_reg1(1);
d_current_set_reg1 = d_current_reg1(5);

%Für den Faktor setzte ich einfach in der Formel der Integrierten Terme den Set Strom ein 
Fid1_Giq1_reg1 = (1/2).*(aq3-aq6_reg1).*((q_current_set_reg1).^2)+((aq1./aq2).*log(cosh(aq2.*q_current_set_reg1)))-((aq4_reg1/aq5_reg1).*log(cosh(aq5_reg1.*q_current_set_reg1)));
Fid2_Giq2_reg1 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set_reg1-ad3))))) - (((ad1.*ad4_reg1)).*(log(cosh(ad5_reg1.*(d_current_set_reg1-ad6_reg1)))./ad5_reg1));

%Kreuzkopplung ist dann
psi_d_cross_reg1 = (1/Fid1_Giq1_reg1).*((psid_cross_s1_reg1').*(psiiq_cross_s1_integrated_reg1));
psi_q_cross_reg1 = (1/Fid2_Giq2_reg1).*((psiq_cross_s1_reg1).*(psiid_cross_s1_integrated_reg1));

 %% Region 2

%dann ist die Kreuzkopplungin diesem Punkt
psid_cross_s1_reg2 = psidself - psid_s1_reg2;
psiq_cross_s1_reg2 = psiqself - psiq_s1_reg2;

%Die beiden werden dann integriert (wieso auch immer) 
%psiid_cross_s1_integrated = (1/2)*(ad3-ad6).*((d_current).^2)+((ad1/ad2).*log(cosh(ad2.*d_current)))-((ad4/ad5).*log(cosh(ad5.*d_current)));
%psiid_cross_s1_integrated = (1/3)*(ad1-ad4).*((d_current).^3)+(1/2)*(ad2-ad5).*((d_current).^2)+(ad3-ad6).*((d_current));

psiid_cross_s1_integrated_reg2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current-ad3))))) - (((ad1.*ad4_reg2)).*(log(cosh(ad5_reg2.*(d_current-ad6_reg2)))./ad5_reg2));
psiiq_cross_s1_integrated_reg2 = ((1/2).*(aq3-aq6_reg2).*((q_current).^2))+((aq1./aq2).*log(cosh(aq2.*q_current)))-((aq4_reg2./aq5_reg2).*log(cosh(aq5_reg2.*q_current)));

% psiid_cross_s1_integrated_reg2 = [zeros(10, 1); psiid_cross_s1_integrated_reg2(1:10)];
% psiiq_cross_s1_integrated_reg2 = [zeros(10, 1); psiiq_cross_s1_integrated_reg2(1:10)];

%Berechnen von F(i1)*G(i1) (wie im Paper)

%Das sind die Setpoints kann mit gespielt werden um Ergebnis zu verändern müssen oben dann auch geändert werden.  
q_current_set_reg2 = d_current_reg2(10);
d_current_set_reg2 = d_current_reg2(5);

%Für den Faktor setzte ich einfach in der Formel der Integrierten Terme den Set Strom ein 
Fid1_Giq1_reg2 = (1/2).*(aq3-aq6_reg2).*((q_current_set_reg2).^2)+((aq1./aq2).*log(cosh(aq2.*q_current_set_reg2)))-((aq4_reg2/aq5_reg2).*log(cosh(aq5_reg2.*q_current_set_reg2)));
Fid2_Giq2_reg2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set_reg2-ad3))))) - (((ad1.*ad4_reg2)).*(log(cosh(ad5_reg2.*(d_current_set_reg2-ad6_reg2)))./ad5_reg2));

%Kreuzkopplung ist dann
psi_d_cross_reg2 = (1/Fid1_Giq1_reg2).*((psid_cross_s1_reg2').*(psiiq_cross_s1_integrated_reg2));
psi_q_cross_reg2 = (1/Fid2_Giq2_reg2).*((psiq_cross_s1_reg2).*(psiid_cross_s1_integrated_reg2));

%% ab hier nur noch einsetzten
%Eigeninduktivität noch "padden"
psidself_padded = repmat(Fluxd_iqnull_fitted, 1, 20)';
psiqself_padded = repmat(Fluxq_idnull_fitted, 1, 20);

% psiid_cross_s1_integrated = repmat(psiid_cross_s1_integrated, 20, 1);
% psiiq_cross_s1_integrated = repmat(psiiq_cross_s1_integrated, 1, 20);

% %"Fertig Approximierter Fluss
% psi_d_approx_reg1 = psidself_padded - psi_d_cross_reg1;
% psi_q_approx_reg1 = psiqself_padded - psi_q_cross_reg1;
% 
% %"Fertig Approximierter Fluss
% psi_d_approx_reg2 = psidself_padded - psi_d_cross_reg2;
% psi_q_approx_reg2 = psiqself_padded - psi_q_cross_reg2;


%% Berechnung des errors
%Error berechung zwischen den Flusskarten
fluxd_max = max(fluxd_real, [], 'all')
fluxq_max = max(fluxq_real, [], 'all');

% ed = ((abs(fluxd_real-psi_d_approx))/fluxd_max).*100;
% eq = ((abs(fluxq_real-psi_q_approx))/fluxq_max).*100;

%% plotten

figure;
% Approximierter Fluss
subplot(2,1,1); 
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current,psi_d_cross_reg1);
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
surf(d_current, q_current,psi_d_cross_reg2);
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


% figure;
% % Error psid zwischen approx und echtem Fluss
% grid on;
% % plot(q_current_q_Flux, Fluxd_iqnull);
% surf(d_current, q_current, ed);
% xlabel('D Current');
% ylabel('Q Current');
% zlabel('error %');
% title('error psid');
% legend;
% 
% figure;
% % Error psiq zwischen approx und echtem Fluss
% grid on;
% % plot(q_current_q_Flux, Fluxd_iqnull);
% surf(d_current, q_current, eq);
% xlabel('D Current');
% ylabel('Q Current');
% zlabel('error %');
% title('error psiq');
% legend;





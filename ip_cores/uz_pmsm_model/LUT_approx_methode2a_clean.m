%Fitting_flux_approximation

close all;
%% LUT Fitting

%% Preparation
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt');
d_current = id(1,:);
q_current = iq(:,1);
[~,id_null] = min(abs(d_current))
[~,iq_null] = min(abs(q_current))

id1 = id_null-1;

% [~,id1] = max(abs(id))
% [~,id1] = max(id)
[~,iq1] = max(abs(q_current))

%% start of the fitting procedure

%LeastSquare Problems
% 1. Self-axis flux linkage d-axis
psi_d_iq_null = psi_d(iq_null,:);
fun0=@(ad) psi_d_iq_null-(ad(1).*tanh(ad(2)*(d_current-ad(3))));
beta1 =  [0.0305;0.0402; -16.4812]; %random starting parameters
ad_self = lsqnonlin(fun0,beta1,[],[],options);
%Zuweisung der Parameter
ad1 = ad_self(1);
ad2 = ad_self(2);
ad3 = ad_self(3);

% 2. Self-axis flux linkage q-axis
psi_q_id_null = psi_q(:,id_null);
psi_q_id_null = psi_q(:,9); %für hoeerner
fun2=@(aq)(psi_q_id_null-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current)));
beta2 = [1;1;1]; %random starting parameters
aq_self = lsqnonlin(fun2,beta2,[],[],options);
aq1 = aq_self(1);
aq2 = aq_self(2);
aq3 = aq_self(3);

% 3. flux linkage d-axis with maximum cross-coupling
psi_d_iq1 = psi_d(iq1,:);
fun3=@(ad_cross)psi_d_iq1-(ad_cross(1).*(tanh(ad_cross(2)*(d_current-ad_cross(3)))));
beta3 =   [0.0305;0.0402; -16.4812];  %random starting parameters
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

%% plot of the fitting results
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
q_current_set = q_current(iq1);
d_current_set = d_current(id1);

%Für den Faktor setzte ich einfach in der Formel der Integrierten Terme den Set Strom ein 
Fid1_Giq1 = ((1/2).*(aq3-aq6).*((q_current_set).^2))+((aq1./aq2).*log(cosh(aq2.*q_current_set)))-((aq4/aq5).*log(cosh(aq5.*q_current_set)));
Fid2_Giq2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current_set-ad6)))));

%% fitting only to plot the function and see if the fitting worked

% d_current = id;
% q_current = iq;

%Die beiden werden dann integriert (wieso auch immer) 
psiid_cross_s1_integrated = ((ad1./ad2).*(log(cosh(ad2.*(d_current-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current-ad6)))));
psiiq_cross_s1_integrated = ((1/2).*(aq3-aq6).*((q_current).^2))+((aq1./aq2).*log(cosh(aq2.*q_current)))-((aq4./aq5).*log(cosh(aq5.*q_current)));

% Kreuzkopplung ist dann
psi_d_cross = (1/Fid1_Giq1).*((psid_cross_s1).*(psiiq_cross_s1_integrated));
psi_q_cross = (1/Fid2_Giq2).*((psiq_cross_s1).*(psiid_cross_s1_integrated));


% Eigeninduktivität noch "padden"
[numRows_psid,numCols_psid] = size(psi_d)
[numRows_psiq,numCols_psiq] = size(psi_q)
psidself_padded = repmat(psidself, numRows_psid, 1);
psiqself_padded = repmat(psiqself, 1, numCols_psiq);

% Fertig Approximierter Fluss
psi_d_approx = psidself_padded - psi_d_cross;
psi_q_approx = psiqself_padded - psi_q_cross;


%% Error berechung zwischen den Flusskarten
fluxd_real = psi_d; %setting  new name so its clear what is the real flux linkage
fluxq_real = psi_q; %setting  new name so its clear what is the real flux linkage
%% Error berechung zwischen den Flusskarten
fluxd_max = max(fluxd_real, [], 'all');
fluxq_max = max(fluxq_real, [], 'all');

e_psid = ((abs(fluxd_real-psi_d_approx))/fluxd_max).*100;
e_psiq = ((abs(fluxq_real-psi_q_approx))/fluxq_max).*100;

%% plot of the final fitting results shown as in 3D 

% Approximierte Flüsse
%Approximierter Fluss psid
figure;
subplot(2,3,2); 
grid on;
surf(d_current, q_current,psi_d_approx);
xlabel('$$i_{d}$$/A','FontSize', 18,'Interpreter','Latex');
ylabel('$$i_{q}$$/A','FontSize', 18,'Interpreter','Latex');
zlabel('$$\hat{\psi}_{d}/Vs$$','FontSize', 18,'Interpreter','Latex');
%title('Approximierter Fluss $$\hat{\psi}_{d}$$','Interpreter','Latex');

%Approximierter Fluss psiq
subplot(2,3,5);
grid on;
surf(d_current, q_current,psi_q_approx);
xlabel('$$i_{d}/A$$','FontSize', 18,'Interpreter','Latex');
ylabel('$$i_{q}/A$$','FontSize', 18,'Interpreter','Latex');
zlabel('$$\hat{\psi}_{q}/Vs$$','FontSize', 18,'Interpreter','Latex');
%title('Approximierter Fluss $$\hat{\psi}_{q}$$','Interpreter','Latex');

%Echter Fluss psid
subplot(2,3,1); 
grid on;
surf(d_current, q_current, fluxd_real);
xlabel('$$i_{d}$$/A','FontSize', 18,'Interpreter','Latex');
ylabel('$$i_{q}$$/A','FontSize', 18,'Interpreter','Latex');
zlabel('$$\psi_{d}$$/Vs','FontSize', 18,'Interpreter','Latex');

%Echter Fluss psiq
subplot(2,3,4); 
grid on;
surf(d_current, q_current,fluxq_real);
xlabel('$$i_{d}/A$$','FontSize', 18,'Interpreter','Latex');
ylabel('$$i_{q}/A$$','FontSize', 18,'Interpreter','Latex');
zlabel('$$\psi_{q}/Vs$$','FontSize', 18,'Interpreter','Latex');

% Error psid zwischen approx und echtem Fluss
grid on;
subplot(2,3,3);
surf(d_current, q_current, e_psid);
xlabel('$i_d/A$','FontSize', 18,'Interpreter','Latex');
ylabel('$i_q/A$','FontSize', 18,'Interpreter','Latex');
zlabel('$\varepsilon_d/\%$','FontSize', 18,'Interpreter','Latex');
mittlerer_fehler_psid = mean(mean(e_psid))

% Error psiq zwischen approx und echtem Fluss
grid on;
subplot(2,3,6);
surf(d_current, q_current, e_psiq);
xlabel('$i_d/A$','FontSize', 18,'Interpreter','Latex');
ylabel('$i_q/A$','FontSize', 18,'Interpreter','Latex');
zlabel('$\varepsilon_q/\%$','FontSize', 18,'Interpreter','Latex');
mittlerer_fehler_psiq = mean(mean(e_psiq))






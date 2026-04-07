%Fitting_flux_approximation

close all;
set(0,'defaulttextinterpreter','latex')
%% LUT Fitting

%% extract Lookup table data
%For nonlinear Model to work LUTs have to be implemented
% Import the data from csv for lookup table
FluxMapData = readtable('FluxMapData_Prototyp_1000rpm_D');

% Currents
id = FluxMapData{1,1:20};
iq = FluxMapData{22:41,1};
%Psi_d
psi_d = FluxMapData{43:62,1:20}*(1e-3);
%Psi_q
psi_q = FluxMapData{108:127,1:20}*(1e-3);

figure;
surf(id,iq,psi_d)
figure;
surf(id,iq,psi_q)

%% Preparation for the fitting
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt'); 
d_current = id(1,:);
q_current = iq(:,1);
%Setpoints where the flux-linkage does not have 
[~,id_null] = min(abs(d_current));
[~,iq_null] = min(abs(q_current));

%The setpoints with the best results might differ for diffrent flux-linkages
id1 = id_null-1;   %This is the overall point with the best results for all flux linkages 
%[~,id1] = max(abs(id))
[~,iq1] = max(abs(q_current));  %Setpoint of flux-linkage with cross-coupling
% [~,id1] = max(id)


%% start of the fitting procedure

%LeastSquare Problems
% 1. Self-axis flux linkage d-axis
psi_d_iq_null = psi_d(iq_null,:);
fun0=@(ad) psi_d_iq_null-(ad(1).*tanh(ad(2)*(d_current-ad(3))));
beta1 = [0.0305;0.0402; -16.4812]; %set starting parameters for the following function
ad_self = lsqnonlin(fun0,beta1,[],[],options);
ad1 = ad_self(1);
ad2 = ad_self(2);
ad3 = ad_self(3);

% 2. Self-axis flux linkage q-axis
psi_q_id_null = psi_q(:,id_null);
fun2=@(aq)(psi_q_id_null-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current)));
beta2 = [1;1;1]; %random starting parameters for the following function
aq_self = lsqnonlin(fun2,beta2,[],[],options);
aq1 = aq_self(1);
aq2 = aq_self(2);
aq3 = aq_self(3);

% 3. flux linkage d-axis with cross-coupling
psi_d_iq1 = psi_d(iq1,:);
fun3=@(ad_cross)psi_d_iq1-(ad_cross(1).*(tanh(ad_cross(2)*(d_current-ad_cross(3)))));
beta3 = [0.0305;0.0402; -16.4812];  %set starting parameters for the following function
ad_4_6 = lsqnonlin(fun3,beta3,[],[],options);
ad4 = ad_4_6(1);
ad5 = ad_4_6(2);
ad6 = ad_4_6(3);

% 4. flux linkage q-axis with cross-coupling
psi_q_id1 = psi_q(:,id1);
fun4=@(aq_cross)psi_q_id1-((aq_cross(1).*(tanh(aq_cross(2).*q_current)))+(aq_cross(3).*q_current));
beta4 = [1;1;1]; %random starting parameters for the following function
aq_4_6 = lsqnonlin(fun4,beta4,[],[],options);
aq4 = aq_4_6(1);
aq5 = aq_4_6(2);
aq6 = aq_4_6(3);

%Calculating F(i1)*G(i1) at the setpoint, they are also parameters for the approximation
q_current_set = q_current(iq1);
d_current_set = d_current(id1);

Fid1_Giq1 = ((1/2).*(aq3-aq6).*((q_current_set).^2))+((aq1./aq2).*log(cosh(aq2.*q_current_set)))-((aq4/aq5).*log(cosh(aq5.*q_current_set)));
Fid2_Giq2 = ((ad1./ad2).*(log(cosh(ad2.*(d_current_set-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current_set-ad6)))));

%Saving Variables in .mat file
save('fitting_parameter','ad1','ad2','ad3','ad4','ad5','ad6','aq1','aq2','aq3','aq4','aq5','aq6','Fid1_Giq1','Fid2_Giq2');

% inserting the parameters to get the resulting flux-linkages 
psidself = ad1.*(tanh(ad2*(d_current-ad3)));
psiqself = (aq1.*(tanh(aq2*q_current)))+(aq3.*q_current);
psid_s1 = ad4.*(tanh(ad5*(d_current-ad6))); 
psiq_s1 = (aq4.*(tanh(aq5.*q_current)))+(aq6.*q_current);
% cross coupling in s1
psid_cross_s1 = psidself - psid_s1;
psiq_cross_s1 = psiqself - psiq_s1;

%% plot of the fitting results
figure;
% self flux-linkage of d-axis
subplot(2,2,1); 
plot(d_current, psidself, 'DisplayName', '$\hat{\psi}_{\mathrm{self,fitted}}^d/Vs$');
hold on;
plot(d_current, psi_d_iq_null,'*', 'Color', 'red', 'DisplayName', '$\psi_{\mathrm{self}}^d/Vs$');
xlabel('$$i_{d}$$/A','FontSize', 18);
ylabel('$$\psi_{d}/Vs$$','FontSize', 18);
% legend('show', 'Interpreter', 'latex');
legend('show', 'Interpreter', 'latex', 'FontSize', 18);
grid on;

% flux-linkage of q-axis
subplot(2,2,2); 
plot(q_current, psiqself, 'DisplayName', '$\hat{\psi}_{self,fitted}^q/Vs$');
hold on;
plot(q_current, psi_q_id_null,'*', 'Color', 'red', 'DisplayName', '$\hat{\psi}_{self}^q/Vs$');
xlabel('$$i_{q}$$/A','FontSize', 18);
ylabel('$$\psi_{q}/Vs$$','FontSize', 18);
legend('show', 'Interpreter', 'latex', 'FontSize', 18);
grid on;

% flux-linkage of d-axis in setpoint s1
subplot(2,2,3); 
plot(d_current, psid_s1, 'DisplayName', '$\hat{\psi}_{s1,fitted}^d/Vs$');
hold on;
plot(d_current, psi_d_iq1,'*', 'Color', 'red', 'DisplayName', '$\hat{\psi}_{s1}^d/Vs$');
xlabel('$$i_{d}$$/A','FontSize', 18);
ylabel('$$\psi_{d}/Vs$$','FontSize', 18);
legend('show', 'Interpreter', 'latex', 'FontSize', 18);
grid on;

% flux-linkage of q-axis in setpoint s1
subplot(2,2,4); 
% grid on;
plot(q_current, psiq_s1, 'DisplayName', '$\hat{\psi}_{s1,fitted}^q/Vs$');
hold on;
plot(q_current, psi_q_id1,'*', 'Color', 'red', 'DisplayName', '$\hat{\psi}_{s1}^q/Vs$');
xlabel('$$i_{q}$$/A','FontSize', 18);
ylabel('$$\psi_{q}/Vs$$','FontSize', 18);
legend('show', 'Interpreter', 'latex', 'FontSize', 18);
grid on;

%% plot the entire flux-linkage function and see if the fitting worked

%according to the paper these two have to be integrated
psiid_cross_s1_integrated = ((ad1./ad2).*(log(cosh(ad2.*(d_current-ad3))))) - ((ad4./ad5).*(log(cosh(ad5.*(d_current-ad6)))));
psiiq_cross_s1_integrated = ((1/2).*(aq3-aq6).*((q_current).^2))+((aq1./aq2).*log(cosh(aq2.*q_current)))-((aq4./aq5).*log(cosh(aq5.*q_current)));

% Crosscoupling
psi_d_cross = (1/Fid1_Giq1).*((psid_cross_s1).*(psiiq_cross_s1_integrated));
psi_q_cross = (1/Fid2_Giq2).*((psiq_cross_s1).*(psiid_cross_s1_integrated));

% self flux linkage "padden" to get a matrix
[numRows_psid,numCols_psid] = size(psi_d);  %This is to get the size of flux-linkages
[numRows_psiq,numCols_psiq] = size(psi_q);  %This is to get the size of flux-linkages
psidself_padded = repmat(psidself, numRows_psid, 1); 
psiqself_padded = repmat(psiqself, 1, numCols_psiq);

% entire approximated flux-linkage in d- and q-axis
psi_d_approx = psidself_padded - psi_d_cross;
psi_q_approx = psiqself_padded - psi_q_cross;

%% normalized Error between measured and approximated flux-linkage

fluxd_mea = psi_d; %setting new name so its clear what the measured flux linkage is
fluxq_mea = psi_q; %setting new name so its clear what the measured flux linkage is

fluxd_max = max(fluxd_mea, [], 'all');
fluxq_max = max(fluxq_mea, [], 'all');

e_psid = ((abs(fluxd_mea-psi_d_approx))/fluxd_max).*100;
e_psiq = ((abs(fluxq_mea-psi_q_approx))/fluxq_max).*100;

%% plot of the final approximation results with the corresponding error to the measured flux-linkages

% approximated flux-linkage in q-axis
figure;
subplot(2,3,2); 
grid on;
surf(d_current, q_current,psi_d_approx);
xlabel('$$i_{d}$$/A','FontSize', 18);
ylabel('$$i_{q}$$/A','FontSize', 18);
zlabel('$$\hat{\psi}_{d}/Vs$$','FontSize', 18);
title('approximated flux-linkage $$\hat{\psi}_{d}$$','Interpreter','Latex', 'FontSize', 18);

% approximated flux-linkage in q-axis
subplot(2,3,5);
grid on;
surf(d_current, q_current,psi_q_approx);
xlabel('$$i_{d}/A$$','FontSize', 18);
ylabel('$$i_{q}/A$$','FontSize', 18);
zlabel('$$\hat{\psi}_{q}/Vs$$','FontSize', 18);
title('approximated flux-linkage $$\hat{\psi}_{q}$$','Interpreter','Latex', 'FontSize', 18);

% measured flux-linkage in d-axis
subplot(2,3,1); 
grid on;
surf(d_current, q_current, fluxd_mea);
xlabel('$$i_{d}$$/A','FontSize', 18);
ylabel('$$i_{q}$$/A','FontSize', 18);
zlabel('$$\psi_{d}$$/Vs','FontSize', 18);
title('measured flux-linkage $$\psi_{d}$$','Interpreter','Latex', 'FontSize', 18);

% measured flux-linkage in q-axis
subplot(2,3,4); 
grid on;
surf(d_current, q_current,fluxq_mea);
xlabel('$$i_{d}/A$$','FontSize', 18);
ylabel('$$i_{q}/A$$','FontSize', 18);
zlabel('$$\psi_{q}/Vs$$','FontSize', 18);
title('measured flux-linkage $$\psi_{q}$$','Interpreter','Latex', 'FontSize', 18);

% Error of measured and approximated flux-linkage in d-axis
grid on;
subplot(2,3,3);
surf(d_current, q_current, e_psid);
xlabel('$i_d/A$','FontSize', 18);
ylabel('$i_q/A$','FontSize', 18);
zlabel('$\varepsilon_d/\%$','FontSize', 18);
title('normalized error $\varepsilon_d/\%$','Interpreter','Latex', 'FontSize', 18);

% Error of measured and approximated flux-linkage in q-axis
grid on;
subplot(2,3,6);
surf(d_current, q_current, e_psiq);
xlabel('$i_d/A$','FontSize', 18);
ylabel('$i_q/A$','FontSize', 18);
zlabel('$\varepsilon_q/\%$','FontSize', 18);
title('normalized error $\varepsilon_q/\%$','Interpreter','Latex', 'FontSize', 18);
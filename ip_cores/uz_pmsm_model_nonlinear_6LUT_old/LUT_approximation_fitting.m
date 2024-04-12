%Fitting_fluxlinkage_approximation
close all;
%LUT Fitting

%LeastSquare Problems
options.Algorithm = 'levenberg-marquardt';
% 1. Gleichung
Fluxd_iqnull = Flux_d(:,10);
% Fluxd_iqnull = Fluxd_iqnull+ rand(1,length(Fluxd_iqnull))
% test = Flux_d(:,10)'.*0.5;
% fun1=@(ad) sum((Fluxd_iqnull-ad(1)*tanh(ad(2)*d_current_d_Flux)-ad(3)*d_current_d_Flux).^2);
d_current = d_current_d_Flux';
% Fluxd_iqnull_modell = ad(1).*tanh(ad(2).*d_current)+ad(3).*d_current
%funtest=@(ad) Fluxd_iqnull-(ad(1).*tanh(d_current)+ad(2).*d_current);
%fun1=@(ad,d_current_d_Flu) ad(1)*tanh(ad(2)*d_current_d_Flux)+ad(3)*d_current_d_Flux;
% ad = fminsearch(fun1,[1 1 1])
beta1 = [1;1;1];
% opts = statset('nlinfit');
% opts.RobustWgtFun = 'bisquare';
% ad = nlinfit(d_current_d_Flux,Fluxd_iqnull,fun1,beta1)
% lb=min(Fluxd_iqnull)
% ub=max(Fluxd_iqnull)
ad = lsqnonlin(@(a) fun1(a),beta1,[],[],options)
% ad = lsqcurvefit(fun1,beta1,d_current_d_Flux,Fluxd_iqnull)
%Einfach ein anderer solver
% options = optimoptions('lsqcurvefit','Algorithm','levenberg-marquardt');
% lb = [];
% ub = [];
% test2 = lsqcurvefit(fun,beta0,d_current_d_Flux,fluxdtest,lb,ub,options)
% d_current = linspace(-24,10,1.7)
Fluxd_iqnull_fitted = ad(1).*(tanh(ad(2).*d_current))+(ad(3).*d_current);
% Fluxd_iqnull_fitted = ad(1)+(ad(2).*d_current);
% Fluxd_iqnull_fitted = (ad(1).*(tanh(d_current)))+(ad(2).*d_current);
% Fluxd_iqnull_fitted = fun1(ad_search, d_current_d_Flux);

ad1 = ad(1);
ad2 = ad(2);
ad3 = ad(3);

% 2. Gleichung
Fluxq_idnull = Flux_q(15,:)';
q_current = q_current_d_Flux;
fun2=@(aq)Fluxq_idnull-((aq(1).*(tanh(q_current)))+(aq(2).*q_current));
beta2 = [1;1];
aq_1 = lsqnonlin(fun2,beta2,[],[],options)
% aq = nlinfit(q_current,Fluxq_idnull,fun2,beta2);
Fluxq_idnull_fitted = ((aq_1(1).*(tanh(q_current)))+(aq_1(2).*q_current));

aq1 = aq_1(1);
aq2 = 1;
aq3 = aq_1(2);

% 3. Gleichung
Fluxd_iq1 = Flux_d(:,20);
%fun3=@(ad_zwei)Fluxd_iq1-((ad_zwei(1).*(tanh(d_current)))+(ad_zwei(2).*d_current));
% fun3=@(ad_zwei,d_current)Fluxd_iq1-((ad_zwei(1).*(tanh(d_current)))+(ad_zwei(2).*d_current));
fun3=@(ad_zwei,d_current)ad_zwei(1).*(tanh(d_current))+(ad_zwei(2).*d_current)
beta3 = [1;1];
% ad_3_6 = lsqnonlin(fun3,beta3,[],[],options)
ad_3_6 = nlinfit(d_current,Fluxd_iq1,fun3,beta3)
Fluxd_iq1_fitted = ((ad_3_6(1).*(tanh(d_current)))+(ad_3_6(2).*d_current));

ad4 = ad_3_6(1);
ad5 = 1;
ad6 = ad_3_6(2);

% 4. Gleichung
Fluxq_id1 = Flux_q(1,:)';
fun4=@(aq_zwei)Fluxq_id1-((aq_zwei(1).*(aq_3_6(2).*tanh(q_current)))+(aq_zwei(3).*q_current));
beta4 = [1;1;1];
aq_3_6 = lsqnonlin(fun4,beta4,[],[],options)
% aq_3_6 = nlinfit(q_current_d_Flux,Fluxq_id1,fun4,beta4);
Fluxq_id1_fitted = ((aq_3_6(1).*(aq_3_6(2).*tanh(q_current)))+(aq_3_6(3).*q_current));

aq4 = aq_3_6(1);
aq5 = aq_3_6(2);
aq6 = aq_3_6(3);

% test Gleichung
Fluxd_iq1 = Flux_d(:,20);
fun5=@(ad_zwei_test)Fluxd_iq1-((ad_zwei_test(1).*(ad_zwei_test(2).*tanh(d_current)))+(ad_zwei_test(3)*d_current));
beta5 = [1;1;1];
ad_test = lsqnonlin(fun5,beta5)
% aq_3_6 = nlinfit(q_current_d_Flux,Fluxq_id1,fun4,beta4);
Fluxd_iq1_fitted_test = ((ad_test(1).*(ad_test(2).*tanh(d_current)))+(ad_test(3).*d_current));

figure;
% Erster Plot
subplot(2,1,1); % Erstelle das obere Subplot
grid on;
plot(q_current, Fluxq_id1_fitted  , 'DisplayName', 'Fluxd_iqnull_fitted');
hold on;
plot(q_current, Fluxq_id1,'*', 'DisplayName', 'Fluxd_iqnull');
legend('show');

% Zweiter Plot
subplot(2,1,2); % Erstelle das untere Subplot
grid on;
plot(d_current, Fluxd_iq1_fitted  , 'DisplayName', 'Fluxd_iqnull_fitted');
hold on;
plot(d_current, Fluxd_iq1,'*', 'DisplayName', 'Fluxd_iqnull');
legend('show');


%Alte Funktionsversuche
% function F=fun(ad1,ad2,ad3)
% fun=Flux_d(7,:)-ad1*tanh(ad2*d_current_d_Flux(:))+ad3*d_current_d_Flux(:)
% end 
% fun=@(ad1,ad2,ad3)Flux_d(7,:)-ad1*tanh(ad2*d_current_d_Flux(:))+ad3*d_current_d_Flux(:);
%Parameterfinding 
% fun=@(ad1,ad2,ad3)Flux_d(:,7)-ad1.*tanh(ad2.*d_current_d_Flux(:))+ad3.*d_current_d_Flux(:);
% x0=[10 1 1];
% x=lsqnonlin(fun,x0)
% 
% for j = 1:size(d_current_q_Flux')
% (Flux_d(7,j)-ad1*tanh(ad2*d_current_d_Flux(j))+ad3*d_current_d_Flux(j))^2;
% end
% test = min()

% syms ad1 ad2 ad3 ad4 ad5 ad6 aq1 aq2 aq3 aq4 aq5 aq6;
% syms id iq;

%Maximum Crosscoupling current constants id1 und iq1

%Selbstinduktion
% psidself = [Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,
%             Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,
%             Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,
%             Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted,Fluxd_iqnull_fitted];
% psidself = repmat(Fluxd_iqnull_fitted, 1, 20);
psidself = Fluxd_iqnull_fitted;

% psiqself = [Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,
%             Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,
%             Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,
%             Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted,Fluxq_idnull_fitted];
% psiqself = repmat(Fluxq_idnull_fitted, 1, 20);
psiqself = Fluxq_idnull_fitted

%gesamte induktion in im maximalen kreuzekkopplungsstrom (also ein
%ausgewählter betriebspuntk) 
% psid_s1 = [Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,
%            Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,
%            Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,
%            Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted,Fluxd_iq1_fitted];
% psid_s1 = repmat(Fluxd_iq1_fitted, 1, 20);

psid_s1 = Fluxd_iq1_fitted; 
% psiq_s1 = [Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,
%            Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,
%            Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,
%            Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted,Fluxq_id1_fitted];
% psiq_s1 = repmat(Fluxq_id1_fitted, 1, 20);

psiq_s1 = Fluxq_id1_fitted;


%dann ist die Kreuzkopplungin diesem Punkt 
psid_cross_s1 = psidself - psid_s1;
psiq_cross_s1 = psiqself - psiq_s1;

%die beiden werden dann integriert (wieso auch immer) 
psiid_cross_s1_integrated = (1/2)*(ad3-ad6).*((d_current).^2)+((ad1/ad2).*log(cosh(ad2.*d_current)))-((ad4/ad5).*log(cosh(ad5.*d_current)));

psiiq_cross_s1_integrated = (1/2)*(aq3-aq6).*((q_current).^2)+((aq1/aq2).*log(cosh(aq2.*q_current)))-((aq4/aq5).*log(cosh(aq5.*q_current)));

%jetzt ist noch die Frage wie in dem einen Paper auf die genaue
%Kruezkopplung gekommen wird weil der einfach die beiden
%kreuezkopplungsterme in dem betriebspunkt mit den integration
%multipliziert werden und dann hat man plötzlich die kreuzkopplung
q_current_set = q_current(20);
Fid1_Giq1 = (1/2)*(aq3-aq6)*((q_current_set).^2)+((aq1/aq2)*log(cosh(aq2*q_current_set)))-((aq4/aq5)*log(cosh(aq5*q_current_set)));
% Fid1_Giq1=1;
psi_d_cross = (1/Fid1_Giq1).*((psid_cross_s1)*(psiiq_cross_s1_integrated)');
psi_q_cross = (1/Fid1_Giq1).*((psiq_cross_s1)*(psiid_cross_s1_integrated)');

psidself_padded = repmat(Fluxd_iqnull_fitted, 1, 20);
psiqself_padded = repmat(Fluxq_idnull_fitted, 1, 20);

psi_d = psidself_padded - psi_d_cross;
psi_q = psiqself_padded - psi_q_cross;

figure;
% Erster Plot
subplot(2,1,1); % Erstelle das obere Subplot
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current, psi_d');
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_d');

legend;

% Zweiter Plot
subplot(2,1,2); % Erstelle das untere Subplot
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, psi_q);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_q');
legend;



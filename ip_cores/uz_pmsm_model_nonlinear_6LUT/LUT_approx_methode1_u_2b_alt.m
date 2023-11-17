%Fitting_fluxlinkage_approximation
close all;
%LUT Fitting

%LeastSquare Problems
options = optimoptions(@lsqnonlin,'Algorithm','levenberg-marquardt');
d_current = d_current_d_Flux';
q_current = q_current_d_Flux;


% Fluxd_iqnull = Flux_d(:,10);
% beta1 = [1;1];
% ad = lsqnonlin(@(a) fun1(a),beta1,[],[],options)
% Fluxd_iqnull_fitted = ad(1).*(tanh(d_current))+(ad(2).*d_current);
% % Fluxd_iqnull_fitted = ad(1)+(ad(2).*d_current);
% % Fluxd_iqnull_fitted = (ad(1).*(tanh(d_current)))+(ad(2).*d_current);
% % Fluxd_iqnull_fitted = fun1(ad_search, d_current_d_Flux);
% 1. Gleichung
% (ad(1)*(tanh(ad2*(id-ad3))))-(k1*((2*(ad4^2)*id)*exp(-(ad4*id)^2))*(1-exp(-(aq4*iq)^2)))+...
%     (k2*((2*(ad5^2)*id)*exp(-(ad5*id)^2)) *(1-exp(-(aq5*iq)^2)) )+...
%     (k3*((2*(ad6^2)*id)*exp(-(ad6*id)^2)) *(1-exp(-(aq6*iq)^2))) + ...
%     (k4*((2*(ad7^2)*id)*exp(-(ad7*id)^2)) *(1-exp(-(aq7*iq)^2))) +...
%     (k1*(1-exp(-(ad4*id)^2))*((2*(aq4^2)*iq)*exp(-(aq4*iq)^2))) + ...
%     (k2*(1-exp(-(ad5*id)^2))*((2*(aq5^2)*iq)*exp(-(aq5*iq)^2))) + ...
%     (k3*(1-exp(-(ad6*id)^2))*((2*(aq6^2)*iq)*exp(-(aq6*iq)^2))) + ...
%     (k4*(1-exp(-(ad7*id)^2))*((2*(aq7^2)*iq)*exp(-(aq7*iq)^2))) 
Fluxd_iqnull = Flux_d(:,10);
%fun0=@(ad)Fluxd_iqnull-((ad(1).*(tanh(ad(2).*d_current)))+(ad(3).*d_current))
%fun0=@(ad)Fluxd_iqnull-(ad(1).*(tanh(ad(2)*(d_current-ad(3)))))
%fun0=@(ad,d_current)((ad(1).*tanh(ad(2).*d_current))+(ad(3).*d_current))
fun0=@(ad,d_current)(ad(1).*(tanh(ad(2)*(d_current-ad(3)))))
%fun0=@(adeins,adzwei,addrei,d_current) (adeins.*(tanh(adzwei*(d_current-addrei))))
%f_dnull = @(ad_para) norm(fun0(ad_para(1),ad_para(2),ad_para(3),d_current)-Fluxd_iqnull);
%funtest=@(ad_irgendwas)(Fluxd_iqnull-((ad_irgendwas(1).*((d_current).^2))+(ad_irgendwas(2).*d_current)+ad_irgendwas(3)));
beta1 = [0.0305;0.0402; -16.4812];
%beta1 = [1;1;1];
%ad_1 = lsqnonlin(fun0,beta1,[],[],options)
%ad_1 = fminsearch(f_dnull,beta1)
ad_1 = nlinfit(d_current,Fluxd_iqnull,fun0,beta1);
%Fluxd_iqnull_fitted = ((ad_1(1).*tanh(ad_1(2).*d_current))+(ad_1(3).*d_current))
Fluxd_iqnull_fitted = ad_1(1).*(tanh(ad_1(2)*(d_current-ad_1(3))))

Fluxd_iqnull_test = ((beta1(1).*(tanh(d_current)))+(beta1(2).*d_current));



ad1 = ad_1(1);
ad2 = ad_1(2);
ad3 = ad_1(3);

%Fluxd_iqnull_fitted = fun0(ad1,ad2,ad3,d_current)

% 2. Gleichung
Fluxq_idnull = Flux_q(15,:)';
%fun2=@(aq)(Fluxq_idnull-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current)));
fun2=@(aq)(Fluxq_idnull-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current)));
beta2 = [1;1;1];
aq_1 = lsqnonlin(fun2,beta2,[],[],options)
%aq_1 = fminsearch(fun2,beta2)
% aq = nlinfit(q_current,Fluxq_idnull,fun2,beta2);
Fluxq_idnull_fitted = ((aq_1(1).*(tanh(aq_1(2)*q_current)))+(aq_1(3).*q_current));

aq1 = aq_1(1);
aq2 = aq_1(2);
aq3 = aq_1(3);

% 3. Gleichung
Fluxd_iq1 = Flux_d(:,20);
%fun3=@(ad_zwei)Fluxd_iq1-((ad_zwei(1).*(tanh(d_current)))+(ad_zwei(2).*d_current));
% fun3=@(ad_zwei,d_current)Fluxd_iq1-((ad_zwei(1).*(tanh(d_current)))+(ad_zwei(2).*d_current));
% fun3=@(ad_zwei,d_current)ad_zwei(1).*(tanh(d_current))+(ad_zwei(2).*d_current)
fun3=@(ad_zwei,d_current)(ad_zwei(1).*((d_current).^2))+(ad_zwei(2).*d_current)+ad_zwei(3)
beta3 = [1;1;1];
% ad_3_6 = lsqnonlin(fun3,beta3,[],[],options)
ad_3_6 = nlinfit(d_current,Fluxd_iq1,fun3,beta3)
Fluxd_iq1_fitted = (ad_3_6(1).*((d_current).^2))+(ad_3_6(2).*d_current)+ad_3_6(3);

ad4 = ad_3_6(1);
ad5 = ad_3_6(2);
ad6 = ad_3_6(3);

% 4. Gleichung
Fluxq_id1 = Flux_q(1,:)';
fun4=@(aq_zwei)Fluxq_id1-((aq_zwei(1).*(aq_zwei(2).*tanh(q_current)))+(aq_zwei(3).*q_current));
beta4 = [1;1;1];
aq_3_6 = lsqnonlin(fun4,beta4,[],[],options)
% aq_3_6 = nlinfit(q_current_d_Flux,Fluxq_id1,fun4,beta4);
Fluxq_id1_fitted = ((aq_3_6(1).*(aq_3_6(2).*tanh(q_current)))+(aq_3_6(3).*q_current));

aq4 = aq_3_6(1);
aq5 = aq_3_6(2);
aq6 = aq_3_6(3);

% 5. Gleichung
Fluxd_id_24 = Flux_d(1,:)';
fun5=@(ad_drei)Fluxd_id_24-(ad_drei(1)+(ad_drei(2)/(1+(ad_drei(3)*(q_current.^2)))));
beta5 = [1;1;1];
ad_7_9 = lsqnonlin(fun5,beta5,[],[],options)
% aq = nlinfit(q_current,Fluxq_idnull,fun2,beta2);
% Fluxd_iqnull_fitted = ((ad_1(1).*(tanh(ad_1(2)*d_current)))+(ad_1(3).*d_current))
Fluxd_id_24_fitted = (ad_7_9(1)+(ad_7_9(2)/(1+(ad_7_9(3)*(q_current.^2)))));

ad7 = ad_7_9(1);
ad8 = ad_7_9(2);
ad9 = ad_7_9(3);
% test Gleichung
% Fluxd_iq1 = Flux_d(:,20);
% fun5=@(ad_zwei_test)Fluxd_iq1-((ad_zwei_test(1).*(ad_zwei_test(2).*tanh(d_current)))+(ad_zwei_test(3)*d_current));
% beta5 = [1;1;1];
% ad_test = lsqnonlin(fun5,beta5)
% % aq_3_6 = nlinfit(q_current_d_Flux,Fluxq_id1,fun4,beta4);
% Fluxd_iq1_fitted_test = ((ad_test(1).*(ad_test(2).*tanh(d_current)))+(ad_test(3).*d_current));

figure;
% Erster Plot
subplot(2,1,1); % Erstelle das obere Subplot
grid on;
plot(d_current, Fluxd_iqnull_fitted , 'DisplayName', 'Fluxd_iqnull_fitted');
hold on;
plot(d_current, Fluxd_iqnull,'*', 'DisplayName', 'Fluxd_iqnull');

legend('show');

% Zweiter Plot
subplot(2,1,2); % Erstelle das untere Subplot
grid on;

plot(q_current, Fluxq_idnull_fitted  , 'DisplayName', 'Fluxq_idnull_fitted');
hold on;
plot(q_current, Fluxq_idnull,'*', 'DisplayName', 'Fluxq_idnull');
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
psidself = Fluxd_iqnull_fitted;

psiqself = Fluxq_idnull_fitted;

test = d_current_d_Flux'*q_current_d_Flux';

q_current_T = q_current';





% 
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
% F1_strich = (2*(a_d4.^2)*d_current)*exp(-(a_d4*d_current).^2)
% F2_strich = (2*(a_d5.^2)*d_current)*exp(-(a_d5*d_current).^2)
% F3_strich = (2*(a_d6.^2)*d_current)*exp(-(a_d6*d_current).^2)
% F4_strich = (2*(a_d7.^2)*d_current)*exp(-(a_d7*d_current).^2)
% 
% G1_strich = (2*(a_q4.^2)*q_current)*exp(-(a_q4*q_current).^2)
% G2_strich = (2*(a_q5.^2)*q_current)*exp(-(a_q5*q_current).^2)
% G3_strich = (2*(a_q6.^2)*q_current)*exp(-(a_q6*q_current).^2)
% G3_strich = (2*(a_q7.^2)*q_current)*exp(-(a_q7*q_current).^2)

% F1 = 1-exp(-(a_d4*x).^2);
% F2 = 1-exp(-(a_d5*x).^2);
% F3 = 1-exp(-(a_d6*x).^2);
% F4 = 1-exp(-(a_d7*x).^2);
% F5 = 1-exp(-(a_d8*x).^2);
% F6 = 1-exp(-(a_d9*x).^2);
% F7 = 1-exp(-(a_d10*x).^2);
% 
% G1 = 1-exp(-(a_q4*y).^2);
% G2 = 1-exp(-(a_q5*y).^2);
% G3 = 1-exp(-(a_q6*y).^2);
% G4 = 1-exp(-(a_q7*y).^2);
% G5 = 1-exp(-(a_q8*y).^2);
% G6 = 1-exp(-(a_q9*y).^2);
% G7 = 1-exp(-(a_q10*y).^2);
% 
% F1_strich = (2*(a_d4.^2)*x)*exp(-(a_d4*x).^2)
% F2_strich = (2*(a_d5.^2)*x)*exp(-(a_d5*x).^2)
% F3_strich = (2*(a_d6.^2)*x)*exp(-(a_d6*x).^2)
% F4_strich = (2*(a_d7.^2)*x)*exp(-(a_d7*x).^2)
% F5_strich = (2*(a_d7.^2)*x)*exp(-(a_d7*x).^2)
% F6_strich = (2*(a_d7.^2)*x)*exp(-(a_d7*x).^2)
% F7_strich = (2*(a_d7.^2)*x)*exp(-(a_d7*x).^2)
% 
% G1_strich = (2*(a_q4.^2)*y)*exp(-(a_q4*y).^2)
% G2_strich = (2*(a_q5.^2)*y)*exp(-(a_q5*y).^2)
% G3_strich = (2*(a_q6.^2)*y)*exp(-(a_q6*y).^2)
% G4_strich = (2*(a_q7.^2)*y)*exp(-(a_q7*y).^2)
% G3_strich = (2*(a_q7.^2)*y)*exp(-(a_q7*y).^2)

% %psid_fitted
 %k1*((2*(a_d4^2)*x)*exp(-(a_d4*x)^2)*(1-exp(-(a_q4*y)^2)))   +   k2*((2*(a_d5.^2)*x)*exp(-(a_d5*x)^2)*(1-exp(-(a_q5*y)^2))) + k3*((2*(a_d6^2)*x)*exp(-(a_d6*x)^2)*(1-exp(-(a_q6*y)^2)))  + k4*((2*(a_d7^2)*x)*exp(-(a_d7*x)^2)*(1-exp(-(a_q7*y)^2))) +k5*((2*(a_d8^2)*x)*exp(-(a_d8*x)^2)*(1-exp(-(a_q8*y)^2)))  +  k6*((2*(a_d9^2)*x)*exp(-(a_d9*x)^2)*(1-exp(-(a_q9*y)^2)))  + k7*((2*(a_d10^2)*x)*exp(-(a_d10*x)^2)*(1-exp(-(a_q10*y)^2)));
% 
% %psiq_fitted
%k1*(1-exp(-(a_d4*y)^2))*((2*(a_q4^2)*x)*exp(-(a_q4*x)^2))   +   k2*(1-exp(-(a_d5*y)^2))*((2*(a_q5.^2)*x)*exp(-(a_q5*x)^2)) + k3*(1-exp(-(a_d6*y)^2))*((2*(a_q6^2)*x)*exp(-(a_q6*x)^2))  + k4*(1-exp(-(a_d7*y)^2))*((2*(a_q7^2)*x)*exp(-(a_q7*x)^2));
% %Neue f1 und g1

%k1*((2*(a_d4^2)*x)*exp(-(a_d4*x)^2)*(1-exp(-(a_q4*y)^2)))   +   k2*((2*(a_d5.^2)*x)*exp(-(a_d5*x)^2)*(1-exp(-(a_q5*y)^2))) + k3*((2*(a_d6^2)*x)*exp(-(a_d6*x)^2)*(1-exp(-(a_q6*y)^2)))  


% F1 = (1-exp(-(a_d4*(d_current-a_d5)).^2));
% F2 = (1-exp(-(a_d6*(d_current-a_d7)).^2));
% 
% G1 = (1-exp(-(a_q4*(q_current_T-a_q5)).^2));
% G2 = (1-exp(-(a_q6*(q_current_T-a_q7)).^2));
% 
% F1_strich = (2*((a_d4^2)*(d_current-a_d5))).*(1-exp(-(a_d4*(d_current-a_d5)).^2));
% F2_strich = (2*((a_d6^2)*(d_current-a_d7))).*(1-exp(-(a_d6*(d_current-a_d7)).^2));
% 
% G1_strich = (2*((a_q4^2)*(q_current_T-a_q5))).*(1-exp(-(a_q4*(q_current_T-a_q5)).^2));
% G2_strich = (2*((a_q6^2)*(q_current_T-a_q7))).*(1-exp(-(a_q6*(q_current_T-a_q7)).^2));


%DIESE FUNKTION WAR IM CURVE FITTER DRIN

%k1*(((2*(a_d4^2)*d_current).*exp(-(a_d4*d_current).^2))*(1-exp(-(a_q4*q_current_T).^2)))+k2*(((2*(a_d5^2)*d_current).*exp(-(a_d5*d_current).^2))*(1-exp(-(a_q5*q_current_T).^2)))+k3*(((2*(a_d6^2)*d_current).*exp(-(a_d6*d_current).^2))*(1-exp(-(a_q6*q_current_T).^2)))+k4*(((2*(a_d7^2)*d_current).*exp(-(a_d7*d_current).^2))*(1-exp(-(a_q7*q_current_T).^2)))

%weis gar net ob man die noch braucht
psid_s1 = Fluxd_iq1_fitted; 
psiq_s1 = Fluxq_id1_fitted;

%psicross_reall berechnung
psidself_padded = repmat(Fluxd_iqnull_fitted, 1, 20)';
psiqself_padded = repmat(Fluxq_idnull_fitted, 1, 20);

psid_cross_real = psidself_padded-Flux_d';
psiq_cross_real = psiqself_padded-Flux_q';

crosscoupling_real = psid_cross_real + psiq_cross_real;

testereien = psidself_padded-psid_cross_real;
flux_q_mit_cross = psiqself_padded-psiq_cross_real;

f1 = @(a,d_current,q_current_T)psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))
f2 = @(a,d_current,q_current_T)psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))
ftest = @(a)(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))


%psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  
%fanother = @(a)sqrt(((psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))).^2)+((psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))).^2))

finalef1 =@(f_ad4,f_ad5,f_ad6,f_ad7,f_aq4,f_aq5,f_aq6,f_aq7,f_k1,f_k2,f_k3,f_k4,d_current,q_current_T) psid_cross_real-(f_k1*((2*(f_ad4^2)*d_current).*exp(-(f_ad4*d_current).^2)*(1-exp(-(f_aq4*q_current_T).^2)))+f_k2*((2*(f_ad5.^2)*d_current).*exp(-(f_ad5*d_current).^2)*(1-exp(-(f_aq5*q_current_T).^2)))+f_k3*((2*(f_ad6^2)*d_current).*exp(-(f_ad6*d_current).^2)*(1-exp(-(f_aq6*q_current_T).^2)))+f_k4*((2*(f_ad7^2)*d_current).*exp(-(f_ad7*d_current).^2)*(1-exp(-(f_aq7*q_current_T).^2))))
finalef2 = @(f_ad4,f_ad5,f_ad6,f_ad7,f_aq4,f_aq5,f_aq6,f_aq7,f_k1,f_k2,f_k3,f_k4,d_current,q_current_T) psiq_cross_real-f_k1*(1-exp(-(f_ad4*d_current).^2))*((2*(f_aq4^2)*q_current_T).*exp(-(f_aq4*q_current_T).^2))   +   f_k2*(1-exp(-(f_ad5*d_current).^2))*((2*(f_aq5.^2)*q_current_T).*exp(-(f_aq5*q_current_T).^2)) + f_k3*(1-exp(-(f_ad6*d_current).^2))*((2*(f_aq6^2)*q_current_T).*exp(-(f_aq6*q_current_T).^2))  + f_k4*(1-exp(-(f_ad7*d_current).^2))*((2*(f_aq7^2)*q_current_T).*exp(-(f_aq7*q_current_T).^2))

%finalecombined = @(a) norm(sqrt((finalef1(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)+(finalef2(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)),"fro").^2
%f2 = @(a,d_current,q_current_T)(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))
funreal = @(a)[psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))));psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))];
% funreal = {f1,f2}
initial = [1;1;1;1;1;1;1;1;1;1;1;1];

%adq_red = lsqnonlin(fanother,initial,[],[],options)

%adq_linfit = nlinfit(d_current,q_current_T,psid_cross_real,f2,initial);

% d_current=d_current';
% q_current_T = q_current_T';
% for j = 1:length(q_current_T)
%     j
%     for i = 1:length(d_current)
%         i;
%         psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))
% 
%     end
% end

combined_function = @(a)sum((f1(d_current,q_current_T,a).^2)+(f2(d_current,q_current_T,a).^2),"all");
%combined_function = @(a) sum((psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))).^2+((psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))).^2),"all"); 
combined_functiontest = @(a) sqrt((psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))).^2+((psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))).^2)); 


%combined_function = @(a) sum((psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2).*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))).^2+((psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))).^2),"all"); 

% adq_red = lsqnonlin(combined_functiontest,initial,[],[],options)
% dq_current = 0;

%combined_new = @(a) sum((a(1)*exp(-a(2)*q_current_T)+a(3)*exp(-a(4)*q_current_T))*(exp(-(a(5)*exp(-a(6)*q_current_T,"all")

%adq_red = lsqcurvefit(ftest,initial,[d_current'; q_current_T],psid_cross_real)

finalecombined = @(a,d_current,q_current_T) sqrt((finalef1(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)+(finalef2(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2))


options = optimset('MaxFunEvals',9999);
 % adq_red = fminsearch(finalecombined, initial,options);
 % adq_red = fminsearch(finalecombined, adq_red,options);

dq_current = [d_current';q_current']

matrix = zeros(20, 20);

OPTIONS = optimoptions('lsqcurvefit','Algorithm','levenberg-marquardt');
%adq_red = lsqcurvefit(finalecombined, initial, dq_current, matrix,OPTIONS)

%f3 = @(a)psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))
% adq_zwei = lsqnonlin(f3,adq_red,[],[],options)

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

% a_d4 = adq_zwei(2);
% a_d5 = adq_zwei(5);
% a_d6 = adq_zwei(8);
% a_d7 = adq_zwei(11);
% 
% a_q4 = adq_zwei(3);
% a_q5 = adq_zwei(6);
% a_q6 = adq_zwei(9);
% a_q7 = adq_zwei(12);
% 
% k1 = adq_zwei(1);
% k2 = adq_zwei(4);
% k3 = adq_zwei(7);
% k4 = adq_zwei(10);

% a_d4 = 0.1413;
% a_d5 = 0.4427;
% a_d6 = 1.0908;
% a_d7 = 0.1704;
% 
% a_q4 = 1.3190;
% a_q5 = 0.7707;
% a_q6 = 0.4186;
% a_q7 = 1.0530;
% k1 = 0.0762;
% k2 = 0.0016;
% k3 = -0.0004;
% k4 = -0.0468;

keineahnung= -((a_d4*d_current).^2);

keineahnung2= -((a_d4*d_current).^2);



psid_cross_approx = k1*(((2*(a_d4^2)*d_current).*exp(-(a_d4*d_current).^2))*(1-exp(-(a_q4*q_current_T).^2)))+k2*(((2*(a_d5^2)*d_current).*exp(-(a_d5*d_current).^2))*(1-exp(-(a_q5*q_current_T).^2)))+k3*(((2*(a_d6^2)*d_current).*exp(-(a_d6*d_current).^2))*(1-exp(-(a_q6*q_current_T).^2)))+k4*(((2*(a_d7^2)*d_current).*exp(-(a_d7*d_current).^2))*(1-exp(-(a_q7*q_current_T).^2)));

psiq_cross_approx = k1*(1-exp(-(a_d4*d_current).^2))*((2*(a_q4^2)*q_current_T).*exp(-(a_q4*q_current_T).^2))   +   k2*(1-exp(-(a_d5*d_current).^2))*((2*(a_q5.^2)*q_current_T).*exp(-(a_q5*q_current_T).^2)) + k3*(1-exp(-(a_d6*d_current).^2))*((2*(a_q6^2)*q_current_T).*exp(-(a_q6*q_current_T).^2))  + k4*(1-exp(-(a_d7*d_current).^2))*((2*(a_q7^2)*q_current_T).*exp(-(a_q7*q_current_T).^2));

antohertest = sum(psid_cross_approx.^2);

flux_d_approx = psidself_padded-psid_cross_approx;
flux_q_approx = psiqself_padded-psid_cross_approx;

%[fitresult, gof] = PolynomFit_Function(d_current, q_current, psid_cross_real);

fluxd_real = Flux_d';
fluxq_real = Flux_q';
%Perfekte Parameter (Saumäsig zufällig) 
aq1 = 0.0077;
aq10 = 0.0636;
aq11 = -0.0603;
aq12 = 0.0421;
aq2 = 0.1589;
aq3 = 0.0010;
aq4 = 0.2646;
aq5 = 0.2202;
aq6 = 1.7343;
aq7 =0.0877;
aq8 = -0.0637;
aq9 = 0.0089;
q6 = 0.0010;

%q6 war ursprünglich ein kleiner fehler aber er macht das fitting weit aus
%besser 

%Lower and upper dazu
% 0.0045	0.0109
% -0.0454	0.1726
% -0.1645	0.0439
% -0.3586	0.4428
% 0.1251	0.1927
% 0.0008	0.0012
% -4.1900	4.7192
% 0.1153	0.3252
% -4.0047	7.4733
% -0.2005	0.3758
% -0.2549	0.1275
% -0.1084	0.1262
% -0.0007	0.0027


%Neue bessere Parameter nur mit  den eigentlichen parameter a1-12für psid
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

%neue parameterpsiq
% -0.0003
% 0.0212
% 0.0507
% 0.0098
% 0.4165
% 0.0023
% 4.6300
% -3.3143
% 0.0003
% 0.0175
% -3.3617
% 72.3955

%Nochmal neue Parameter für psiq (sind die besten) 
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

q_current_T = q_current_T';
d_current = d_current';



 %flux_q_approx =(  ((aq1*tanh(aq2.*q_current_T))+(aq3.*q_current_T))   .*(  ( (aq4+(aq5./(1+(aq6.*(q_current_T.^2)))))   .*exp(-((aq7+(aq8./(1+(aq9.*(q_current_T.^2))))).*d_current).^2) )  +(     (1-((aq4+(aq5./(1+(aq6.*(q_current_T.^2)))))).*exp(-((aq10+(aq11./(1+(aq12.*(q_current_T.^2)))))*d_current).^2))   )      )       )  


 finalef1 =@(f_aq1,f_aq2,f_aq3,f_aq4,f_aq5,f_aq6,f_aq7,f_aq8,f_aq9,f_aq10,f_aq11,f_aq12,d_current,q_current_T) fluxq_real -(  ((f_aq1*tanh(f_aq2.*q_current_T))+(f_aq3.*q_current_T))   .*(  ( (f_aq4+(f_aq5./(1+(f_aq6.*(q_current_T.^2)))))   .*exp(-((f_aq7+(f_aq8./(1+(f_aq9.*(q_current_T.^2))))).*d_current).^2) )  +(     (1-((f_aq4+(f_aq5./(1+(f_aq6.*(q_current_T.^2)))))).*exp(-((f_aq10+(f_aq11./(1+(f_aq12.*(q_current_T.^2)))))*d_current).^2))   )      )       )  
 
 finalef2psid = @(f_ad1,f_ad2,f_ad3,f_ad4,f_ad5,f_ad6,f_ad7,f_ad8,f_ad9,f_ad10,f_ad11,f_ad12,d_current,q_current_T) fluxd_real -(  (f_ad1*(tanh(f_ad2*(d_current-f_ad3))))   .*(  ( (f_ad4+(f_ad5./(1+(f_ad6.*(d_current.^2)))))   .*exp(-((f_ad7+(f_ad8./(1+(f_ad9.*(d_current.^2))))).*q_current_T).^2) )  +(     (1-((f_ad4+(f_ad5./(1+(f_ad6.*(d_current.^2)))))).*exp(-((f_ad10+(f_ad11./(1+(f_ad12.*(d_current.^2)))))*q_current_T).^2))   )      )       )  
 

 finalecombined = @(a) norm(finalef1(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2).^2

 finalecombinedf2d = @(ad) norm(finalef1(ad(1),ad(2),ad(3),ad(4),ad(5),ad(6),ad(7),ad(8),ad(9),ad(10),ad(11),ad(12),d_current,q_current_T).^2).^2
% initial=[0.0041;0.0032;0.6133;0.1467;0.2092;0.0010;28.4940;-24.2348;0.0405;-0.0030;-0.6286;0.1516];

initialgenauer = [0.0041;
0.0032;
0.6133;
0.1467;
0.2092;
0.0010;
28.4940;
-24.2348;
0.0405;
-0.0030;
-0.6286;
0.1516];

 adq_red = fminsearch(finalecombined, initialgenauer);
 adq_red_d = fminsearch(finalecombinedf2d, initial);

 % aq1 = adq_red(1);
 % aq2 = adq_red(2);
 % aq3 = adq_red(3);
 % aq4 = adq_red(4);
 % aq5 = adq_red(5);
 % aq6 = adq_red(6);
 % aq7 = adq_red(7);
 % aq8 = adq_red(8);
 % aq9 = adq_red(9);
 % aq10 = adq_red(10);
 % aq11 = adq_red(11);
 % aq12 = adq_red(12);
 % 
 % ad1 = adq_red_d(1);
 % ad2 = adq_red_d(2);
 % ad3 = adq_red_d(3);
 % ad4 = adq_red_d(4);
 % ad5 = adq_red_d(5);
 % ad6 = adq_red_d(6);
 % ad7 = adq_red_d(7);
 % ad8 = adq_red_d(8);
 % ad9 = adq_red_d(9);
 % ad10 = adq_red_d(10);
 % ad11 = adq_red_d(11);
 % ad12 = adq_red_d(12);


 %andere Werte für psid die auch ein relativ gutes ergebniss erzielen
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

%noch bessere Werte für psi d

% ad1 = 7.2940;
% ad2 = 0.0001;
% ad3 = -15.5992;
% ad4 = -186.4725;
% ad5 = 187.4853;
% ad6 = 0.0000;
% ad7 = 0.0205;
% ad8 = 0.0187;
% ad9 = 0.0247;
% ad10 = -0.0291;
% ad11 = 73.4312;
% ad12 = 5.9081;

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

7.4648

0.0001
-15.5451
-185.5154
186.5382
0.0000
0.0396
-0.0789
0.0046
-0.0255
74.6056
6.8989


p00= 0.0167;
p10 = 7.8264e-04;
p01 = 1.6049e-05;
p20 = 2.1681e-08;
p11 = -0.0000
p02 = -3.3394e-05
p30 = 4.1224e-07
p21 = -5.0330e-08
p12 = -7.7794e-07
p03 = -1.1882e-07
p40 = 5.1334e-08
p31 = 3.2042e-08
p22 = 5.1152e-08
p13 = -3.3426e-09
p04 = 3.3261e-08
p50 =9.4763e-10
p41 = 1.2311e-09
p32 = 1.3180e-09
p23 = -3.0471e-10
p14 = 1.4475e-09
p05 = 1.0813e-10



 flux_q_approx =(  ((aq1*tanh(aq2.*q_current_T))+(aq3.*q_current_T)) ...
     .*(  ( (aq4+(aq5./(1+(aq6.*(q_current_T.^2)))))   .*exp(-((aq7+(aq8./(1+(aq9.*(q_current_T.^2))))).*d_current).^2) ) ...
     +(     (1-((aq4+(aq5./(1+(aq6.*(q_current_T.^2)))))).*exp(-((aq10+(aq11./(1+(aq12.*(q_current_T.^2)))))*d_current).^2))   )      )       );

 flux_d_approx = (ad1.*(tanh(ad2.*(d_current-ad3))))    .*(   (ad4+(ad5./(1+(ad6.*(d_current.^2)))))   .*exp(-((ad7+(ad8./(1+(ad9.*(d_current.^2))))).*q_current_T).^2)   + (    (    1-((ad4+(ad5./(1+(ad6.*(d_current.^2))))))  ).*exp(-((ad10+(ad11./(1+(ad12.*(d_current.^2))))).*q_current).^2)   )      );


 fluxd_poly_approx = p00 + (p10.*d_current) +(p01.*q_current_T) +(p20.*(d_current.^2)) +(p02.*(q_current_T.^2)) + (p30.*(d_current.^3))+ (p21.*(d_current.^2).*q_current_T) +(p12.*d_current.*(q_current.^2))+ (p03.*(q_current.^3)) + (p40.*(d_current.^4)) + (p31.*(d_current.^3).*q_current_T)... 
     + (p22.*(d_current.^2).*(q_current_T.^2)) + (p13.*d_current.*q_current_T) +(p04.*(q_current_T.^4)) +(p50.*(d_current.^5)) +(p41.*(d_current.^4).*q_current_T) +(p32.*(d_current.^3).*(q_current.^2)) + (p23.*(d_current.^2).*(q_current.^3)) + (p14.*d_current.*(q_current_T.^4)) + (p05.*(q_current.^5));
 fluxq_poly_approx = 0;
 
 % d_current21=[d_current(1:15);0;d_current(16:20)];
% q_current21=[q_current(1:10);0;q_current(11:20)];
% 
% fluxd_real_21 = [fluxd_real(1:10,:);fluxd_real(10,:);fluxd_real(11:20,:)]
% fluxd_real_21 = [fluxd_real_21(:,1:15),fluxd_real_21(:,15),fluxd_real_21(:,16:20)]

%das sind die anderen formeln aus dem "alten" Paper.
%  ((ad1*tanh(ad2*id))+(ad3*id))   *(   (ad4+(ad5/(1+(ad6*(id^2)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^6)))))*iq)^2)   +(     (1-((ad4+(ad5/(1+(d6*(id^2))))))*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2))  )      )
%  (ad1*(tanh(ad2*(id-ad3))))   *(  ( (ad4+(ad5/(1+(ad6*(id^2)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^2)))))*iq)^2) )  +(     (  (1-(ad4+(ad5/(1+(ad6*(id^2)))))  )*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2)  )  )      )
% 
%    (ad1*(tanh(ad2*(id-ad3))))   *(  ( (ad4+(ad5/(1+(ad6*(id^2)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^2)))))*iq)^2) )  +(     (  (1-(ad4+(ad5/(1+(ad6*(id^2)))))  )*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2)  )      ))
%    (ad1*(tanh(ad2*(id-ad3))))   *(  ( (ad4+(ad5/(1+(ad6*(id^2)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^6)))))*iq)^2) )  +(     (  1-((ad4+(ad5/(1+(ad6*(id^2))))))  )*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2)  )      )
% % 
% %     (ad1*(tanh(ad2*(id-ad3))))   *(  ( (ad4+(ad5/(1+(ad6*(id^4)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^2)))))*iq)^2) )  +(     (   (  1-(ad4+(ad5/(1+(ad6*(id^4)))))  )*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2)  )      ))
% %  % 
  ((aq1*tanh(aq2*iq))+(aq3*iq))   *(   (aq4+(aq5/(1+(aq6*(iq^2)))))   *exp(-((aq7+(aq8/(1+(aq9*(iq^2)))))*id)^2)   + (    (    1-((aq4+(aq5/(1+(aq6*(iq^2))))))  )*exp(-((aq10+(aq11/(1+(aq12*(iq^2)))))*id)^2)   )      )
% 
% 
%   (ad1*(tanh(ad2*(id-ad3))))    *(   (ad4+(ad5/(1+(ad6*(id^2)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^2)))))*iq)^2)   + (    (    1-((ad4+(ad5/(1+(ad6*(id^2))))))  )*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2)   )      )

  (aq4+(aq5/(1+(aq6*(iq^2)))))   *exp(-(aq9*(iq^2)))
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

% % 
% %Mit dieser Formel ging es 
%  ((aq1*tanh(aq2*iq))+(aq3*iq))   *(  ( (aq4+(aq5/(1+(aq6*(iq^2)))))   *exp(-((aq7+(aq8/(1+(aq9*(iq^2)))))*id)^2) )  +(     (1-((aq4+(aq5/(1+(q6*(iq^2))))))*exp(-((aq10+(aq11/(1+(aq12*(iq^2)))))*id)^2))   )      )
% 
%  ((aq1*tanh(aq2*iq))+(aq3*iq))   *(  ( (aq4+(aq5/(1+(aq6*(iq^2)))))   *exp(-((aq7+(aq8/(1+(aq9*(iq^2)))))*id)^2) )  +(     ( 1-((aq4+(aq5/(1+(q6*(iq^2))))))  )*exp(-((aq10+(aq11/(1+(aq12*(iq^2)))))*id)^2)   )      )

fluxd_max = max(fluxd_real, [], 'all')
fluxq_max = max(fluxq_real, [], 'all');

%ed = ((abs(fluxd_real-flux_d_approx))/max(fluxd_real)).*100

ed = ((abs(fluxd_real-flux_d_approx))/fluxd_max).*100

ed = ((abs(fluxd_real-fluxd_poly_approx))/fluxd_max).*100

eq = ((abs(fluxq_real-flux_q_approx))/fluxq_max).*100


[X, Y] = meshgrid(d_current, q_current);
figure;
% Erster Plot
subplot(2,1,1); % Erstelle das obere Subplot
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(X, Y,  fluxd_poly_approx);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_qapprox');
legend;

% Zweiter Plot
subplot(2,1,2); % Erstelle das untere Subplot
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, fluxd_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_qreal');
legend;

% Zweiter Plot
% subplot(3,1,3); % Erstelle das untere Subplot
figure;
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, ed);
xlabel('D Current');
ylabel('Q Current');
zlabel('error/%');
legend;





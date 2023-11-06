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
Fluxd_iqnull = Flux_d(:,10);
%fun0=@(ad)(Fluxd_iqnull-((ad(1).*(tanh(ad(2)*d_current)))+(ad(3).*d_current)))
funtest=@(ad_irgendwas)(Fluxd_iqnull-((ad_irgendwas(1).*((d_current).^2))+(ad_irgendwas(2).*d_current)+ad_irgendwas(3)));
beta1 = [1;1;1];
ad_1 = lsqnonlin(funtest,beta1,[],[],options)
% aq = nlinfit(q_current,Fluxq_idnull,fun2,beta2);
% Fluxd_iqnull_fitted = ((ad_1(1).*(tanh(ad_1(2)*d_current)))+(ad_1(3).*d_current))
Fluxd_iqnull_fitted = (ad_1(1).*((d_current).^2))+(ad_1(2).*d_current)+ad_1(3)
Fluxd_iqnull_test = ((beta1(1).*(tanh(d_current)))+(beta1(2).*d_current));



ad1 = ad_1(1);
ad2 = ad_1(2);
ad3 = ad_1(3);

% 2. Gleichung
Fluxq_idnull = Flux_q(15,:)';
%fun2=@(aq)(Fluxq_idnull-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current)));
fun2=@(aq)(Fluxq_idnull-((aq(1).*(tanh(aq(2)*q_current)))+(aq(3).*q_current))).^2;
beta2 = [1;1;1];
 %aq_1 = lsqnonlin(fun2,beta2,[],[],options)
aq_1 = fminsearch(fun2,beta2)
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
plot(d_current, Fluxd_iq1_fitted , 'DisplayName', 'Fluxd_iqnull_fitted');
hold on;
plot(d_current, Fluxd_iq1,'*', 'DisplayName', 'Fluxd_iqnull');

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

testereien = psidself_padded-psid_cross_real;
flux_q_mit_cross = psiqself_padded-psiq_cross_real;

f1 = @(d_current,q_current_T,a)psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))
f2 = @(d_current,q_current_T,a)psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))
ftest = @(a)(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))


%f2 = @(a,d_current,q_current_T)(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))
funreal = @(a)[psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))));psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))]
% funreal = {f1,f2}
initial = [1;1;1;1;1;1;1;1;1;1;1;1];

%adq_linfit = nlinfit(d_current,q_current_T,psid_cross_real,f2,initial);

% d_current=d_current';
% q_current_T = q_current_T';
combined_function = @(a)sum((f1(d_current,q_current_T,a).^2)+(f2(d_current,q_current_T,a).^2),"all")
%combined_function = @(a) sum((psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))).^2+((psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))).^2),"all"); 
combined_functiontest = @(a) sqrt((psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))).^2+((psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))).^2)); 


%combined_function = @(a) sum((psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2).*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))).^2+((psiq_cross_real-a(1)*(1-exp(-(a(2)*d_current).^2))*((2*(a(3)^2)*q_current_T).*exp(-(a(3)*q_current_T).^2))   +   a(4)*(1-exp(-(a(5)*d_current).^2))*((2*(a(6).^2)*q_current_T).*exp(-(a(6)*q_current_T).^2)) + a(7)*(1-exp(-(a(8)*d_current).^2))*((2*(a(9)^2)*q_current_T).*exp(-(a(9)*q_current_T).^2))  + a(10)*(1-exp(-(a(11)*d_current).^2))*((2*(a(12)^2)*q_current_T).*exp(-(a(12)*q_current_T).^2))).^2),"all"); 

% adq_red = lsqnonlin(combined_functiontest,initial,[],[],options)
% dq_current = 0;

%combined_new = @(a) sum((a(1)*exp(-a(2)*q_current_T)+a(3)*exp(-a(4)*q_current_T))*(exp(-(a(5)*exp(-a(6)*q_current_T,"all")

%adq_red = lsqcurvefit(ftest,initial,[d_current'; q_current_T],psid_cross_real)

adq_red = fminsearch(combined_function, initial)
adq_red = fminsearch(combined_function, adq_red)

%f3 = @(a)psid_cross_real-(a(1)*((2*(a(2)^2)*d_current).*exp(-(a(2)*d_current).^2)*(1-exp(-(a(3)*q_current_T).^2)))+a(4)*((2*(a(5).^2)*d_current).*exp(-(a(5)*d_current).^2)*(1-exp(-(a(6)*q_current_T).^2)))+a(7)*((2*(a(8)^2)*d_current).*exp(-(a(8)*d_current).^2)*(1-exp(-(a(9)*q_current_T).^2)))+a(10)*((2*(a(11)^2)*d_current).*exp(-(a(11)*d_current).^2)*(1-exp(-(a(12)*q_current_T).^2))))
% adq_zwei = lsqnonlin(f3,adq_red,[],[],options)

a_d4 = adq_red(2);
a_d5 = adq_red(5);
a_d6 = adq_red(8);
a_d7 = adq_red(11);

a_q4 = adq_red(3);
a_q5 = adq_red(6);
a_q6 = adq_red(9);
a_q7 = adq_red(12);

k1 = adq_red(1);
k2 = adq_red(4);
k3 = adq_red(7);
k4 = adq_red(10);

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


flux_d_approx = psidself_padded-psid_cross_approx;
flux_q_approx = psiqself_padded-psid_cross_approx;

[fitresult, gof] = PolynomFit_Function(d_current, q_current, psid_cross_real);

fluxd_real = Flux_d';
fluxq_real = Flux_q';

figure;
% Erster Plot
subplot(2,1,1); % Erstelle das obere Subplot
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull_fitted);
surf(d_current, q_current, flux_d_approx);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_d');

legend;

% Zweiter Plot
subplot(2,1,2); % Erstelle das untere Subplot
grid on;
% plot(q_current_q_Flux, Fluxd_iqnull);
surf(d_current, q_current, fluxd_real);
xlabel('D Current');
ylabel('Q Current');
zlabel('Flux_q');
legend;



%Fitting_fluxlinkage_approximation

%LUT Fitting
syms ad1 ad2 ad3 ad4 ad5 ad6 aq1 aq2 aq3 aq4 aq5 aq6;
syms id iq;


%Maximum Crosscoupling current constants id1 und iq1

id1 = d_current_d_Flux(1);
iq1 = q_current_d_Flux(1);


%Selbstinduktion
psidself = ad1*tanh(ad2*id)+ad3*id;
psiqself = aq1*tanh(aq2*iq)+aq3*iq;

%gesamte induktion in im maximalen kreuzekkopplungsstrom (also ein
%ausgewählter betriebspuntk) 
psid_s1 = ad4*tanh(ad5*id)+ad6*id;
psiq_s1 = aq4*tanh(aq5*iq)+aq6*iq;

%dann ist die Kreuzkopplungin diesem Punkt 
psid_cross_s1 = psidself - psid_s1;
psiq_cross_s1 = psiqself - psiq_s1;

%die beiden werden dann integriert (wieso auch immer) 
psiid_cross_s1_integrated = (1/2)*(ad3-ad6)*((id)^2)+((ad1/ad2)*log(cosh(ad2*id)))-((ad4/ad5)*log(cosh(ad5*id)));
psiiq_cross_s1_integrated = (1/2)*(aq3-aq6)*((iq)^2)+((aq1/aq2)*log(cosh(aq2*iq)))-((aq4/aq5)*log(cosh(aq5*iq)));

%jetzt ist noch die Frage wie in dem einen Paper auf die genaue
%Kruezkopplung gekommen wird weil der einfach die beiden
%kreuezkopplungsterme in dem betriebspunkt mit den integration
%multipliziert werden und dann hat man plötzlich die kreuzkopplung

Fid1_Giq1 = (1/2)*(aq3-aq6)*((iq1)^2)+((aq1/aq2)*log(cosh(aq2*iq1)))-((aq4/aq5)*log(cosh(aq5*iq1)));

psi_d_cross = (1/Fid1_Giq1)*(psid_cross_s1)*(psiiq_cross_s1_integrated);
psi_q_cross = (1/Fid1_Giq1)*(psiq_cross_s1)*(psiid_cross_s1_integrated);


psi_d = psidself - psi_d_cross;
psi_q = psiqself - psi_q_cross;

fluxdtest = Flux_d(7,:)

fun=@(ad,d_current_d_Flux)fluxdtest-ad(1)*tanh(ad(2)*d_current_d_Flux)+ad(3)*d_current_d_Flux;

beta0 = [4;4;4];
% opts = statset('nlinfit');
% opts.RobustWgtFun = 'bisquare';
test = nlinfit(d_current_d_Flux,fluxdtest,fun,beta0)

options = optimoptions('lsqcurvefit','Algorithm','levenberg-marquardt');
lb = [];
ub = [];
test2 = lsqcurvefit(fun,beta0,d_current_d_Flux,fluxdtest,lb,ub,options)

done = fluxdtest-test(1)*tanh(test(2)*d_current_d_Flux)+test(3)*d_current_d_Flux;

figure;

% Erster Plot
subplot(2,1,1); % Erstelle das obere Subplot
plot(done, 'DisplayName', 'Done');
hold on;
grid on;
plot(fluxdtest, 'DisplayName', 'Fluxdtest');
legend;

% Zweiter Plot
subplot(2,1,2); % Erstelle das untere Subplot
plot(done, 'DisplayName', 'Done');
hold on;
grid on;
plot(fluxdtest, 'DisplayName', 'Fluxdtest');
legend;
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


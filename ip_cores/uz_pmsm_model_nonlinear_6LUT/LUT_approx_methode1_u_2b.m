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


%Nochmal aufgeschrieben um besser rauskopieren zu können
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


%Vorbereitung

%Selbstinduktion Namensgebung
psidself = Fluxd_iqnull_fitted;

psiqself = Fluxq_idnull_fitted;

q_current_T = q_current';

q_current_T = q_current_T';
d_current = d_current';

fluxd_real = Flux_d';
fluxq_real = Flux_q';

%Berechnen der selbsinduktivität
psidself_padded = repmat(Fluxd_iqnull_fitted, 1, 20)';
psiqself_padded = repmat(Fluxq_idnull_fitted, 1, 20);

psid_cross_real = psidself_padded-Flux_d';
psiq_cross_real = psiqself_padded-Flux_q';

%Addieren des Crosscoupling für "simultane berechnung"
komplettes_crosscoupling_real = psid_cross_real + psiq_cross_real;

%Schauen ob auch das richtige wieder rauskommt
flux_d_mit_cross = psidself_padded-psid_cross_real;
flux_q_mit_cross = psiqself_padded-psiq_cross_real;


%AB HIER geht die eigentliche Versucherei für das Simultane los

%Für fminsearch
finalef1 =@(f_ad4,f_ad5,f_ad6,f_ad7,f_aq4,f_aq5,f_aq6,f_aq7,f_k1,f_k2,f_k3,f_k4,d_current,q_current_T) psid_cross_real-...
    (f_k1.*((2.*(f_ad4.^2).*d_current).*exp(-(f_ad4.*d_current).^2)*(1-exp(-(f_aq4.*q_current_T).^2)))+... 
    f_k2.*((2.*(f_ad5.^2).*d_current).*exp(-(f_ad5.*d_current).^2)*(1-exp(-(f_aq5*q_current_T).^2)))+...
    f_k3.*((2.*(f_ad6.^2).*d_current).*exp(-(f_ad6.*d_current).^2).*(1-exp(-(f_aq6.*q_current_T).^2)))+...
    f_k4.*((2*(f_ad7.^2).*d_current).*exp(-(f_ad7.*d_current).^2).*(1-exp(-(f_aq7.*q_current_T).^2))));
finalef2 = @(f_ad4,f_ad5,f_ad6,f_ad7,f_aq4,f_aq5,f_aq6,f_aq7,f_k1,f_k2,f_k3,f_k4,d_current,q_current_T) psiq_cross_real-...
    ((f_k1.*(1-exp(-(f_ad4.*d_current).^2)).*((2.*(f_aq4.^2).*q_current_T).*exp(-(f_aq4.*q_current_T).^2)))   +  ...
    (f_k2.*(1-exp(-(f_ad5.*d_current).^2)).*((2.*(f_aq5.^2).*q_current_T).*exp(-(f_aq5.*q_current_T).^2))) + ...
    (f_k3.*(1-exp(-(f_ad6.*d_current).^2)).*((2.*(f_aq6.^2).*q_current_T).*exp(-(f_aq6.*q_current_T).^2)))  + ...
    (f_k4.*(1-exp(-(f_ad7.*d_current).^2)).*((2.*(f_aq7.^2).*q_current_T).*exp(-(f_aq7.*q_current_T).^2)))  );

%2 Verschiedene möglichkeiten
finalecombined = @(a)norm(sqrt((finalef1(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)+...
    (finalef2(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)),"fro").^2;
%finalecombined = @(a,d_current,q_current_T) sqrt((finalef1(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2)+(finalef2(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2));

initial_fmin_paper = [ 33.032; 0.029; 0.008; 0.581 ; 0.064; 0.084; 0.202; 0.223; 0.227; 3.567; 0.101; 0.020];
initial_fmin = [1;1;1;1;1;1;1;1;1;1;1;1];
options = optimset('MaxFunEvals',9999);

adq_red = fminsearch(finalecombined, initial_fmin_paper, options);
adq_red = fminsearch(finalecombined, adq_red,options);


%nlinfit
%In der Doku steht dass nur eine X-Variable vorgegeben werden muss (müsste eben beide d_current und q_current in einem Array festgehalten werden
%adq_linfit = nlinfit(d_current,q_current_T,psid_cross_real,f2,initial);

%lsqnonlin
initial_lsqnonlin = [1;1;1;1;1;1;1;1;1;1;1;1];
initial_lsqnonlin_paper = [ 33.032; 0.029; 0.008; 0.581 ; 0.064; 0.084; 0.202; 0.223; 0.227; 3.567; 0.101; 0.020];

%Einzelne Formeln
% f3_psid = @(a)psid_cross_real-(a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2)))+ ...
%     a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2)))+ ...
%     a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2)))+ ...
%     a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2))));

% f3_psiq = @(a)(a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2)))+ ...
%     a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2)))+ ...
%     a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2)))+ ...
%     a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2))));

%Schritt 2 Die Parameter werden in der Kreuzkopplung gesucht 
f_combined_cross = @(a)sqrt(((psid_cross_real-( (a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2))))+ ...
    (a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2))))+ ...
    (a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2))))+ ...
    (a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2)))   ))).^2)...
    +((psiq_cross_real-(a(1).*((1-exp(-(a(2).*d_current).^2)).*((2.*(a(3).^2).*q_current_T).*exp(-(a(3).*q_current_T).^2)))) +  ... 
    (a(4).*(1-exp(-(a(5).*d_current).^2)).*((2.*(a(6).^2).*q_current_T).*exp(-(a(6).*q_current_T).^2))) + ... 
    (a(7).*(1-exp(-(a(8).*d_current).^2)).*((2.*(a(9).^2).*q_current_T).*exp(-(a(9).*q_current_T).^2)))  + ... 
    (a(10).*((1-exp(-(a(11).*d_current).^2)).*((2.*(a(12).^2).*q_current_T).*exp(-(a(12).*q_current_T).^2))))  ).^2)   );

adq_zwei = lsqnonlin(f_combined_cross,initial_lsqnonlin_paper,[],[],options);

%Schritt 3 die angepassten Parameter aus der Selbstkopplung und der kruezkopplung werden benutzt um die realen werte auszurechnen
f_combined_real = @(a)sqrt(((fluxd_real-(  psidself_padded - ... 
    ((a(1).*((2.*(a(2).^2).*d_current).*exp(-(a(2).*d_current).^2).*(1-exp(-(a(3).*q_current_T).^2))))+ ...
    (a(4).*((2.*(a(5).^2).*d_current).*exp(-(a(5).*d_current).^2).*(1-exp(-(a(6).*q_current_T).^2))))+ ...
    (a(7).*((2.*(a(8).^2).*d_current).*exp(-(a(8).*d_current).^2).*(1-exp(-(a(9).*q_current_T).^2))))+ ...
    (a(10).*((2.*(a(11).^2).*d_current).*exp(-(a(11).*d_current).^2).*(1-exp(-(a(12).*q_current_T).^2)))))  )  ).^2)...
    +((fluxq_real-( psiqself_padded  - ...
    ((a(1).*(1-exp(-(a(2).*d_current).^2)).*((2.*(a(3).^2).*q_current_T).*exp(-(a(3).*q_current_T).^2))) +  ... 
    (a(4).*(1-exp(-(a(5).*d_current).^2)).*((2.*(a(6).^2).*q_current_T).*exp(-(a(6).*q_current_T).^2))) + ... 
    (a(7).*(1-exp(-(a(8).*d_current).^2)).*((2.*(a(9).^2).*q_current_T).*exp(-(a(9).*q_current_T).^2)))  + ... 
    (a(10).*(1-exp(-(a(11).*d_current).^2)).*((2.*(a(12).^2).*q_current_T).*exp(-(a(12).*q_current_T).^2)) ) ) )  ).^2)   );
initial_combinedreal = [adq_zwei;ad1;ad2;ad3;aq1;aq2;aq3];
adq_zwei = lsqnonlin(f_combined_real,initial_combinedreal ,[],[],options);

%Mit lsqcurvefit
%Ähnliches Problem wie bei nlinfit in der Doku steht dass nur eine X-Variable vorgegeben werden muss (müsste eben beide d_current und q_current in einem Array festgehalten werden
OPTIONS = optimoptions('lsqcurvefit','Algorithm','levenberg-marquardt');

dq_current = [d_current;q_current_T'];
%adq_red = lsqcurvefit(finalecombined,initial_lsqnonlin_paper, dq_current, matrix,[],[],[],[],[],[],[],OPTIONS)

%Hiermit kommt ein Fehler wegen input arguements
% adq_red = lsqcurvefit(f_combined_cross,initial_lsqnonlin_paper,dq_current,psid_cross_real);

%Verschiedene Parameter können aus(einkommentiert) werden wie sie gebraucht werden
%für fminsearch
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

%für lsqnonlin
a_d4 = adq_zwei(2);
a_d5 = adq_zwei(5);
a_d6 = adq_zwei(8);
a_d7 = adq_zwei(11);

a_q4 = adq_zwei(3);
a_q5 = adq_zwei(6);
a_q6 = adq_zwei(9);
a_q7 = adq_zwei(12);

k1 = adq_zwei(1);
k2 = adq_zwei(4);
k3 = adq_zwei(7);
k4 = adq_zwei(10);

a_d1 = adq_zwei(13);
a_d2 = adq_zwei(14);
a_d3 = adq_zwei(15);

a_q1 = adq_zwei(16);
a_q2 = adq_zwei(17);
a_q3 = adq_zwei(18);

%Methode 1
%Versuch einfach mal Fminsearch zu Vergleichen
 % finalef1 =@(f_aq1,f_aq2,f_aq3,f_aq4,f_aq5,f_aq6,f_aq7,f_aq8,f_aq9,f_aq10,f_aq11,f_aq12,d_current,q_current_T) fluxq_real -(  ((f_aq1*tanh(f_aq2.*q_current_T))+(f_aq3.*q_current_T))   .*(  ( (f_aq4+(f_aq5./(1+(f_aq6.*(q_current_T.^2)))))   .*exp(-((f_aq7+(f_aq8./(1+(f_aq9.*(q_current_T.^2))))).*d_current).^2) )  +(     (1-((f_aq4+(f_aq5./(1+(f_aq6.*(q_current_T.^2)))))).*exp(-((f_aq10+(f_aq11./(1+(f_aq12.*(q_current_T.^2)))))*d_current).^2))   )      )       )  
 % finalef2psid = @(f_ad1,f_ad2,f_ad3,f_ad4,f_ad5,f_ad6,f_ad7,f_ad8,f_ad9,f_ad10,f_ad11,f_ad12,d_current,q_current_T) fluxd_real -(  (f_ad1*(tanh(f_ad2*(d_current-f_ad3))))   .*(  ( (f_ad4+(f_ad5./(1+(f_ad6.*(d_current.^2)))))   .*exp(-((f_ad7+(f_ad8./(1+(f_ad9.*(d_current.^2))))).*q_current_T).^2) )  +(     (1-((f_ad4+(f_ad5./(1+(f_ad6.*(d_current.^2)))))).*exp(-((f_ad10+(f_ad11./(1+(f_ad12.*(d_current.^2)))))*q_current_T).^2))   )      )       )  
 
 finalef1psiq = @(aq) fluxq_real -( ((aq(1).*tanh(aq(2).*q_current_T))+(aq(3).*q_current_T))   .*(   (aq(4)+(aq(5)./(1+(aq(6).*(q_current_T.^2)))))   .*exp(-((aq(7)+(aq(8)./(1+(aq(9).*(q_current_T.^2))))).*d_current).^2)   + (    (    1-((aq(4)+(aq(5)./(1+(aq(6).*(q_current_T.^2))))))  ).*exp(-((aq(10)+(aq(11)/(1+(aq(12).*(q_current_T.^2))))).*d_current).^2)   )      )    );
 finalef2psid = @(ad,d_current,q_current_T) fluxd_real -(  (ad(1)*(tanh(ad(2).*(d_current-ad(3)))))           .*(   (ad(4)+(ad(5)./(1+(ad(6).*(d_current.^2)))))   .*exp(-((ad(7)+(ad(8)./(1+(ad(9).*(d_current.^2))))).*q_current_T).^2)   + (    (    1-((ad(4)+(ad(5)./(1+(ad(6).*(d_current.^2))))))  ).*exp(-((ad(10)+(ad(11)./(1+(ad(12).*(d_current.^2))))).*q_current_T).^2)   )      )   );
 
 % finalecombined = @(a) norm(finalef1psiq(a(1),a(2),a(3),a(4),a(5),a(6),a(7),a(8),a(9),a(10),a(11),a(12),d_current,q_current_T).^2).^2
 % finalecombinedf2d = @(ad) norm(finalef1psiq(ad(1),ad(2),ad(3),ad(4),ad(5),ad(6),ad(7),ad(8),ad(9),ad(10),ad(11),ad(12),d_current,q_current_T).^2).^2

 %Anfangswerte von Selbstinduktivität
 initial_psiq_m1 = [0.004816670542863;0.171595254784258;9.262938633610718e-04;1;1;1;1;1;1;1;1;1];
 initial_psid_m1 = [0.030483840951002;0.040244227373267;-16.481195185733903;1;1;1;1;1;1;1;1;1];

 %Anfangswerte aus Curvefitting Toolbox (Sind schon sehr gut)
 initial_psiq_m1_genauer=[0.0041;0.0032;0.6133;0.1467;0.2092;0.0010;28.4940;-24.2348;0.0405;-0.0030;-0.6286;0.1516];

 % adq_red_d = fminsearch(finalef1psiq, initial_psiq_m1);
 % adq_red = fminsearch(finalef1psiq,  initial_psiq_m1_genauer);

 %Sind einfach Parameter um verschiedene sachen zu Vergleichen
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

%Wieder die Werte aus der Curvefitting Toolbox (Methode 2b)
% a_d4 = 0.1413;
% a_d5 = 0.4427;
% a_d6 = 1.0908;
% a_d7 = 0.1704;
% 
% a_q4 = 1.3190;
% a_q5 = 0.7707;
% a_q6 = 0.4186;
% a_q7 = 1.0530;
% 
% k1 = 0.0762;
% k2 = 0.0016;
% k3 = -0.0004;
% k4 = -0.0468;


%das sind die anderen formeln aus dem "ersten" Paper also das wurde eingefügt in Curvefitting toolbox für Methode1
% ((aq1*tanh(aq2*iq))+(aq3*iq))   *(   (aq4+(aq5/(1+(aq6*(iq^2)))))   *exp(-((aq7+(aq8/(1+(aq9*(iq^2)))))*id)^2)   + (    (    1-((aq4+(aq5/(1+(aq6*(iq^2))))))  )*exp(-((aq10+(aq11/(1+(aq12*(iq^2)))))*id)^2)   )      )
% (ad1*(tanh(ad2*(id-ad3))))    *(   (ad4+(ad5/(1+(ad6*(id^2)))))   *exp(-((ad7+(ad8/(1+(ad9*(id^2)))))*iq)^2)   + (    (    1-((ad4+(ad5/(1+(ad6*(id^2))))))  )*exp(-((ad10+(ad11/(1+(ad12*(id^2)))))*iq)^2)   )      )

%Dann kommen folgende Parameter raus
%Nochmal neue Parameter für psiq aus der Curvefittingtoolbox 
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


%Formeln für die Methode 2b
psid_cross_approx_m2b = (k1.*(((2.*(a_d4.^2).*d_current).*exp(-(a_d4.*d_current).^2)).*(1-exp(-(a_q4.*q_current_T).^2))))+ ...
    (k2.*(((2.*(a_d5.^2).*d_current).*exp(-(a_d5.*d_current).^2)).*(1-exp(-(a_q5.*q_current_T).^2))))+ ...
    (k3.*(((2.*(a_d6.^2).*d_current).*exp(-(a_d6.*d_current).^2)).*(1-exp(-(a_q6.*q_current_T).^2))))+ ...
    (k4.*(((2*(a_d7.^2).*d_current).*exp(-(a_d7.*d_current).^2)).*(1-exp(-(a_q7.*q_current_T).^2))));
psiq_cross_approx_m2b = (k1.*(1-exp(-(a_d4.*d_current).^2)).*((2.*(a_q4.^2).*q_current_T).*exp(-(a_q4.*q_current_T).^2)))+ ...
    (k2.*(1-exp(-(a_d5.*d_current).^2)).*((2.*(a_q5.^2).*q_current_T).*exp(-(a_q5.*q_current_T).^2))) + ... 
    (k3.*(1-exp(-(a_d6.*d_current).^2)).*((2.*(a_q6.^2).*q_current_T).*exp(-(a_q6.*q_current_T).^2)))  +...
    (k4.*(1-exp(-(a_d7.*d_current).^2)).*((2.*(a_q7.^2).*q_current_T).*exp(-(a_q7.*q_current_T).^2)));

flux_d_approx_m2b = psidself_padded - psid_cross_approx_m2b;
flux_q_approx_m2b = psiqself_padded - psiq_cross_approx_m2b;

%Berechnen des Fehlers in %
fluxd_max = max(fluxd_real, [], 'all');
fluxq_max = max(fluxq_real, [], 'all');

ed = ((abs(fluxd_real-flux_d_approx_m1))/fluxd_max).*100;
eq = ((abs(fluxq_real-flux_q_approx_m1))/fluxq_max).*100;

%Error für Polyfit
% ed = ((abs(fluxd_real-fluxd_poly_approx))/fluxd_max).*100;
% eq = ((abs(fluxq_real-fluxq_poly_approx))/fluxq_max).*100;

%Error für Methode 2b
% ed = ((abs(fluxd_real-psid_cross_approx_m2b))/fluxd_max).*100;
% eq = ((abs(fluxq_real-psiq_cross_approx_m2b))/fluxq_max).*100;


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


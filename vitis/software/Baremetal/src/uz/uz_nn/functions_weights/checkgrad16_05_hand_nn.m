% Matrizen/Inputvektoren definieren
clear
close all
format long
load layer1_bias_test1.mat
load layer1_weights_test1.mat
load layer2_bias_test1.mat
load layer2_weights_test1.mat
load layer3_bias_test1.mat
load layer3_weights_test1.mat

% input/output werte
x = [15.2 47.1;12.3 1.7];
t = [13.2 9.3];

% einzelne Gewichte und Bias schreiben
theta_1 = layer1_weights;
b_1 = layer1_bias;
theta_2 = layer2_weights;
b_2 = layer2_bias;
theta_3 = layer3_weights;
b_3 = layer3_bias;

y_0_1 = x(:,1)';
s_1_1 = (y_0_1*theta_1+b_1)
y_1_1 = tanh(s_1_1) % runden wie Schroeder S. 108
s_1_2 = (y_1_1*theta_2+b_2)
y_1_2 = tanh(s_1_2)
s_1_3 = (y_1_2*theta_3+b_3)
y_1_3 = s_1_3
% l_3 ist -1.52 wie im example -> check
e_1 = (y_1_3-t(1))^2



% Ableitungen
T3=[1]
T2=[1-(tanh(s_1_2(1))*tanh(s_1_2(1))) 0; 0 1-(tanh(s_1_2(2))*tanh(s_1_2(2)))]
T1=[1-(tanh(s_1_1(1))*tanh(s_1_1(1))) 0 0 0 0; 0 1-(tanh(s_1_1(2))*tanh(s_1_1(2))) 0 0 0;...
 0 0 1-(tanh(s_1_1(3))*tanh(s_1_1(3))) 0 0; 0 0 0 1-(tanh(s_1_1(4))*tanh(s_1_1(4))) 0;...
 0 0 0 0 1-(tanh(s_1_1(5))*tanh(s_1_1(5)))]

derivatesarray = zeros(30,1);
derivatesarray = horzcat(reshape(T1,1,[]),reshape(T2,1,[]),reshape(T3,1,[]))'
% Zurückpropagieren
delta_3 = -T3*e_1
T2
theta_3'
delta_3
delta_2 = T2*theta_3.*delta_3
delta_1 = T1*theta_2*delta_2


% Gradienten für Gewichte
gradwl1 = delta_1*y_0_1
gradwl2 = delta_2*y_1_1
gradwl3 = delta_3*y_1_2

% Gradienten für bias
gradbl1=delta_1
gradbl2=delta_2
gradbl3=delta_3

grad_gesamt = horzcat(reshape(gradwl1,1,[]),reshape(gradbl1,1,[]),reshape(gradwl2,1,[]),reshape(gradbl2,1,[]),reshape(gradwl3,1,[]),reshape(gradbl3,1,[]))'
% % grad gesamt entspricht dem schroeder vektor werten exakt
% export grad_gesamt
for i=1:numel(grad_gesamt)
    Gradmat{:,i} = append(num2str(grad_gesamt(i)),'f');
end
writecell(Gradmat,'gradmat.csv','Delimiter','comma');

clear
close all
%% https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
%% ohne matrizenschreibweise!
x = [0.05 0.1];
y = [0.01; 0.99];
Episoden = 10000;
lr = 0.5;
w1 = [0.15  0.25 ;0.2 0.3];
b1 = 0.35;
w2 = [0.4 0.5 ;0.45 0.55];
b2 = 0.6;

for j=1:Episoden

%% FF rechnen
y_0_1 = x;
s_1_1 = (y_0_1*w1+b1);
y_1_1 = 1./(1+exp(-s_1_1));
s_1_2 = (y_1_1*w2+b2);
y_1_2 = 1./(1+exp(-s_1_2));

%% calc etotal
E_Total =0.5*sum((y-y_1_2).^2);
deltaETotal_deltaout1 = -(y(1)-y_1_2(1));
deltaETotal_deltaout2 = -(y(2)-y_1_2(2));

%% calc w5,w6,w7 und w8
change5 = (-(y(1)-y_1_2(1))*y_1_2(1)*(1-y_1_2(1)))*y_1_1(1);
change6 = (-(y(1)-y_1_2(1))*y_1_2(1)*(1-y_1_2(1)))*y_1_1(2);
change7 = (-(y(2)-y_1_2(2))*y_1_2(2)*(1-y_1_2(2)))*y_1_1(1);
change8 = (-(y(2)-y_1_2(2))*y_1_2(2)*(1-y_1_2(2)))*y_1_1(2);


%% calc w1,w2,w3 und w4
change1_1 = -((y(1)-y_1_2(1))*(y_1_2(1)*(1-y_1_2(1))))*w2(1);
change1_2 = -((y(2)-y_1_2(2))*(y_1_2(2)*(1-y_1_2(2))))*w2(3);
change1 = (change1_1+change1_2)*y_1_1(1)*(1-y_1_1(1))*x(1);
change2_1 = -((y(1)-y_1_2(1))*(y_1_2(1)*(1-y_1_2(1))))*w2(1);
change2_2 = -((y(2)-y_1_2(2))*(y_1_2(2)*(1-y_1_2(2))))*w2(3);
change2 = (change2_1+change2_2)*y_1_1(1)*(1-y_1_1(1))*x(2);
change3_1 = -((y(1)-y_1_2(1))*(y_1_2(1)*(1-y_1_2(1))))*w2(2);
change3_2 = -((y(2)-y_1_2(2))*(y_1_2(2)*(1-y_1_2(2))))*w2(4);
change3 = (change3_1+change3_2)*y_1_1(2)*(1-y_1_1(2))*x(1);
change4_1 = -((y(1)-y_1_2(1))*(y_1_2(1)*(1-y_1_2(1))))*w2(2);
change4_2 = -((y(2)-y_1_2(2))*(y_1_2(2)*(1-y_1_2(2))))*w2(4);
change4 = (change4_1+change4_2)*y_1_1(2)*(1-y_1_1(2))*x(2);

w1(1) = w1(1)-lr*change1;
w1(2) = w1(2)-lr*change2; 
w1(3) = w1(3)-lr*change3;
w1(4) = w1(4)-lr*change4; 

w2(1) = w2(1)-lr*change5;
w2(2) = w2(2)-lr*change6; 
w2(3) = w2(3)-lr*change7;
w2(4) = w2(4)-lr*change8; 
end
y_1_2

% deltaouto1_deltaneto1 = y_1_2(1)*(1-y_1_2(1))
% deltaneto1_deltaw_5 = y_1_1(1)
% deltaEtotal_w_5 = deltaETotal_deltaout1*deltaouto1_deltaneto1*deltaneto1_deltaw_5
% w2(1) = w2(1)-lr*deltaEtotal_w_5
% deltaneto1_deltaw_6 = y_1_1(1)
% deltaEtotal_w_6 = deltaETotal_deltaout1*deltaouto1_deltaneto1*deltaneto1_deltaw_6
% w2(2) = w2(2)-lr*deltaEtotal_w_6
% 
% deltaouto2_deltaneto2 = y_1_2(2)*(1-y_1_2(2))
% deltaneto2_deltaw_7= y_1_2(2)
% deltaEtotal_w_7 = deltaETotal_deltaout2*deltaouto2_deltaneto2*deltaneto2_deltaw_7
% w2(3) = w2(3)-lr*deltaEtotal_w_7
% deltaneto2_deltaw_8 = y_1_2(2)
% deltaEtotal_w_8 = deltaETotal_deltaout2*deltaouto2_deltaneto2*deltaneto2_deltaw_8
% w2(4) = w2(4)-lr*deltaEtotal_w_8

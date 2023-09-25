clear
close all
%% https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
%% matrizenschreibweise
x = [0.05 0.1];
y = [0.01 0.99];
Episoden = 1;
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
E_Total = 0.5*sum((y-y_1_2).^2);
e = -(y-y_1_2);

%% delta rule output
% delta
deltaout = e.*(y_1_2.*(1-y_1_2));
delta1 = deltaout'*y_1_1;
%einfach
delta00 = (deltaout*w2')'.*(y_1_1.*(1-y_1_1))'.*x;

%umständlich
deltahiddenvec = deltaout.*w2;
deltahiddena= cumsum(deltahiddenvec,2);
deltahidden3 = deltahiddena(:,2);
delta0 = deltahidden3.*(y_1_1.*(1-y_1_1))'.*x;

%ergibt selbes ergebnis für delta 0 und delta00
%% delta rule hidden

w1 = w1-lr*delta00';
w2 = w2-lr*delta1';
loss{:,j} = E_Total;
end
y_1_2
b=cell2mat(loss);
plot(b);
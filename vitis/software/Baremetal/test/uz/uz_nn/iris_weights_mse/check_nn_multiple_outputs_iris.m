clear
close all
format short
load iris_dataset.mat

rng("default")
rand(1,5)
% Randbedingungen
Episoden = 2000;
lernrate=single(0.005); % Schrittweite
xn = irisInputs;
tn = irisTargets;
%% netz initialisieren und werte speichern für training
net = feedforwardnet( [50 20],'traingd');
net.divideFcn='';
net.divideMode='none'; % ausstellen der Teilung in Trainings und Testdaten, kein Sampling
%% Parameter für GD festlegen
% set values for Initialisiserung
net.trainParam.epochs=0;
net.trainParam.lr=0.001;
net.trainParam.show = 1;
net.trainParam.showCommandLine = true;
% train (Initialisierung 0 episoden)
[net,tr] = train(net,xn,tn)

%% parameter speichern
%% zuweisen der netzparameter

layer1_weights=single(net.IW{1,1}'); 
layer1_bias=single(net.b{1,1}');

layer2_weights=single(net.LW{2,1}');
layer2_bias=single(net.b{2,1}');

layer3_weights=single(net.LW{3,2}');
layer3_bias=single(net.b{3,1}');

%% reshaping weights for export
% transpose weights
l1wex=layer1_weights';
l2wex=layer2_weights';
l3wex=layer3_weights';

%% exportieren input output
% export to .csv
%turn into a float
for i=1:numel(xn)
    Xn{:,i} = strcat(sprintf('%0.2f\n',xn(i)),'f');
end

for i=1:numel(tn)
    Tn{:,i} = strcat(sprintf('%0.2f\n',tn(i)),'f');
end
writecell(Xn,'xn_iris.csv','Delimiter','comma');
writecell(Tn,'tn_iris.csv','Delimiter','comma');

% inputvektor x und outputvektor T, jeweils nur zeilenvektor
x_input= xn(:,1)';
t_output=tn(:,1)';
%turn into a float
for i=1:numel(x_input)
    X_input{:,i} = append(num2str(x_input(i)),'f');
end
for i=1:numel(t_output)
    T_output{:,i} = append(num2str(t_output(i)),'.0f');
end

% export to .csv
writecell(X_input,'x_iris_in.csv','Delimiter','comma');
writecell(T_output,'t_iris_in.csv','Delimiter','comma');
%% double to floating point

for i=1:numel(layer1_bias)
    Layer1_bias{:,i} = append(num2str(layer1_bias(i)),'f');
end
for i=1:numel(layer2_bias)
    Layer2_bias{:,i} = append(num2str(layer2_bias(i)),'f');
end
for i=1:numel(layer3_bias)
    Layer3_bias{:,i} = append(num2str(layer3_bias(i)),'f');
end
for i=1:numel(l1wex)
    Layer1_weights{:,i} = append(num2str(l1wex(i)),'f');
end
for i=1:numel(l2wex)
    Layer2_weights{:,i} = append(num2str(l2wex(i)),'f');
end
for i=1:numel(l3wex)
    Layer3_weights{:,i} = append(num2str(l3wex(i)),'f');
end

writecell(Layer1_weights,'layer1_weights_iris.csv','Delimiter','comma');
writecell(Layer1_bias,'layer1_bias_iris.csv','Delimiter','comma');
writecell(Layer2_weights,'layer2_weights_iris.csv','Delimiter','comma');
writecell(Layer2_bias,'layer2_bias_iris.csv','Delimiter','comma');
writecell(Layer3_weights,'layer3_weights_iris.csv','Delimiter','comma');
writecell(Layer3_bias,'layer3_bias_iris.csv','Delimiter','comma');

%% eigenen trainingsloop
Minibatchsize = size(tn,2);
% einzelne Gewichte und Bias schreiben
theta_1 = layer1_weights;
b_1 = layer1_bias;
theta_2 = layer2_weights;
b_2 = layer2_bias;
theta_3 = layer3_weights;
b_3 = layer3_bias;

for j=1:Episoden
E_Total = 0;
% Gradienten nullen
gradwl1(:) = 0; 
gradwl2(:) = 0;
gradwl3(:) = 0;

% Gradienten für bias
gradbl1(:)= 0;
gradbl2(:)= 0;
gradbl3(:)= 0;
%% FF rechnen (4.49-4.51 S.108)
for z=1:Minibatchsize
y_0_1 = single(xn(:,z)');
s_1_1 = (y_0_1*theta_1+b_1);
y_1_1 = tanh(s_1_1);% runden wie Schroeder S. 108
s_1_2 = (y_1_1*theta_2+b_2);
y_1_2 = tanh(s_1_2);
s_1_3 = (y_1_2*theta_3+b_3);
y_1_3 = s_1_3;

%% calc etotal
E_Total = E_Total+1/size(tn,1)*sum((tn(:,z)'-y_1_3).^2);
e = -(tn(:,z)'-y_1_3);


%% Ableitungen S.109
T3=[1];
T2=eye(20);
%% loop through rows
for i=1:size(T2,1)
    T2(:,i)=T2(:,i).*(1-(tanh(s_1_2(i))*tanh(s_1_2(i))));
end
T1=eye(50);
%% loop through rows
for i=1:size(T1,1)
    T1(:,i)=T1(:,i).*(1-(tanh(s_1_1(i))*tanh(s_1_1(i))));
end
% output layer
% deltaout = e*1
% delta1 = deltaout*y_1_2;
% Zurückpropagieren
delta_3 = T3*single(e'); %4.52
delta_2 = T2*theta_3*delta_3; %4.53
delta_1 = T1*theta_2*delta_2; %4.53

% Gradienten für Gewichte
gradwl1 = gradwl1+delta_1*y_0_1; %4.54
gradwl2 = gradwl2+delta_2*y_1_1; %4.54
gradwl3 = gradwl3+delta_3*y_1_2; %4.54

% Gradienten für bias
gradbl1=gradbl1+delta_1; %4.55
gradbl2=gradbl2+delta_2; %4.55
gradbl3=gradbl3+delta_3; %4.55

grad_gesamt= horzcat(reshape(gradwl1,1,[]),reshape(gradbl1,1,[]),reshape(gradwl2,1,[]),reshape(gradbl2,1,[]),reshape(gradwl3,1,[]),reshape(gradbl3,1,[]))';
grad_sum{:,z} = grad_gesamt;
end
% % grad gesamt entspricht dem schroeder vektor werten exakt
theta_1 = theta_1-lernrate/Minibatchsize*gradwl1';
theta_2 = theta_2-lernrate/Minibatchsize*gradwl2';
theta_3 = theta_3-lernrate/Minibatchsize*gradwl3';
b_1 = b_1-lernrate/Minibatchsize*gradbl1';
b_2 = b_2-lernrate/Minibatchsize*gradbl2';
b_3 = b_3-lernrate/Minibatchsize*gradbl3';
Fehler{:,j}=E_Total/Minibatchsize;
end
ymse = cell2mat(Fehler);
for i=1:numel(ymse)
    MSE_MBtrain{:,i} = append(num2str(ymse(i)),'f');
end
writecell(MSE_MBtrain,'mse_mean_iris_2000episodes_lr005.csv','Delimiter','comma');

Fehler
% Define x and y:
y1 = cell2mat(Fehler);
x1 = ones(size(y1,1),1)*(1:size(y1,2));
rand(1,5)
% plot:
plot(x1,y1,'LineWidth',2,'DisplayName','Matlab-Implementation')
hold on;
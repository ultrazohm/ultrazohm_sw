%% 16.05. test 1
%% Support Ticket Rosner code

% From this example: https://de.mathworks.com/help/deeplearning/ug/train-and-apply-multilayer-neural-networks.html
clc
clear
rng(0)
format long;

%% 1. Setting up Gradient descent without stochastic or batch gd

net = feedforwardnet([5 2],'traingd');
net.divideFcn='';
net.divideMode='none'; % ausstellen der Teilung in Trainings und Testdaten, kein Sampling
% net.layers{1}.transferFcn = 'tansig';% Tanh Aktivierungsfunktion in layer 1
% net.layers{2}.transferFcn = 'tansig';% Tanh Aktivierungsfunktion in layer 2
% net.layers{1}.transferFcn = 'poslin';% Tanh Aktivierungsfunktion in layer 1
% net.layers{2}.transferFcn = 'poslin';% Tanh Aktivierungsfunktion in layer 2
% net.layers{3}.transferFcn = 'purelin';% Linear Aktivierungsfunktions in layer3
view(net)
x = [15.2 47.1;12.3 1.7];
t = [13.2 9.3];

%% Parameter für GD festlegen
% set values for Initialisiserung
net.trainParam.epochs=0;
net.trainParam.lr=0.001;
net.trainParam.show = 1;
net.trainParam.showCommandLine = true;
% train (Initialisierung 0 episoden)
[net,tr] = train(net,x,t)

%% ff result zu Episode 0
 result1=net(x(:,1))
 resultall=net(x)
 msefirsttraindata=immse(result1,t(1))
 msealltraindata = immse(resultall,t)

%% export parameter für VS Code

layer1_weights=net.IW{1,1}'; 
layer1_bias=net.b{1,1}';

layer2_weights=net.LW{2,1}';
layer2_bias=net.b{2,1}';

layer3_weights=net.LW{3,2}';
layer3_bias=net.b{3,1}';

%% export als .mat

save("layer1_weights_test1.mat","layer1_weights")
save("layer2_weights_test1.mat","layer2_weights")
save("layer3_weights_test1.mat","layer3_weights")
save("layer1_bias_test1.mat","layer1_bias")
save("layer2_bias_test1.mat","layer2_bias")
save("layer3_bias_test1.mat","layer3_bias")
%% reshaping weights for export
% transpose weights
layer1_weights=layer1_weights';
layer2_weights=layer2_weights';
layer3_weights=layer3_weights';

%% exportieren der Inputtrainingsdaten und der zugehörigen 
% inputvektor x und outputvektor T, jeweils nur zeilenvektor
x_input= x(:,1)';
t_output=t(:,1)';
%turn into a float
for i=1:numel(x_input)
    X_input{:,i} = append(num2str(x_input(i)),'f');
end
for i=1:numel(t_output)
    T_output{:,i} = append(num2str(t_output(i)),'f');
end

% export to .csv
writecell(X_input,'X_test1.csv','Delimiter','comma');
writecell(T_output,'T_test1.csv','Delimiter','comma');
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
for i=1:numel(layer1_weights)
    Layer1_weights{:,i} = append(num2str(layer1_weights(i)),'f');
end
for i=1:numel(layer2_weights)
    Layer2_weights{:,i} = append(num2str(layer2_weights(i)),'f');
end
for i=1:numel(layer3_weights)
    Layer3_weights{:,i} = append(num2str(layer3_weights(i)),'f');
end

writecell(Layer1_weights,'layer1_weights_test1.csv','Delimiter','comma');
writecell(Layer1_bias,'layer1_bias_test1.csv','Delimiter','comma');
writecell(Layer2_weights,'layer2_weights_test1.csv','Delimiter','comma');
writecell(Layer2_bias,'layer2_bias_test1.csv','Delimiter','comma');
writecell(Layer3_weights,'layer3_weights_test1.csv','Delimiter','comma');
writecell(Layer3_bias,'layer3_bias_test1.csv','Delimiter','comma');

%% 1 Episode Trainieren, Gradienten herausziehen resultate vergleichen...
% mit VS Code

% set values for training
net.trainParam.epochs=1;
net.trainParam.lr=0.01;
net.trainParam.showCommandLine = true;
net.trainParam.showWindow = true;
weights = [];
gwb = [];
jwb = [];

result1

for i = 1:1
y = net(x(:,1))
perf = perform(net,t(:,1),y)
net = train(net,x(:,1),t(1));
y = net(x(:,1))
perf = perform(net,t(1),y)
gwb = [gwb fpderiv('dperf_dwb',net,x(:,1),t(:,1));];
jwb  = [jwb fpderiv('de_dwb',net,x(:,1),t(:,1));];
weights = getwb(net);
[b,iw,lw] = separatewb(net,weights)
end
result2=net(x(:,1))
%export gwb
gwb = gwb';
for i=1:numel(gwb)
    GWB{:,i} = append(num2str(gwb(i)),'f');
end

writecell(GWB,'GWB_test1.csv','Delimiter','comma');
%% export trainierte Parameter

%% zuweisen der parameter
layer1_weightstrained=net.IW{1,1}'; 
layer1_biastrained=net.b{1,1}';

layer2_weightstrained=net.LW{2,1}';
layer2_biastrained=net.b{2,1}';

layer3_weightstrained=net.LW{3,2}';
layer3_biastrained=net.b{3,1}';
%% reshaping weights for export
% transpose weights
layer1_weightstrained=layer1_weightstrained';
layer2_weightstrained=layer2_weightstrained';
layer3_weightstrained=layer3_weightstrained';

%% export als .mat

save("layer1_weights_test1tr.mat","layer1_weightstrained")
save("layer2_weights_test1tr.mat","layer2_weightstrained")
save("layer3_weights_test1tr.mat","layer3_weightstrained")
save("layer1_bias_test1tr.mat","layer1_biastrained")
save("layer2_bias_test1tr.mat","layer2_biastrained")
save("layer3_bias_test1tr.mat","layer3_biastrained")
%% combine strings to floating points

for i=1:numel(layer1_bias)
    Layer1_biastrained{:,i} = append(num2str(layer1_biastrained(i)),'f');
end
for i=1:numel(layer2_bias)
    Layer2_biastrained{:,i} = append(num2str(layer2_biastrained(i)),'f');
end
for i=1:numel(layer3_bias)
    Layer3_biastrained{:,i} = append(num2str(layer3_biastrained(i)),'f');
end
for i=1:numel(layer1_weights)
    Layer1_weightstrained{:,i} = append(num2str(layer1_weightstrained(i)),'f');
end
for i=1:numel(layer2_weights)
    Layer2_weightstrained{:,i} = append(num2str(layer2_weightstrained(i)),'f');
end
for i=1:numel(layer3_weights)
    Layer3_weightstrained{:,i} = append(num2str(layer3_weightstrained(i)),'f');
end
writecell(Layer1_weightstrained,'layer1_weightstrained_test1.csv','Delimiter','comma');
writecell(Layer1_biastrained,'layer1_biastrained_test1.csv','Delimiter','comma');
writecell(Layer2_weightstrained,'layer2_weightstrained_test1.csv','Delimiter','comma');
writecell(Layer2_biastrained,'layer2_biastrained_test1.csv','Delimiter','comma');
writecell(Layer3_weightstrained,'layer3_weightstrained_test1.csv','Delimiter','comma');
writecell(Layer3_biastrained,'layer3_biastrained_test1.csv','Delimiter','comma');
% print result 1 und result 2

result1
result2

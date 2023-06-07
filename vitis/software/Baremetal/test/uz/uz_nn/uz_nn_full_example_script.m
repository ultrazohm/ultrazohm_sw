%% Matlab example to generate values for ceedling
% From this example: https://de.mathworks.com/help/deeplearning/ug/train-and-apply-multilayer-neural-networks.html
clc
clear
rand(0); % Fix random number generator to ensure reproducable results

% From this example: https://de.mathworks.com/help/deeplearning/ug/train-and-apply-multilayer-neural-networks.html
[x,t] = bodyfat_dataset;
%  Explizitly use mapminmax to have the same input/output processing in the matlab toolbox as in the hand-coded implementation
% See: https://de.mathworks.com/help/deeplearning/ref/mapminmax.html
[xn,ps] = mapminmax(x);
[tn,ts] = mapminmax(t);
net = feedforwardnet( [50 20]);
net.layers{1}.transferFcn='poslin'; % Set ReLU activation function for layer 1
net.layers{2}.transferFcn='poslin'; % Set ReLU activation function for layer 2
net = train(net,xn,tn);
view(net)


%% Extract values
layer1_weights=net.IW{1,1}'; 
layer1_bias=net.b{1,1}';

layer2_weights=net.LW{2,1}';
layer2_bias=net.b{2,1}';

layer3_weights=net.LW{3,2}';
layer3_bias=net.b{3,1}';

writematrix(reshape(layer1_weights',[],1)','layer1_weights.csv','Delimiter','comma'); % Transpose weights since matlab and uz neural network definition differs
writematrix(layer1_bias,'layer1_bias.csv','Delimiter','comma');
writematrix(reshape(layer2_weights',[],1)','layer2_weights.csv','Delimiter','comma');
writematrix(layer2_bias,'layer2_bias.csv','Delimiter','comma');
writematrix(reshape(layer3_weights',[],1)','layer3_weights.csv','Delimiter','comma');
writematrix(layer3_bias,'layer3_bias.csv','Delimiter','comma');
%% Manual calculation
input=[1 2 3 4 5 6 7 8 9 10 11 12 13];

% firts layer
s1=input * layer1_weights+layer1_bias;
s1(s1<0)=0; % Threshold at 0
y1=s1;

% Second layer
s2=y1* layer2_weights+layer2_bias;
s2(s2<0)=0; % Threshold at 0
y2=s2;

% Third layer (output)
s3=y2*layer3_weights+layer3_bias;
y3=s3; % linear activation function

handcoded_result=y3
matlab_toolbox_result=net(input')
assert( (handcoded_result-matlab_toolbox_result) < 1e-5); % Error has to be in the range of floating point errors

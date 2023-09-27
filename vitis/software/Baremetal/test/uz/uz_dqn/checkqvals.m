
%% referenz check um Gewichte und bias von C und Matlab zu vergleichen
%Tool: Heatmaplots, die Differenzwerte darstellen
% Step 1: .csv laden aus C Implementierung, nur erstes layer betrachten
clc
clear
format long

load trained_layer1_bias.csv
load trained_layer1_weights.csv
load trained_layer2_bias.csv
load trained_layer2_weights.csv

% reshape in richtige array form
trained_layer1_weights=reshape(trained_layer1_weights,[256,8])'
trained_layer2_weights=reshape(trained_layer2_weights,[4,256])'

%% Manual calculation
input1=[0 0 0 0 1 1 1 1];

% firts layer
s1=input1* trained_layer1_weights+trained_layer1_bias;
s1(s1<0)=0; % Threshold at 0
y1=s1;

% second layer (output)
s3=y1*trained_layer2_weights+trained_layer2_bias;
y3=s3; % linear activation function

Q0000 = y3

input2=[1 0 0 0 1 1 1 1];

% firts layer
s1=input2 * trained_layer1_weights+trained_layer1_bias;
s1(s1<0)=0; % Threshold at 0
y1=s1;

% second layer (output)
s3=y1*trained_layer2_weights+trained_layer2_bias;
y3=s3; % linear activation function

Q1000 = y3

input2=[1 1 0 0 1 1 1 1];

% firts layer
s1=input2 * trained_layer1_weights+trained_layer1_bias;
s1(s1<0)=0; % Threshold at 0
y1=s1;

% second layer (output)
s3=y1*trained_layer2_weights+trained_layer2_bias;
y3=s3; % linear activation function

Q1100 = y3

input2=[1 1 1 0 1 1 1 1];

% firts layer
s1=input2 * trained_layer1_weights+trained_layer1_bias;
s1(s1<0)=0; % Threshold at 0
y1=s1;

% second layer (output)
s3=y1*trained_layer2_weights+trained_layer2_bias;
y3=s3; % linear activation function

Q1110 = y3

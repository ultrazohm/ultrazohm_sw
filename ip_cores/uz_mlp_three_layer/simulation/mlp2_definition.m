clc
clear
close all
rng(4546);
numInput=13; 
numNeurons=2^6;
numHiddenLayer=3;
numOut=4;
activation={'ReLU';'linear'};

nn=el_neural_network(); % Initializes the neural network nn as an object of type el_neural_network
nn=nn.create_nn(numNeurons,numHiddenLayer,numInput,numOut,activation); % initializes the neural network with the settings above
%nn=nn.create_nn(); % initializes the neural network with the settings above
rand_variables=randi([-3 3],nn.nvar,1)*0.321531;
%rand_varialbes=fi(rand_variables,1,18,0);
%rand_variables(rand_variables==0)=randi([2 3]);
nn=nn.set_all_parameter(rand_variables); % set every parameter, weight and bias, to one
%nn=nn.set_all_parameter(ones(nn.nvar,1)); % set every parameter, weight and bias, to one

nn_data_type_max=131071;
nn.ff([ones(1,numInput)*5]')
clear
% Fix random generator
rng(0);
RLAgenttype = 'DQN';
%% Switch Case for RL Training
switch (RLAgenttype)
    case 'DQN' 
%% Functions and Definition of all variables for Parallel Training
init_Einfachpendel_mit_Agent
%% Setting variables
n_Ts=[0.01 0.007 0.005]; % 100,200,500 Hz
Tf=5; % simtime
numep=1200; % Number of episodes to train
numag=420; % Number of agents to train parallel
minbuf=1e4; % Minimum buffer size
maxbuf=1e6; % Maximum buffer size
minlearn=1e-6;% Minimum learnrate
maxlearn=1e-2;% Maximum learnrater
mindis=0.6;% Minimum discount factor
maxdis=1;% Maximum discount factor
numhyp=6;% Number of hyperparameters
numneu=128;% Number of neurons for training network (depth 2,same number of neurons (power of 2))
mdl = 'Einfachpendel_mit_Agent';
trainingtype='random'; % 'flexible for random parameters and 'hard' for fixed hyperparameters, 'mixed' possible
%% Creating randomnumbers with lhs
[X] = randomcreate(numag,numhyp,minbuf,maxbuf,minlearn,maxlearn,mindis,maxdis,n_Ts,trainingtype);
%% initialize the environment
[obsInfo,actInfo,env]= initializeEinfachpendel(mdl);
%% initialize network
[dnn]= createDQNnetwork(obsInfo,actInfo,numneu);
%% create Agents
[agenttrain]= createDQNAgents(X,numag,dnn,obsInfo,actInfo,numep,n_Ts);
%% Set training Options
for i = 1:numag
trainingOptions(i) = rlTrainingOptions(...
        'MaxEpisodes',ceil(numep*1.25),... % Training 125% of episodes to be sure that epsilon min is reached and the agent is trained long enough
        'MaxStepsPerEpisode',ceil(Tf/agenttrain(i).AgentOptions.SampleTime),...
        'UseParallel',false,...
        'ScoreAveragingWindowLength',5,...
        'Verbose',false,...
        'Plots','none',...
        'StopTrainingCriteria','AverageReward',...
        'StopTrainingValue',100,...
        'SaveAgentCriteria','EpisodeReward',...
        'SaveAgentValue',100);
end
%% delete all simulink scopes to speed up training
all_scope_viewer = find_system(mdl,'AllBlocks','on','BlockType','Scope');
delete_block(all_scope_viewer);
%% train agents with parallel computing
[parout,agentoutput]=partrain(numag,agenttrain,env,trainingOptions);
%% sim all agents and get reward of learned policy
% supress Simscape Mechanics Editor
set_param(mdl,'SimMechanicsOpenEditorOnUpdate','off')
[cumulatedreward,rewardpersample,expout]  = simallagents(agentoutput,env,Tf);
%% simulate and check best agent policy
% enable Simscape Mechanics Editor
set_param(mdl,'SimMechanicsOpenEditorOnUpdate','on')
[ARval,ARidx,experience,bestagent] = getbestagentandsimulate(agentoutput,cumulatedreward,env);
%% visualize
visualizetraindqn(parout,agentoutput,experience,ARidx,cumulatedreward,rewardpersample,numep);

%% plot weights and bias from best agent
[layers,critic,criticNet]=plotweightsandbias(bestagent);

%% export parameters from best DQN agent into .csv files
[error_vec,folder]=exportLearnablesDQN(bestagent,layers,critic,criticNet);
%% save simulink model in folder
[name]=saveinfolder(mdl,bestagent,folder,RLAgenttype);

    case 'DDPG'
%% Functions and Definition of all variables for Parallel Training
% init_Einfachpendel_mit_Agent % init for Florians Pendulum
%% Setting variables

% note: If fixed value desired, set min to value and max to = min
% e.g. minlearn = 0.001, maxlearn = minlearn

% Time
Ts_var = false; % false: one sample time; true: varied sample time
if Ts_var == true
    n_Ts=[0.01 0.005 0.002]; % 100,200,500 Hz
else 
    n_Ts = 0.05; % 100 Hz
end
Tf=20; % simtime

% Training options
% numep=2000; % Number of episodes to train
% numag=12; % Number of agents to train parallel
numep=5; % Number of episodes to train
numag=4; % Number of agents to train parallel

% Optimizer options
minlearn_cr=1e-6;% Minimum learnrate critic
maxlearn_cr=1e-2;% Maximum learnrater critic
minlearn_ac=1e-6;% Minimum learnrate actor
maxlearn_ac=1e-2;% Maximum learnrater actor
minreg=1e-4; % Minimum L2RegularizationFactor
maxreg=1e-2; % Maximum L2RegularizationFactor
grad_thr=1; % GradientThreshold, default=inf

% Agent options
minbuf=1e4; % Minimum buffer size
maxbuf=1e5; % Maximum buffer size
bat_var = true; % true: varied Minibatch size; false: one Minibatch size
if bat_var == true
    bat=[64 128 256 512]; % varied Minibatch size
else
    bat=64; % one Minibatch size
end
mindis=0.1;% Minimum discount factor
maxdis=1;% Maximum discount factor
minupd=1; % Minimum TargetUpdateFrequency
maxupd=10; % Maximum TargetUpdateFrequency
tar_sm=1e-3;% TargetSmoothFactor, default=1e-3
mindev=0; % Minimum StandardDeviation
maxdev=1; % Maximum StandardDeviation
mindec=0; % Minimum StandardDeviationDecayRate
maxdec=1e-4; % Maximum StandardDeviationDecayRate

numhyp=8; % Number of hyperparameters that shold be varied during training

% Number of neurons for training network (depth 2, critic & actor)
numneu1=400; % first hidden layer
numneu2=300; % second hidden layer

mdl = 'rlSimplePendulumModel'; % choose Mathwork example
% mdl = 'Einfachpendel_mit_Agent'; % choose Florians Pendel
%% Creating randomnumbers with lhs
[X] = randomcreate_ddpg(numag,numhyp,n_Ts,bat,minlearn_cr,maxlearn_cr,minlearn_ac,maxlearn_ac,minreg,maxreg,minbuf,maxbuf,mindis,maxdis,mindev,maxdev,mindec,maxdec,minupd,maxupd);
%% initialize the environment
[obsInfo,actInfo,env]= initializeEinfachpendel_continuous(mdl);
%% initialize network
[criticNetwork,actorNetwork]= createDDPGnetwork(obsInfo,actInfo,numneu1,numneu2);
%% create Agents
[agenttrain]= createDDPGAgents(criticNetwork,actorNetwork,obsInfo,actInfo,X,n_Ts,bat,grad_thr,tar_sm);
%% Set training Options
for i = 1:numag
trainingOptions(i) = rlTrainingOptions(...
        'MaxEpisodes',numep,...
        'MaxStepsPerEpisode',ceil(Tf/agenttrain(i).AgentOptions.SampleTime),...
        'UseParallel',false,... % default=false
        'ScoreAveragingWindowLength',5,... % default=5
        'Verbose',false,... % default=false
        'Plots','none',... % default=training-progress
        'StopTrainingCriteria','AverageReward',...
        'StopTrainingValue',-700,...
        'SaveAgentCriteria','EpisodeReward',...
        'SaveAgentValue',-740);
end
%% delete all simulink scopes to speed up training
%all_scope_viewer = find_system(mdl,'AllBlocks','on','BlockType','Scope');
% delete_block(all_scope_viewer);
%% train agents with parallel computing
[parout,agentoutput]=partrain(numag,agenttrain,env,trainingOptions);
%% sim all agents and get reward of learned policy
% % supress Simscape Mechanics Editor
% set_param(mdl,'SimMechanicsOpenEditorOnUpdate','off')
[cumulatedreward,rewardpersample,expout]  = simallagents(agentoutput,env,Tf);
%% simulate and check best agent policy
% % enable Simscape Mechanics Editor
% set_param(mdl,'SimMechanicsOpenEditorOnUpdate','on')
[ARval,ARidx,experience,bestagent] = getbestagentandsimulate(agentoutput,cumulatedreward,env);
%% visualize
visualizetrainddpg(parout,agentoutput,experience,ARidx,cumulatedreward,rewardpersample,numep);
%% plot weights and bias from best agent
[actor,ac_layers,actorNet,critic,cr_layers,criticNet]=plotweightsandbias_ddpg(bestagent);
%% export parameters from best DDPG agent into .csv files
[error_vec,folder]=exportLearnablesDDPG(bestagent,actor,ac_layers,actorNet,critic,cr_layers,criticNet,actInfo);
%% save simulink model in folder
[name]=saveinfolder(mdl,bestagent,folder,RLAgenttype);
end
        
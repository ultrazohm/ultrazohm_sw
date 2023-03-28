clc
clear
close all


ddpg_1_2_0rpm=load('ddpg_1_2_0rpm.mat');
foc_0rpm=load('foc_0rpm.mat');

% find enable jump 0->1
ddpg_1_2_0rpm.jump_index= find(ddpg_1_2_0rpm.log.CH1, 1, 'first');
ddpg_1_2_0rpm.jump_index=ddpg_1_2_0rpm.jump_index-200; % keep 10 values before jump

foc_0rpm.jump_index= find(foc_0rpm.log.CH1, 1, 'first');
foc_0rpm.jump_index=foc_0rpm.jump_index-200; % keep 10 values before jump

ddpg_1_2_0rpm.t     =ddpg_1_2_0rpm.log.time(ddpg_1_2_0rpm.jump_index:end);
ddpg_1_2_0rpm.id_set=ddpg_1_2_0rpm.log.CH19(ddpg_1_2_0rpm.jump_index:end);
ddpg_1_2_0rpm.iq_set=ddpg_1_2_0rpm.log.CH20(ddpg_1_2_0rpm.jump_index:end);
ddpg_1_2_0rpm.iq    =ddpg_1_2_0rpm.log.CH7(ddpg_1_2_0rpm.jump_index:end);
ddpg_1_2_0rpm.id    =ddpg_1_2_0rpm.log.CH6(ddpg_1_2_0rpm.jump_index:end);
ddpg_1_2_0rpm.enable=ddpg_1_2_0rpm.log.CH1(ddpg_1_2_0rpm.jump_index:end);
ddpg_1_2_0rpm.t=ddpg_1_2_0rpm.t-ddpg_1_2_0rpm.t(1); % start time at 0s


foc_0rpm.t      =foc_0rpm.log.time(foc_0rpm.jump_index:end);
foc_0rpm.id_set =foc_0rpm.log.CH19(foc_0rpm.jump_index:end);
foc_0rpm.iq_set =foc_0rpm.log.CH20(foc_0rpm.jump_index:end);
foc_0rpm.id     =foc_0rpm.log.CH6(foc_0rpm.jump_index:end);
foc_0rpm.iq     =foc_0rpm.log.CH7(foc_0rpm.jump_index:end);
foc_0rpm.enable =foc_0rpm.log.CH1(foc_0rpm.jump_index:end);
foc_0rpm.t=foc_0rpm.t-foc_0rpm.t(1);





%%
figure
subplot(2,1,1)
plot(ddpg_1_2_0rpm.t,ddpg_1_2_0rpm.id);
hold on
plot(foc_0rpm.t,foc_0rpm.id);
grid minor
plot(ddpg_1_2_0rpm.t,ddpg_1_2_0rpm.id_set,'b--');
plot(foc_0rpm.t,foc_0rpm.id_set,'r--');
xlim([0 0.7]);

subplot(2,1,2)
plot(ddpg_1_2_0rpm.t,ddpg_1_2_0rpm.iq);
hold on
plot(foc_0rpm.t,foc_0rpm.iq);
grid minor
plot(ddpg_1_2_0rpm.t,ddpg_1_2_0rpm.iq_set,'--');
xlim([0 0.7]);













NN_IP_30us_before=load('NN_IP_30us_before.mat').log;
NN_IP_20us_before=load('NN_IP_20us_before.mat').log;
NN_IP_15us_before=load('NN_IP_15us_before.mat').log;
NN_IP_30us_after=load('NN_IP_30us_after.mat').log;
NN_IP_20us_after=load('NN_IP_20us_after.mat').log;
NN_IP_15us_after=load('NN_IP_15us_after.mat').log;
NN_SW_normal=load('NN_SW_normal.mat').log;

changes_IP_30us_before = find(diff(NN_IP_30us_before.start_marker))+1;
changes_IP_20us_before = find(diff(NN_IP_20us_before.start_marker))+1;
changes_IP_15us_before = find(diff(NN_IP_15us_before.start_marker))+1;
changes_IP_30us_after = find(diff(NN_IP_30us_after.start_marker))+1;
changes_IP_20us_after = find(diff(NN_IP_20us_after.start_marker))+1;
changes_IP_15us_after = find(diff(NN_IP_15us_after.start_marker))+1;
changes_SW_normal = find(diff(NN_SW_normal.start_marker))+1;

for k=1:3
IP_30us_before_array{k} = NN_IP_30us_before(changes_IP_30us_before(2*k-1):changes_IP_30us_before(2*k),:);
IP_30us_before_array{k}.time = IP_30us_before_array{k}.time - IP_30us_before_array{k}.time(1); 
IP_20us_before_array{k} = NN_IP_20us_before(changes_IP_20us_before(2*k-1):changes_IP_20us_before(2*k),:);
IP_20us_before_array{k}.time = IP_20us_before_array{k}.time - IP_20us_before_array{k}.time(1); 
IP_15us_before_array{k} = NN_IP_15us_before(changes_IP_15us_before(2*k-1):changes_IP_15us_before(2*k),:);
IP_15us_before_array{k}.time = IP_15us_before_array{k}.time - IP_15us_before_array{k}.time(1); 
IP_30us_after_array{k} = NN_IP_30us_after(changes_IP_30us_after(2*k-1):changes_IP_30us_after(2*k),:);
IP_30us_after_array{k}.time = IP_30us_after_array{k}.time - IP_30us_after_array{k}.time(1); 
IP_20us_after_array{k} = NN_IP_20us_after(changes_IP_20us_after(2*k-1):changes_IP_20us_after(2*k),:);
IP_20us_after_array{k}.time = IP_20us_after_array{k}.time - IP_20us_after_array{k}.time(1);
IP_15us_after_array{k} = NN_IP_15us_after(changes_IP_15us_after(2*k-1):changes_IP_15us_after(2*k),:);
IP_15us_after_array{k}.time = IP_15us_after_array{k}.time - IP_15us_after_array{k}.time(1); 
SW_normal{k} = NN_SW_normal(changes_SW_normal(2*k-1):changes_SW_normal(2*k),:);
SW_normal{k}.time = SW_normal{k}.time - SW_normal{k}.time(1); 
end

%% Plots
sgtitle('Varianz zwischen verschiedenen Runs (30us before)')
subplot(2,2,1)
plot(IP_30us_before_array{1}.time,IP_30us_before_array{1}.id)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.id)
plot(IP_30us_before_array{3}.time,IP_30us_before_array{3}.id)
title('i_d')
subplot(2,2,2)
plot(IP_30us_before_array{1}.time,IP_30us_before_array{1}.iq)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.iq)
plot(IP_30us_before_array{3}.time,IP_30us_before_array{3}.iq)
title('i_q')
subplot(2,2,3)
plot(IP_30us_before_array{1}.time,IP_30us_before_array{1}.iX)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.iX)
plot(IP_30us_before_array{3}.time,IP_30us_before_array{3}.iX)
title('i_x')
subplot(2,2,4)
plot(IP_30us_before_array{1}.time,IP_30us_before_array{1}.iY)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.iY)
plot(IP_30us_before_array{3}.time,IP_30us_before_array{3}.iY)
title('i_y')
legend('Run1','Run2','Run3')

figure
sgtitle('Varianz IP(30us before/after) und SW')
subplot(2,2,1)
plot(SW_normal{1}.time,SW_normal{1}.id)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.id)
plot(IP_30us_after_array{3}.time,IP_30us_after_array{3}.id)
title('i_d')
subplot(2,2,2)
plot(SW_normal{1}.time,SW_normal{1}.iq)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.iq)
plot(IP_30us_after_array{3}.time,IP_30us_after_array{3}.iq)
title('i_q')
subplot(2,2,3)
plot(SW_normal{1}.time,SW_normal{1}.iX)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.iX)
plot(IP_30us_after_array{3}.time,IP_30us_after_array{3}.iX)
title('i_x')
subplot(2,2,4)
plot(SW_normal{1}.time,SW_normal{1}.iY)
hold on
plot(IP_30us_before_array{2}.time,IP_30us_before_array{2}.iY)
plot(IP_30us_after_array{3}.time,IP_30us_after_array{3}.iY)
title('i_y')
legend('SW','IP-30us-before','IP-30us-after')

figure
sgtitle('Varianz zwischen verschiedenen Runs (SW)')
subplot(2,2,1)
plot(SW_normal{1}.time,SW_normal{1}.id)
hold on
plot(SW_normal{2}.time,SW_normal{2}.id)
plot(SW_normal{3}.time,SW_normal{3}.id)
title('i_d')
subplot(2,2,2)
plot(SW_normal{1}.time,SW_normal{1}.iq)
hold on
plot(SW_normal{2}.time,SW_normal{2}.iq)
plot(SW_normal{3}.time,SW_normal{3}.iq)
title('i_q')
subplot(2,2,3)
plot(SW_normal{1}.time,SW_normal{1}.iX)
hold on
plot(SW_normal{2}.time,SW_normal{2}.iX)
plot(SW_normal{3}.time,SW_normal{3}.iX)
title('i_x')
subplot(2,2,4)
plot(SW_normal{1}.time,SW_normal{1}.iY)
hold on
plot(SW_normal{2}.time,SW_normal{2}.iY)
plot(SW_normal{3}.time,SW_normal{3}.iY)
title('i_y')
legend('Run1','Run2','Run3')
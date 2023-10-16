input=load('pt1_dqn_input.csv');
error=load('pt1_dqn_error.csv');
output=load('pt1_dqn_output.csv');


figure
subplot(3,1,1)
plot(input(:,end));
title('input');

subplot(3,1,2)
plot(error(:,end));
title('error');

subplot(3,1,3)
plot(output(:,end));
title('output');
%% Plot FPGA version
%
% 1: time
% 2: i_q
% 3: i_d
% 4: u_d
measurements_1=readmatrix('pmsm_step_response.csv');
measurements_2=readmatrix('pmsm_step_response_one_glitch.csv');
measurements_3=readmatrix('pmsm_step_response_one_glitch2.csv');
%%
close all
adjust_measurements(measurements_1);
adjust_measurements(measurements_2);
adjust_measurements(measurements_3);

function adjust_measurements(measurements)
figure(1)
subplot(2,1,1)
grid on
hold on
first_nonzero=find(measurements(:,4),1,'first');
time_offset=measurements(first_nonzero,1)-0.2;
measurements(:,1)=measurements(:,1)-time_offset;
%plot(measurements(first_nonzero-1:end,1), measurements(first_nonzero-1:end,4) ); % u_d input
plot(measurements(first_nonzero-1:end,1), measurements(first_nonzero-1:end,3),'LineWidth',2); % i_d
xlim([0.2 0.3]);

subplot(2,1,2)
grid on
hold on
%plot(measurements(first_nonzero-1:end,1), -measurements(first_nonzero-1:end,4) ); % u_q input
plot(measurements(first_nonzero-1:end,1), measurements(first_nonzero-1:end,2),'LineWidth',2); % i_q
xlim([0.2 0.3]);

end
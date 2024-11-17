clc
clear
close all
log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/ld_jump_phase_b_brose.parquet');

figure
plot(log.time,log.dut_ia);
hold on
plot(log.time,log.dut_ib);
plot(log.time,log.dut_ic);
plot(log.time,log.dut_vq);
plot(log.time,log.dut_vd);
legend('ia','ib','ic','vq','vd')

start_time=14.1437;
end_time=start_time+1;

% Assuming time-domain data: t (time vector), dut_vd (voltage), dut_ia (current)
log=log(log.time>start_time,:);
log=log(log.time<end_time,:);
t=log.time-log.time(1);
dut_vd=log.dut_vd;
dut_ia=log.dut_ib;

figure
plot(t,dut_vd);
hold on
plot(t,dut_ia);
% Assuming time-domain data: t (time vector), dut_vd (voltage), dut_ia (current)
% Assuming time-domain data: t (time vector), dut_vd (voltage step input), dut_ia (current response)

% Step 1: Define the input step voltage, assuming it's approximately constant
V_step = mean(dut_vd);  % Step input voltage, can be averaged if constant

% Step 2: Define the RL circuit model as a function
% Model for current response: I(t) = (V_step / R) * (1 - exp(- (R / L) * t))

rl_current_model = @(R, L, t) (V_step / R) * (1 - exp(- (R / L) * t));

% Step 3: Define the objective function for fminsearch
% The objective is the sum of squared errors between the model and measured current
objective_func = @(params) sum((dut_ia - rl_current_model(params(1), params(2), t)).^2);

% Step 4: Set initial guesses for R and L
initial_guess = [0.0001, 0.0001];  % Rough initial guesses for R and L

% Step 5: Use fminsearch to minimize the objective function
% options = optimset('MaxIter', 1000, 'TolX', 1e-8, 'TolFun', 1e-8, 'Display', 'iter');  % Set options for more iterations
[optimal_params, fval] = fminsearch(objective_func, initial_guess);

% Extract fitted parameters R and L
R = optimal_params(1);
L = optimal_params(2);

% Display the fitted values
fprintf('Fitted Parameters:\n');
fprintf('Resistance (R): %.8f Ohms\n', R);
fprintf('Inductance (L): %.8f H\n', L);

% Step 6: Plot the results to see the fit
figure;
plot(t, dut_ia, 'b.', 'DisplayName', 'Measured Current');
hold on;
plot(t, rl_current_model(R, L, t), 'r-', 'DisplayName', 'Fitted Model');
xlabel('Time (s)');
ylabel('Current (A)');
legend;
title('RL Circuit Step Response Fit Using fminsearch');
grid on;




R_1=2.1;
L_d=50e-3;
L_q=50e-3;
psi_pm=0.05;
polepair=2;
ts=1/1e6;

ts_regler=1/20e3;

tau_d=L_d/R_1;
tau_q=L_q/R_1;
tau_sum=2*ts_regler;

% Parallel PID
k_p_d=L_d/(2*tau_sum);
k_p_q=L_q/(2*tau_sum);
k_i_d=R_1/(2*tau_sum);
k_i_q=R_1/(2*tau_sum);

            
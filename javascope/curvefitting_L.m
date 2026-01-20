xdata=table2array(log(15354:16000,1));
ydata=table2array(log(15354:16000,10));
xdata = xdata-1.5353;
modelFun = @(p,t) (1.08/p(1))*(1-exp(-(p(1)/p(2))*t));
p0=[0.1,0.1];
lb = [];
ub = [];
p_est = lsqcurvefit(modelFun, p0, xdata, ydata, lb, ub);
figure;hold on; grid on;
plot(table2array(log(15300:16000,1))-1.5300, table2array(log(15300:16000,10)), '-','LineWidth',1.5)
plot(xdata+0.0054, modelFun(p_est, xdata), '-','LineWidth',1.5)
legend('i_x', 'Fit')

% writetable(table(table2array(log(15300:16000,1))-1.5300, table2array(log(15300:16000,8)), 'VariableNames', {'time', 'value'}), 'sprung_alpha.csv');
% writetable(table(xdata+0.0054, modelFun(p_est, xdata), 'VariableNames', {'time', 'value'}), 'fit_alpha.csv');
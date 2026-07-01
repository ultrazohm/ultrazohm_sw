% Testskript fuer kubische Soft-Sign-Funktion aus uz_VoltageCompensation.c
clear; clc; close all;

threshold_A = 2.0;              % wie self->config.threshold_current
i_A = linspace(-3*threshold_A, 3*threshold_A, 2001);

% Kubische Soft-Sign: f(x) = 1.5*x - 0.5*x^3 fuer |x|<1, sonst +/-1
soft = arrayfun(@(i) soft_sign_cubic(i, threshold_A), i_A);

% Vergleich: harte Sign-Funktion mit Schwellwert
hard = zeros(size(i_A));
hard(i_A >= threshold_A) = 1;
hard(i_A <= -threshold_A) = -1;

figure('Color','w');
plot(i_A, soft, 'b', 'LineWidth', 2); hold on;
plot(i_A, hard, '--r', 'LineWidth', 1.5);
xline( threshold_A, ':k', 'LineWidth', 1);
xline(-threshold_A, ':k', 'LineWidth', 1);
yline(0, ':k');
grid on;
xlabel('Strom i [A]');
ylabel('Vorzeichenfaktor');
title('Kubische Soft-Sign vs. harte Sign-Funktion');
legend('soft-sign kubisch','hard-sign mit threshold','Location','SouthEast');

% Beispielwerte ausgeben
probe = [-1.5 -1.0 -0.5 0 0.5 1.0 1.5] * threshold_A;
vals = arrayfun(@(i) soft_sign_cubic(i, threshold_A), probe);
T = table(probe(:), vals(:), 'VariableNames', {'i_A','soft_sign'});
disp(T);

function y = soft_sign_cubic(value, threshold)
    abs_threshold = abs(threshold);
    if abs_threshold <= 0
        y = sign(value);
        return;
    end

    x = value / abs_threshold;
    if x >= 1
        y = 1;
    elseif x <= -1
        y = -1;
    else
        y = 1.5*x - 0.5*x^3;
    end
end

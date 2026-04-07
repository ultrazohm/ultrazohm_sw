load("log.mat");

figure();
plot_log(spwm, 1, [20 30], "SPWM");
plot_log(svm, 2, [50 80], "SVM");



function plot_log(data, first_subplot, x_axis, title_in)
    subplot(3,2,first_subplot);
    plot_set;
    plot(data.time, data.speed);
    ylim([500 680]);
    ylabel("speed (rpm)");
    legend("n_{mech}");
    yticks(500:20:680);
    xlim(x_axis);
    legend('Location','northwest')
    title(title_in);

    subplot(3,2,first_subplot+2);
    plot_set;
    plot(data.time, data.lim);
    ylim([0 1.1]);
    yticks([0 1]);
    xlim(x_axis);
    legend("limited");
    legend('Location','northwest')

    subplot(3,2,first_subplot+4);
    plot_set;
    plot(data.time, data.id);
    plot(data.time, data.iq);
    ylim([-0.7 0.7]);
    ylabel("current (A)");
    legend("i_d", "i_q");
    xlim(x_axis);
    legend('Location','northwest')
    xlabel("time (s)");
end

function plot_set
    hold on;
    grid on;
end
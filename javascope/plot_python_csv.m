% Read the CSV file
data = csvread('i_d_i_q_data3000.csv', 1, 0); % Assuming the data starts from the second row

% Extract columns
originalTime = data(:, 1);
i_d = data(:, 2);
i_q = data(:, 3);
i_d_ref = data(:, 4);  % Renamed ref_i_d to i_d_ref
i_q_ref = data(:, 5);  % Renamed ref_i_q to i_q_ref

% Convert time to seconds
originalTimeInSeconds = originalTime; % Assuming the time values are in seconds with a step of 0.0001 seconds

% Set the paper size to match the plot size in centimeters
figure

plot(originalTimeInSeconds, i_d, 'Color', '#0072BD', 'LineWidth', 0.7);
hold on;
plot(originalTimeInSeconds, i_q, 'Color', '#D95319', 'LineWidth', 0.7);
plot(originalTimeInSeconds, i_d_ref, 'Color', '#0072BD', 'LineWidth', 0.7, 'LineStyle', ':'); % Dashed line for i_d_ref
plot(originalTimeInSeconds, i_q_ref, 'Color', '#D95319', 'LineWidth', 0.7, 'LineStyle', ':'); % Dashed line for i_q_ref

%title('n = 0 min $^{-1}$', 'Interpreter', 'latex', 'FontName', 'Times New Roman');
xlabel('Zeit  in s', 'FontName', 'Times New Roman'); % Time in seconds
ylabel('Strom in A', 'FontName', 'Times New Roman'); % Current in amperes

% Legend with horizontal orientation and smaller font size
%legend('$i_{d}$', '$i_{q}$', '$i_{dref}$', '$i_{qref}$', 'Interpreter', 'latex', 'FontName', 'Times New Roman', 'Orientation', 'horizontal', 'FontSize', 12);

grid on;

% Set x-axis ticks every 0.002 seconds
xtickangle(90);
xticks(0:0.02:0.21);
set(gca, 'XTickLabel', get(gca, 'XTick'), 'FontName', 'Times New Roman');
xlim([0, 0.21]);
ylim([-5, 5]);
yticks(-5:1:5);

% Set y-axis ticks font
set(gca, 'YTickLabel', get(gca, 'YTick'), 'FontName', 'Times New Roman');

hold off;

% Export the figure to a PDF with 8 cm width
fig = gcf;
fig.PaperUnits = 'centimeters';
fig.PaperPosition = [-.23, .05, 9, 7]; % Width and height in centimeters
print('python3000min.pdf', '-dpdf', '-r300'); % Specify the resolution if needed

% cut 0 230 130 0

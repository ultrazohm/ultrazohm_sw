filename = 'DPT_10A_60A_T25_125_R47.xlsx';  % Replace with your Excel file name
sheetname = 'TEST_10A_to_60A_25°';    % Replace with the name of the sheet you want to read from

% Use readtable to read data from the specific sheet
data = readtable(filename, 'Sheet', sheetname); 

% Extract the relevant columns
I = data{:, 1};      % Assuming 'I' is in the first column
Esw = data{:, 4};    % Assuming 'Esw' is in the fourth column

% Plotting I vs Esw
figure;
plot(I, Esw, '-o', 'LineWidth', 2, 'MarkerSize', 8);

% Adding labels and title
xlabel('Current I (Amp)', 'FontSize', 12);
ylabel('Switching Energy Esw (μJ)', 'FontSize', 12);
title('Switching Energy vs Current', 'FontSize', 14);

% Grid on for better visualization
grid on;

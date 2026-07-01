%% Init parameters
clc
clear
close all

uz_pmsm_model_init_parameter;

% Adjust simulation settings
simulate_mechanical = false;
simulate_open_loop = true;
setpoint_step = 10.0;

%% Run simulation once
mdl = 'uz_pmsm_model';
out = sim(mdl);

%% Convert all logged Simulink signals to one table

logs = out.logsout;
time = logs{1}.Values.Time(:);
result_table = table(time);

for k = 1:logs.numElements
    ts = logs{k}.Values;
    signal_name = string(logs{k}.Name);

    if strlength(signal_name) == 0
        signal_name = "signal_" + k;
    end

    signal_name = matlab.lang.makeValidName(signal_name);
    signal_name = matlab.lang.makeUniqueStrings(signal_name, result_table.Properties.VariableNames);

    signal_time = ts.Time(:);
    data = squeeze(ts.Data);
    data = data(:);

    if numel(data) ~= numel(signal_time)
        error("Signal '%s' is not scalar. Extend export_csv.m before exporting vector signals.", signal_name);
    end

    if ~isequal(signal_time, time)
        data = interp1(signal_time, data, time, 'previous', 'extrap');
    end

    result_table.(char(signal_name)) = data;
end

%% Export
csv_name = 'uz_pmsm_model_simulation_results.csv';
parquet_name = 'uz_pmsm_model_simulation_results.parquet';

writetable(result_table, csv_name);
parquetwrite(parquet_name, result_table);

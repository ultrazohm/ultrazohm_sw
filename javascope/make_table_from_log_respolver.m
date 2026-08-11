function T = make_table_from_log_resolver(log)
    file_name = "Log_2026-08-07_09-34-21";

    opts = detectImportOptions(file_name);
opts.VariableNamesLine = 1;
opts = setvartype(opts, 'double');
    log = readtable(file_name, opts);
    % removes not valid data and groups each variable by operatingpoints
    % log=log(log.CH16__50_data_valid_rc_meas==true,:); % sortiert alle Werte aus, bei denen data valid= 0
    % T=groupsummary(log,'CH20__52_op_rc_meas','mean'); % mittelt über die Betriebspunkte
    % T=removevars(T, "GroupCount"); % entfernt eine unnötige variable
    % Hier müssen die Variablen nach TIme die Reihenfolge wie im javascope
    % haben. Wichtig: die Variable operating points wird im zweiten Schritt
    % beim mitteln schon vor gezogen, fällt also hinten dann weg
    names = ["operating_points","Time","DUT_ia","DUT_ib","DUT_ic","DUT_id","DUT_iq","DUT_id_ref","DUT_iq_ref","DUT_vd","DUT_vq","DUT_vd_ref","DUT_vq_ref","DUT_speed","LM_speed_ref","DUT_torque","DUT_avg_temp","rc_meas_data_valid", "rc_meas_iq_ref","rc_meas_id_ref","rc_meas_n_ref"];
    T.Properties.VariableNames=names; 

end
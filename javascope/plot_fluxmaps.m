clear all;
data = readtable('Log_2025-05-22_18-40-41.csv');
table = make_table_from_log(data);
Rs = 0.51;  % Statorwiderstand in Ohm

meas_n_ref = unique(table.rc_meas_n_ref);

for i = 1:length(meas_n_ref)
    n_ref_temp = meas_n_ref(i);

    data = table(table.rc_meas_n_ref == n_ref_temp, :);

    u_d = data.DUT_vd;
    u_q = data.DUT_vq;
    i_d = data.DUT_id;
    i_q = data.DUT_iq;

    n_rpm = data.rc_meas_n_ref;  % Drehzahl in U/min
    omega = 2 * pi * n_rpm / 60;
    
    % === Flussverkettung berechnen ===
    psi_d = (u_q - Rs .* i_q) ./ omega;
    psi_q = -(u_d - Rs .* i_d) ./ omega;
    psi_abs = sqrt(psi_d.^2 + psi_q.^2);
    
    
    % % Schritt 1: Gitterpunkte definieren
    i_d_lin = linspace(min(i_d), max(i_d), 500);  % z.B. 100 Punkte
    i_q_lin = linspace(min(i_q), max(i_q), 500);
    [i_d_grid, i_q_grid] = meshgrid(i_d_lin, i_q_lin);
    
    psi_q_grid = griddata(i_d, i_q, psi_q, i_d_grid, i_q_grid);
    figure;
    mesh(i_d_grid, i_q_grid, psi_q_grid)
    shading interp   % Glatte Farbverläufe
    colorbar
    xlabel('i_d [A]')
    ylabel('i_q [A]')
    zlabel('\psi_q [Vs]')
    title(['Flussverkettung \psi_q für ',num2str(n_ref_temp),' rpm'])
    
    psi_d_grid = griddata(i_q, i_d, psi_d, i_q_grid, i_d_grid, 'natural');
    figure;
    mesh(i_q_grid, i_d_grid, psi_d_grid)
    shading flat   % Glatte Farbverläufe
    colorbar
    xlabel('i_q [A]')
    ylabel('i_d [A]')
    zlabel('\psi_d [Vs]')
    title(['Flussverkettung \psi_d für ',num2str(n_ref_temp),' rpm'])
end




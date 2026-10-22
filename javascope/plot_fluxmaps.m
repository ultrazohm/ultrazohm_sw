clear all;
data = readtable('Log_2025-06-03_17-04-51.csv');
table = make_table_from_log(data);
Rs = 1;  % Statorwiderstand in Ohm

meas_n_ref = unique(table.rc_meas_n_ref);

%% Flux Maps
for i = 1:length(meas_n_ref)

    n_ref_temp = meas_n_ref(i);
    data = table(table.rc_meas_n_ref == n_ref_temp, :);

    u_d = data.DUT_vd_ref;
    u_q = data.DUT_vq_ref;
    i_d = data.DUT_id;
    i_q = data.DUT_iq;

    n_rpm = data.rc_meas_n_ref;  % Drehzahl in U/min
    omega = 2 * pi * n_rpm * 4 / 60;    %für elektrische Drehfrequenz Polpaarzahl beachten
    
    % === Flussverkettung berechnen ===
    psi_d = (u_q - Rs * i_q) ./ omega;
    psi_q = (-(u_d - Rs * i_d)) ./ (omega);
    % psi_abs = sqrt(psi_d.^2 + psi_q.^2);
    
    % % Schritt 1: Gitterpunkte definieren
    i_d_lin = linspace(min(i_d), max(i_d), 100);  
    i_q_lin = linspace(min(i_q), max(i_q), 100);

    [i_d_grid, i_q_grid] = meshgrid(i_d_lin, i_q_lin);   
    psi_q_grid = griddata(i_q, i_d, psi_q, i_q_grid, i_d_grid);
    figure;
    mesh(i_q_grid, i_d_grid, psi_q_grid)
    shading faceted   % Glatte Farbverläufe
    colormap winter
    % colorbar
    xlabel('i_q in A')
    ylabel('i_d in A')
    zlabel('\psi_q in Vs')
    title(['Flux linkage \psi_s^q for ',num2str(n_ref_temp),' rpm'])
    % csv = [i_d(:), i_q(:), psi_q(:)];
    % filename = sprintf('psi_q_%d.csv',n_ref_temp);
    % writematrix(csv, filename);

    [i_d_grid, i_q_grid] = meshgrid(i_d_lin, i_q_lin);
    psi_d_grid = griddata(i_d, i_q, psi_d, i_d_grid, i_q_grid);
    figure;
    mesh(i_d_grid, i_q_grid, psi_d_grid)
    shading faceted   % Glatte Farbverläufe
    colormap winter
    % % colorbar
    xlabel('i_d in A')
    ylabel('i_q in A')
    zlabel('\psi_d in Vs')
    title(['Flux linkage \psi_s^d for ',num2str(n_ref_temp),' rpm'])
    % csv = [i_d(:), i_q(:), psi_d(:)];
    % filename = sprintf('psi_d_%d.csv',n_ref_temp);
    % writematrix(csv, filename);

    % Psi_q und Psi_d in einem Diagramm
    % figure;
    % mesh(i_q_grid, i_d_grid, psi_q_grid)
    % hold on;
    % mesh(i_q_grid, i_d_grid, psi_d_grid)
    % xlabel('i_d in A')
    % ylabel('i_q in A')
    % zlabel('\psi_d and \psi_q in Vs')
    % title(['Flux linkage \psi_s^d and \psi_q for ',num2str(n_ref_temp),' rpm'])

end

%% Differnetial Inductances
for e = 1:length(meas_n_ref)

    % für die Korrekte Darstellung von Lqd müssen für einen Wert von Iq die
    % passenden von Id herausgefiltert werden. Sonst funktioniert die
    % Berechnung des delta i nicht
    n_ref_temp = meas_n_ref(i);
    data = table(table.rc_meas_n_ref == n_ref_temp, :);

    i_d = data.DUT_id;
    i_q = data.DUT_iq;
    u_d = data.DUT_vd_ref;
    u_q = data.DUT_vq_ref;

    % --- Initialisierung für Differenzierung ---
    n = length(i_d);
    Ldd = NaN(n,1);
    Ldq = NaN(n,1);
    Lqd = NaN(n,1);
    Lqq = NaN(n,1);
    
    n_rpm = data.rc_meas_n_ref;  % Drehzahl in U/min
    omega = 2 * pi * n_rpm *4 / 60;
    
    % === Flussverkettung berechnen ===
    psi_d = (u_q - Rs * i_q) ./ omega;
    psi_q = (-(u_d - Rs * i_d)) ./ (omega);

    
    for k = 2:n-1
        did = i_d(k+1) - i_d(k-1);
        diq = i_q(k+1) - i_q(k-1);
        % did = mean(unique(i_d));
        % diq = mean(unique(i_q));

        % Prüfen, ob id oder iq über den Index konstant ist, sonst überspringen
        if did ~= 0
            Ldd(k) = (psi_d(k+1) - psi_d(k-1)) / did;
            Lqd(k) = (psi_q(k+1) - psi_q(k-1)) / did;
        end
        if diq ~= 0
            Ldq(k) = (psi_d(k+1) - psi_d(k-1)) / diq;
            Lqq(k) = (psi_q(k+1) - psi_q(k-1)) / diq;
        end
    end

    % --- Gitter erzeugen für Interpolation ---
    id_grid = linspace(min(i_d), max(i_d), 500);
    iq_grid = linspace(min(i_q), max(i_q), 500);
    [ID, IQ] = meshgrid(id_grid, iq_grid);
    
    % --- Interpolation der Induktivitäten auf das Gitter ---
    Ldd_grid = griddata(i_d, i_q, Ldd, ID, IQ, 'natural');
    Ldq_grid = griddata(i_d, i_q, Ldq, ID, IQ, 'natural');
    Lqd_grid = griddata(i_d, i_q, Lqd, ID, IQ, 'natural');
    Lqq_grid = griddata(i_d, i_q, Lqq, ID, IQ, 'natural');
    
    % --- Flächenplots ---
    figure;
    subplot(2,2,1);
    mesh(ID, IQ, Ldd_grid); 
    shading faceted   % Glatte Farbverläufe
    colormap winter
    title('L_{dd}'); xlabel('i_d [A]'); ylabel('i_q [A]'); zlabel('L [H]');
     view(45,30); 
    
    subplot(2,2,2);
    mesh(ID, IQ, Ldq_grid); 
    shading faceted   % Glatte Farbverläufe
    colormap winter
    title('L_{dq}'); xlabel('i_d [A]'); ylabel('i_q [A]'); zlabel('L [H]');
     view(45,30); 
    
    subplot(2,2,3);
    mesh(ID, IQ, Lqd_grid, 'EdgeColor', 'none'); 
    shading faceted   % Glatte Farbverläufe
    colormap winter
    title('L_{qd}'); xlabel('i_d [A]'); ylabel('i_q [A]'); zlabel('L [H]');
    view(45,30);
    
    subplot(2,2,4);
    mesh(ID, IQ, Lqq_grid, 'EdgeColor', 'none'); 
    shading faceted   % Glatte Farbverläufe
    colormap winter
    title('L_{qq}'); xlabel('i_d [A]'); ylabel('i_q [A]'); zlabel('L [H]');
    view(45,30); 
    
    sgtitle('Interpolierte Differentielle Induktivitäten');
end


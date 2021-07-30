%% Init parameters
clc
clear
close all
set(0,'defaulttextinterpreter','latex')
plot_figures=false;


uz_pmsm_model_init_parameter;
% Adjust simulation settings
simulate_mechanical=true;
simulate_open_loop=true;
setpoint_step=10.0;

if simulate_open_loop==true
measruement_csv_name='open_loop_measruement.csv';
else
    measruement_csv_name='closed_loop_measruement.csv';
end


%
mdl='uz_pmsm_model';
out=sim(mdl);

%% Plot Simulink
%                         Name                   BlockPath
%                         _____________________  ____________________________________
%    1  [1x1 Signal]      u_d                    uz_pmsm_model/Data Type Conversion
%    2  [1x1 Signal]      u_q                    uz_pmsm_model/Data Type Conversion1
%    3  [1x1 Signal]      i_q_soll               uz_pmsm_model/Data Type Conversion10
%    4  [1x1 Signal]      load_torque            uz_pmsm_model/Data Type Conversion15
%    5  [1x1 Signal]      torque_hdl             uz_pmsm_model/Data Type Conversion5
%    6  [1x1 Signal]      i_d_hdl                uz_pmsm_model/Data Type Conversion6
%    7  [1x1 Signal]      i_q_hdl                uz_pmsm_model/Data Type Conversion7
%    8  [1x1 Signal]      omega_mech_output_hdl  uz_pmsm_model/Data Type Conversion8
%    9  [1x1 Signal]      i_d_soll               uz_pmsm_model/Data Type Conversion9
%   10  [1x1 Signal]      ''                     uz_pmsm_model/PID Controller
%   11  [1x1 Signal]      ''                     uz_pmsm_model/PID Controller1
%   12  [1x1 Signal]      iq_regler              uz_pmsm_model/Rate Transition11
%   13  [1x1 Signal]      id_regler              uz_pmsm_model/Rate Transition12
%   14  [1x1 Signal]      u_q_input              uz_pmsm_model/Step1
%   15  [1x1 Signal]      i_d                    uz_pmsm_model/uz_pmsm_model/pmsm
sim.ud=out.logsout{1}.Values.Data;
sim.uq=out.logsout{2}.Values.Data;
sim.id=out.logsout{6}.Values.Data;
sim.iq=out.logsout{7}.Values.Data;
sim.speed=out.logsout{8}.Values.Data;
sim.time=out.logsout{8}.Values.Time-0.00005; % Some magic number adjustments to align the steps
sim.time=sim.time*1e3-199.8;
sim.id_soll=out.logsout{9}.Values.Data;
% There are two 'times' since one is 2 MHz and one is 20 kHz
sim.id_soll_time=out.logsout{9}.Values.Time*1e3-199.8; % Scale time to ms and move to one time step before set-point step happens
sim.iq_soll=out.logsout{3}.Values.Data;

%% Plot FPGA version
%
% 1: time
% 2: i_q
% 3: i_d
% 4: speed
% 5: ud
measurements=readmatrix(measruement_csv_name);
first_nonzero=find(measurements(:,5),1,'first'); % Finds first nonzero in set-point to adjust time between measruement and simulation
time_offset=measurements(first_nonzero,1)-0.2;
measurements(:,1)=measurements(:,1)-time_offset;
measurment.id=measurements(first_nonzero:end,3);
measurment.iq=measurements(first_nonzero:end,2);
measurment.time=measurements(first_nonzero:end,1)*1e3-199.8; % Scale time to ms and move to one time step before set-point step happens
measurment.sollwert=measurements(first_nonzero:end,5);
measurment.speed=measurements(first_nonzero:end,4);

%% Matlab2Tikz options

if plot_figures
    extraaxisoptions = ['y tick label style={/pgf/number format/.cd, fixed,precision=2}'...
        ,',ylabel style={yshift=-0.2cm,font=\small}'...
        ,',xlabel style={font=\small}'...
        ];
    PPI = 600;
end
%% Compare for OPTIM Paper
close all
figure
grid on
hold on
box on
stairs(sim.id_soll_time,sim.id_soll,'Color', [0 127/255 0]); % u_d input
plot(measurment.time, measurment.id,'rx'); % i_d
plot(sim.time,sim.id,'b'); % i_d

xlabel('Time (ms)');
%ylabel('Current (A)');
xlim([0.15 1.5]);
ylim([-1.2 0]);
title('')

if plot_figures
    cleanfigure('targetResolution',300);
    matlab2tikz('id_step.tikz','showInfo', false,   ...
        'width', '\fwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);
end

figure
grid on
hold on
box on
stairs(sim.id_soll_time,sim.iq_soll,'Color', [0 127/255 0]); % u_d input
plot(sim.time,sim.iq,'b'); % i_d
plot(measurment.time, measurment.iq,'rx'); % i_d
xlabel('Time (ms)');
%ylabel('Current (A)');
xlim([0.15 1.5]);
ylim([-0.001 1.2]);
title('')

if plot_figures
    cleanfigure('targetResolution',600);
    matlab2tikz('iq_step.tikz','showInfo', false,  ...
        'width', '\fwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);
end
% calculate error
sim_id=timeseries(sim.id,sim.time);
meas_id=timeseries(measurment.id,measurment.time);
[sim_id,meas_id]=synchronize(sim_id,meas_id,'union');

sim_iq=timeseries(sim.iq,sim.time);
meas_iq=timeseries(measurment.iq,measurment.time);
[sim_iq,meas_iq]=synchronize(sim_iq,meas_iq,'union');

sim_omega=timeseries(sim.speed,sim.time);
meas_omega=timeseries(measurment.speed,measurment.time);
[sim_omega,meas_omega]=synchronize(sim_omega,meas_omega,'union');

abs_error_id=( sim_id-meas_id );
abs_error_iq=( sim_iq-meas_iq );
abs_error_omega=( sim_omega-meas_omega );
%%
figure
plot(abs_error_id,'r');
grid on
hold on
xlabel('Time (ms)');
%ylabel('Current (A)');
plot(abs_error_iq,'b');
%legend('i_d error','i_q error','Location','eastoutside');
xlabel('Time (ms)');
ylabel('');
xlim([0.199 5]);
ylim([-4 4]*1e-3);
title('')

if plot_figures
    extraaxisoptions = ['scaled y ticks = true',...
    'y tick label style={/pgf/number format/.cd, fixed,precision=2}'...
    ,',ylabel style={yshift=-0.2cm,font=\small}'...
    ,',xlabel style={font=\small}'...
    ];
    cleanfigure('targetResolution',600);
    matlab2tikz('step_error.tikz','showInfo', false,  ...
        'width', '\fwidth', 'height', '\fheight', 'extraaxisoptions', extraaxisoptions);
end

%%
%% Compare
f=figure(3);
f.Position(3:4) = 2*[1024 768];
subplot(2,3,1)
title('Compare simulation and measurement');
grid on
hold on
plot(sim.time,sim.id,'LineWidth',3); % i_d
plot(measurment.time, measurment.id,'--','LineWidth',3); % i_d
legend('i_d sim','i_d meas', 'FontSize', 18,'Location','south');
xlim([0.19 200]);
title('Step Response $I_d$', 'FontSize', 20);
xlabel('Time (ms)', 'FontSize', 18);
ylabel('Current (A)', 'FontSize', 18);
set(gca,'fontsize',20);

subplot(2,3,2)
grid on
hold on
plot(sim.time,sim.iq,'LineWidth',3); % i_d
plot(measurment.time, measurment.iq,'--','LineWidth',3); % i_d
legend('i_q sim','i_q meas', 'FontSize', 18);
xlim([0.19 200]);
title('Step Response $I_q$', 'FontSize', 20);
xlabel('Time (ms)', 'FontSize', 18);
ylabel('Current (A)', 'FontSize', 18);
set(gca,'fontsize',20);

subplot(2,3,3)
grid on
hold on
plot(sim.time,sim.speed,'LineWidth',3);
plot(measurment.time, measurment.speed,'--','LineWidth',3);
xlim([0.19 200]);
title('Rotational speed', 'FontSize', 20);
legend('\omega_{mech} sim','\omega_{mech} meas', 'FontSize', 18);
xlabel('Time (ms)', 'FontSize', 18);
ylabel('Rotational speed ($\frac{1}{s}$)', 'FontSize', 18);
set(gca,'fontsize',20);

% calculate error
sim_id=timeseries(sim.id,sim.time);
meas_id=timeseries(measurment.id,measurment.time);
[sim_id,meas_id]=synchronize(sim_id,meas_id,'union');

sim_iq=timeseries(sim.iq,sim.time);
meas_iq=timeseries(measurment.iq,measurment.time);
[sim_iq,meas_iq]=synchronize(sim_iq,meas_iq,'union');

sim_omega=timeseries(sim.speed,sim.time);
meas_omega=timeseries(measurment.speed,measurment.time);
[sim_omega,meas_omega]=synchronize(sim_omega,meas_omega,'union');

abs_error_id=( sim_id-meas_id );
abs_error_iq=( sim_iq-meas_iq );
abs_error_omega=( sim_omega-meas_omega );

subplot(2,3,4)
plot(abs_error_id,'LineWidth',3);
grid on
title('Error $I_d$', 'FontSize', 20);
legend('i_d error', 'FontSize', 18);
xlabel('Time (ms)', 'FontSize', 18);
ylabel('Current (A)', 'FontSize', 18);
set(gca,'fontsize',20);
xlim([0.19 200]);

subplot(2,3,5)
plot(abs_error_iq,'LineWidth',3);
grid on
title('Error $I_q$', 'FontSize', 20);
legend('i_q error', 'FontSize', 18);
xlabel('Time (ms)', 'FontSize', 18);
ylabel('Current (A)', 'FontSize', 18);
set(gca,'fontsize',20);
xlim([0.19 200]);

subplot(2,3,6)
plot(abs_error_omega,'LineWidth',3);
set(0,'defaulttextinterpreter','latex')
grid on
title('Rotational speed', 'FontSize', 20);
legend('\omega_{mech} error', 'FontSize', 18);
xlabel('Time (ms)', 'FontSize', 18);
ylabel('Rotational speed in $\frac{1}{s}$', 'FontSize', 18);
xlim([0.19 200]);
set(gca,'fontsize',20);
saveas(gcf,'referance_ip_core_measurment_comparision','svg');
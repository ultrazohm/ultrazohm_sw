[l w] = size(measurement.Transient_3_0_606061_);
num_of_measured_points = w;
data_point_length = repmat(l,1,w); %1x41
i_ph = zeros(3,l,w);
%%
% i_ph
% goal has to be to have phase_currents for all data points in dimension
% num_of_phasesXlenght_of_data_pointXdata_point_idx (e.g. 3x10001x41)
for i=1:w
i_ph(1,1:l,i) = measurement.Transient_3_0_606061_(:,i);
i_ph(2,1:l,i) = measurement.Transient_4_0_606061_(:,i);
i_ph(3,1:l,i) = measurement.Transient_5_0_606061_(:,i);
end

% time
% and we need time information as data_point_idxXlength_of_data_point (e.g.
% 41x10001)
dt = 1/measurement.TR_psr(1);
time_vec = linspace(0,measurement.t_tr_s(1),measurement.TR_ptlen(1));
time = repmat(time_vec,w,1);

% figure
% plot(time_vec,i_ph(:,:,1))

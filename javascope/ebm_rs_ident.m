clc
clear
close all

L_d=0.0;
polepairs=4;
current_value=0.1;

log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/ebm_rs_ident.parquet');

log=log(log.enable==1,:);
log.omega_el=log.dut_speed_rpm/60*2*pi*polepairs; % 5 is pole pair of brose machine
speeds=unique(log.pm_speed_rpm_ref);

lq_log=log( abs(log.dut_iq_set-log.dut_iq) <0.1,:); % Only steady state
lq_log=lq_log( abs(lq_log.dut_iq_set) >0.1,:); % Only (1) and (2), i.e., not zero current

log=log(abs(log.dut_iq_set)<0.1,:);
log=log( abs(log.dut_id_set-log.dut_id) <0.1,:); % Only steady state
log=log( abs(log.dut_id_set) >0.1,:); % Only (1) and (2), i.e., not zero current

for i=1:length(speeds)
    local_speed=speeds(i);
    local_data=log(log.pm_speed_rpm_ref ==local_speed,:);
    positive=mean(local_data(local_data.dut_id>current_value,:));
    negative=mean(local_data(local_data.dut_id<current_value,:));
    rs=1./(negative.dut_id - positive.dut_id)*(negative.dut_vd_ref - positive.dut_vd_ref) + negative.omega_el*L_d*(negative.dut_iq -positive.dut_iq  );

    omega_el_mean=(negative.omega_el+positive.omega_el)/2;
    L_d_mean=1/omega_el_mean * (negative.dut_vq_ref - positive.dut_vq_ref )/(negative.dut_id - positive.dut_id);

    psi_pm=(1/(2*omega_el_mean))*( (positive.dut_vq + negative.dut_vq)-rs *(positive.dut_iq + negative.dut_iq) - omega_el_mean*L_d_mean*(positive.dut_id + negative.dut_id) );
    psi_pm_over_speed(i)=psi_pm;
    L_d_over_speed(i)=L_d_mean;
    rs_over_speed(i)=mean(rs);
    L_d_over_speed_second_method(i)=(positive.dut_vq_ref-positive.omega_el*psi_pm)./(positive.omega_el*positive.dut_id);
end

for i=1:length(speeds)
    local_speed=speeds(i);
    local_data=lq_log(lq_log.pm_speed_rpm_ref ==local_speed,:);
    positive=(local_data(local_data.dut_iq>current_value,:));
    negative=(local_data(local_data.dut_iq<current_value,:));
    % positive=positive(height(positive)/2:end,:);
    % negative=positive(height(negative)/2:end,:);
    positive=mean(positive);
    negative=mean(negative);
    L_q_over_speed_second_method(i)=-positive.dut_vd_ref./(positive.omega_el.*positive.dut_iq);
    L_q_mean(i)=1/positive.omega_el * (negative.dut_vq_ref - positive.dut_vq_ref )/(negative.dut_iq - positive.dut_iq); % Is this even correct?
end

figure
plot(speeds,rs_over_speed,'x--')
mean(rs_over_speed)

figure
plot(speeds,L_d_over_speed_second_method,'x--')
hold on
%title('using kellner two operating points')
plot(speeds,L_q_over_speed_second_method,'o--')
legend('L_d','L_q');

figure
plot(speeds,L_d_over_speed,'x--')
hold on
% title('using voltage equations')
plot(speeds,L_q_mean,'o--')
legend('L_d (Kellner)','L_q (Kellner)');

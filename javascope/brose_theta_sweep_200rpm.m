clc
clear

log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/buehler_theta_sweep_200rpm.parquet');
log=log(log.enable==1,:);

pos_speed=log(log.time<200,:);
neg_speed=log(log.time>227,:);
neg_speed=neg_speed(neg_speed.time<421,:);

figure
subplot(2,1,1)
plot(pos_speed.dut_theta_offset,pos_speed.dut_vd_ref);
hold on
plot(neg_speed.dut_theta_offset,neg_speed.dut_vd_ref);

subplot(2,1,2)
plot(pos_speed.dut_theta_offset,pos_speed.dut_vq_ref);
hold on
plot(neg_speed.dut_theta_offset,neg_speed.dut_vq_ref);

figure
subplot(2,1,1)
plot(pos_speed.dut_theta_offset,pos_speed.dut_vd);
hold on
plot(neg_speed.dut_theta_offset,neg_speed.dut_vd);

subplot(2,1,2)
plot(pos_speed.dut_theta_offset,pos_speed.dut_vq);
hold on
plot(neg_speed.dut_theta_offset,neg_speed.dut_vq);

%%
figure
plot(pos_speed.dut_theta_offset,pos_speed.dut_vd);
hold on
plot(pos_speed.dut_theta_offset,pos_speed.dut_vd_ref);
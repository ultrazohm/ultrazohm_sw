clc
clear
close all

log=parquetread('/home/ts/Documents/pr_review/hoerner/ultrazohm_sw/javascope/brose_theta_sweep_after_wrap.parquet');
log=log(log.enable==1,:);

pos_speed=log(log.dut_speed_rpm>450,:);
neg_speed=log(log.dut_speed_rpm<450,:);

figure
subplot(2,1,1)

plot(pos_speed.dut_theta_offset,pos_speed.dut_vd_ref);
hold on
plot(neg_speed.dut_theta_offset,neg_speed.dut_vd_ref);
title('vd')
legend('pos','neg')
grid on

subplot(2,1,2)
plot(pos_speed.dut_theta_offset,pos_speed.dut_vq_ref);
hold on
plot(neg_speed.dut_theta_offset,neg_speed.dut_vq_ref);
title('vq')

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
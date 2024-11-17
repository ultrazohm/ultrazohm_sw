clc
clear

log=parquetread('/home/ts/Documents/ts_rlc/storage/measurements/parameter_identification/brose_theta_sweep_1000rpm.parquet');
log=log(log.enable==1,:);

pos_speed=log(log.dut_speed_rpm>450,:);
neg_speed=log(log.dut_speed_rpm<450,:);

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

%%

clc
clear
close all

fp_muliply= readtable('pcg_50float_scale_fp_mult.csv');
fp_divide= readtable('pcg_50float_scale_fp_divide.csv');
shift_multi= readtable('pcg_50float_scale_fp_shift_multi.csv');

isr_offset=16.2;

start_index=40000;
end_index=50000;

fp_muliply=(fp_muliply.CH1(start_index:end_index)-isr_offset)/50
fp_divide=(fp_divide.CH1(start_index:end_index)-isr_offset)/50
shift_multi=(shift_multi.CH1(start_index:end_index)-isr_offset)/50

fp_muliply_mean=mean(fp_muliply)
fp_divide_mean=mean(fp_divide)
shift_multi_mean=mean(shift_multi)


figure
subplot(3,1,1);
plot(fp_muliply);

subplot(3,1,2);
plot(fp_divide);

subplot(3,1,3);
plot(shift_multi);


%%
[fp_multiply_f,fp_multiply_xi]=ksdensity(fp_muliply);
figure
plot(fp_multiply_xi,fp_multiply_f)

[fp_divide_f,fp_divide_xi]=ksdensity(fp_divide);
figure
plot(fp_divide_xi,fp_divide_f)

[shift_multi_f,shift_multi_xi]=ksdensity(shift_multi);
% figure
% plot(xi,f)

out=table(fp_muliply,fp_divide,shift_multi);
density_plot=table(fp_multiply_f',fp_multiply_xi',fp_divide_f',fp_divide_xi',shift_multi_f',shift_multi_xi');

writetable(out,'generator_isr_float.csv');
writetable(density_plot,'generator_isr_float_density.csv');


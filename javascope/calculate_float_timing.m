clc
clear
close all


fp_muliply= readtable('pcg_50float_scale_fp_mult.csv');
fp_divide= readtable('pcg_50float_scale_fp_divide.csv');
shift_multi= readtable('pcg_50float_scale_fp_shift_multi.csv');

isr_offset=16.2;

start_index=40000;
end_index=start_index+200


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

out=table(fp_muliply,fp_divide,shift_multi);

writetable(out,'generator_isr_float.csv');



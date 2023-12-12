clc
clear
close all

float_mult= readtable('uz_prng_get_uniform_uint32_zero_to_range_float_mult.csv');
int_mult= readtable('uz_prng_get_uniform_uint32_zero_to_range_int_mult.csv');
unbiased= readtable('uz_prng_get_uniform_uint32_zero_to_range_unbiased.csv');
unbiased_opt= readtable('uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt.csv');


isr_offset=16.2;

start_index=55000;
end_index=75000;

float_mult=(float_mult.CH1(start_index:end_index)-isr_offset)/50
int_mult=(int_mult.CH1(start_index+100000:end_index+100000)-isr_offset)/50
unbiased=(unbiased.CH1(start_index:end_index)-isr_offset)/50
unbiased_opt=(unbiased_opt.CH1(start_index:end_index)-isr_offset)/50


float_mult_mean=mean(float_mult)
int_mult_mean=mean(int_mult)
unbiased_mean=mean(unbiased)
unbiased_opt_mean=mean(unbiased_opt)

figure
subplot(4,1,1);
plot(float_mult);

subplot(4,1,2);
plot(int_mult);

subplot(4,1,3);
plot(unbiased);

subplot(4,1,4);
plot(unbiased_opt);

% %%
[float_mult_f,float_mult_xi]=ksdensity(float_mult);
figure
plot(float_mult_xi,float_mult_f)

[int_mult_f,int_mult_xi]=ksdensity(int_mult);
figure
plot(int_mult_xi,int_mult_f)

[unbiased_f,unbiased_xi]=ksdensity(unbiased);
figure
plot(unbiased_xi,unbiased_f)

[unbiased_opt_f,unbiased_opt_xi]=ksdensity(unbiased_opt);
figure
plot(unbiased_opt_xi,unbiased_opt_f)

%out=table(fp_muliply,fp_divide,shift_multi);
density_plot=table(float_mult_f',float_mult_xi',int_mult_f',int_mult_xi',unbiased_f',unbiased_xi',unbiased_opt_f',unbiased_opt_xi');

%writetable(out,'generator_isr_float.csv');
writetable(density_plot,'generator_isr_bounded_uint32_density.csv');


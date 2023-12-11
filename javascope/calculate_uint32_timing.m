clc
clear
close all


halton= readtable('uint32_halton_20_values.csv');
mtwister= readtable('uint32_mtwister_20_values.csv');
pcg= readtable('uint32_pcg_20_values.csv');
squares= readtable('uint32_squares_20_values.csv');
xoshiro= readtable('uint32_xoshiro_20_values.csv');

isr_offset=16.2;

start_index=72400
end_index=start_index+200


halton_result=(halton.CH1(start_index:end_index)-isr_offset)/20
mtwister_result=(mtwister.CH1(start_index:end_index)-isr_offset)/20
squares_result=(squares.CH1(start_index:end_index)-isr_offset)/20
pcg_result=(pcg.CH1(start_index:end_index)-isr_offset)/20
xoshiro_result=(xoshiro.CH1(start_index:end_index)-isr_offset)/20

halton_mean=mean(halton_result)
mtwister_mean=mean(mtwister_result)
squares_mean=mean(squares_result)
pcg_mean=mean(pcg_result)
xoshiro_mean=mean(xoshiro_result)

figure
subplot(5,1,1);
plot(halton_result);

subplot(5,1,2);
plot(mtwister_result);

subplot(5,1,3);
plot(squares_result);

subplot(5,1,4);
plot(pcg_result);

subplot(5,1,5);
plot(xoshiro_result);

%%
out=table(halton_result,mtwister_result,squares_result,pcg_result,xoshiro_result);

writetable(out,'generator_isr_measurement.csv');



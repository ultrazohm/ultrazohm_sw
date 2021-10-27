%07.10.2021
%FFT calculation of currents

start_time = 0.02;
activation_time = 0.1;

length_timeseries = length(phase_currents.Time);
start_index = find(phase_currents.Time > start_time,1);
activation_index = find(phase_currents.Time > activation_time,1);

%i_a = phase_currents.Data(start_index:length_timeseries,1);
%i_b = phase_currents.Data(start_index:length_timeseries,2);
%i_c = phase_currents.Data(start_index:length_timeseries,3);

i_q_before = idq.Data(start_index:(activation_index-10),2);
i_q_after = idq.Data((activation_index+10):length_timeseries,2);
w_el = omega_el.Data(start_index:length(omega_el.Data),1);
f_el = mean(w_el)/(2*pi);

%Select length of signal for fft to get multiple frequencies of f_el
selected_length = round(f_c/f_el);

iq_before = i_q_before(1:selected_length);
iq_after = i_q_after(1:selected_length);

iq_before = iq_before-mean(iq_before);
iq_after = iq_after-mean(iq_after);



Y_iq_before = fft(iq_before);
P2_before = abs(Y_iq_before/selected_length);
P1_before = P2_before(1:selected_length/2+1);
P1_before(2:end-1) = 2*P1_before(2:end-1);

f = f_c*(0:(selected_length/2))/selected_length;

Y_iq_after = fft(iq_after);
P2_after = abs(Y_iq_after/selected_length);
P1_after = P2_after(1:selected_length/2+1);
P1_after(2:end-1) = 2*P1_after(2:end-1);


subplot(2,1,1)
bar(f./f_el,P1_before)
grid on
xlim([0,20])
ylim([0,0.5])
title('FFT of Iq without resonant controller')
subplot(2,1,2)
bar(f./f_el,P1_after)
xlim([0,20])
ylim([0,0.5])
title('FFT of Iq with resonant controller')
grid on
xlabel('Harmonic Order of f-el = ' + string(f_el) + 'Hz')

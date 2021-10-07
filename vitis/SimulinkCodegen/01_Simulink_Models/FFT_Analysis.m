%07.10.2021
%FFT calculation of currents

length_timeseries = length(phase_currents.Time);
start_index = find(phase_currents.Time > 0.02,1);

i_a = phase_currents.Data(start_index:length_timeseries,1);
i_b = phase_currents.Data(start_index:length_timeseries,2);
i_c = phase_currents.Data(start_index:length_timeseries,3);

i_q = idq.Data(start_index:length_timeseries,2);

time = phase_currents.Time(start_index:length_timeseries);

length_ia = length(i_q);
frequency_meas = 1/(time(5)-time(4));

Y_ia = fft(i_q);
P2 = abs(Y_ia/length_ia);
P1 = P2(1:length_ia/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = 2*pi*frequency_meas*(0:(length_ia/2))/length_ia;

omega_0 = omega_el.Data(length(omega_el.Data));

figure(1)
stem(f,P1)
hold on

%plot harmonic lines
plot([omega_0,omega_0], [0,10], 'r--');
plot([omega_0*2,omega_0*2], [0,10], 'r--');
plot([omega_0*3,omega_0*3], [0,10], 'r--');
plot([omega_0*4,omega_0*4], [0,10], 'r--');
plot([omega_0*5,omega_0*5], [0,10], 'r--');
plot([omega_0*6,omega_0*6], [0,10], 'r--');
plot([omega_0*7,omega_0*7], [0,10], 'r--');
grid on
xlabel('Frequency [rad/s]')

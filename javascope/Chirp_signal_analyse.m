%filename = 'Log_2026-03-20_13-48-44_Kp_Ki_Variation.csv';
filename = 'Log_2026-03-25_08-26-56.csv';
fs = 20000; % sampling frq

table = readtable(filename);

id_ref = table.CH8_23_id_ref;
id = table.CH6_19_id;

figure()
plot(table.time, id_ref)
hold on
grid on
plot(table.time, id)

k=1;
% Sprungstellen finden
for i=1:length(id_ref)-1
    if abs(id_ref(i+1)-id_ref(i)) > 3 && id_ref(i) == 0
        index_sprung(k) = i+1;
        k=k+1;
    end
    if abs(id_ref(i+1)-id_ref(i)) > 3 && id_ref(i+1) == 0
        index_sprung(k) = i+1;
        k=k+1;
    end
end

for i=1:length(index_sprung)/2
    width(i) = index_sprung(i*2)-1-index_sprung((i-1)*2 + 1);
end

width = min(width);

for i=1:length(index_sprung)/2
    time_fft{i} = table.time(index_sprung((i-1)*2 + 1):index_sprung((i-1)*2 + 1)+width);
    id_ref_fft{i} = id_ref(index_sprung((i-1)*2 + 1):index_sprung((i-1)*2 + 1)+width);
    id_fft{i} = id(index_sprung((i-1)*2 + 1):index_sprung((i-1)*2 + 1)+width);
end

fn = fs/2; %nyquist


for i=1:length(time_fft)
    L = length(id_ref_fft{i});
    
    
    g(:,i) = fft(id_ref_fft{i}-mean(id_ref_fft{i}))/L;
    h(:,i) = fft(id_fft{i}-mean(id_fft{i}))/L;
    
    f(:,i) = h(:,i)./g(:,i);
    
    frqs = linspace(0,1,fix(L/2))*fn;
    indx = 1:numel(frqs);
    
    phase(:,i) = angle(f(indx,i)).*180/pi;
    betrag(:,i) = abs(f(indx,i));

    figure()
    plot(frqs, 20*log10((betrag(indx,i))))
    set(gca, 'XScale', 'log')
    xlabel('Frequency (Hz)')
    ylabel('Amplitude (dB)')
    grid
    
    figure()
    plot(frqs, (phase(indx,i)))
    set(gca, 'XScale', 'log');
    xlabel('Frequency (Hz)')
    ylabel('Phase (deg)')
    grid

end



figure()
plot(frqs, 20*log10(mean(betrag(indx,:),2)))
set(gca, 'XScale', 'log')
xlabel('Frequency (Hz)')
ylabel('Amplitude (dB)')
grid

figure()
plot(frqs, mean(phase(indx,:),2))
set(gca, 'XScale', 'log');
xlabel('Frequency (Hz)')
ylabel('Phase (deg)')
grid
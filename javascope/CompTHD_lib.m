function [Thd_avg, Freq_f0, Ampl_f0] = CompTHD_lib(signal_abc, t, samples_removed_f0, use_fit_function)

% compute the current THD of one or three-phase signal
%
% inputs:
% signal_abc    abc signal waveform [pu peak]
%               signal should be normalized
% t             time-axis
% samples_removed_f0    removes this many samples left and right of the
% fundamental frequency (default = 3)
% use_fit_function      boolean, if true, the data is fitted to a sin wave
% to extract f0 and amplitude (default = true)
%
% output:
% THD (average in case of three-phase signal)
% fundamental frequency
% fundamental amplitude


% define frequency range in which f0 can be
f_min = 0;
f_max = 1000;

% basic parameters
t = t(:);
Ts = mean(diff(t));         % sampling interval
fs = 1/Ts;                  % sampling frequency

% make sure that the signal is in vector form
if size(signal_abc, 2) > size(signal_abc, 1)
    signal_abc = signal_abc';
end

if ~exist('samples_removed_f0','var')
    % if parameter does not exist, this default is used
    samples_removed_f0 = 3;
end
if ~exist('use_fit_function','var')
    % if parameter does not exist, this default is used
    use_fit_function = 1;
end

% signal for f0 estimation
i1_f0est = signal_abc(:,1);

if(use_fit_function)
    [f0_final, ~] = extract_fundamental_of_sin(t, i1_f0est, 0);
else
    % FFT of phase A
    [m, f] = dft( i1_f0est , fs, Ts);

    % get peak of harmonics in the range [f_min, f_max]
    [~, ind_start] = min(abs(f - f_min));
    [~, ind_end] = min(abs(f - f_max));
    [Ind, Magn] = peaks(abs(m(ind_start:ind_end)));

    % extract phasor and frequency of fundmental component
    [~, ind_fund] = max(Magn);
    magn0_est = m(Ind(ind_fund) + ind_start - 1);
    f0_est = f(Ind(ind_fund) + ind_start - 1);

    %% Correct estimate using the phase in alpha-beta 

    % transformation abc -> alpha beta (peak invariant)
    K = (2/3) * [1 -0.5 -0.5;
        0 sqrt(3)/2 -sqrt(3)/2;
        0.5 0.5 0.5];
    signal_alBe0 = (K * signal_abc')';

    % transformation alpha beta -> dq (synchronized based on f0_est)
    phi = 2 * pi * f0_est * t + angle(magn0_est);
    signal_dq = [];
    signal_dq(:,1) = cos(phi) .* signal_alBe0(:,1) + sin(phi) .* signal_alBe0(:,2);
    signal_dq(:,2) = -sin(phi) .* signal_alBe0(:,1) + cos(phi) .* signal_alBe0(:,2);

    % phase angle of 3-phase signal in dq: difference between instantaneous and
    % average value
    signal_dqAngl = atan2(signal_dq(:,2), signal_dq(:,1));   % instantaneous angle in dq
    signal_dqAnglAvg = signal_dqAngl - detrend(signal_dqAngl, 'linear');  % average angle in dq

    % correct frequency (f0_est plus correction due to phase shift)
    timeInt = t(end) - t(1) - Ts;
    f0_corr = (signal_dqAnglAvg(end) - signal_dqAnglAvg(1)) / (2 * pi * timeInt);
    f0_final = f0_est + f0_corr;

end

Thd_abc  = NaN(3,1);
Ampl_abc = NaN(3,1);
% compute the THD of each phase individually
for phase = 1:size(signal_abc,2)
    [Thd_abc(phase),Ampl_abc(phase)] = phaseThd(signal_abc(:,phase), f0_final, Ts, samples_removed_f0);
end

% take average THD -> 3-phase THD
Thd_avg = mean(Thd_abc);
Freq_f0 = f0_final;
Ampl_f0 = mean(abs(Ampl_abc));

return

%%
function [m,f] = dft(signal, f_fund, Ts)
% Perform DFT over multiple of fundamental period 
% return complex magnitude and frequencies

% ensure that DFT is computed over multiple of fundamental period
if (nargin > 2) && (f_fund > 0)
    % fundamental period
    T_fund = 1 / f_fund;     
    % number of samples in fundamental period
    n_samples = T_fund / Ts;        
    % number of periods
    n_period = floor(length(signal) / n_samples);   
    n_end = n_period * n_samples;
    if n_period > 0
        x = signal(1:round(n_end));
    else
        x = signal;
    end
else
    x = signal;
end

N = length(x);
Ns = length(signal);
fh = 1/(Ts * N);

% Normalize signal to make it independent of length of FFT
% Compute complex magnitude m
m = fft(x)/N;
m = m(:);

% remove negative frequencies from spectrum
if rem(N,2)
    % N odd
    m = m(1:(N+1)/2);
else
    % N even
    m = m(1:N/2+1);
end

% Double amplitudes to reflect loss of negative frequency components
m(2:end) = m(2:end)*2;

% Compute frequencies f
% ensure that dimensions of m and f match with those of signal
if rem(Ns,2)
    f = (0:(Ns+1)/2)*fh;
else
    f = (0:Ns/2)*fh;
end

m = [m; zeros(length(f)-length(m), 1)];
return


%% 
function [Thd, Amp_f0] = phaseThd(s, f0, Ts, samples_removed_f0)

% compute DFT
m = dft(s, f0, Ts);

% remove fundamental 
[Amp_f0, i_fund] = max(m);
% remove neighbouring frequencies as well
number_neighbours_removed = samples_removed_f0;
I = max(1, i_fund-number_neighbours_removed) : i_fund+number_neighbours_removed;  
m_ripple = m;  
m_ripple(I) = 0;

% THD up to Nyquist frequency [%]
Hi = abs(m_ripple).^2;
Thd = 100 * sqrt(sum(Hi));

return

%%
function [Ind, Magn] = peaks(s)

% Find all peaks in the signal s.
% Any peak is defined as: s(i-1) < s(i) > s(i+1)
% s(1) > s(2)       - peak at left end 
% s(end-1) < s(end) - peak at right end 

if length(s) == 1
    Ind = 1;
    Magn = s;
    return
end

% Peak indices
Ind = [];     
% Peak magnitudes
Magn = [];     

% check left end
if s(2) < s(1)
    Ind(end + 1) = 1;
    Magn(end + 1) = s(1);
end

% check intermediate peaks
for ii = 2:length(s)-1
    if (s(ii-1) < s(ii)) && (s(ii+1) < s(ii))
        Ind(end + 1) = ii;
        Magn(end + 1) = s(ii);
    end
end

% check right end
if s(end-1) < s(end)
    Ind(end+1) = length(s);
    Magn(end+1) = s(end);
end

Ind = Ind(:);
Magn = Magn(:);

return

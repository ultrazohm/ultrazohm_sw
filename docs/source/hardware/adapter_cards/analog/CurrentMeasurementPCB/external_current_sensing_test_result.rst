.. _external_current_sensing_test_result:

========================
Performance Test Results
========================


DC Analysis
===========

The following figure shows the percentage error between the expected and measured differential output voltage over a DC input current range of -10 A to +10 A using the CASR 6-NP sensor.

At positive currents the error remains below 0.3%, while at negative currents, the error increases slightly, peaking at -2 A, reaching approximately 1.3%, and then decreases toward ~0.5% at -10 A.

This asymmetry is likely due to slight sensor nonlinearity or residual offset in the amplifier or measurement system.


.. figure:: dc_performance.png
   :alt: DC Measurement Error of CASR 6-NP
   :align: center
   :width: 600px


DC Performance Conclusion
-------------------------

The PCB demonstrates good accuracy, with the total error falling below **1.3% across the full ±10 A range**. 

Time-Domain and Harmonics Analysis
----------------------------------

To evaluate the output ripple and stability, and harmonic distortion behavior of different sensor technologies, 
a time-domain observation combined with FFT-based harmonics analysis was performed. This test involved all four measurement channels operating simultaneously, each populated with a different sensor. 
A sinusoidal input current of 100 mA peak at 100 Hz was applied. This test was conducted without any common-mode filter populated on the analog card to allow for a direct comparison of raw sensor.

Despite the input being only a small fraction of the sensors' nominal range, the LEM CASR 50-NP (fluxgate) exhibited the lowest ripple and most stable waveform. 
This indicates that current measurement accuracy is not directly limited by the sensor's full-scale range, 
but is instead strongly influenced by the internal signal conditioning architecture and magnetic core technology.

In the FFT spectrum, clear peaks were observed at 430 kHz, as well as its odd harmonics (3rd, 5th, 7th, etc.). 
This matches the internal excitation frequency of the CASR sensor, which is based on a modulated fluxgate principle.

The fluxgate sensor periodically excites a ferromagnetic core (typically at 450 kHz) driving it into saturation. 
The resulting harmonics are inherent to the magnetization demagnetization cycles and they are visible in the frequency domain 
as regular odd harmonics. This matches the manufacturer's published data:

.. figure:: lem_casr_noise_spectrum.png
   :align: center
   :width: 500px
   :alt: CASR datasheet noise spectrum

   Figure: Input-referred output noise current spectral density from CASR datasheet, 
   showing dominant excitation peak and its harmonics around ~430 kHz.

In comparison, the Sensitec CAS series (TMR-based) showed slightly higher ripple and more harmonic content in the FFT spectrum.
Their broader frequency bandwidth (400 kHz) may allow more high-frequency noise to appear at the output 
when operating at low signal amplitudes.

%.. figure:: time_domain_ripple_comparison.png
%   :align: center
% :width: 700px
%   :alt: Oscilloscope screenshot comparing 4 sensor outputs
%
%   Time-domain waveform comparison of four current sensors under identical excitation (100 mA, 100 Hz). 
%   The LEM CASR 50-NP output shows minimal ripple compared to the TMR-based alternatives.

Conclusion 2
------------

Fluxgate-based closed-loop sensors (LEM CASR series) offer better low-noise performance compared to TMR alternatives (Sensitec CAS5000-Series), even if the signal amplitude is far below the rated current range.

AC Impedance Measurement 
------------------------

This section presents a comparative impedance measurements using various sensors under various conditions.


The first test result shows the impedance magnitude and phase of Sensitec CAS5015SRA-LI under varying AC excitation and DC offset conditions. 
The following configurations were tested:

- Black trace: 0 A DC offset, 0 dBm AC amplitude → ≈ 1.67 A AC
- Green trace: 2 A DC offset, 0 dBm AC amplitude → ≈ 1.67 A AC
- Red trace: 0 A DC offset, 12 dBm AC amplitude → ≈ 5.30 A AC

 .. figure:: impedance_cas5015sra_sweep_amplitude_offset.png
   :align: center
   :width: 800px
   :alt: Impedance Bode plot for CAS5015SRA-LI under varying excitation

- The impedance magnitude remains nearly constant across all test conditions in the low-frequency region. 
  A noticeable drop occurs around 2 kHz for all traces, with the effect being more pronounced in the black trace. 
  Above approximately 200 kHz, all curves exhibit a clear roll-off in magnitude and phase.

The second test result shows the impedance magnitude and phase of four different current sensors 
under identical excitation conditions: 0 A DC offset and 0 dBm AC source level (≈ 1.67 A peak current). 
The sensors evaluated in this test include:

- STB-6CAS/F - Orange trace
- CASR 6-NP - Blue trace
- CAS5015SRA-LI - Black trace
- CAS5025SRA-LI - Purple trace

.. figure:: impedance_sensor_comparison.png
   :align: center
   :width: 800px
   :alt: Impedance and phase plots comparing four current sensors under identical conditions

   Impedance magnitude (top) and phase (bottom) response of four different sensors.

- Similar to the previous test, a slight drop in impedance magnitude occurs around 2 kHz for all sensors 

- Across the full sweep, all sensors show stable impedance values in the low-frequency region, 
  closely matching their expected impedance levels, calculated as before:

   .. math::

     Z_{\text{expected}} = \text{OpAmp Gain} \times \text{Sensor Sensitivity} \quad [\text{in } \mathrm{m\Omega}]

- A consistent roll-off in magnitude is observed beginning around 200 kHz for all sensors, 
  attributed to the sensing chain low-pass behavior.

- Also the phase responses of all four sensors follow a similar trend, 
  with noticeable phase lag beginning around 50-100 kHz. 
  The exact roll-off frequency and slope vary slightly between sensors.

The third test compares the impedance magnitude and phase of two sensors under different AC source levels, while maintaining **0 A DC offset**. The sensors used are:

- CAS5015SRA-LI - 12 dBm (~5.30 A peak) - Red trace
- CAS5025SRA-LI - 12 dBm (~5.30 A peak) - Black trace
- CAS5025SRA-LI - 0 dBm (~1.67 A peak) - Purple trace

.. figure:: impedance_sensor_amplitude_comparison.png
   :align: center
   :width: 800px
   :alt: Impedance and phase plots comparing Sensitec TMR sensors under two AC amplitude levels

   Impedance magnitude and phase of CAS5015SRA and CAS5025SRA sensors under varying AC amplitudes

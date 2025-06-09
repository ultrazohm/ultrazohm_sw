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

The sensor demonstrates a good accuracy, with the total error falling below **1.3% across the full ±10 A range**. 

AC Analysis - Time and Frequency Domain
=======================================

Time and Frequency Domain Analysis
----------------------------------

To evaluate the ripple characteristics and internal modulation effects of different sensor technologies, 
a test was conducted using equally rated sensors: the LEM CASR25-NP and the Sensitec CAS5025SRA-LI.
A 500 Hz, 1 Arms sinusoidal current was applied, and the sensor outputs were captured using both 
single-ended and differential probes.

- **Red trace**: LEM CASR25-NP output (single-ended)
- **Black trace**: Sensitec CAS5025SRA-LI output (single-ended)  
- **Green trace**: Same Sensitec CAS5025SRA-LI output measured using a Micsig MOIP350P optical differential probe, 
  connected at the RJ45 output. This includes the effect of the populated differential filter capacitor 
  (C18 = 5.6 nF), while the common-mode capacitors (C16, C20) remain unpopulated.

  .. figure:: TimeDomain_FFT.png
   :align: center
   :width: 1000px
   :alt: Side-by-side FFT and time-domain signals for LEM and Sensitec sensors

   Comparison of CASR (LEM) and CAS5025 (Sensitec) outputs in time and frequency domains. 

The frequency-domain FFT (top panel) reveals differences between the LEM CASR and Sensitec TMR sensors:

- The LEM CASR(red) output shows a strong modulation peak around 435 kHz along with odd-order harmonics.  
  This matches the internal fluxgate excitation frequency documented in the CASR datasheet (see figure below),  
  confirming the presence of periodic ripple due to internal modulation.  
  These harmonics translate into visible ripple in the time-domain waveform (red trace, bottom panel).

- By contrast, the Sensitec CAS5025 TMR sensor shows a flat frequency spectrum in the same FFT panel,  
  with no excitation-related harmonics. Its time-domain output is smoother and less noisy,  
  under identical test conditions.

.. figure:: lem_casr_noise_spectrum.png
   :align: center
   :width: 500px
   :alt: CASR datasheet input noise spectrum

   Input noise spectrum of LEM CASR sensor (from datasheet).  
   Strong excitation harmonic appears at ~435 kHz with visible odd harmonics.


.. note::

   The time-domain ripple is caused by spectral components shown in the FFT. 
   In fluxgate sensors, these originate from internal excitation at ~435 kHz. 
   By contrast, TMR sensors do not use modulated excitation and thus show less periodic ripple.

Its shown that the internal excitation frequency of fluxgate sensors
introduces strong harmonic components into the output signal. While these harmonics can be attenuated with 
an analog low-pass filter, such early filtering limits the measurement bandwidth because it the must attenuate frequencies below or around 435 kHz to suppress the internal ripple.

As a result, the sensor's output bandwidth becomes restricted. To overcome this limitation, advanced digital filtering techniques such as oversampling, digital filtering, 
and notch filters implemented in the FPGA can be used. These methods allow selective attenuation 
of modulation-related harmonics without compromising the full analog bandwidth. This would enable more accurate 
high-frequency signal acquisition while still suppressing and rejecting modulation related harmonic peaks.

FFT Comparison Between CAS5025 and CAS5015
------------------------------------------

A follow-up test was performed to compare the spectral behavior of the Sensitec CAS5025SRA-LI
and CAS5015SRA-LI under identical conditions (500 Hz, 1 Arms sinusoidal current) with differential measurement using Micsig MOIP350P on Ethernet adapter.

The 25 A variant showed a distinct narrowband spike at ~2 MHz in the FFT spectrum (see earlier figure), 
while the 15 A variant exhibited a flat frequency spectrum with no such harmonic content at ~2 Mhz, as shown below:

.. figure:: TimeDomain_FFT_S15.png
   :align: center
   :width: 800px
   :alt: FFT of CAS5015 showing no 2 MHz spike

   FFT and time-domain waveform of the CAS5015SRA-LI sensor. No spectral peak is present at 2 MHz, 
   unlike in the CAS5025SRA-LI.

This suggests the 2 MHz spike in CAS5025 originates from internal circuitry specific to the 25 A variant and is **not present** in the 15 A model.


AC Analysis - Impedance Measurement
===================================

This section presents comparative impedance measurements using various sensors under various conditions.


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

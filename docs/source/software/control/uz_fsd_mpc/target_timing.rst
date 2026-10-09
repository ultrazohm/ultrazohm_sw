.. _uz_fsd_mpc_target_timing:

=========================================
FSD-MPC idle-state execution-time benchmark
=========================================

This is a default-disabled R5 benchmark hook. It never writes FSD outputs to
PWM registers or the application's duty variables. It runs only while the
platform state machine is ``idle_state``. Keep the inverter unenergized and
verify the platform is idle before enabling this mode. The timer code is
host-checked; measured R5 results are recorded in ``FSD_EXECUTION_TIME_REPORT.md``.

Configuration
=============

``uz_global_configuration.h`` defaults to ``UZ_FSD_BENCHMARK_ENABLE=0`` and
``UZ_FSD_BENCHMARK_VARIANT=0``. For a timing firmware build, explicitly set
enable to ``1`` and select one variant:

.. csv-table:: Native SimplexFace variants
   :header: "Index", "Candidate selector", "Modulation", "QP solves/step"

   "0", "exhaustive", "SVM", "6"
   "1", "exhaustive", "IFT", "6"
   "2", "exhaustive", "VFT", "12"
   "3", "deadbeat", "SVM", "1"
   "4", "deadbeat", "IFT", "1"
   "5", "deadbeat", "VFT", "2"

Build and deploy with the normal UltraZohm Vitis workflow. One controller
instance is initialized after ``uz_SystemTime_init`` in ``main.c``. While
idle, the ISR feeds it six fixed inputs in order, repeating them for 12
warm-up calls and 6,000 measured calls. The values originate from frozen
JSON SHA-256 ``78f4870515e6af85204f02269a25dc927b76ab14a1d1a136a06b489d9bb7ff45``.
They cover a sector crossing, low DC voltage, negative-id reference,
negative electrical speed and a zero-speed corner. This is a synthetic
stateful sequence, not a closed-loop motor trajectory. Rebuild for each
variant. The benchmark's preloaded command and persistent command history
remain intact across the sequence.

Capture and interpretation
==========================

After the bounded run, the main loop prints one report on the R5 terminal.
No printing or Javascope update is added inside the timed section. The report
contains the BSP timer frequency, preload ticks, minimum empty timer-read
pair overhead, raw step min/max/mean ticks, 1-us histogram p95/p99 bins,
sample count and count at or above 100 us. Histogram bin ``100`` means
**100 us or more**, so it is censored rather than an upper bound. A nonzero
status marks failure and stops the benchmark.

Convert raw ticks with ``duration_us = ticks * 1e6 / timer_frequency_hz``.
If correcting for measurement overhead, report both raw and
``max(0, raw_ticks - read_pair_overhead_ticks)`` values. The 64-bit timer
frequency comes from the target BSP macro
``XPAR_UZ_SYSTEM_TIMER_UPTIME_64BIT_CLOCK_FREQ_HZ``. The controller-only
raw maximum is separate from p95/p99. The existing
``uz_SystemTime_GetIsrExectionTimeInUs`` reports ISR duration separately;
the full 100-us deadline also contains ADC, encoder, PWM and logging work.
Finite-case samples cannot prove WCET.

Run the new Unity statistics test and existing module tests with
``ceedling test:all`` from ``vitis/software/Baremetal``. Disable the mode by
restoring ``UZ_FSD_BENCHMARK_ENABLE=0`` for normal firmware. The optional
academic-license generated ActiveSet backend is not part of this benchmark.

.. _uz_fsd_mpc:

===========================
Three-phase FSD-MPC (staged)
===========================

``uz_fsd_mpc`` is a fixed-size, float32 controller for a three-phase SPMSM.
It is host-qualified against frozen Python binary64 vectors. It has not been
timed on the UltraZohm target or qualified with a power stage.

Interface and timing
====================

``uz_fsd_mpc_input`` contains instantaneous phase currents ``ia``, ``ib``,
``ic`` in A, the **unshifted** measured electrical angle ``theta_e`` in rad,
electrical speed ``omega_e`` in rad/s, DC-link voltage ``v_dc`` in V, and peak
amplitude-invariant current references ``id_ref``, ``iq_ref`` in A. The
controller performs Clarke/Park at the measured angle. It predicts the
response to the currently applied command using ``theta_e + 0.5 omega_e Ts``
and forms the next command using ``theta_e + 1.5 omega_e Ts``. The hardware
contract activates the newly calculated duty at the next PWM update; the C
controller therefore stores the applied command but has no PWM delay queue.

Configuration owns predictor resistance, d/q inductances, PM flux, period,
lambda, coordinate system, candidate selector, modulation and QP backend.
``uz_fsd_mpc_init`` allocates from the static pool configured by
``UZ_FSD_MPC_MAX_INSTANCES`` and computes a preload. ``uz_fsd_mpc_step``
returns the applied/calculated commands, three normalized phase duties,
status and optional fixed-size diagnostics. ``uz_fsd_mpc_reset`` recomputes
the preload and clears a latched runtime fault. No heap allocation is used.

Qualified choices are SI with exhaustive or deadbeat selection, SVM/VFT/IFT
and SimplexFace; p.u. currently supports exhaustive SimplexFace with the
same modulation policies. The optional generated ActiveSet backend extends
the SI matrix only when explicitly compiled in. Unsupported combinations
assert at initialization; there is no automatic backend fallback.

The core uses float32 arithmetic. The optional extracted MATLAB-generated
active-set solver accepts converted float32 QP inputs, solves internally in
double, and returns dwells converted to float32. Its academic-use notice
limits use to teaching, academic research and degree-granting institutions;
it is **not** copied into this tree. Its static managers are non-reentrant,
and its seven-iteration limit remains unchanged. A local research build may
supply the unchanged source/header and set
``UZ_FSD_MPC_ENABLE_GENERATED_ACTIVE_SET=1`` explicitly.

Failure and PWM boundary
========================

Invalid runtime input, QP failure or invalid output returns a non-OK status,
latches the controller fault and marks all duties NaN. NaN is only an invalid
marker, **not** a PWM-off command. A platform adapter must check status,
``isfinite`` and the range ``[0,1]`` before calling a PWM duty API, and must
request a verified PWM/power-electronics inhibit on failure. This controller
does not call the PWM driver. The physical controller-side B6 schedule starts
with ``000`` and is symmetric about the period center; any hardware compare
polarity transformation belongs to the platform adapter.

Example (controller only; no PWM writes)::

    struct uz_fsd_mpc_output preload, output;
    uz_fsd_mpc_t *controller = uz_fsd_mpc_init(config, &sample, &preload);
    if (preload.status == UZ_FSD_MPC_OK &&
        uz_fsd_mpc_step(controller, &sample, &output, NULL) == UZ_FSD_MPC_OK) {
        /* A separate checked hardware adapter may consume output. */
    }

The independent source repository's ``c/test/quickstart.c`` is a complete
compilable example. Native fixtures and tests are under
``test/uz/uz_fsd_mpc``; from ``vitis/software/Baremetal`` run
``ceedling test:all``. The fixture header
records the frozen JSON SHA-256 and uses field-specific float32 limits.
Target WCET, stack and hardware inhibit latency remain to be measured.

.. _uz_sogipll_sw:

=================================
Software SOGI PLL (uz_sogipll_sw)
=================================

Description
===========

``uz_sogipll_sw`` estimates the phase and angular frequency of a single-phase voltage using a second-order generalized integrator and a phase-locked loop.
It uses single-precision arithmetic, a combination of forward- and backward-Euler integration, a parallel PI controller, and phase integration with positive modulo.
The SOGI uses the Euler arrangement in Section III of [#sogipll_paper]_: forward Euler for the in-phase integrator and backward Euler for the quadrature integrator.

Block diagram
=============

The diagram shows the signal flow for normalization with ``voltage_scaling`` in reciprocal volts; internal voltages are dimensionless ratios to the reference voltage.
Parallelograms denote inputs, rectangles denote calculations, and rounded nodes denote returned outputs.
The sample ordering and state updates are described below.

.. mermaid::

   flowchart LR
       V[/"voltage_V / V"/] --> SCALE["Multiply by voltage_scaling"]
       SCALE -->|"scaled_voltage / 1"| SOGI["SOGI<br/>Forward / backward Euler"]
       SOGI -->|"voltage_estimate / 1, quadrature_voltage_estimate / 1"| PARK["Park transform"]
       PARK -->|"voltage_q / 1"| PI["PI controller"]
       PI -->|"delta_omega_rad_per_s / (rad/s)"| SUM["Add feedforward frequency"]
       FF[/"omega_feedforward_rad_per_s / (rad/s)"/] --> SUM
       SUM -->|"omega_rad_per_s / (rad/s)"| SOGI
       SUM -->|"omega_rad_per_s / (rad/s)"| PHASE["Phase integration and wrapping"]
       PHASE -->|"theta_rad / rad"| PARK
       SOGI -->|"voltage_estimate / 1, quadrature_voltage_estimate / 1"| RESCALE["Optional division by voltage_scaling<br/>when rescale_voltage_outputs is true"]
       PARK -->|"voltage_d / 1, voltage_q / 1"| RESCALE
       RESCALE --> VO(["voltage_estimate, quadrature_voltage_estimate<br/>voltage_d, voltage_q<br/>in V if rescaled, otherwise normalized"])
       SUM --> WO(["omega_rad_per_s / (rad/s)"])
       PHASE --> TO(["theta_rad / rad"])

Output rescaling is applied after the control calculations and does not feed back into the SOGI or PI controller.

Discrete-time implementation
============================

Let :math:`a_n`, :math:`b_n`, :math:`I_n` and :math:`\theta_n` denote the in-phase voltage state, quadrature voltage state, PI integral and phase at the start of sample :math:`n`.
With scaled voltage :math:`u_n`, the outputs are:

.. math::

   d_n &= a_n\cos\theta_n + b_n\sin\theta_n \\
   q_n &= b_n\cos\theta_n - a_n\sin\theta_n \\
   \omega_n &= K_p q_n + I_n + \omega_{ff}

The next states are:

.. math::

   a_{n+1} &= a_n + T_s\omega_n\left[k(u_n-a_n)-b_n\right] \\
   b_{n+1} &= b_n + T_s\omega_n a_{n+1} \\
   I_{n+1} &= I_n + T_s K_i q_n \\
   \theta_{n+1} &= \operatorname{mod}(\theta_n+T_s\omega_n, 2\pi)

The in-phase integrator uses the previous SOGI states.
The quadrature integrator then uses the updated in-phase state :math:`a_{n+1}`.
The estimated frequency :math:`\omega_n` is held constant for both updates during this sample.
The returned voltage estimates and phase are :math:`a_n`, :math:`b_n` and :math:`\theta_n`, not the newly integrated states.
The first sample after initialization or reset therefore returns zero voltage states and phase, with the feedforward frequency.

Implementation and sample time
==============================

The default sample rate used in the configuration example and tracking test is 10 kHz (``sample_time_s = 0.0001f``).
The application supplies ``sample_time_s`` during initialization and calls ``uz_sogipll_sw_sample`` at that interval.
Each call processes one input voltage sample and advances the internal states.

``uz_integrator_eulerforward`` integrates the in-phase SOGI state and the phase.
A local pure function, ``uz_sogipll_sw_integrator_eulerbackward``, integrates the quadrature state from the updated in-phase state.
``uz_transformation_3ph_alphabeta_to_dq`` transforms the SOGI voltage estimates into direct and quadrature components.
``uz_PI_Controller`` runs in parallel mode with the quadrature voltage as its error signal.
Its output is added to the feedforward angular frequency.
``uz_signals_wrap`` wraps the integrated phase, with a rounded upper endpoint mapped to zero to keep the phase in :math:`[0, 2\pi)`.

Example configuration
=====================

Set ``UZ_SOGIPLL_SW_MAX_INSTANCES`` in ``uz_global_configuration.h`` to the required instance count (production default: zero).
Reserve one additional ``UZ_PI_CONTROLLER_MAX_INSTANCES`` slot per software PLL instance, in addition to any PI controllers used elsewhere.
Initialize before the ISR.
Instances retain their configuration and state for the lifetime of the program.

.. code-block:: c
   :linenos:
   :caption: Configuration and sampling example

   struct uz_sogipll_sw_config_t config = {
       .sample_time_s = 0.0001f,
       .omega_feedforward_rad_per_s = 314.159265f,
       .sogi_gain = 1.41421356f,
       .proportional_gain = 100.0f,
       .integral_gain = 1000.0f,
       .voltage_scaling = 0.0002f,
       .rescale_voltage_outputs = true
   };
   uz_sogipll_sw_t *pll = uz_sogipll_sw_init(config);
   struct uz_sogipll_sw_outputs_t output = uz_sogipll_sw_sample(pll, voltage_V);

With ``rescale_voltage_outputs = true``, all four voltage outputs are divided by ``voltage_scaling`` and returned in volts.
With ``rescale_voltage_outputs = false``, the voltage outputs retain the internal input scaling.
An omitted field in a zero-initialized configuration defaults to ``false``.
Phase and angular frequency are unchanged by this option.
For example, a normalized ``voltage_d`` of 1 with ``voltage_scaling = 0.0002f`` becomes 5000 V when rescaling is enabled.

The gains and scaling above illustrate the interface; tune them for the actual measurement amplitude and required response.
``uz_sogipll_sw_reset`` clears all four integrator states while retaining parameters.
Serialize access to each instance.

Software reference
==================

.. doxygentypedef:: uz_sogipll_sw_t

.. doxygenstruct:: uz_sogipll_sw_config_t
   :members:

.. doxygenstruct:: uz_sogipll_sw_outputs_t
   :members:

.. doxygenfunction:: uz_sogipll_sw_init

.. doxygenfunction:: uz_sogipll_sw_sample

.. doxygenfunction:: uz_sogipll_sw_reset

Literature references
=====================

.. [#sogipll_paper] M. Ciobotaru, R. Teodorescu and F. Blaabjerg, "A New Single-Phase PLL Structure Based on Second Order Generalized Integrator," PESC 2006.
   `DOI: 10.1109/PESC.2006.1711988 <https://doi.org/10.1109/PESC.2006.1711988>`_.
   `Full paper (Aalborg University) <https://www.researchgate.net/profile/Mihai-Ciobotaru/publication/224653073_A_New_Single-Phase_PLL_Structure_Based_on_Second_Order_Generalized_Integrator/links/0046352d5fd26e97de000000/A-New-Single-Phase-PLL-Structure-Based-on-Second-Order-Generalized-Integrator.pdf>`_.

.. _uz_IM_Control:

============================
Induction machine FOC control
============================

.. toctree::
   :maxdepth: 1

   IM_config
   IM_current_control
   IM_observers
   IM_uf_control
   IM_protection

The induction-machine (IM) control implements rotor-flux-oriented control and
reuses the common UltraZohm control modules. The current loop is based on
:ref:`uz_CurrentControl`, the harmonic compensation uses the
:ref:`uz_resonant_controller`, and the resulting voltage vector is passed to the
:ref:`space vector modulation <uz_spacevectormodulation>`.

The implementation consists of the following parts:

* ``uz_IM_config`` contains the ``uz_IM_t`` machine model, derived
  quantities and the selected machine preset.
* ``uz_CurrentControl`` contains both current PI controllers, IM decoupling,
  voltage-vector limitation and PI clamping.
* ``im_foc_control`` combines speed control, current control, resonant control
  and space-vector modulation.
* ``im_observer`` selects either the deterministic rotor-flux observer or the
  Kalman-filter observer.

Control flow
============

The controller is called once per control ISR:

.. code-block:: text

   phase currents, speed and previous applied voltage
                         |
                         v
                 IM flux observer
                         |
               i_dq, psi_r, theta_flux, omega_s
                         |
             speed PI or direct i_q reference
                         |
      +------------------+------------------+
      |                  |                  |
   current PI       IM decoupling     resonant control
      |                  |                  |
      +------------------+------------------+
                         |
              space-vector limitation
                         |
                         v
                space-vector modulation

Machine configuration
=====================

The active preset is selected in
``uz/uz_IM_config/uz_IM_motor_config.h``. All electrical parameters are
star-equivalent, per-phase values referred to the stator side.

.. doxygenstruct:: uz_IM_t
   :members:

.. doxygenfunction:: uz_IM_config_get_selected_motor

.. doxygenfunction:: uz_IM_config_assert

The selected preset is obtained during software initialization:

.. code-block:: c

   #include "uz/uz_IM_config/uz_IM_config.h"

   uz_IM_t im_config = uz_IM_config_get_selected_motor();

Derived machine quantities
--------------------------

.. doxygenfunction:: uz_IM_get_Ls

.. doxygenfunction:: uz_IM_get_Lr

.. doxygenfunction:: uz_IM_get_sigma

.. doxygenfunction:: uz_IM_get_tau_r

.. doxygenfunction:: uz_IM_get_id_ref_for_psi_r

Current controller configuration
================================

Select ``im_rotor_flux_decoupling`` and assign ``config_IM`` when creating the
common current-controller instance. Existing PMSM users can continue using the
original configuration and sample function.

.. code-block:: c

   struct uz_CurrentControl_config current_config = {
      .decoupling_select = im_rotor_flux_decoupling,
      .config_id = config_id,
      .config_iq = config_iq,
      .config_IM = im_config,
      .Kp_adjustment_flag = false,
      .max_modulation_index = 1.0f / sqrtf(3.0f),
   };

   uz_CurrentControl_t *current_control =
      uz_CurrentControl_init(current_config);

The general sample input separates the angular velocity of the rotating
reference frame from the velocity used to choose the voltage-limitation
priority. This distinction is required for an induction machine because the
synchronous flux-frame velocity and electrical rotor velocity are different.

.. doxygenstruct:: uz_CurrentControl_input_t
   :members:

.. doxygenstruct:: uz_CurrentControl_output_t
   :members:

.. doxygenfunction:: uz_CurrentControl_sample_general

IM decoupling
=============

The rotor-flux-oriented decoupling voltages are

.. math::

   u_{d,\mathrm{dec}} = -\omega_s \sigma L_s i_q

.. math::

   u_{q,\mathrm{dec}} = \omega_s \sigma L_s i_d
      + \omega_s \frac{L_m}{L_r}\lvert\Psi_r\rvert .

Here, :math:`\omega_s` is the signed synchronous angular velocity of the rotor
flux frame. The implementation is also available as a standalone stateless
function:

.. doxygenfunction:: uz_CurrentControl_IM_decoupling

Resonant controller integration
===============================

Two :ref:`uz_resonant_controller` instances compensate the selected harmonic in
the d- and q-axes. The controllers use raw measured dq currents so that the
harmonic content is not attenuated by the Kalman-filter estimate.

The resonant voltage is provided through
``uz_CurrentControl_input_t.v_additional_Volts``. It is therefore added before
the common voltage-vector limitation. PI voltage, IM decoupling and resonant
voltage cannot independently exceed the voltage available from the DC link.

For sixth-harmonic compensation, configure ``harmonic_order`` as ``6.0f`` and
pass the fundamental signed angular velocity to
``uz_resonantController_step``. The resonant controller performs the harmonic
multiplication internally.

FOC interface
=============

.. doxygenstruct:: im_foc_control_input_t
   :members:

.. doxygenstruct:: im_foc_control_output_t
   :members:

.. doxygenstruct:: im_foc_control_state_t
   :members:

.. doxygenfunction:: im_foc_control_init

.. doxygenfunction:: im_foc_control_step

.. doxygenfunction:: im_foc_control_reset

Reset behavior
==============

``im_foc_control_reset`` resets all persistent control states:

* both current PI controllers and their external clamping state,
* the speed PI controller,
* both resonant controllers,
* the resonant-frequency filter,
* flux-approximation and gain-adjustment states in ``uz_CurrentControl``.

The deterministic and Kalman observers are reinitialized separately when the
IM is stopped. Their flux, covariance, innovation and PLL states are reset.
The IM decoupling and machine-preset functions are stateless and therefore do
not require reset functions.

Usage example
=============

.. code-block:: c

   im_foc_control_input_t input = {
      .use_speed_control = true,
      .use_resonant_6th = true,
      .id_ref_A = id_reference_A,
      .iq_ref_A = 0.0f,
      .speed_ref_rpm = speed_reference_rpm,
      .id_meas_A = measured_current_d_A,
      .iq_meas_A = measured_current_q_A,
      .omega_s_for_resonant_rad_s = omega_s_rad_per_sec,
   };

   im_foc_control_output_t output = {0};

   im_foc_control_step(&actual_values,
                       &reference_values,
                       &im_config,
                       &input,
                       omega_s_rad_per_sec,
                       psi_r_Vs,
                       theta_flux_rad,
                       &control_state,
                       &output);

Tests
=====

The unit tests are located in:

* ``test/uz/uz_IM_config/test_uz_IM_config.c``
* ``test/uz/uz_CurrentControl/test_uz_im_decoupling.c``
* ``test/uz/uz_CurrentControl/test_uz_CurrentControl.c``

They cover the selected machine preset, configuration validation, positive and
negative synchronous speed, zero-speed decoupling, invalid rotor flux, the
general IM sample path, additional resonant voltage and reset-related APIs.

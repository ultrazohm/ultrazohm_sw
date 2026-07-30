.. _uz_IM_current_control:

==============================
IM current control and decoupling
==============================

The induction machine uses the shared :ref:`uz_CurrentControl`. This reuses the
same PI controllers, external clamping and DC-link-dependent space-vector
limitation as the PMSM current-control path.

Configuration
=============

Select ``im_rotor_flux_decoupling`` and assign a valid ``uz_IM_t`` to
``config_IM``:

.. code-block:: c

   struct uz_CurrentControl_config config = {
      .decoupling_select = im_rotor_flux_decoupling,
      .config_id = id_pi_config,
      .config_iq = iq_pi_config,
      .config_IM = motor,
      .Kp_adjustment_flag = false,
      .max_modulation_index = 1.0f / sqrtf(3.0f),
   };

   uz_CurrentControl_t *controller = uz_CurrentControl_init(config);

General sample interface
========================

.. doxygenstruct:: uz_CurrentControl_input_t
   :members:

.. doxygenstruct:: uz_CurrentControl_output_t
   :members:

.. doxygenfunction:: uz_CurrentControl_sample_general

``omega_dq_rad_per_sec`` is the signed synchronous velocity of the flux frame.
``omega_limitation_rad_per_sec`` is kept separate because the voltage limiter
uses its sign to select d- or q-axis priority. The optional
``v_additional_Volts`` input allows a resonant controller to contribute voltage
before the common limitation.

Standalone decoupling
=====================

.. doxygenfunction:: uz_CurrentControl_IM_decoupling

The implemented feed-forward terms are

.. math::

   u_{d,\mathrm{dec}}=-\omega_s\sigma L_s i_q,

.. math::

   u_{q,\mathrm{dec}}=\omega_s\sigma L_s i_d
     +\omega_s\frac{L_m}{L_r}\lvert\Psi_r\rvert.

The decoupling function is stateless. It validates machine parameters, current,
speed and rotor flux before calculating its output.

Runtime parameter update
========================

.. doxygenfunction:: uz_CurrentControl_set_IM_parameters

Reset
=====

.. doxygenfunction:: uz_CurrentControl_reset

Reset clears both PI integrators, external clamping, flux approximations and
gain-adjustment state. Machine parameters remain configured.

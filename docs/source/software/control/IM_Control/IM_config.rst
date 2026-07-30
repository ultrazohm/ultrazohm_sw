.. _uz_IM_config:

============================
Induction machine configuration
============================

``uz_IM_config`` provides the common machine-parameter type, parameter
validation, derived machine quantities and the discrete state-space model used
by the Kalman-filter observer.

Machine parameters
==================

.. doxygenstruct:: uz_IM_t
   :members:

All resistance and inductance values are per-phase, star-equivalent quantities
referred to the stator side. Delta-connected machine parameters must be
converted before use.

The active compile-time preset is selected in
``uz/uz_IM_config/uz_IM_motor_config.h`` and returned as a validated structure:

.. doxygenfunction:: uz_IM_config_get_selected_motor

.. code-block:: c

   uz_IM_t motor = uz_IM_config_get_selected_motor();

Adding a preset
---------------

To add another machine:

#. Add a unique ``MOTOR_CONFIG_*`` identifier.
#. Add a conditional parameter block containing every required motor, control,
   protection, observer and U/f parameter.
#. Select it through ``MOTOR_CONFIG_SELECT``.
#. Verify the preset with the IM configuration unit tests.

Validation and helper functions
===============================

.. doxygenfunction:: uz_IM_config_assert

.. doxygenfunction:: uz_IM_get_Ls

.. doxygenfunction:: uz_IM_get_Lr

.. doxygenfunction:: uz_IM_get_sigma

.. doxygenfunction:: uz_IM_get_tau_r

.. doxygenfunction:: uz_IM_get_id_ref_for_psi_r

The leakage factor is calculated as

.. math::

   \sigma = 1 - \frac{L_m^2}{L_s L_r},

with :math:`L_s=L_{\sigma s}+L_m` and
:math:`L_r=L_{\sigma r}+L_m`.

State-space model
=================

.. doxygenstruct:: uz_IM_ss_t
   :members:

.. doxygenfunction:: uz_IM_ss_compute

The state-space model uses

.. math::

   x = \begin{bmatrix}i_\alpha & i_\beta &
       \Psi_{r,\alpha} & \Psi_{r,\beta}\end{bmatrix}^{T}.

The speed-independent matrix terms, input matrix, process covariance and
measurement covariance are prepared once during software initialization.
Speed-dependent terms are updated by the observer during every ISR step.

Reset behavior
==============

``uz_IM_t`` and ``uz_IM_ss_t`` contain values rather than dynamic controller
states. They do not require reset functions. Recreating them with
``uz_IM_config_get_selected_motor`` and ``uz_IM_ss_compute`` produces complete,
deterministic structures.

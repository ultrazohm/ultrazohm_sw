.. _uz_IM_observers:

============
IM observers
============

The observer manager provides one output format for a deterministic rotor-flux
observer and a linear Kalman-filter observer. It also implements the startup
fallback used before current calibration and state-space initialization are
complete.

Observer manager
================

.. doxygenstruct:: im_observer_result_t
   :members:

.. doxygenfunction:: im_observer_step

When ``kf_ready`` is false, the deterministic observer output is returned.
When the Kalman filter is ready, ``use_kalman_filter`` selects the output used
by the FOC. The deterministic observer can remain active to provide a separate,
smooth frequency reference for resonant control.

Deterministic rotor-flux observer
=================================

.. doxygenstruct:: im_rotor_flux_observer_state_t
   :members:

.. doxygenstruct:: im_rotor_flux_observer_output_t
   :members:

.. doxygenfunction:: im_rotor_flux_observer_init

.. doxygenfunction:: im_rotor_flux_observer_step

The observer integrates the current-model rotor-flux equations in alpha/beta
coordinates using the bilinear (Tustin) method. It derives flux magnitude and
angle, transforms measured current into the flux-oriented dq frame and uses a
PLL to estimate stator frequency.

Calling ``im_rotor_flux_observer_init`` again clears both flux components,
angle, magnitude and the existing PLL state.

Kalman-filter observer
======================

.. doxygenstruct:: im_kf_observer_state_t
   :members:

.. doxygenfunction:: im_kf_observer_init

.. doxygenfunction:: im_kf_observer_step

.. doxygenfunction:: im_kf_observer_pll_step

The Kalman filter estimates

.. math::

   x = \begin{bmatrix}i_\alpha & i_\beta &
       \Psi_{r,\alpha} & \Psi_{r,\beta}\end{bmatrix}^{T}

from measured stator currents, encoder speed and the phase voltage applied in
the previous ISR period. Its measurement matrix is
:math:`H=[I_2\;0]`, allowing an analytic two-by-two inversion of the innovation
covariance.

The PLL step is deliberately called after the main Kalman function returns.
This avoids keeping the Kalman matrix locals live on the limited ISR stack
while the PLL executes trigonometric functions.

Initialization resets the state estimate, innovation diagnostics and Kalman
gain diagnostics, sets the covariance to the identity matrix and resets the
PLL. Invalid estimates report ``ERR_NAN_OBSERVER``.

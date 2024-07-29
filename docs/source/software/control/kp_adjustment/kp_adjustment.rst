.. _uz_kp_adjustment:

==================
Kp adjustment
==================

.. doxygenfunction:: uz_CurrentControl_kp_adjustment

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate kp adjustment parameters.

  #include "uz_kp_adjustment.h"
  int main(void) {
    struct uz_CurrentControl_config config = {
    config_iq.samplingTime_sec = 0.00001f
    };  //only this parameter is needed
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    struct uz_3ph_dq_t i_actual_Ampere = {.d = 0.8f, .q = 0.8f, .zero = 0.0f};
    struct uz_3ph_dq_t i_reference_Ampere = {.d = 1.0f, .q = 1.0f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_approx = {.d = 0.00040f, .q = 0.0019f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_reference = {.d = 0.00045f, .q = 0.002f, .zero = 0.0f};
    float factor = 2.0f //Magnitude optimum factor
    uz_3ph_dq_t new_Kp = uz_CurrentControl_kp_adjustment(i_actual_Ampere, i_reference_Ampere, flux_approx, flux_reference, sample_time, factor);
    }

Description
^^^^^^^^^^^
 
Calculates the new adjusted values of the kp parameters following the functions described in [[#Schroeder_Regelung]_, p. 913] or [[#Gemassmer_Diss]_, p. 102].

.. math::

    \overline{L}_{dd} = \frac{\psi_{d}(i_{d}^*,i_{q})-\psi_{d}(i_{d},i_{q})}{i_{d}^*-i_{d}} \\
    \overline{L}_{qq} = \frac{\psi_{q}(i_{d},i_{q}^*)-\psi_{q}(i_{d},i_{q})}{i_{q}^*-i_{q}}

Then the new Kp parameters can be calculated:

.. math::

    K_{p,d} = \frac{\overline{L}_{dd}}{2\tau_\sigma}  \qquad \qquad \qquad K_{p,q} = \frac{\overline{L}{qq}}{2\tau_\sigma}

Set Kp adjustment
-----------------

.. doxygenfunction:: uz_CurrentControl_set_kp_adjustment

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to set new kp adjustment parameters.

  int main(void) {
    struct uz_CurrentControl_config config = {
    config_iq.samplingTime_sec = 0.00001f
    };  //only this parameter is needed
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    struct uz_3ph_dq_t i_actual_Ampere = {.d = 0.8f, .q = 0.8f, .zero = 0.0f};
    struct uz_3ph_dq_t i_reference_Ampere = {.d = 1.0f, .q = 1.0f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_approx = {.d = 0.00040f, .q = 0.0019f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_reference = {.d = 0.00045f, .q = 0.002f, .zero = 0.0f};
    float factor = 2.0f //Magnitude optimum factor
    uz_CurrentControl_set_flux_approx(instance,flux_approx); //This sets the parameters in the CurrentControl instance
    uz_CurrentControl_set_kp_adjustment(instance, i_reference_Ampere, i_actual_Ampere, flux_reference, config.config_iq.samplingTime_sec, factor);
    }

.. note::

  In a normal use case the flux values are not steady. Normally this function is getting called with the flux approximation functions.

Description
^^^^^^^^^^^

Allocates the memory for the Current Control instance. 
Furthermore the new adjusted values of the kp parameters are asserted.

.. [#Schroeder_Regelung] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Joachim Böcker, Springer, 2021, 5. Edition (German)
.. [#Gemassmer_Diss] Effiziente und dynamische Drehmomenteinprägung in hoch ausgenutzten Synchronmaschinen mit eingebetteten Magneten, Tobias Gemaßmer, KIT Scientific Publishing, ISBN: 978-3-7315-0366-8
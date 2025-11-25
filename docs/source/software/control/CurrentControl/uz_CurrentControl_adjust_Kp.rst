.. _uz_kp_adjustment:

=============
Kp adjustment
=============

.. doxygenfunction:: uz_CurrentControl_adjust_Kp

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate kp adjustment parameters.

  int main(void) {
    struct uz_CurrentControl_config config = {
    config_iq.samplingTime_sec = 0.00001f
    };  //only this parameter is needed
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    struct uz_3ph_dq_t i_actual_Ampere = {.d = 0.8f, .q = 0.8f, .zero = 0.0f};
    struct uz_3ph_dq_t i_reference_Ampere = {.d = 1.0f, .q = 1.0f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_approx_real = {.d = 0.00040f, .q = 0.0019f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_approx_reference = {.d = 0.00045f, .q = 0.002f, .zero = 0.0f};
    float factor = 2.0f //Magnitude optimum factor
    uz_CurrentControl_set_flux_approx(instance,flux_approx_real,flux_approx_reference);
    uz_CurrentControl_adjust_Kp(i_actual_Ampere, i_reference_Ampere, factor);
    }

Description
^^^^^^^^^^^
 
Calculates the new adjusted values of the kp parameters following the functions described in [[#Schroeder_Regelung]_, p. 913] or [[#Gemassmer_Diss]_, p. 102].
It has to be used in conjunction with :ref:`uz_CurrentControl_set_flux_approx`.

.. math::

    \overline{L}_{dd} = \frac{\psi_{d}(i_{d}^*,i_{q})-\psi_{d}(i_{d},i_{q})}{i_{d}^*-i_{d}} \\
    \overline{L}_{qq} = \frac{\psi_{q}(i_{d},i_{q}^*)-\psi_{q}(i_{d},i_{q})}{i_{q}^*-i_{q}}

Then the new Kp parameters can be calculated:

.. math::

    K_{p,d} = \frac{\overline{L}_{dd}}{2\tau_\sigma}  \qquad \qquad \qquad K_{p,q} = \frac{\overline{L}{qq}}{2\tau_\sigma}

If the flag ``Kp_adjustment_flag`` is set to true in the ``uz_CurrentControl_config``, the calculated :math:`K_{p,d}` and :math:`K_{p,q}` are automatically written to the pi controllers.
If false, no adjustment of :math:`K_{p,d}` and :math:`K_{p,q}` is done. 

.. [#Schroeder_Regelung] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Joachim Böcker, Springer, 2021, 5. Edition (German)
.. [#Gemassmer_Diss] Effiziente und dynamische Drehmomenteinprägung in hoch ausgenutzten Synchronmaschinen mit eingebetteten Magneten, Tobias Gemaßmer, KIT Scientific Publishing, ISBN: 978-3-7315-0366-8
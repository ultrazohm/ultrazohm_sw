.. _uz_CurrentControl_set_flux_approx:

======================
Set flux approximation
======================

.. doxygenfunction:: uz_CurrentControl_set_flux_approx

.. code-block:: c
  :linenos:
  :caption: Example function call to set the approximated flux linkages in a CurrentControl instance.

  int main(void) {
  struct uz_CurrentControl_config config = {0};
  struct uz_3ph_dq_t flux_approx_real = {.d = 0.00038f, .q = 0.0018f, .zero = 0.0f};
  struct uz_3ph_dq_t flux_approx_reference = {.d = 0.00040f, .q = 0.0019f, .zero = 0.0f};
  uz_CurrentControl_set_flux_approx(instance,flux_approx_real,flux_approx_reference);
  }

Description
^^^^^^^^^^^

This function sets the parameters of the approximated flux for usage in other CurrentControl functions.
To calculate the flux approximations see :ref:`uz_flux_approximation` .
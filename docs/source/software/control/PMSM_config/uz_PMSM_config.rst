.. _uz_PMSM_config:

===========
PMSM config
===========

Motor parameters of a permanent magnet synchronous motor (PMSM) are needed for multiple functions.
To streamline the coding process, every necessary PMSM parameter is be bundled inside a ``uz_PMSM_t`` struct, which can be used in the whole UltraZohm project. 

.. doxygenstruct:: uz_PMSM_t
    :members:

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call for configuration
  
  #include "uz/uz_PMSM_config/uz_PMSM_config.h"
  int main(void) {
     struct uz_PMSM_t config = {
      .R_ph_Ohm = 0.08f,
      .Ld_Henry = 0.00027f,
      .Lq_Henry = 0.00027f,
      .Psi_PM_Vs = 0.0082f,
      .polePairs = 4.0f,
      .J_kg_m_squared = 0.00001773f,
      .I_max_Ampere = 10.0f
     }; 
  }


To avoid code duplication a function, which asserts every struct member, is available. 

.. doxygenfunction:: uz_PMSM_config_assert
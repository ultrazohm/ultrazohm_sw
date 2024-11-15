.. _uz_flux_approximation:

==================
Flux approximation
==================

This module implements a method to approximate flux-linkages using the approach described in [[#Shih_Wei_Su_flux_approx]_].

Setup
-----

.. _uz_flux_approximation_config:

Configuration
-------------

In order to configure the flux approximation, the fitting parameter struct has to be initialized.


.. doxygenstruct:: uz_PMSM_flux_fitting_parameter_config_t

.. code-block:: c
  :linenos:
  :caption: Example to initialize the fitting parameter struct.
  
  #include "uz_approximate_flux.h"
  int main(void) {
    struct uz_PMSM_flux_fitting_parameter_config_t fitting_config = {
      .ad1_parameter = 0.030483840951002f,
      .ad2_parameter = 0.040244227373267f,
			.ad3_parameter = -16.481195185733903f,
		  .ad4_parameter = 1.296438633344970f,
			.ad5_parameter = 6.183163374457993e-04f,
			.ad6_parameter = -12.275586044862504f,
			.aq1_parameter = 0.004816670542863f,
			.aq2_parameter = 0.171595254784258f,
			.aq3_parameter = 9.262938633610718e-04f,
			.aq4_parameter = 0.005001870975338f,
			.aq5_parameter = 0.170521235710151f,
			.aq6_parameter = 9.186084507499523e-04f,
			.F1G1_parameter = -0.001356794026337f,
			.F2G2_parameter = 0.078813850391713f
    };
  }

Description
^^^^^^^^^^^

With this fitting config struct one can approximate the flux-linkages for a specific machine.
The fitting parameter can be found solving the nonlinear-square problems discribed in [[#Shih_Wei_Su_flux_approx]_].
For more information of how to get the fitting parameter see :ref:`uz_flux_approximation_script`.

.. _uz_flux_approximation_init:

Init function
-------------

.. doxygentypedef:: uz_approximate_flux_t
.. doxygenfunction:: uz_approximate_flux_init

Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call to init a flux approximation instance.

    int main(void) {
     uz_approximate_flux_t* approximate_flux_instance = uz_approximate_flux_init(fitting_config);;
  }

Description
^^^^^^^^^^^

Allocates the memory for the flux approximation instance. 
Furthermore the input values of the fitting parameter struct are asserted.

.. _uz_flux_approximation_step:

Step function
-------------

.. doxygenfunction:: uz_approximate_flux_step

.. code-block:: c
  :linenos:
  :caption: Example function call to approximate the flux linkages.

    #include "uz_approximate_flux.h"
    #include "../../../src/uz/uz_approximate_flux/approximate_flux_ert_rtw/approximate_flux.h"
    int main(void) {
    uz_PMSM_flux_fitting_parameter_config_t fitting_config = {
      .ad1_parameter = 0.030483840951002f;
	    .ad2_parameter = 0.040244227373267f;
	    .ad3_parameter = -16.481195185733903f;
	    .ad4_parameter = 1.296438633344970f;
	    .ad5_parameter = 6.183163374457993e-04f;
	    .ad6_parameter = -12.275586044862504f;
	    .aq1_parameter = 0.004816670542863f;
	    .aq2_parameter = 0.171595254784258f;
	    .aq3_parameter = 9.262938633610718e-04f;
	    .aq4_parameter = 0.005001870975338f;
	    .aq5_parameter = 0.170521235710151f;
	    .aq6_parameter = 9.186084507499523e-04f;
	    .F1G1_parameter = -0.001356794026337f;
	    .F2G2_parameter = 0.078813850391713f;
    };
    uz_approximate_flux_t* test_instance = uz_approximate_flux_init(fitting_config);
    struct uz_3ph_dq_t i_actual_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_approx = uz_approximate_flux_step(test_instance, i_actual_Ampere);
    }

Description
^^^^^^^^^^^

Approximates the flux linkages in both axis using analytic prototype functions from [[#Shih_Wei_Su_flux_approx]_]

.. _uz_approximate_flux_reference_step:

Reference step function
-----------------------

.. doxygenfunction:: uz_approximate_flux_reference_step

.. code-block:: c
  :linenos:
  :caption: Example function call to approximate the reference flux linkages.

    #include "uz_approximate_flux.h"
    #include "../../../src/uz/uz_approximate_flux/approximate_flux_ert_rtw/approximate_flux.h"
    int main(void) {
    uz_PMSM_flux_fitting_parameter_config_t fitting_config = {
      .ad1_parameter = 0.030483840951002f;
	    .ad2_parameter = 0.040244227373267f;
	    .ad3_parameter = -16.481195185733903f;
	    .ad4_parameter = 1.296438633344970f;
	    .ad5_parameter = 6.183163374457993e-04f;
	    .ad6_parameter = -12.275586044862504f;
	    .aq1_parameter = 0.004816670542863f;
	    .aq2_parameter = 0.171595254784258f;
	    .aq3_parameter = 9.262938633610718e-04f;
	    .aq4_parameter = 0.005001870975338f;
	    .aq5_parameter = 0.170521235710151f;
	    .aq6_parameter = 9.186084507499523e-04f;
	    .F1G1_parameter = -0.001356794026337f;
	    .F2G2_parameter = 0.078813850391713f;
    };
    uz_approximate_flux_t* test_instance = uz_approximate_flux_init(fitting_config);
    struct uz_3ph_dq_t i_actual_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
    struct uz_3ph_dq_t i_reference_Ampere = {.d = 2.0f, .q = 4.0f, .zero = 0.0f};
    struct uz_3ph_dq_t flux_reference = uz_approximate_flux_reference_step(test_instance,i_reference_Ampere,i_actual_Ampere);
    }

Description
^^^^^^^^^^^

Approximates the flux linkages in both axis using analytic prototype functions from [[#Shih_Wei_Su_flux_approx]_].
This function is mainly used to adjust the control parameters during runtime. This follows the approach discribed in [[#Schroeder_Regelung]_, p. 913] or [[#Gemassmer_Diss]_, p. 102].

Set flux approximation
----------------------

.. doxygenfunction:: uz_CurrentControl_set_flux_approx

.. code-block:: c
  :linenos:
  :caption: Example function call to set the approximated flux linkages in a CurrentControl instance.

  int main(void) {
  struct uz_CurrentControl_config config = {0};
  struct uz_3ph_dq_t flux_approx = {.d = 0.00040f, .q = 0.0019f, .zero = 0.0f};
  uz_CurrentControl_set_flux_approx(instance,flux_approx);
  }

Description
^^^^^^^^^^^

This function sets the parameters of the approximated flux so it can be used in other CurrentControl functions.

.. [#Shih_Wei_Su_flux_approx] Analytical Prototype Functions for Flux Linkage Approximation in Synchronous Machines, Shih-Wei Su, Christoph M. Hackl, and Ralph Kennel, IEEE Open Journal of the Industrial Electronics Society, vol. 3, pp. 265-282, 2022, doi: 10.1109/OJIES.2022.3162336
.. [#Schroeder_Regelung] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Joachim Böcker, Springer, 2021, 5. Edition (German)
.. [#Gemassmer_Diss] Effiziente und dynamische Drehmomenteinprägung in hoch ausgenutzten Synchronmaschinen mit eingebetteten Magneten, Tobias Gemaßmer, KIT Scientific Publishing, ISBN: 978-3-7315-0366-8
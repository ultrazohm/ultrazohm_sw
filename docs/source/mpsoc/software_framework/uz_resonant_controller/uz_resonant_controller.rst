.. _uz_resonant_controller:

===================
Resonant controller
===================

Toolbox for a standard resonant controller.
The ideal transfer function is:

.. math::

  \frac{Y(s)}{E(s)}= K_R \cdot \frac{s}{s^2 + \omega_R^2}

with the resonant frequency :math:`\omega_R`.

The implemented discrete time transfer function is created by impulse invariant discretization with delay compensation [[#DiscPaper]_] and is:

.. math::

    G_R(s) = K_R T_{s} \frac{\cos(2\omega_R T_{s}) - z^{-1}\cos(\omega_R T_{s}) }{1-2 z^{-1} \cos(\omega_R T_{s} )+ z^{-2} }

The resonant frequency is specified by :math:`\omega_R = h \cdot \omega_{el}`, with the order of the harmonic :math:`h` to be controlled and the fundamental frequency :math:`\omega_{el}`.

Resonant-Controller
-------------------

.. doxygentypedef:: uz_resonantController_t


Description
^^^^^^^^^^^

Struct to create a resonant controller instance.


.. doxygenstruct:: uz_resonantController_config
  :members:

Description
^^^^^^^^^^^

Struct for the configuration of the resonant controller.


Init function
-------------

.. doxygenfunction:: uz_resonantController_init


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example to create and initialize a resonant controller instance.

  int main(void) {
    
    const struct uz_resonantController_config config_R = {
        .sampling_time = 0.0001f,
        .gain = 52.5f,
        .harmonic_order = 2.0f,
        .fundamental_frequency = 10.0f,
        .lower_limit = -4.0f,
        .upper_limit = 4.0f,
        .antiwindup_gain = 10.0f,
        .in_reference_value = 0.0f,
        .in_measured_value = 0.0f,
    };
    uz_resonantController_t* R_controller_instance= uz_resonantController_init(config_R);
  }


Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *



Sources
-------

.. [#DiscPaper] G. Yepes, F. D. Freijedo, J. Doval-Gandoy, Ó. López, J. Malvar, and P. Fernandez-Domesaña , "Effects on Discretization Methods on the Performance of Resonant Controllers," IEEE Transactions on Power Electronics, vol. 25, no. 7, pp. 1692-1712, Jul. 2010

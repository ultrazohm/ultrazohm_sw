===========
dummy_motor
===========

The ``dummy_motor`` dataset is a synthetic dataset for testing and demonstration purposes.

C usage
=======

.. code-block:: c

   #include "uz_PMSM_config.h"

   uz_PMSM_t motor = UZ_PMSM_DUMMY_MOTOR_NOMINAL_V1_INIT;
   uz_PMSM_config_assert(motor);
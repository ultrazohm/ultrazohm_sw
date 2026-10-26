===========
dummy_motor
===========

The ``dummy_motor`` dataset is a synthetic dataset for testing and demonstration purposes.
It is part of the :ref:`uz_pmsm` motor database; see there for the file formats and how to add a motor.

C usage
=======

.. code-block:: c

   #include "uz_PMSM_config.h"

   uz_PMSM_t motor = UZ_PMSM_DUMMY_MOTOR_NOMINAL_V1_INIT;
   uz_PMSM_config_assert(motor);
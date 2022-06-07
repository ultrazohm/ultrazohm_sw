.. _uz_123_alphabeta_dq_transformation:

=======================================
123_alphabeta_dq Transformation IP-Core
=======================================

- Transforms three input quantities from a three phase system to alpha_beta-coordinates to dq-coordinates
- Input interface is PL-only
- Transformation can only be triggered by a PL signal, but not by the software driver
- Output is supplied to PL-ports as well as AXI4-Lite
- Inputs have to be fixed point and match the interface description of :ref:`ipCore_123_alphabeta_dq_tranformation_interfaces`
- The inputs are transformed on each rising edge on the IP-Core input ``CurrentValid_in``
- ``dq_Done`` indicates that the output values are valid to subsequent IP-Cores

Table :ref:`ipCore_123_alphabeta_dq_tranformation_interfaces` lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. _ipCore_123_alphabeta_dq_tranformation_interfaces:

.. csv-table:: Interface of 123_alphabeta_dq Transformation IP-Core
   :file: dq_transformation_register_mapping.csv
   :widths: 50 50 50 50 50 50 200
   :header-rows: 1

Vitis
=====

Initialize one driver instance and read output:

.. code-block:: c

   static struct uz_dqIPcore_config_t config={
   .base_address= TEST_BASE_ADDRESS,
   .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
   .theta_offset = -1.5f // add your encoder offset here!
   };

   uz_dqIPcore_t* test_instance = uz_123_alphabeta_dqIPcore_init(config);
   uz_3ph_dq_t currents = uz_123_alphabeta_dqIPcore_get_id_iq(test_instance);

.. warning:: The software driver has no way to read the trigger transformation signal ``CurrentValid_in`` nor the output valid signal ``dq_Done``! Thus, the user has to be sure that a transformation took place and is finished. This means that the driver can mostly be used for debugging control algorithms that are fully implemented in the PL!

Driver reference
****************

.. doxygentypedef:: uz_dqIPcore_t

.. doxygenstruct:: uz_dqIPcore_config_t
   :members:

.. doxygenfunction:: uz_123_alphabeta_dqIPcore_init

.. doxygenfunction:: uz_123_alphabeta_dqIPcore_get_id_iq

.. doxygenfunction:: uz_123_alphabeta_dqIPcore_get_i_abc

.. doxygenfunction:: uz_123_alphabeta_dqIPcore_get_i_alphabeta



Vivado
======

.. figure:: trans_123_alphabeta_dq_VIVADO.jpg

The only tested clock frequency for ``IPCORE_CLK`` and ``AXI4_Lie_ACLK`` is 50 Mhz.

.. csv-table:: Vivado block design interfaces of 123_alphabeta_dq Transformation IP-Core
   :file: ./dq_VivadoInterface.csv
   :widths: 50 50 50
   :header-rows: 1
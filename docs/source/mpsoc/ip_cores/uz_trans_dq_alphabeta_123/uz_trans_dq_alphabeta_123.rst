.. _ipCore_dq_alphabeta_123 Transformation:

=======================================
dq_alphabeta_123 Transformation IP-Core
=======================================

- Transforms two input quantities from a dq_ref phase system to alpha/beta-coordinates to abc-coordinates
- Input interface of the dq_ref system is AXI4-Lite only
- Transformation can only be triggered by a PL signal, but not by the software driver
- Outputs are supplied to PL-ports as well as AXI4-Lite
- Inputs have to be fixed point and match the interface description of :ref:`ipCore_dq_alphabeta_123 Transformation_interfaces`
- The inputs are transformed on each rising edge on the IP-Core input ``CurrentValid_in``
- ``dq_Done`` indicates that the output values are valid to subsequent IP-Cores

Table :ref:`ipCore_dq_alphabeta_123 Transformation_interfaces` lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. _ipCore_dq_alphabeta_123 Transformation_interfaces:

.. csv-table:: Interface of dq_alphabeta_123 Transformation IP-Core
   :file: dq_alphabeta_123_transformation_register_mapping.csv
   :widths: 50 50 50 50 50 50 200
   :header-rows: 1

Vitis
=====

Initialize one driver instance and read output for the alpha/beta currents:

.. code-block:: c

   struct uz_dq_alphabeta_123_IPcore_config_t config={
   				   .base_address= BASE_ADDRESS,
   				   .ip_clk_frequency_Hz=IP_CORE_FRQ,
   				   .theta_offset = 1.5f,   //add your encoder offset here!
   				   .id_ref = 0,  //add your id_ref initial current here!
   				   .iq_ref = 30  //add your iq_ref initial current here!
   				};

   uz_dq_alphabeta_123_IPcore_t* test_instance = uz_dq_alphabeta_123_IPcore_init(config);
   struct uz_3ph_alphabeta_t currents = uz_dq_alphabeta_123_IPcore_get_ialpha_ibeta(test_instance);

Update the idref and iqref currents while the IP-Core is running: 

.. code-block:: c

   struct uz_dq_alphabeta_123_IPcore_update_t update={
   				   .base_address= BASE_ADDRESS,
   				   .idref = 0, //add your idref update current here!
   				   .iqref = 30 //add your iqref update current here!
   				};

   uz_dq_alphabeta_123_IPcore_idref_iqref_update(update);

.. warning:: The software driver has no way to read the trigger transformation signal ``CurrentValid_in`` nor the output valid signal ``dq_Done``! Thus, the user has to be sure that a transformation took place and is finished. This means that the driver can mostly be used for debugging control algorithms that are fully implemented in the PL!

Driver reference
****************

.. doxygentypedef:: uz_dq_alphabeta_123_IPcore_t

.. doxygenstruct:: uz_dq_alphabeta_123_IPcore_config_t
   :members:

.. doxygenfunction:: uz_dq_alphabeta_123_IPcore_init

.. doxygenstruct:: uz_dq_alphabeta_123_IPcore_update_t
   :members:

.. doxygenfunction:: uz_dq_alphabeta_123_IPcore_idref_iqref_update

.. doxygenfunction:: uz_dq_alphabeta_123_IPcore_get_i_abc

.. doxygenfunction:: uz_dq_alphabeta_123_IPcore_get_ialpha_ibeta



Vivado
======

.. figure:: trans_dq_alphabeta_123_IP_Core_VIVADO.JPG

The only tested clock frequency for ``IPCORE_CLK`` and ``AXI4_Lie_ACLK`` is 50 Mhz.

.. csv-table:: Vivado block design interfaces of dq_alphabeta_123 Transformation IP-Core
   :file: dq_alphabeta_123_transformation_Vivadointerface.csv
   :widths: 50 50 50
   :header-rows: 1
.. _uz_resolver_pl_interface:

=====================
Resolver PL Interface
=====================

This IP Core is designed as an add-on to the Resolver Interface ``uz_resolverIP``. There are three intended use-cases.

1. This IP Core provides angle and speed outputs in fixed-point SI values in the FPGA for control applications in the FPGA. 
It handles all dependencies to the number of polepairs of the resolver and the machine, as well as angle zero point offset between resolver and machine. 
The electrical and mechanical angle are limited to the range of :math:`0..2{\pi}`.

2. For control algorithms in the processor, saving every :math:`{\mu}s` of calculation effort is sometimes crucial. Therefore most of the software driver 
functionality of the ``uz_resolverIP`` can be "outsourced" into this IP Core. Therefore, no calculations from raw values of the resolver with respect 
to polepairs and offsets will cause workload in the processor, just reading angles and speeds via AXI is necessary.

3. Sometimes you might have a unfavorable combination of resolver polepairs and machine polepairs. E.g. machine polepairs :math:`p_m=5` and resolver polepairs :math:`p_r=2` 
results in a fractional ratio between mechanical and electrical revolutions of the machine and the resolver. A strategy to deal with this is to convert the resolver revolutions 
to one mechanical revolution of the machine and derive electrical revolutions from there. This comes at the cost of loosing absolute position information in the beginning and in the need for  
a defined mechanical init position of the machine at startup. The IP Core handles this complicated sounding calculations. The user just has to provide all the polepair numbers 
and has to define the rotational position of the machine at the testbench at startup. Subsequently, all angle and speed information can be used as usual by reading them via AXI.

Interface Definition
====================

.. _simulink_source:

.. figure:: simulink_block.png
   :width: 800
   :align: center

   Simulink source of ``uz_resolver_pl_interface``

Table :ref:`ipCore_resolver_pl_interfaces` lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. _ipCore_resolver_pl_interfaces:

.. csv-table:: Interface of resolver_pl_interface IP-Core
   :file: uz_resolver_pl_interface_port_mapping.csv
   :widths: 50 50 50 50 50 50 200
   :header-rows: 1

Example Usage
=============

The following step-by-step description shall guide the user in order to properly implement the IP Core and the respective interface and software drivers.

Vivado Block Design
-------------------

First, the ip core has to be added to the block design in vivado:

1. Go to the place where the Resolver Interface IP Core ``uz_resolverIP`` is located (e.g. inside the already existing ``uz_user`` hierarchy) in the block design.
2. Add the Resolver PL Interface IP Core ``uz_resolver_pl_interface``.
3. Connect the signals as shown below. Pay attention that ``position_out_m``, ``velocity_out_m`` and ``valid_m`` are output signals of the Resolver Interface IP Core and serve as the inputs for all calculations inside the ``uz_resolver_pl_interface`` IP Core.
4. Now the output ports ``to your IP`` can be used inside the FPGA block design. In parallel, the AXI4-Lite values are also available.

.. _ip_core:

.. figure:: ip_core.png
    :width: 800
    :align: center

    IP Core in the Vivado block design

Software driver
---------------

For interacting with the IP Core, the following step-by-step example shows a way of implementing one instance of the software driver.

1. In Vitis, in the Baremetal project under the folder ``hw_init`` create a new file ``uz_resolver_pl_interface_init.c`` 
2. Include necessary files and create ``config`` and ``output`` structs as well as an init function for one or more instances:



.. code-block:: c
 :caption: Example of uz_resolver_pl_interface_init.c

 #include "../include/uz_resolver_pl_interface_init.h"
 #include "../uz/uz_HAL.h"
 #include "../uz/uz_global_configuration.h"
 #include "xparameters.h"
 
 struct uz_resolver_pl_interface_config_t resolver_pl_config_d2 = { 
		.base_address = XPAR_UZ_USER_UZ_RESOLVER_PL_INTER_0_BASEADDR,
		.bitToRPS_factor = BIT_TO_RPS_FACTOR_16BIT,
		.ip_clk_frequency_Hz = 100000000,
		.machine_polepairs = 4,
		.position_intmax = 65535,
		.resolver_polepairs = 1,
		.theta_m_offset_rad = -0.3964f
 };

 struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d2 = {
		.n_mech_rpm = 0.0f,
		.omega_mech_rad_s = 0.0f,
		.position_el_2pi = 0.0f,
		.position_mech_2pi = 0.0f,
		.revolution_counter = 0
 };

 uz_resolver_pl_interface_t* initialize_resolver_pl_d2(void){
	return (uz_resolver_pl_interface_init(resolver_pl_config_d2, resolver_pl_outputs_d2));
 }

3. In the ``include`` folder, create a header file ``uz_resolver_pl_interface_init.h``
4. Include necessary files and the function prototype of your init routine:

.. code-block:: c
 :caption: Example of uz_resolver_pl_interface_init

 #pragma once
 #include "../IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"

 uz_resolver_pl_interface_t* initialize_resolver_pl_d2(void);

5. In the Global_Data header file ``globalData.h``, include necessary header and add an object pointer of the respective type in the ``object_pointer_t`` struct:

.. code-block:: c
 :caption: Lines to add in Global_Data header file

 ... 
 #include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
 ...

 typedef struct{
 ...
 uz_resolver_pl_interface_t* resolver_pl_d2;
 ...
 }object_pointers_t;

6. In ``main.c``, initialize an instance of the driver and assign it the the object pointer structure in the Global_Data inside the ``init_ip_cores`` case:

.. code-block:: c
 :caption: Example of init in main.c
 
 ...
 case init_ip_cores:
 ...
 Global_Data.objects.resolver_pl_d2 = initialize_resolver_pl_d2();
 ...
 break;

7. In ``main.h``, include your init header file  ``#include "include/uz_resolver_pl_interface_init.h"``.
8. In ``isr.c``, now you can read the AXI output values of the IP Core and use them e.g. for your control algorithm:

.. code-block:: c
 :caption: Example of reading IP Core outputs in isr.c

 ...
 YourOutputStruct = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d2);
 ...


Driver reference
----------------

.. doxygentypedef:: uz_resolver_pl_interface_t

.. doxygenstruct:: uz_resolver_pl_interface_config_t
  :members:

.. doxygenstruct:: uz_resolver_pl_interface_outputs_t
  :members:

.. doxygenfunction:: uz_resolver_pl_interface_init

.. doxygenfunction:: uz_resolver_pl_interface_set_config

.. doxygenfunction:: uz_resolver_pl_interface_get_outputs

.. doxygenfunction:: uz_resolver_pl_interface_set_theta_m_offset_rad

.. doxygenfunction:: uz_resolver_pl_interface_reset
.. _uz_inverter_adapter:

================
Inverter Adapter
================

This IP core provides a well defined and highly sophisticated interface for inverter adapter boards for the UltraZohm (e.g. uz_d_gan_inverter). 
It provides many useful features:

   - 6 gate signal outputs
   - 1 gate enable signal output
   - 6 over current (OC) input signals
   - 6 fault (FAULT) input signals
   - 6  pwm input signals for measuring e.g. chip temperatures.
     Duty cycle is calculated to degrees celsius in software driver
   - 4 diagnostic input signals (e.g. power good or signal valid of current amplifiers)

Hardware Interface Definition
=============================

Usage of the IP-core requires a defined pin mapping on the respective inverter adapter board, as shown in the table below.

.. _ipCore_uz_inverter_adapter_interfaces:

.. csv-table:: Defined pin mapping of adapter board
   :file: uz_inverter_adapter_pin_mapping.csv
   :widths: 40 40 60 50 50 
   :header-rows: 1

Organization of the sources
===========================

.. _folder_structure_picture:

.. figure:: img/sources.png
   :width: 300
   :align: center

   Folder structure of the sources in ``ip_cores/uz_d_inverter_adapter/``

Folder structure of the sources in ``ip_cores/uz_d_inverter_adapter/``:

- ``constraint_files`` contains ready to use Vivado constraint files for usage of the adapter board interface in any digital slot D1..D4
- ``driver_ip_core`` contains the ip-core with which the user communicates via the software driver
- ``interface_definition`` contains the Vivado interface definition using the pin names from the constraint files
- ``mapping_ip_core`` contains the ip-core that maps and organizes signals from the adapter board
- ``temperature_calculation`` contains excel sheets for determination of the linear interpolation equation to get temperatures in degrees celsius from a duty cycle value of a PWM signal.
  The parameters of the equation depend on the circuit design and/or the used power electronic switch and have to be determined by the adapter board developer carefully

Example Usage
=============

The following step-by-step description shall guide the user in order to properly implement the ip-core and the respective interface and software drivers

Vivado Block Design
-------------------

First, ip cores have to be added to the block design in vivado:

1. Create a hierarchy (e.g. inside the already existing ``uz_user`` hierarchy) in the block design ``right click -> Create Hierarchy...`` in order to keep the block design clean and name it ``uz_inverter_adapter``
2. Inside this new hierarchy click on the plus (``+``) button to add new ip and first add the ``uz_d_inverter_adapter`` ip-core
3. Next, ``right click -> Add IP...`` and add the ``uz_inverter_adapter_mapping_v1_0`` ip-core
4. Connect all signals between those two ip-cores that have equal names
5. Add an additional AXI Port on the next reachable ``AXI SmartConnect`` ip-core and connect it to the ``uz_d_inverter_adapter`` ip-core, as well as clocks and resets. The ip-core is designed for a 100 MHz clock rate. Do not forget to assign a base address in the Address Editor.
6. Provide gate signals to the ``uz_inverter_adapter_mapping_v1_0`` (e.g. by slicing them from the D1_OUT port of the ``uz_digital_adapter`` hierarchy)

After those steps the block design looks like this:

.. _block_design_picture:

.. figure:: img/blockdesign.png
   :width: 600
   :align: center

   Block design after steps above



Vivado Interface
----------------

Second, the interface between the ip-cores and the physical pins has to be implemented:

1. Inside the top level block design ``right click -> Create Interface Pin...``
2. Name the interface according to the digital slot where you plan to use the inverter adapter board (e.g. ``D1``)
3. In the search fiel type in ``inverter``. There should be a result called ``uz_inverter_adapter_rtl:1.0`` in the ``VLNV`` column. Select it and press ``OK``
4. Connect the interface pin ``D1`` with ``uz_inverter_adapter`` interface port at the ``uz_inverter_adapter_mapping_v1_0`` ip-core (unfolding the hierarchies with the ``+`` buttons in their upper left corner makes it really easy)

After those steps the block design inside your hierarchy looks like this:

.. _block_design_interface_picture:

.. figure:: img/blockdesigninterface.png
   :width: 600
   :align: center

   Block design after steps above



The top level block design looks like this

.. _block_design_top_picture:

.. figure:: img/blockdesigntop.png
   :width: 400
   :align: center

   Top level block design after steps above

Due to our interface using all 30 pins of one digital slot, make sure no other pins (e.g. ``D1_OUT_26`` to ``D1_OUT_29`` in our case) are present in the block design. If yes, simply delet them.

Constraints
-----------
Third, the interface definition we connected in the step before uses specific names for the signals and pins. Those have to match the names of the respective constraint file of the respective digital slot. 
In the subfolder ``constraint_files`` inside the ip-core sources (see :numref:`folder_structure_picture`) ready to use constraint files are prepared for this purpose:

1. Open the respective constraint file (in our example the one for D1: ``Digital_D1_packed.xdc``)
2. Copy everything inside the file
3. Paste and overwrite everything inside the constraint file in your vivado project
4. Save the changed file in your vivado project

After those steps the file looks like this:

.. _constraint_picture:

.. figure:: img/constraints.png
   :width: 600
   :align: center

   Constraint file after copy paste

CPLD program
------------

Keep in mind, that a proper CPLD program for this interface and respective adapter boards is required. It can be found in the ``cpld_lattice`` repository 
under ``uz_d_3ph_inverter``

Software driver
---------------
For interacting with the ip-core, the following step-by-step example shows a way of implementing one instance of the software driver.

1. In Vitis, in the Baremetal project under the folder ``hw_init`` create a new file ``uz_inverter_adapter_init.c`` 
2. Include necessary files and create ``config`` and ``output`` structs as well as an init function for one or more instances:

.. code-block:: c
 :caption: Template for uz_inverter_adapter_init.c

 #include "../include/uz_inverter_adapter_init.h"
 #include "../uz/uz_HAL.h"
 #include "../uz/uz_global_configuration.h"
 #include "xparameters.h"
 
 static struct uz_inverter_adapter_config_t uz_inverter_adapter_config_d1 = {
		.base_address = XPAR_UZ_USER_UZ_INVERTER_ADAPTER_UZ_D_INVERTER_ADAPTER_0_BASEADDR,
		.ip_clk_frequency_Hz = 100000000,
		.linear_interpolation_params = {162.35f, 20.107f}
 };

 static struct uz_inverter_adapter_outputs_t uz_inverter_adapter_outputs_d1 = {
    .PWMdutyCycNormalized_H1 = 0.0f,
    .PWMdutyCycNormalized_L1 = 0.0f,
    .PWMdutyCycNormalized_H2 = 0.0f,
    .PWMdutyCycNormalized_L2 = 0.0f,
    .PWMdutyCycNormalized_H3 = 0.0f,
    .PWMdutyCycNormalized_L3 = 0.0f,
    .ChipTempDegreesCelsius_H1 = 0.0f, /**< Chip temperature of H1 in degrees celsius */
    .ChipTempDegreesCelsius_L1 = 0.0f, /**< Chip temperature of L1 in degrees celsius */
    .ChipTempDegreesCelsius_H2 = 0.0f, /**< Chip temperature of H2 in degrees celsius */
    .ChipTempDegreesCelsius_L2 = 0.0f, /**< Chip temperature of L2 in degrees celsius */
    .ChipTempDegreesCelsius_H3 = 0.0f, /**< Chip temperature of H3 in degrees celsius */
    .ChipTempDegreesCelsius_L3 = 0.0f, /**< Chip temperature of L3 in degrees celsius */
    .OC = 0U,
    .OC_H1 = 0U, /**< Over current OC fault signal of H1 */
    .OC_L1 = 0U, /**< Over current OC fault signal of L1 */
    .OC_H2 = 0U, /**< Over current OC fault signal of H2 */
    .OC_L2 = 0U, /**< Over current OC fault signal of L2 */
    .OC_H3 = 0U, /**< Over current OC fault signal of H3 */
    .OC_L3 = 0U, /**< Over current OC fault signal of L3 */
    .FAULT = 0U,
    .FAULT_H1 = 0U, /**< FAULT signal of H1 */
    .FAULT_L1 = 0U, /**< FAULT signal of L1 */
    .FAULT_H2 = 0U, /**< FAULT signal of H2 */
    .FAULT_L2 = 0U, /**< FAULT signal of L2 */
    .FAULT_H3 = 0U, /**< FAULT signal of H3 */
    .FAULT_L3 = 0U, /**< FAULT signal of L3 */
    .I_DIAG = 0U,
    .I_DC_DIAG = 0U, /**< Diagnostic signal of current amplifier for DC current */
    .I1_DIAG = 0U, /**< Diagnostic signal of current amplifier for phase a current */
    .I2_DIAG = 0U, /**< Diagnostic signal of current amplifier for phase b current */
    .I3_DIAG = 0U /**< Diagnostic signal of current amplifier for phase c current */
 };

 uz_inverter_adapter_t* initialize_uz_inverter_adapter_on_D1(void) {
	return(uz_inverter_adapter_init(uz_inverter_adapter_config_d1, uz_inverter_adapter_outputs_d1));
 }


3. When using the pwm measurement feature of the ip core (e.g. for measuring temperatures), set the values in the above ``linear_interpolation_params`` struct according to the linear interpolation function that calculates readable 
SI-values from the duty cycle information. The example values above of ``162.35`` and ``20.107`` are valid for the uz_d_gan_inverter adapter board and the respective TI LMG3425 GaN switch. See also the folder ``temperature_calculation`` in the sources of this ip-core driver for details. 

.. _linear_interpolation:

.. figure:: img/linearinterpolation.png
   :width: 600
   :align: center

   Determination of values for linear_interpolation_params struct


4. In Vitis, in the Baremetal project under the folder ``include`` create a new file ``uz_inverter_adapter_init.h``. 



5. Include necessary files and declare the init functions for one or more instances:

.. code-block:: c
 :caption: Template for uz_inverter_adapter_init.h

 #pragma once
 #include "../IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"

 uz_inverter_adapter_t* initialize_uz_inverter_adapter_on_D1(void);


6. In Vitis, in the Baremetal project in ``main.h`` include necessary header files:

.. code-block:: c
 :caption: Additions for main.h

 #include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
 #include "include/uz_inverter_adapter_init.h"



7. In Vitis, in the Baremetal project in ``globalData.h`` include necessary header file:

.. code-block:: c
 :caption: Includes in globalData.h

  #include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"



8. In the same file, add an object pointer variable in the ``object_pointers_t`` struct:

.. code-block:: c
 :caption: Additions in globalData.h

  typedef struct {
  ...
  uz_inverter_adapter_t* inverter_d1;
  }object_pointers_t;



9. In Vitis, in the Baremetal project in ``main.c`` initialize an instance:

.. code-block:: c
 :caption: Initialize instance

    case init_ip_cores:
    ...
    Global_Data.objects.inverter_d1 = initialize_uz_inverter_adapter_on_D1();
    break;



10. For reading signals and states of the ip-core use the function ``uz_inverter_adapter_get_outputs`` which updates the states and returns them in the form of a ``uz_inverter_adapter_outputs_t`` struct. This 
way you can get the states of the status signals of the driver e.g. for assigning them into the ``Global_Data`` struct. 

.. code-block:: c
 :caption: Example usage of uz_inverter_adapter_get_outputs function

  void ISR_Control(void *data)
  {
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
  ..
   }


In order to enable the gates of the power electronics use the function ``uz_inverter_adapter_set_PWM_EN``. After power up, the gates are disabled by default.

.. code-block:: c
   :caption: Example usage of uz_inverter_adapter_PWM_EN function

    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);



Reference
=========

.. doxygentypedef:: uz_inverter_adapter_t

.. doxygenstruct:: linear_interpolation_params_t
  :members:



.. doxygenstruct:: uz_inverter_adapter_config_t
  :members:

.. doxygenstruct:: uz_inverter_adapter_outputs_t
  :members:

.. doxygenfunction:: uz_inverter_adapter_update_states

User interfaces
---------------

.. doxygenfunction:: uz_inverter_adapter_init

.. doxygenfunction:: uz_inverter_adapter_set_PWM_EN

.. doxygenfunction:: uz_inverter_adapter_get_outputs

Helper functions
----------------

.. doxygenfunction:: extract_state_from_bitpattern

.. doxygenfunction:: uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius
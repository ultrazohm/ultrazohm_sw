.. _uz_resolverIP:

==================
Resolver Interface
==================

The ResolverIP interface implements communication between the Ultrazohm PS and PL and the `AD2S1210 <https://www.analog.com/media/en/technical-documentation/data-sheets/AD2S1210.pdf>`_ resolver-to-digital converter IC on the Encoder Board.

Introduction
============

The Ultrazohm PL and the IC interact via a :math:`12.5MHz` SPI Bus. New position or velocity values can be obtained with a maximum frequency of :math:`400kHz`. The delay between triggering and a new value becoming valid is :math:`2.48 \mu s`.

As illustrated by figure :numref:`structure`, the AD2S1210 continously outputs an excitation signal on Pins 5 and 6 of J1 of the Encoder Board. A resolver connected to J1 will return two differential signals (Cos +/-, Sin +/-). Upon triggering via the N_SAMPLE signal, these analog signals are converted. Position and velocity values are stored in registers of the AD2S1210. Depending on the user's need, either position or velocity or both values can be read out by the PL via SPI. Raw values are made available in the PL as IPCore outputs. Also, raw values can be transfered to the PS via the AXI-Bus. Functions for post-processing of the raw values in the PS are implemented.

.. _structure:

.. figure:: structure_resolverIP1.png
   :width: 800
   :align: center

   Block diagram of resolverIP IP Core 



The ResolverIP interface also allows for reading and writing register values of the AD2S1210. This fuctionality can be used to modify i.e. the resolver excitation frequency. For more details on register functionalities, 
er to the `AD2S1210 Datasheet <https://www.analog.com/media/en/technical-documentation/data-sheets/AD2S1210.pdf>`_ and the documentation :ref:`below <FunctionList>`.


Setup
=====
To use the ResolverIP interface, set up your hardware as described in the respective adapter board documentation, set up your Vivado project as described below in :ref:`Vivado Setup <vivado_setup>` and use the Vitis functions as described further below in :ref:`Vitis Setup <vitis_setup>`.

.. _vivado_setup:

Vivado Setup
************

For successful SPI communication, make sure that the following pins of the AD2S1210 are routed from the Encoder Board to the PL via the CPLD:

.. list-table:: Connection Table for SPI Communication 
   :widths: 25
   :header-rows: 1
   :align: center

   * - AD2S1210 Pin
   * - SPI_MOSI
   * - SPI_MISO
   * - SPI_CLK
   * - SPI_SS
   * - N_SAMPLE
   * - N_RESET
   * - F_SYNC
   * - A0
   * - A1

The IP core shown in figure :numref:`pic_Resolver_ipCore` can be added to the project's block design. The source files can be found in ``ip_cores\uz_resolverIP\src``. 

.. _pic_Resolver_ipCore:

.. figure:: pic_ResolverIPCore1.png
   :width: 300
   :align: center

   Resolver IP Core in Vivado Block design 

The pins of the IP Core have the following functionalities:

.. list-table:: Functionality of Resolver IP Core pins 
   :widths: 25 400
   :header-rows: 1
   :align: center

   * - Pin
     - Functionality
   * - s00_axi
     - AXI-Interface, connect to to AXI-SmartConnect
   * - SPI_MISO
     - SPI Interface, connect to pin DIG_IO_09 of Encoder Board 
   * - sample_trigger
     - if sample_trigger = '1' and SPI Communication is not busy, a position and/or velocity conversion of the AD2S1210 is triggered via the N_SAMPLE signal. SPI Communication reads in position and/or velocity values to the PL. Values are made available to the PL via position_out_m and/or velocity_out_m pins. Values are made available to the PS via AXI registers. Connect to trigger source.
   * - s00_axi_aclk
     - Clock, connect to respective global clock, this clock is used for AXI and for clocking of all processes of the IPCore
   * - s00_axi_aresetn
     - Reset, connect to respective global reset, this Reset is used for AXI and for resetting of all processes of the IPCore
   * - SPI_MOSI
     - SPI Interface, connect to pin DIG_IO_08 of Encoder Board  
   * - SPI_SCLK
     - SPI Interface, connect to pin DIG_IO_07 of Encoder Board
   * - SPI_SS
     - SPI Interface, connect to pin DIG_IO_10 of Encoder Board
   * - busy
     - indicates busy SPI communication
   * - error
     - indicates internal State Machine failure, never happened during testing
   * - AD2S1210_n_reset
     - AD2S1210 Interface, connect to pin DIG_IO_13 of Encoder Board
   * - AD2S1210_n_sample
     - AD2S1210 Interface, connect to pin DIG_IO_12 of Encoder Board
   * - AD2S1210_n_fsync
     - AD2S1210 Interface, connect to pin DIG_IO_11 of Encoder Board
   * - AD2S1210_mode_A0
     - AD2S1210 Interface, connect to pin DIG_IO_15 of Encoder Board
   * - AD2S1210_mode_A1
     - AD2S1210 Interface, connect to pin DIG_IO_14 of Encoder Board
   * - position_out_m
     - 16 bit position value as read out from AD2S1210 register, new values available with rising edge of valid_m
   * - velocity_out_m
     - 16 bit velocity value as read out from AD2S1210 register, new values available with rising edge of valid_m
   * - valid_m
     - LOW, if since last conversion triggered by sample_trigger new value is not yet available at position_out_m and/or velocity_out_m 

AD2S1210 Interface
^^^^^^^^^^^^^^^^^^

An example conversion triggered by sample_trigger with the IPCore in ``POSITION_MODE`` is shown below. In ``POSITION_MODE`` only the position register of the AD2S1210 is read out.


.. figure:: timing_POSMODE.png
   :width: 600
   :align: center

   Conversion in POSITION_MODE

Note that the conversion is triggered by a 1 tick long HIGH on sample_trigger. The next tick, AD2S1210_n_sample is pulled LOW for a defined time and the busy indicator is HIGH. Valid_m goes LOW. After a defined time, the data is available for SPI read out. SPI communication starts with AD2S1210_n_fsync going LOW and data being clocked out of the AD2S1210 on SPI_MISO with SPI_CLK. As soon as all data is transmitted, the new value is made available on position_out_m or velocity_out_m and valid_m goes HIGH.

In ``POSITION_AND_VELOCITY_MODE``, the ResolverIP interface can also read out both position and velocity with one SPI interaction. An example conversion is shown below in figure :numref:`pic_Conversion`. Note that AD2S1210_n_sample goes to zero only once. This means that position and velocity values are both sampled by the AD2S1210 at the moment of tiggering via sample_trigger. Then both velocity and position registers of the AD2S1210 are read out with two 16 bit transmissions. Between the two transmissions the AD2S1210 pin A1 is switched to make velocity register entries available via the SPI Interface. Valid_m only goes high after both values are transmitted. 

.. _pic_Conversion:

.. figure:: timing_POSVELMODE.png
   :width: 600
   :align: center

   Conversion in POSITION_AND_VELOCITY_MODE

.. _vitis_setup:

Vitis Setup
***********
To integrate AXI communication between your PS project and the PL IP Core follow the instructions below. 


Initialization
^^^^^^^^^^^^^^

Important constant configuration parameters are stored in the struct ``uz_resolverIP_config_t``:

.. doxygenstruct:: uz_resolverIP_config_t
	:members:

Note that the member ``base_address`` needs to be set to the AXI base address assgined to the IPCore by Vivado. This value is stored in ``XPAR_RESOLVER_INTERFACE_V_0_BASEADDR`` in the ``xparameters.h`` file. Make sure you include this file.

Note that the member ``ip_clk_frequency_Hz`` needs to be set to the clock frequency of the clock input at pin ``s00_axi_aclk``. The tested value was 100MHz (``100000000U``).

Note that the member ``resolution`` is determined by the hardware configuration RES pins of the AD2S1210. Tests were conducted for 16 bits.

Note that the member ``freq_clockin`` needs to be set to the frequency of the external crystal of the AD2S1210. By default the adapter boards come with a 8.192MHz (``8192000U``) crystal.

Note that the member ``pole_pairs_machine`` needs to be set according to the electric machine the resolver is attached to. It influences the conversion from mechanical to electrical position and velocity.

Note that the member ``pole_pairs_resolver`` needs to be set according to the resolver data. It influences the conversion from measured to mechanical velocity.

Note that the member ``zero_Position`` allows for setting an initial position that corresponds to position = 0. All mechanical and electrical positions returned by the functions ``uz_resolverIP_readElectricalPosition`` and ``uz_resolverIP_readMechanicalPosition`` are with reference to ``zero_Position``. ``zero_Position`` can be set via the function ``uz_resolverIP_setZeroPosition``.

Note that the member ``mode_after_init`` defines the operating mode of the ip core after init. This is important when the IP Core shall be used in the PL without using the software driver functions 
that read position and velocity values via AXI. Set the mode to the intended operating mode that you'd like to use the IP Core in the PL. Every mode except ``CONFIG_MODE`` is allowed. When using 
the resolverIP just in the processor, set the mode to ``CONFIG_MODE``. Switching modes during operation is handled via the read functions for position and velocity.

.. code-block:: c
   :caption: A declaration of the struct ``uz_resolverIP_config_t``

   #include "xparameters.h"
   #define CRYSTAL_FREQUENCY 8192000U
   #define IP_CLK_FREQ 100000000U
   struct uz_resolverIP_config_t resolver_config={
           .base_address=XPAR_RESOLVER_INTERFACE_V_0_BASEADDR,
           .ip_clk_frequency_Hz=IP_CLK_FREQ,
           .resolution = 16,
           .freq_clockin = CRYSTAL_FREQUENCY,
		       .pole_pairs_machine = 4.0f,
		       .pole_pairs_resolver = 1.0f,
		       .zero_position_mechanical = 0.3964f,
           .mode_after_init = CONFIG_MODE,
        };

With a parameter of type  ``uz_resolverIP_config_t``, the function ``uz_resolverIP_init`` in ``vitis\software\Baremetal\src\IP_Cores\uz_resolverIP\uz_resolverIP.c`` is called. It returns a pointer to an instance of the struct ``uz_resolverIP_t``.

.. doxygentypedef:: uz_resolverIP_t

.. doxygenfunction:: uz_resolverIP_init

Because doxygen can't display nested structs, here is the declaration of ``uz_resolverIP_t``  as code snippet:

.. code-block:: c

   /**
    * @brief Data type for object resolverIP
    *
    */
    struct uz_resolverIP_t {
    	bool is_ready;/**< Boolean that indicates successful initialization */
    	struct uz_resolverIP_config_t config;/**< Configuration struct with members seen below */
    	uz_resolverIP_mode mode;/**< enum that indicates current mode of AD2S1210 between Configuration Mode, Position Mode, Velocity Mode or PositionAndVelocityMode */
      float bitToRpsFactor = 0;
      uint32_t bit_offset = 0;
    	union{
    		int32_t registerValue; /** RESDAT Value 32bit*/
    		uint16_t pos_Vel[2]; /** 16bit position value in pos_Vel[0], 16bit velocity value in pos_Vel[1]*/
    	}; 
    };

Note that the member ``mode`` coincides with the AD2S1210's modes (see `datasheet <https://www.analog.com/media/en/technical-documentation/data-sheets/AD2S1210.pdf>`_), with the exception of the ``POSITION_VELOCITY_MODE``. Here the IPCore manages the timely transition between ``POSITION_MODE`` and ``VELOCITY_MODE`` for reading both position and velocity.

The member ``union`` is used for buffering the position and velocity values read in via AXI from the RESDAT register. Position values are written to bits 0 to 15, velocity values are written to bits 16 to 31.

A pointer to an  instance of type uz_resolverIP_t can be stored in ``GlobalData.objects.resolverIP``.

.. code-block:: c

   Global_Data.objects.resolver_IP = uz_resolverIP_init(resolver_config)
   uz_resolverIP_setZeroPosition(Global_Data.objects.resolver_IP,0.45F);
   uz_resolverIP_setMachinePolePairs(Global_Data.objects.resolver_IP,2.F);
   uz_resolverIP_setResolverPolePairs(Global_Data.objects.resolver_IP,1.F);

Data Aquistition
^^^^^^^^^^^^^^^^

The ResolverIP interface was designed for time critical applications like motor control. As illustrated by figure :numref:`pic_timing3`, it is recommended to trigger the conversion via the sample_trigger input of the IPCore with the same trigger, that calls the corresponding data aquistition function. The data aquisition function will load in position and/or velocity values as soon as new values are valid. For ``uz_resolverIP_readMechanicalPosition`` and ``uz_resolverIP_readMechanicalVelocity``, this is after :math:`2.48 \mu s` which allows for a maximal sampling frequency of 400kS/s, for ``uz_resolverIP_readMechanicalPositionAndVelocity`` it is after :math:`4.98 \mu s` which allows for a maximal sampling frequency of 200kS/s. 

.. _pic_timing3:

.. figure:: timing3_resolverIP1.png
   :width: 600
   :align: center

   Illustration of recommended triggering setup 

.. doxygenfunction:: uz_resolverIP_readMechanicalPosition

.. doxygenfunction:: uz_resolverIP_readMechanicalVelocity

Note that the two functions above return the position or velocity value as float.
The function ``uz_resolverIP_readMechanicalPositionAndVelocity`` returns a struct of type ``uz_resolverIP_position_velocity_t`` where position and velocity are stored in members.

.. doxygenstruct:: uz_resolverIP_position_velocity_t
  :members:

.. doxygenfunction:: uz_resolverIP_readMechanicalPositionAndVelocity

Note that similar functions for aquisition of electrical position and/or velocity are available:

.. doxygenfunction:: uz_resolverIP_readElectricalPosition

.. doxygenfunction:: uz_resolverIP_readElectricalVelocity

.. doxygenfunction:: uz_resolverIP_readElectricalPositionAndVelocity

Exemplary implementations for one connected resolver that write to the ``GlobalData`` struct are shown below and could be called in ``isr.c`` : 

.. code-block:: c

   void update_position_of_resolverIP(DS_Data* const data){
   	data->av.theta_mech = uz_resolverIP_readMechanicalPosition(data->objects.resolver_IP);
   	data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)) - 2 * UZ_PIf * floor(data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)  / (2* UZ_PIf));
   }
   
   void update_speed_of_resolverIP(DS_Data* const data){
   	data->av.mechanicalRotorSpeed = uz_resolverIP_readMechanicalVelocity(data->objects.resolver_IP) * 60.f; //in rpm
   }
   
   void update_position_and_speed_of_resolverIP(DS_Data* const data){
   	uz_resolverIP_position_velocity_t  mechanical = uz_resolverIP_readMechanicalPositionAndVelocity(data->objects.resolver_IP);
   	data->av.theta_mech = mechanical.position;
   	data->av.mechanicalRotorSpeed = mechanical.velocity * 60.F; //rpm
   	data->av.theta_elec = (data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)) - 2.0f * UZ_PIf * floorf(data->av.theta_mech * uz_resolverIP_getMachinePolePairs(data->objects.resolver_IP)  / (2.0f * UZ_PIf));
   }


More functioniality
===================

The ResolverIP Interface comes with a wide range of functions to write or read configuration registers of the AD2S1210. 
A list of all registers can be seen in figure :numref:`fig_registers`.

.. _fig_registers:

.. figure:: register_table1.png
   :width: 300
   :align: center

   List of all configuration registers of the AD2S1210

For all possible read and write operations, high level functions have been implemented. For applicable write funcitons, the user only needs to input the desired value in float format, the function will take over the conversion to the 8 bit register value. For applicable read functions, values are returned in float format. A list of all functions is given :ref:`below <FunctionList>`.


If the user wants to manually write a definded integer value to a register, the function ``writeRegister`` can be used.

.. doxygenfunction:: uz_resolverIP_writeRegister

For reading of a register ``readRegister`` can be used.

.. doxygenfunction:: uz_resolverIP_readRegister

.. _FunctionList:

High Level Register Operation Functions
***************************************

.. doxygenfunction:: uz_resolverIP_setLOSThresh

.. doxygenfunction:: uz_resolverIP_getLOSThresh

.. doxygenfunction:: uz_resolverIP_setDOSOverrangeThresh

.. doxygenfunction:: uz_resolverIP_getDOSOverrangeThresh

.. doxygenfunction:: uz_resolverIP_setDOSMismatchThresh

.. doxygenfunction:: uz_resolverIP_getDOSMismatchThresh

.. doxygenfunction:: uz_resolverIP_setDOSResetMax

.. doxygenfunction:: uz_resolverIP_setDOSResetMin

.. doxygenfunction:: uz_resolverIP_getDOSResetMin

.. doxygenfunction:: uz_resolverIP_getDOSResetMax

.. doxygenfunction:: uz_resolverIP_setLOTHighThresh

.. doxygenfunction:: uz_resolverIP_getLOTHighThresh

.. doxygenfunction:: uz_resolverIP_setLOTLowThresh

.. doxygenfunction:: uz_resolverIP_getLOTLowThresh

.. doxygenfunction:: uz_resolverIP_setExcitationFrequency

.. doxygenfunction:: uz_resolverIP_getExcitationFrequency

.. doxygenfunction:: uz_resolverIP_setCTRLReg

.. doxygenfunction:: uz_resolverIP_getCTRLReg

.. doxygenfunction:: uz_resolverIP_resetSoftware

.. doxygenfunction:: uz_resolverIP_getFLTRegister

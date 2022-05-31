.. _uz_dac_ip_interface:

====================
uz_dac_spi_interface
====================

The uz_dac_interface IP-Core takes input values for the :ref:`uz_dac8831_pcb` DAC adapter card from the processor by AXI and writes them to the adapter card.
The IP-Core is designed for simplicity.
One AXI register for each DAC and a trigger conversion register is present.
On a rising edge on the trigger conversion register (only possible by AXI), all values are written to all DACs.
The SPI clk frequency can not be changed during runtime and is hard-coded to :math:`f_{SPI}=0.5 \cdot f_{IP-Core}`.
The software driver features a conversion factor for each of the DAC channels to account for different gains in the OpAMP circuit of the card.

Software interface
==================

Example
-------

The following example initializes one driver instance and writes values to it.
Note that the values of DAC1 and DAC8 are out of range for the +- 5V output and will clip accordingly.
However, supplying out of range values does not trigger an assertion to be able to model the behavior of clipping sensors if they measure out-of-range values.

.. code-block:: c
    :caption: Initialization of the driver instance. Base address depends on ``xparameters.h``, gains are set to their nominal value in this case (``2.0f``).

    #include "uz_dac_interface.h"
    #include "xparameters.h"
    #include "uz_array.h"

    struct uz_dac_interface_config_t dac_config={
        .base_address=XPAR_UZ_USER_UZ_DAC_SPI_INTERFACE_0_BASEADDR, // Depends on xparameters.h!
        .ip_clk_frequency_Hz=100000000,
        .gain={2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f}
    };
    uz_dac_interface_t* dac_instance=uz_dac_interface_init(dac_config);


.. code-block:: c
    :caption: Writes values of ``dac_input`` to the DAC channels 

    float dac_input[8]={-6.0f, -5.0f, -4.0f, -3.0f, 1.0f, 3.0f, 4.0f, 8.0f};
        uz_array_float_t dac_input_array={
        .data=&dac_input[0],
        .length=UZ_ARRAY_SIZE(dac_input)
    };
    uz_dac_interface_set_ouput_values(dac_instance,&dac_input_array);



Driver reference
----------------

.. doxygendefine:: UZ_DAC_INTERFACE_OUTPUT_CHANNELS

.. doxygentypedef:: uz_dac_interface_t

.. doxygenstruct:: uz_dac_interface_config_t
   :members:

.. doxygenfunction:: uz_dac_interface_init

.. doxygenfunction:: uz_dac_interface_set_ouput_values

IP-Core interface (Vivado)
==========================

The FPGA interface of the IP-Core is a single signal while the :ref:`uz_dac8831_pcb` PCB expects LVDS signals.
Therefore, additional ``Utility Buffers`` (with ``C Buf Type`` set to ``OBUFDS``) have to be added to the Vivado block design between the output ports and the ``uz_dac_spi_interface`` IP-Core.
Constraints for using the DAC card :ref:`uz_dac8831_pcb` in the slot A3 are supplied in the constraints folder (``uz_dac8831_A3.xdc``).
The SPI clk frequency of the IP-Core output is always half of the ``IP_CORE_CLK``.
The IP-Core is only tested with ``IPCORE_CLK`` and ``AXI_ACLK`` connected to 100 MHz clock!

.. figure:: uz_user_dac.png
   :width: 500

   Wiring to output ports.


.. figure:: uz_user_dac_extended.png
   :width: 500
   
   Detailed setup of uz_dac_spi_interface IP-Core and Utility Buffer


.. figure:: uz_dac_utility_buffer.png
   :width: 500

   Settings of Utility Buffer


.. csv-table:: Interface and ports of the IP-Core
    :file: uz_dac_interface_table.csv
    :widths: 5 5 5 5 5 10
    :header-rows: 1


References
==========

* Data sheet of DAC8831: https://www.ti.com/lit/ds/slas449d/slas449d.pdf?ts=1653291212982
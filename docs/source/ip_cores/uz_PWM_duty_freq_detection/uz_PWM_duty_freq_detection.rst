.. _uz_PWM_duty_freq_detection:

===============================
PWM DutyCycle Detection IP-Core
===============================

This IP core realizes a measurement of the DutyCycle and frequency of a PWM signal.
This IP core is primarily designed to measure the DutyCycle of a temperature measurement from e.g. a inverter, which is encoded in a PWM signal.
In this case the DutyCycle is directly proportional to the temperature.
Linear interpolation is used to convert the DutyCycle to a temperature in degrees Celsius.
The parameters of the interpolation can be freely configured.
However, the IP core can also be used to simply measure any PWM signal's DutyCycle and frequency.
To save FPGA resource, the calculation of the DutyCycle shown below is done on the PS.
The IP core ensures synchronization of the outputs by updating all output values simultaneously whenever a new rise of the PWM is detected.

.. math::

    DutyCycle=\frac{PWM_{hightime}}{PWM_{Freq}}

Usage
-----

The following step-by-step description guides the user in order to properly implement the IP Core and the respective software driver.

Vivado
======

First, the IP-core has to be added to the block design in Vivado:

#. Open the already existing ``uz_user`` hierarchy in the block design.
#. Inside this hierarchy click on the plus (``+``) button to add a new IP-Core and select the ``uz_pwmdutyfreqdetect`` IP-Core.
#. Connect the ``IPCORE_CLK``, ``AXI4_Lite_ACLK``, ``IPCORE_RESETN``, and ``AXI4_LITE_ARESETN`` ports as shown in the image below. The IP-Core is designed for 100 MHz.

   .. figure:: Vivado_1.png
      :width: 400
      :align: center

      Vivado block design

#. Connect the ``PWMin`` port to your PWM signal, which you want to measure.
#. Go to the Address Editor and assign the based address of the IP Core.
#. Generate the bitstream and export the hardware to Vitis.

Vitis
=====

#. In the :ref:`global_configuration` include at least one ``uz_PWM_duty_freq_detection`` IP-Core driver instance.

   .. code-block:: c
      :caption: ``uz_global_configuration.h`` example code

      #define UZ_PWM_DUTY_FREQ_DETECTION_MAX_INSTANCES    1U


#. In the ``globalData.h`` file add the following code to the ``object_pointers_t`` struct:

   .. code-block:: c
      :caption: Code for ``globalData.h`` file

      #include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
      ...
      typedef struct{
      ...
      uz_PWM_duty_freq_detection_t* PWM_Detect_instance;
      }object_pointers_t;

#. In the ``main.h`` file include the header file of the IP-Core driver:

   .. code-block:: c
    :caption: Code for ``main.h`` file

    #include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"

#. In the ``main.c`` file add the following code

   .. code-block:: c
      :caption: Code for ``main.c`` file

       struct uz_PWM_duty_freq_detection_outputs_t outputs = {0};
       struct uz_PWM_duty_freq_detection_config_t config = {
        .base_address = XPAR_UZ_USER_UZ_PWMDUTYFREQDETECT_0_BASEADDR,
        .ip_clk_frequency_Hz = 100000000U,
        .linear_interpolation_parameters_t = {
            .a = 2.0f,
            .b = 3.0f
        }
       };
       ...
       int main(void)
       {
           ...
           switch (initialization_chain)
           {
           ...
           case init_ip_cores:
               ...
               Global_Data.objects.PWM_Detect_instance = uz_PWM_duty_freq_detection_init(config,outputs);
               ...
           }
           ...
       }
#. In the ``isr.c`` file add the following code to read the temperature

   .. code-block:: c
      :caption: Code for ``isr.c`` file

       extern struct uz_PWM_duty_freq_detection_outputs_t outputs;
       ...
       void ISR_Control(void *data) {
        ...
        outputs = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.PWM_Detect_instance);
        float temp = outputs.TempDegreesCelsius;
        ...

Driver reference
----------------

.. doxygentypedef:: uz_PWM_duty_freq_detection_t

.. doxygenstruct:: linear_interpolation_parameters_t
    :members:

.. doxygenstruct:: uz_PWM_duty_freq_detection_config_t
    :members:

.. doxygenstruct:: uz_PWM_duty_freq_detection_outputs_t
    :members:

.. doxygenfunction:: uz_PWM_duty_freq_detection_init

.. doxygenfunction:: uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius

.. doxygenfunction:: uz_PWM_duty_freq_detection_update_states

.. doxygenfunction:: uz_PWM_duty_freq_detection_get_outputs

.. doxygenfunction:: uz_PWM_duty_freq_detection_get_Temperature
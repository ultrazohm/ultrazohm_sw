.. _uz_PWM_duty_freq_detection:

===============================
PWM DutyCycle Detection IP-Core
===============================

This IP core realizes a measurement of the duty cycle and frequency of a PWM signal.
This IP core is primarily designed to measure the duty cycle of a temperature measurement from, e.g., an inverter, which is encoded in a PWM signal.
Typical application is reading the output of `LTC6992 <https://www.analog.com/media/en/technical-documentation/data-sheets/LTC6992-1-6992-2-6992-3-6992-4.pdf>`_.
In this case, the duty cycle is directly proportional to the temperature.
Linear interpolation is used to convert the duty cycle to a temperature in degrees Celsius.
The parameters of the interpolation can be freely configured.
However, the IP core can also be used to simply measure any PWM signal's duty cycle and frequency.
To save FPGA resources, the calculation of the duty cycle shown below is done on the PS.
The IP core ensures synchronization of the outputs by updating all output values simultaneously whenever a new rise of the PWM is detected.
The IP-core counts the number of clock cycles the PWM signal is high (:math:`N_{high}`) and the total number of clock cycles in one period (:math:`N_{period}`).
The outputs are synchronized with a strobe signal.
From these two values, the duty cycle is calculated as:

.. math::

    DutyCycle=\frac{N_{high}}{N_{period}}

Usage
-----

The following step-by-step description guides the user in order to properly implement the IP Core and the respective software driver.

Vivado
======

First, the IP-core has to be added to the block design in Vivado:

#. Open the already existing ``uz_user`` hierarchy in the block design.
#. Inside this hierarchy, click on the plus (``+``) button to add a new IP-Core and select the ``uz_pwmdutyfreqdetect`` IP-Core.
#. Connect the ``IPCORE_CLK``, ``AXI4_Lite_ACLK``, ``IPCORE_RESETN``, and ``AXI4_LITE_ARESETN`` ports as shown in the image below. The IP-Core is designed for 100 MHz.

   .. figure:: Vivado_1.png
      :width: 400
      :align: center

      Vivado block design

#. Connect the ``PWMin`` port to your PWM signal, which you want to measure.
#. Go to the Address Editor and assign the base address of the IP Core.
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

#. In the ``main.c`` file, add the following code

   .. code-block:: c
      :caption: Code for ``main.c`` file

       struct uz_PWM_duty_freq_detection_config_t config = {
        .base_address = XPAR_UZ_USER_UZ_PWMDUTYFREQDETECT_0_BASEADDR,
        .ip_clk_frequency_Hz = 100000000U,
       };
       struct linear_interpolation_parameters_t lin_inter_param= {
        .a = 100.0f,
        .b = -50.0f
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
               Global_Data.objects.PWM_Detect_instance = uz_PWM_duty_freq_detection_init(config);
               ...
           }
           ...
       }

#. In the ``isr.c`` file, add the following code to read the temperature

   .. code-block:: c
      :caption: Code for ``isr.c`` file

       extern struct uz_PWM_duty_freq_detection_outputs_t outputs;
       ...
       void ISR_Control(void *data) {
        ...
        float pwm_freq = uz_PWM_duty_freq_detection_get_frequency_in_Hz(Global_Data.objects.PWM_Detect_instance);
        float duty_cycle = uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(Global_Data.objects.PWM_Detect_instance);
        float temp = uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(duty_cycle,lin_inter_param);
        ...

Driver reference
----------------

.. doxygentypedef:: uz_PWM_duty_freq_detection_t

.. doxygenstruct:: linear_interpolation_parameters_t
    :members:

.. doxygenstruct:: uz_PWM_duty_freq_detection_config_t
    :members:

.. doxygenfunction:: uz_PWM_duty_freq_detection_init

.. doxygenfunction:: uz_PWM_duty_freq_detection_get_frequency_in_Hz

.. doxygenfunction:: uz_PWM_duty_freq_detection_get_duty_cycle_in_percent

.. doxygenfunction:: uz_PWM_duty_freq_detection_get_Temperature_in_degree_C
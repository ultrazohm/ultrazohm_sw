.. _uz_IIR_filter_setpoint:

====================
IIR filter set-point
====================

.. doxygenfunction:: uz_signals_IIR_Filter_dq_setpoint


Description
===========

The set-point filter function uses two :ref:`uz_IIR_filter` objects to filter the d- and q-current set-points of a controller.
The intended use is for cascaded control structures as well as direct user input (e.g., via the GUI).
As large changes in set-points may result in big current jumps, this function smoothes the set-point change and reduces stress on the system hardware.
The suggested filter configuration in the `Example configuration`_  can be used as a baseline and has to be tuned to the specific application.

Example configuration
=====================

.. code-block:: c
  :linenos:
  :caption: Example to init the filter

  #include "uz/uz_signals/uz_signals.h"
  uz_IIR_Filter_t* filter_1 = NULL;
  uz_IIR_Filter_t* filter_2 = NULL;
  #define ISR_SAMPLE_FREQ_HZ 10000.0f
  int main(void) {
     //...
     struct uz_IIR_Filter_config config_filter = {
                                             .selection = LowPass_first_order,
                                             .cutoff_frequency_Hz = 1.0f,
                                             .sample_frequency_Hz = ISR_SAMPLE_FREQ_HZ};
     filter_1 = uz_signals_IIR_Filter_init(config);
     filter_2 = uz_signals_IIR_Filter_init(config);
     //...
  }

.. code-block:: c
  :linenos:
  :caption: Example to use the filter (initialization if uz_current_control not included, code will not compile!)

  #include "../uz_signals/uz_signals.h"
  extern uz_IIR_Filter_t* filter_1;
  extern uz_IIR_Filter_t* filter_2;
  void ISR_Control(void *data) {
     //...
     uz_3ph_dq_t setpoints_filtered= uz_signals_IIR_Filter_dq_setpoint(filter_1, filter_2, Global_Data.rasv.i_ref_dq)
     controller_out = uz_CurrentControl_sample(cc_instance, uz_signals_IIR_Filter_dq_setpoint(filter_1, filter_2, Global_Data.rasv.i_ref_dq), Global_Data.av.i_actual_dq, Global_Data.av.V_dc, Global_Data.av.omega_el);
     //...
  }
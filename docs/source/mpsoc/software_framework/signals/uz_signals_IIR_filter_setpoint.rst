.. _uz_IIR_filter_setpoint:

===================
IIR filter setpoint
===================

.. doxygenfunction:: uz_signals_IIR_Filter_dq_setpoint


Description
===========

The setpoint filter function uses the existing :ref:`uz_IIR_filter` objects and combines to of them to filter ``d`` and ``q`` of a controller setpoint.
The intended use is for any controller setpoints, coming from other functions or user input via GUI.
As large changes in setpoints may result in big current jumps, this function can smooth them out and protect hardware and system to ensure a more smooth operation.
The suggested filter configuration in the ``Example`` chapter has shown to give a very smooth result and can be used as a baseline for later tuning.

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example to init the filter

  #include "uz/uz_signals/uz_signals.h"
  uz_IIR_Filter_t* filter_1 = NULL;
  uz_IIR_Filter_t* filter_2 = NULL;
  #define ISR_SAMPLE_FREQ_HZ 10000.0f
  int main(void) {
     //...
     struct uz_IIR_Filter_config config_filter = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 1.0f, .sample_frequency_Hz = ISR_SAMPLE_FREQ_HZ};
     filter_1 = uz_signals_IIR_Filter_init(config);
     filter_2 = uz_signals_IIR_Filter_init(config);
     //...
  }

.. code-block:: c
  :linenos:
  :caption: Example to use the filter (initalisation if uz_current_control not included, code will not compile!)

  #include "../uz_signals/uz_signals.h"
  extern uz_IIR_Filter_t* filter_1;
  extern uz_IIR_Filter_t* filter_2;
  void ISR_Control(void *data) {
     //...
     controller_out = uz_CurrentControl_sample(cc_instance, uz_signals_IIR_Filter_dq_setpoint(filter_1, filter_2, Global_Data.rasv.i_ref_dq), Global_Data.av.i_actual_dq, Global_Data.av.V_dc, Global_Data.av.omega_el);
     //...
  }
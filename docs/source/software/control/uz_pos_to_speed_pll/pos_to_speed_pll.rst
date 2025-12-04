.. _pos_to_speed_pll:

=====================
Position to Speed PLL
=====================

Description
-----------

General description

Example configuration
---------------------

.. code-block:: c
  :linenos:
  :caption: Example to init the PLL

  #include "uz/uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"
  #define ISR_SAMPLE_FREQ_HZ 10000.0f
  const struct uz_IIR_Filter_config config_filter = {
    .selection = LowPass_first_order,
    .cutoff_frequency_Hz = 1.0f,
    .sample_frequency_Hz = ISR_SAMPLE_FREQ_HZ};
  struct uz_dq_setpoint_filter_config config = {
    .config_filter_d = config_filter,
    .config_filter_q = config_filter};
  uz_dq_setpoint_filter* obj_1 = NULL;
  uz_dq_setpoint_filter* obj_2 = NULL;
  int main(void) {
     //...
     obj_1 = uz_uz_dq_setpoint_filter_init(config);
     obj_2 = uz_uz_dq_setpoint_filter_init(config);
     //...
  }

.. code-block:: c
  :linenos:
  :caption: Example to use the PLL

  #include "../uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"
  extern uz_dq_setpoint_filter* obj_1;
  extern uz_dq_setpoint_filter* obj_2;
  void ISR_Control(void *data) {
     //...
     uz_3ph_dq_t setpoints_filtered = uz_signals_IIR_Filter_dq_setpoint(obj_1, Global_Data.rasv.i_ref_dq)
     controller_out = uz_CurrentControl_sample(cc_instance, uz_signals_IIR_Filter_dq_setpoint(obj_2, Global_Data.rasv.i_ref_dq), Global_Data.av.i_actual_dq, Global_Data.av.V_dc, Global_Data.av.omega_el);
     //...
  }

  
Position to Speed PLL reference
===============================

.. doxygenstruct:: uz_pos_to_speed_pll_config_t
  :members:

.. doxygenstruct:: uz_pos_to_speed_pll_t
  :members:  

.. doxygentypedef:: uz_pos_to_speed_pll

.. doxygenfunction:: uz_pos_to_speed_pll_init

.. doxygenfunction:: uz_pos_to_speed_pll_set_config

.. doxygenfunction:: uz_pos_to_speed_pll_step

.. doxygenfunction:: uz_pos_to_speed_pll_get_omega_mech_si

.. doxygenfunction:: uz_pos_to_speed_pll_get_omega_el_si
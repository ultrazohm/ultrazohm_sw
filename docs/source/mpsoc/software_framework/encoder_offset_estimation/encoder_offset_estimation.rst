.. _uz_encoder_offset_estimation:

=========================
Encoder Offset Estimation
=========================

Workflow:
Estimate Theta with "wrong" method.
Use estimated theta in code below and algorithm will find true theta in that range.


.. doxygenstruct:: uz_encoder_offset_estimation_config
  :members: 

.. doxygenfunction:: uz_encoder_offset_estimation_init

.. doxygenfunction:: uz_encoder_offset_estimation_step

.. doxygenfunction:: uz_encoder_offset_estimation_get_finished


.. code-block:: c
    :caption: main

    #include "uz/uz_EncOffEst/uz_EncOffEst.h"
    uz_EncOffEst_t* enc_off = NULL;
    struct uz_EncOffEst_config enc_off_config = {
            .actual = &Global_Data.av,
            .polepair = 5.0f,
            .setpoint_current = 3.0f
    };

    // your own current controller stuff here

    Global_Data.av.theta_offset = 2.0f; // initial theta offset
    ..
    // in main loop
    enc_off = uz_EncOffEst_init(enc_off_config);
    ..

.. code-block:: c
    :caption: isr

    #include "../uz/uz_EncOffEst/uz_EncOffEst.h"
    extern uz_EncOffEst_t* enc_off;
    float theta = 0.0f;
    uz_3ph_dq_t enc_off_set = {0};
    uz_3ph_dq_t cc_3ph_out = {0};

    // use current control of choice
    extern uz_CurrentControl_t* CC_instance_1;
    ..
    //in isr loop
    Global_Data.av.U_q = cc_3ph_out.q;
	theta = Global_Data.av.theta_elec - Global_Data.av.theta_offset;
    if (current_state==control_state)
    {
    	if(!uz_EncOffEst_get_finished(enc_off))
    	{
    		enc_off_set = uz_EncOffEst_step(enc_off);
    	}
    	cc_3ph_out = uz_CurrentControl_sample(CC_instance_1, enc_off_set, actual_i_dq, 36.0f, omega_el_rad_per_sec);
    	// set to PWM here
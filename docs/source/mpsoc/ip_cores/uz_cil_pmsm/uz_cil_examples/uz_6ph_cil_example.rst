.. _uz_6ph_cil_example:

=====================
Six-phase CIL Example
=====================

On this page, a description of a six-phase PMSM CIL model will be given, using the respective UZ IP-Cores.

Vivado
======

In this example, PWM blocks have been placed individually for the CIL.
Alternatively, the PWM blocks from the standard model can be used.
The outputs of the PWM blocks are combined with a Concat block and routed to the inverter's gate inputs.
Their voltage outputs are connected with the respective inputs of the Transformation IP-core, who's current oututs are fed back to the inverters.
The transformation's transformed output is connected with the PMSM, while the PMSM's rotor angle and current outputs are connected with the Transformation.
The trigger and refresh signals of the Transformation are connected with the RS-Flip-Flop as shown below.

.. figure:: vivado_6ph.jpg

    Vivado setup

Vitis
=====

For a quick initialization, the pre-made HW-init ``uz_CIL_6ph`` files can be used.
They initialize all necessary IP-cores and contain their pointers in the ``uz_CIL_objects_t`` struct.
Values of an imaginary six-phase machine have been used, but they can be exchanged for real parameters in the ``uz_CIL_6ph.c`` file.

.. code-block:: c
  :caption: Changes in ``main.c`` (R5)

  ...
  // include init file and create reference the struct that holds al pointers
  #include "include/uz_CIL_6ph.h"
  extern uz_CIL_objects_t cil_objects;
  // create PI controllers
  #include "uz/uz_piController/uz_piController.h"
  const struct uz_PI_Controller_config PI_config = {
    .Kp = 1250.0f,
    .Ki = 78250.0f,
    .samplingTime_sec = 0.0001f,
    .upper_limit = 100.0f,
    .lower_limit = -100.0f};
  uz_PI_Controller *PI_d_current=NULL;
  uz_PI_Controller *PI_q_current=NULL;
  ...
  int main(void)
  {
    ...
    case init_ip_cores:
      // init transfromation, pmsm and inverters
      init_CIL_6phase(&cil_objects);
      // init pwm ip-cores, only if own ip-cores are used
      init_PWM_CIL_6phase(&cil_objects);
      // init PI-controllers
      PI_d_current = uz_PI_Controller_init(PI_config);
      PI_q_current = uz_PI_Controller_init(PI_config);
      ...

.. code-block:: c
  :caption: Changes in ``isr.c`` (R5)

  ...
  // include necessary files and reference struct that holds pointers to IP-cores
  #include "../include/uz_CIL_6ph.h"
  extern uz_CIL_objects_t cil_objects;

  // Data for PMSM
  float omega_mech = 100.0f;
  float load_torque = 0.0f;
  struct uz_pmsm_model6ph_dq_outputs_general_t pmsm_output = {0};

  // Data for Transformation
  uz_6ph_abc_t transformation_currents_abc = {0};
  float theta_el = 0.0f;

  // Data for PI
  #include "../uz/uz_piController/uz_piController.h"
  extern uz_PI_Controller *PI_d_current;
  extern uz_PI_Controller *PI_q_current;
  uz_6ph_dq_t transformed_currents = {0};
  uz_3ph_dq_t setp_currents = {0};
  uz_6ph_dq_t output_voltage_dq = {0};
  uz_6ph_abc_t out_voltage_abc = {0};
  uz_3ph_abc_t out_voltage_abc1 = {0};
  uz_3ph_abc_t out_voltage_abc2 = {0};

  // Data for PWM
  #include "../uz/uz_FOC/uz_FOC.h"
  float V_dc_volts = 500.0f;
  struct uz_DutyCycle_t duty_cycle_sys1 = {0};
  struct uz_DutyCycle_t duty_cycle_sys2 = {0};
  ...
  void ISR_Control(void *data)
  {
    ...
    // CIL
    uz_pmsm_model6ph_dq_set_inputs_general(cil_objects.cil_pmsm,omega_mech,load_torque);    // set omega and load torque (only one active)
    pmsm_output = uz_pmsm_model6ph_dq_get_outputs_general(cil_objects.cil_pmsm);            // read outputs from PMSM
    transformation_currents_abc = uz_pmsm6ph_transformation_get_currents(cil_objects.cil_transformation);        // read current from transformation
    theta_el = uz_pmsm6ph_transformation_get_theta_el(cil_objects.cil_transformation);      // read theta from transformation

    // Controller
    transformed_currents = uz_transformation_asym30deg_6ph_abc_to_dq(transformation_currents_abc, theta_el);      // transform currents
    output_voltage_dq.d = uz_PI_Controller_sample(PI_d_current, setp_currents.d, transformed_currents.d, false);  // sample d-current controller
    output_voltage_dq.q = uz_PI_Controller_sample(PI_q_current, setp_currents.q, transformed_currents.q, false);  // sample q-current controller
    out_voltage_abc = uz_transformation_asym30deg_6ph_dq_to_abc(output_voltage_dq, theta_el);                     // transform setpoint voltages to phase volatges
    out_voltage_abc1.a = out_voltage_abc.a1;                                                                      // seperate voltages into 3ph structs
    out_voltage_abc1.b = out_voltage_abc.b1;
    out_voltage_abc1.c = out_voltage_abc.c1;
    out_voltage_abc2.a = out_voltage_abc.a2;
    out_voltage_abc2.b = out_voltage_abc.b2;
    out_voltage_abc2.c = out_voltage_abc.c2;

    // Duty Cycles
    duty_cycle_sys1 = uz_FOC_generate_DutyCycles(out_voltage_abc1, V_dc_volts); //create Duty-Cycles for subsets
    duty_cycle_sys2 = uz_FOC_generate_DutyCycles(out_voltage_abc2, V_dc_volts); //create Duty-Cycles for subsets
    uz_PWM_SS_2L_set_duty_cycle(cil_objects.cil_pwm1, duty_cycle_sys1.DutyCycle_U, duty_cycle_sys1.DutyCycle_V, duty_cycle_sys1.DutyCycle_W);
    uz_PWM_SS_2L_set_duty_cycle(cil_objects.cil_pwm2, duty_cycle_sys2.DutyCycle_U, duty_cycle_sys2.DutyCycle_V, duty_cycle_sys2.DutyCycle_W);
    ...

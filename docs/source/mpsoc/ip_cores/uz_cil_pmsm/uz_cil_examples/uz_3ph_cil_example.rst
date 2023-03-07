.. _uz_3ph_cil_example:

=======================
Three-phase CIL Example
=======================

On this page, a description of a three-phase PMSM CIL model will be given, using the respective UZ IP-Cores.

Vivado
======

In this example, a PWM IP-Core is placed individually for the CIL.
Alternatively, the PWM blocks from the standard model can be used.
The outputs of the PWM block are combined with a Concat block and routed to the inverter's gate inputs.
Their voltage outputs are connected with the respective inputs of the Transformation IP-core, whose current outputs are fed back to the inverter.
The transformation's transformed output is connected with the PMSM, while the PMSM's rotor angle and current outputs are connected with the Transformation.
The trigger and refresh signals of the Transformation are connected with the RS-Flip-Flop as shown below.

.. note:: 

   To simplify the usage of the CIL and to reduce possible errors, a tcl script was created, that places all necessary IP-Cores automatically and connects them.
   To use this, open the Vivado block design in a clean project and run the following commands seperately in the TCL-console.
   "cd [ get_property DIRECTORY [current_project] ]" 
   "source ../../docs/source/mpsoc/ip_cores/uz_cil_pmsm/uz_cil_examples/threephase_cil.tcl"
   Do not forget to assign the addresses afterwards, as this is not included in the tcl-script!
   During the validation in Vivado, a warning for the unconnected PWM IP-core's inputs will show up, which can be ignored.


.. figure:: vivado_3ph.jpg

    Vivado setup

All individual connections of each IP-core are shown in the table below.

.. csv-table:: Connection of IP-cores
   :file: uz_3ph_cil_connections.csv
   :widths: 50 50 50 50
   :header-rows: 1

Vitis
=====

Each IP-core is initialized in ``main.c``, as well as a pointer with the respective type.
The init functions are called during the init process of all IP-cores.
Please check all MAX_INSTANCE defines, including the amount of PWM instances, if additional IP-cores are used.

.. code-block:: c
  :caption: Changes in ``main.c`` (R5)

  ...
  // includes
  #include "IP_Cores/uz_pmsm_model_3ph_dq/uz_pmsm_model3ph_dq.h"
  #include "IP_Cores/uz_pmsm3ph_transformation/uz_pmsm3ph_transformation.h"
  #include "IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
  #include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
  #include "uz/uz_FOC/uz_FOC.h"

  // PMSM
  uz_pmsm_model3ph_t *pmsm = NULL;
  const struct uz_pmsm_model3ph_config_t cil_pmsm_comfig = {
    .base_address = XPAR_UZ_USER_UZ_PMSM_MODEL_3PH_DQ_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .polepairs = 4.0f,
    .r_1 = 0.3f,
    .L_d = 0.3f,
    .L_q = 0.3f,
    .psi_pm = 0.0075f,
    .friction_coefficient = 0.001f,
    .coulomb_friction_constant = 0.001f,
    .inertia = 0.001f,
    .simulate_mechanical_system = false, //false: set fixed rpm, true: set load torque
    .switch_pspl = false};               //false: voltage input from CIL, true: voltage input from AXI

  // Transformation
  uz_pmsm3ph_transformation_t *transformation = NULL;
  struct uz_pmsm3ph_config_t cil_transformation_config = {
    .base_address = XPAR_UZ_USER_UZ_THREEPHASE_VSD_TR_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f};

  // Inverter
  uz_inverter_3ph_t *inverter = NULL;
  struct uz_inverter_3ph_config_t cil_inverter_config = {
    .base_address = XPAR_UZ_USER_UZ_INVERTER_3PH_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .switch_pspl_abc = false,
    .switch_pspl_gate = false,
    .udc = 100.0f};

  // PWM (optional, only necessary if default PWM blocks are not used)
  uz_PWM_SS_2L_t *PWM = NULL;
  struct uz_PWM_SS_2L_config_t cil_pwm_config = {
    .base_address= XPAR_UZ_USER_PWM_AND_SS_CONTROL_V_0_BASEADDR,
    .ip_clk_frequency_Hz=100000000.0f,
    .Tristate_HB1 = false,
    .Tristate_HB2 = false,
    .Tristate_HB3 = false,
    .min_pulse_width = 0.01f,
    .PWM_freq_Hz = UZ_PWM_FREQUENCY,
    .PWM_mode = normalized_input_via_AXI,
    .PWM_en = true,
    .use_external_counter = true};

  // FOC (optional)
  const struct uz_PI_Controller_config cil_pi_config = {
	  .Kp = 1250.0f,
    .Ki = 78250.0f,
	  .samplingTime_sec = 0.0001f,
	  .upper_limit = 100.0f,
	  .lower_limit = -100.0f};
  const uz_PMSM_t foc_pmsm = {
    .I_max_Ampere = 10.0f,
    .J_kg_m_squared = 0.001f,
    .Ld_Henry = cil_pmsm_comfig.L_d,
    .Lq_Henry = cil_pmsm_comfig.L_q,
    .Psi_PM_Vs = cil_pmsm_comfig.psi_pm,
    .R_ph_Ohm = cil_pmsm_comfig.r_1,
    .polePairs = cil_pmsm_comfig.polepairs};
  uz_FOC *foc = NULL;
  struct uz_FOC_config cil_foc_config = {
    .decoupling_select = no_decoupling,
    .config_id = cil_pi_config,
    .config_iq = cil_pi_config,
    .config_PMSM = foc_pmsm};
  ...
  int main(void)
  {
    ...
    case init_ip_cores:
      // init IP-cores
      pmsm = uz_pmsm_model3ph_init(cil_pmsm_comfig);
      transformation = uz_pmsm3ph_transformation_init(cil_transformation_config);
      inverter = uz_inverter_3ph_init(cil_inverter_config);
      PWM = uz_PWM_SS_2L_init(cil_pwm_config);
      // init FOC
      foc = uz_FOC_init(cil_foc_config);
    ...


To use the CIL setup, the IP-core's pointers have to be imported to the ``isr.c``.
Also, variables to store the outputs of the CIL model are defined.
In this example, a PI controller is used to control the PMSM.
The usage is not necessary and the respective parts can be disregarded if other controllers are used.
In the end, the duty cycles are given to the defined PWM modules.
Depending on the used controller, this might not be necessary.

.. code-block:: c
  :caption: Changes in ``isr.c`` (R5)

  ...
  // Data for PMSM
  #include "../IP_Cores/uz_pmsm_model_3ph_dq/uz_pmsm_model3ph_dq.h"
  extern uz_pmsm_model3ph_t *pmsm;
  struct uz_pmsm_model3ph_outputs_t pmsm_output = {0};
  struct uz_pmsm_model3ph_inputs_t pmsm_input = {
      .load_torque = 0.0f,								// torque or omega dont need to be set here, only as an example
      .omega_mech_1_s = 100.0f,
      .v_d_V = 0.0f,									    // AXI voltage inputs are not used if CIL setup inf FPGA is used
      .v_q_V = 0.0f};

  // Data for Transformation
  #include "../IP_Cores/uz_pmsm3ph_transformation/uz_pmsm3ph_transformation.h"
  #include "../uz/uz_Transformation/uz_Transformation.h"
  extern uz_pmsm3ph_transformation_t *transformation;
  uz_3ph_abc_t transformation_currents_abc = {0};
  float theta_el = 0.0f;

  // Data for Controller
  #include "../uz/uz_FOC/uz_FOC.h"
  uz_3ph_dq_t transformed_currents = {0};
  uz_3ph_dq_t setpoint_currents = {0};
  uz_3ph_abc_t abc_out_controller = {0};
  extern uz_FOC *foc;

  // Data for PWM
  #include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
  extern uz_PWM_SS_2L_t *PWM;
  float V_dc_volts = 100.0f;
  struct uz_DutyCycle_t duty_cycle = {0};

  ...

  void ISR_Control(void *data)
  {
    ...
    // CIL
    uz_pmsm_model3ph_set_inputs(pmsm,pmsm_input);                                          						  // set omega and load torque (only one active)
    uz_pmsm_model3ph_trigger_input_strobe(pmsm);																                        // write inputs to HW
    uz_pmsm_model3ph_trigger_output_strobe(pmsm);																                        // update outputs from HW
    pmsm_output = uz_pmsm_model3ph_get_outputs(pmsm);                                                   // read outputs from PMSM
    transformation_currents_abc = uz_pmsm3ph_transformation_get_currents(transformation);               // read current from transformation
    theta_el = uz_pmsm3ph_transformation_get_theta_el(transformation);                                  // read theta from transformation

    // Controller
    transformed_currents = uz_transformation_3ph_abc_to_dq(transformation_currents_abc,theta_el);				         // transform currents to dq
    abc_out_controller = uz_FOC_sample_abc(foc,setpoint_currents,transformed_currents,V_dc_volts,pmsm_output.omega_mech_1_s,theta_el); // controller

    // Duty Cycles
    duty_cycle = uz_FOC_generate_DutyCycles(abc_out_controller, V_dc_volts); 									                   // create Duty-Cycles
    uz_PWM_SS_2L_set_duty_cycle(PWM, duty_cycle.DutyCycle_U, duty_cycle.DutyCycle_V, duty_cycle.DutyCycle_W);    // write Duty-Cycles to PWM module
    ...

.. _uz_inverter_3ph:

==============
Inverter Model
==============

- IP-Core of a 3 phase inverter
- Simulates the inverter on the FPGA
- Intended for controller-in-the-loop (CIL) on the UltraZohm
- IP-Core clock frequency **must** be :math:`f_{clk}=100\,MHz`!

Model Description
=================

The Simscape model of the inverter is shown in the figure below.
While in the light blue areas, only the inputs are handled (mainly switching between PS and PL inputs depending on the configuration) and in the yellow area the ouputs are realized, the central part of the model is placed in the dark blue areas.
The power electronics part is modelled with six N-channel MOSFET from the Simscape parts library.
Note that their electrical parameters are listed in the table below and can only be changed in the Simscape model but not after the IP-core generation.
The MOSFETs are placed to model three half bridges (HB) and each of the switches can be controlled individually.
There is no logic implemented to prevent short circuits, if top and bottom switch of one HB are closed simultaneously.
Because the physical references of the Simscape model will be lost after the IP-core generation, the two controlled currents sources from phases ``a`` and ``b`` to phase ``c`` are placed.
The usage of the IP-core demands the user to feed back the actual flowing currents in the current application to the inverter for it to determine the voltage drop across the switches and diodes.
If the user does not feed back any currents or sets the feedback to zero, no voltage drops will be considered for the ouput voltage.
The voltages are output as line-to-line voltages :math:`u_{ab},u_{bc},u_{ca}`.

..	figure:: ./inverter_overview.svg

   Overview of Simscape inverter model ``uz_inverter_3ph.slx``


.. csv-table:: Parameter Switch (MOSFET and body diode)
   :file: ./MOSFET_parameter.csv
   :widths: 50 50 50
   :header-rows: 1


IP-Core Interfaces
==================

.. csv-table:: IP-core Interfaces Switch
   :file: ./inverter_interfaces.csv
   :widths: 50 40 60 50 60 210
   :header-rows: 1


Driver Reference
================

.. doxygentypedef:: uz_inverter_3ph_t

.. doxygenstruct:: uz_inverter_3ph_config_t
  :members:

.. doxygenstruct:: uz_inverter_3ph_gate_ps_t
  :members:

.. doxygenfunction:: uz_inverter_3ph_init

.. doxygenfunction:: uz_inverter_3ph_get_u_abc_ps

.. doxygenfunction:: uz_inverter_3ph_set_i_abc_ps

.. doxygenfunction:: uz_inverter_3ph_set_gate_ps

.. doxygenfunction:: uz_inverter_3ph_trigger_u_abc_ps_strobe

.. doxygenfunction:: uz_inverter_3ph_trigger_i_abc_ps_strobe

.. doxygenfunction:: uz_inverter_3ph_trigger_gate_ps_strobe


Example Usage
=============

The inverter IP-core can be used in several different ways because the inputs and outputs can be accessed from PS or PL individually.
For this example only the access via PS is shown.
Using the IP-core in PL mainly demands the usage of other IP-cores to provide the inputs and utilize the outputs which is shown in :ref:`uz_pmsm_model_9ph_dq`.

.. figure:: open_loop_ps.jpg

   Placement of the IP-core in Vivado for PS only access


The following code is used in ``main.c`` (initialization) and ``isr.c`` (application):

.. code-block:: c
  :caption: initialization in ``main.c`` (R5)

  #include "IP_Cores/uz_pmsm_model_9ph_dq/uz_pmsm_model9ph_dq.h"
  uz_pmsm_model9ph_dq_t *pmsm=NULL;
  struct uz_pmsm_model9ph_dq_config_t pmsm_config = {   // example config values
    .base_address=XPAR_UZ_PMSM_MODEL_0_BASEADDR,
    .ip_core_frequency_Hz = 100000000.0f,
    .polepairs = 3.0f,
    .r_1 = 31.3f,
    .inductance.d = 0.46f,
    .inductance.q = 0.46f,
    .inductance.x1 = 0.08f,
    .inductance.y1 = 0.08f,
    .inductance.x2 = 0.08f,
    .inductance.y2 = 0.08f,
    .inductance.x3 = 0.08f,
    .inductance.y3 = 0.08f,
    .inductance.zero = 0.08f,
    .psi_pm = 0.072f,
    .friction_coefficient = 0.001f,
    .coulomb_friction_constant = 0.001f,
    .inertia = 0.001f,
    .simulate_mechanical_system = false,
    .switch_pspl = true};

  // .. rest of the code in main.c before loop
  int main(void)
  // ..
    case init_ip_cores: // default line from main.c
      pmsm = uz_pmsm_model9ph_dq_init(pmsm_config);

.. code-block:: c
  :caption: usage in ``isr.c``

  #include "../IP_Cores/uz_pmsm_model_9ph_dq/uz_pmsm_model9ph_dq.h"
  extern uz_pmsm_model9ph_dq_t *pmsm;                               // pointer to PMSM object
  struct uz_pmsm_model9ph_dq_outputs_general_t out_general = {0};   // stores general outputs
  uz_9ph_dq_t in_voltages = {                                       // stores input voltages (set random voltages for testing)
		.d = 1.0f,
		.q = 2.0f,
		.x1 = 3.0f,
		.y1 = 4.0f,
		.x2 = 5.0f,
		.y2 = 6.0f,
		.x3 = 7.0f,
		.y3 = 8.0f,
		.zero = 9.0f};                                   
  uz_9ph_dq_t out_currents = {0};                                   // stores output currents
  float omega_mech = 10.0f;                                         // fixed speed can be set from Expressions with this variable
  int reset = 0;                                                    // use reset variable to reset integrators from Expressions 

  // .. rest of the code in isr.c before loop
  void ISR_Control(void *data)
  // ..
    update_speed_and_position_of_encoder_on_D5(&Global_Data);       // default line from isr.c

    if(reset)
      uz_pmsm_model9ph_dq_reset(pmsm);                              // use reset variable to reset integrators from Expressions   

    uz_pmsm_model9ph_dq_set_inputs_general(pmsm,omega_mech,0.0f);   // set fixed speed, because load simulation is disabled by pmsm_config.simulate_mechanical_system
    uz_pmsm_model9ph_dq_set_voltage(pmsm,in_voltages);              // set input voltage
    out_general = uz_pmsm_model9ph_dq_get_outputs_general(pmsm);    // read out resulting general outputs
    out_currents = uz_pmsm_model9ph_dq_get_output_currents(pmsm);   // read out actual currents


Reference
=========

“Troubleshoot conversion of simscape permanent magnet synchronous motor to hdlcompatible simulink model.” [Online]. Available: https://de.mathworks.com/help/releases/R2021a/hdlcoder/ug/troubleshoot-generate-implementation-model-from-simscape-pmsm.html
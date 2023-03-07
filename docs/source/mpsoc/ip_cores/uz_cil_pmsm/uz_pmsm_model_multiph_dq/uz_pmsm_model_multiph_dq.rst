.. _uz_pmsm_model_multiph_dq:

======================
Multi-phase PMSM Model
======================

Important:

 - The multi-phase PMSM IP-cores are based on the three-phase :ref:`uz_pmsmModel` IP-core, where the basics (e.g. working principle of the integrations is explained)
 - There are two mulit-phase IP-cores, a six-phase and a nine-phase one

Differences to the three-phase PMSM model IP-core:

 - IP-Cores model a six-phase and nine-phase PMSM
 - Sample frequency of the integrator is :math:`T_s=\frac{1}{1\,MHz}`
 - IP-Core clock frequency **must** be :math:`f_{clk}=100\,MHz`!
 - All calculations in the IP-Core are done in double precision
 - Interfaces to PL are realized in fixedpoint, while interfaces to the PS use single precision float values

System description
==================
The modelling of the multi-phase machine is based on [[#Slunjski_Diss]_].
The general idea in this work and also the common approach to model multi-phase machines is, to transform the phase variables with the VSD and Park transformations, as shown and done in :ref:`uz_vsd_transformation` and :ref:`uz_transformation`.
Transformed voltages are used as input for this IP-core and the outputs will also be in the rotary or stationary reference frame ant not phase variables.
This IP-core contains the electric differential equations and the mechanical part, where the torque is calculated.
Additionally, either a torque load or a fixed speed can be set to test the machine model.
While the equations are mostly similar to the ones of the three-phase :ref:`uz_pmsmModel`, they will be shown here again for the sake of completeness.
To obtain more details about the equations and integrators, reading :ref:`uz_pmsmModel` is advised.

dq equations
------------
.. math::

  \begin{align}
      \psi_{d}(k+1) &= T_s \big( v_{d}(k) - R_{1} i_{d}(k) + \omega_{el} \psi_{q}(k) \big) + \psi_{d}(k)\\
      \psi_{q}(k+1) &= T_s \big( v_{q}(k) - R_{1} i_{q}(k) - \omega_{el} \psi_{d}(k) \big) + \psi_{q}(k)\\
      \psi_{d}(k) &= \psi_{PM} + L_{d} i_{d}(k) \\
      \psi_{q}(k) &= L_{q} i_{q}(k) \label{eq:psiq_ld}
  \end{align}

Mechanical equations
--------------------
.. math::

  \begin{align}
    M_M &= \frac{9}{2}\cdot{p}\cdot{(\Psi_{PM}\cdot{i_q}+(L_d-L_q)\cdot{i_d}\cdot{i_q})}\\ 
    \theta_{el}(k+1) &= T_s \big(\omega_{mech}(k)\cdot{p}) + \theta_{el}(k)\\
    \omega_{mech}(k+1) &=  T_s \bigg( \frac{M_M(k)-M_L(k)}{J} \bigg) + \omega_{mech}(k)
  \end{align}

Note that the integrator for :math:`\theta_{el}` is limited to :math:`\pm \pi` to avoid overflow (wrapping integrator).

Additional system equations
---------------------------
Six-phase model
***************
.. math::

  \begin{align}
    \psi_{x}(k+1) &= T_s \big( v_{x}(k) - R_{1} i_{x}(k))+\psi_{x}(k)\\
    \psi_{x}(k) &= L_{ls} i_{x}(k) \\
    \psi_{y}(k+1) &= T_s \big( v_{y}(k) - R_{1} i_{y}(k))+\psi_{y}(k)\\
    \psi_{y}(k) &= L_{ls} i_{y}(k) \\
    \psi_{zi}(k+1) &= T_s \big( v_{zi}(k) - R_{1} i_{zi}(k))+\psi_{zi}(k)\\
    \psi_{zi}(k) &= L_{ls} i_{zi}(k) \\
    \nonumber\textrm{with } i&=1,2
  \end{align}

Nine-phase model
****************
.. math::

  \begin{align}
    \psi_{xi}(k+1) &= T_s \big( v_{xi}(k) - R_{1} i_{xi}(k))+\psi_{xi}(k)\\
    \psi_{xi}(k) &= L_{ls} i_{xi}(k) \\
    \psi_{yi}(k+1) &= T_s \big( v_{yi}(k) - R_{1} i_{yi}(k))+\psi_{yi}(k)\\
    \psi_{yi}(k) &= L_{ls} i_{yi}(k) \\
    \psi_{0}(k+1) &= T_s \big( v_{0}(k) - R_{1} i_{0}(k))+\psi_{0}(k) \\
    \psi_{0}(k) &= L_{ls} i_{0}(k) \\
    \nonumber\textrm{with } i&=1,2,3
  \end{align}

IP-core interfaces
==================
.. csv-table:: Interface of nine-phase PMSM Model IP-Core
   :file: uz_pmsm_model_multiph_dq_interfaces.csv
   :widths: 50 40 80 60 60 190
   :header-rows: 1

Driver reference
================
The set and get functions for voltage and currents are implemented as normal and unsafe version.
In addition to the regular functions, *unsafe* versions of the driver exist (``_unsafe``).
These functions are considerably faster than their safe counterparts but violate the software rules outlined in :ref:`software_development_guidelines`.
It is strongly advised to manually test by comparing the safe and unsafe versions before using *_unsafe*!""

Three-phase model
-----------------
.. doxygentypedef:: uz_pmsm_model3ph_dq_t

.. doxygenstruct:: uz_pmsm_model3ph_dq_config_t
  :members:

.. doxygenstruct:: uz_pmsm_model3ph_outputs_t
  :members:

.. doxygenstruct:: uz_pmsm_model3ph_inputs_t
  :members:

.. doxygenfunction:: uz_pmsm_model3ph_init

.. doxygenfunction:: uz_pmsm_model3ph_trigger_input_strobe

.. doxygenfunction:: uz_pmsm_model3ph_trigger_output_strobe

.. doxygenfunction:: uz_pmsm_model3ph_set_inputs

.. doxygenfunction:: uz_pmsm_model3ph_get_outputs

.. doxygenfunction:: uz_pmsm_model3ph_reset

.. doxygenfunction:: uz_pmsm_model_dq_set_use_axi_input

.. doxygenfunction:: uz_pmsm_model3ph_dq_get_input_voltages

Six-phase model
---------------
.. doxygentypedef:: uz_pmsm_model6ph_dq_t

.. doxygenstruct:: uz_pmsm_model6ph_dq_config_t
  :members:

.. doxygenstruct:: uz_pmsm_model6ph_dq_outputs_general_t
  :members:

.. doxygenfunction:: uz_pmsm_model6ph_dq_init

.. doxygenfunction:: uz_pmsm_model6ph_trigger_voltage_input_strobe

.. doxygenfunction:: uz_pmsm_model6ph_trigger_voltage_output_strobe

.. doxygenfunction:: uz_pmsm_model6ph_trigger_current_output_strobe

.. doxygenfunction:: uz_pmsm_model6ph_dq_set_inputs_general

.. doxygenfunction:: uz_pmsm_model6ph_dq_get_outputs_general

.. doxygenfunction:: uz_pmsm_model6ph_dq_set_voltage

.. doxygenfunction:: uz_pmsm_model6ph_dq_set_voltage_unsafe

.. doxygenfunction:: uz_pmsm_model6ph_dq_get_input_voltages

.. doxygenfunction:: uz_pmsm_model6ph_dq_get_input_voltages_unsafe

.. doxygenfunction:: uz_pmsm_model6ph_dq_get_output_currents

.. doxygenfunction:: uz_pmsm_model6ph_dq_get_output_currents_unsafe

.. doxygenfunction:: uz_pmsm_model6ph_dq_reset

.. doxygenfunction:: uz_pmsm_model6ph_dq_set_use_axi_input

Nine-phase model
----------------
.. doxygentypedef:: uz_pmsm_model9ph_dq_t

.. doxygenstruct:: uz_pmsm_model9ph_dq_config_t
  :members:

.. doxygenstruct:: uz_pmsm_model9ph_dq_outputs_general_t
  :members:

.. doxygenfunction:: uz_pmsm_model9ph_dq_init

.. doxygenfunction:: uz_pmsm_model9ph_trigger_voltage_input_strobe

.. doxygenfunction:: uz_pmsm_model9ph_trigger_voltage_output_strobe

.. doxygenfunction:: uz_pmsm_model9ph_trigger_current_output_strobe

.. doxygenfunction:: uz_pmsm_model9ph_dq_set_inputs_general

.. doxygenfunction:: uz_pmsm_model9ph_dq_get_outputs_general

.. doxygenfunction:: uz_pmsm_model9ph_dq_set_voltage

.. doxygenfunction:: uz_pmsm_model9ph_dq_set_voltage_unsafe

.. doxygenfunction:: uz_pmsm_model9ph_dq_get_input_voltages

.. doxygenfunction:: uz_pmsm_model9ph_dq_get_input_voltages_unsafe

.. doxygenfunction:: uz_pmsm_model9ph_dq_get_output_currents

.. doxygenfunction:: uz_pmsm_model9ph_dq_get_output_currents_unsafe

.. doxygenfunction:: uz_pmsm_model9ph_dq_reset

.. doxygenfunction:: uz_pmsm_model9ph_dq_set_use_axi_input

Example usage (standalone)
==========================
The IP-core has two intended use cases:

 - Using the model in the dq domain only with inputs coming from the PS
 - Simulating a complete multi-phase drive system including the :ref:`uz_inverter_3ph`, :ref:`uz_vsd_transformation` (see the CIL examples in :ref:`uz_cil_pmsm`)

Using the IP-core in PS only is similar to the use cases shown in :ref:`uz_pmsmModel` open loop example which is recreated here.
The placement of the IP-core for the use from PS only is straight forward as only the default PL interfaces have to be connected.
For the example the nine-phase model is used, but the same can also be applied for the six-phase model.

.. figure:: open_loop_ps.jpg

   Test setup for IP-core PS test in Vivado

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

To prove functionality, the output currents of the shown example are evaluated.
The resulting machine torque is :math:`-0.01562337\,Nm` an the resulting currents are shown in the following equation.
The results were recreated with the Simulink model.

.. math::

  \begin{align}
    out-currents = 
    \begin{bmatrix} i_{d} \\ i_{q} \\ i_{x_1} \\ i_{y_1} \\ i_{x_2} \\ i_{y_2} \\ i_{x_3} \\ i_{y_3} \\ i_{zero} \end{bmatrix} = 
    \begin{bmatrix} 0.03166196\\ -0.006507777 \\ 0.09584665 \\ 0.1277955 \\ 0.1597444 \\ 0.1916933 \\ 0.2236422 \\ 0.2555911 \\ 0.2875399 \end{bmatrix}
  \end{align}

Sources
=======
.. [#Slunjski_Diss] M. Slunjski, “Control of a ninephase symmetrical pmsm with reduced rare earth material,” Dissertation, Liverpool John Moores University, 2020. [Online]. Available: https://researchonline.ljmu.ac.uk/id/eprint/14732/1/2021MarkoPhD.pdf
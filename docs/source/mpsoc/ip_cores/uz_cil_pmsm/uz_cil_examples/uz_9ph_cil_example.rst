.. _uz_9ph_cil_example:

======================
Nine-phase CIL Example
======================

On this page, a description of a nine-phase PMSM CIL model will be given, using the respective UZ IP-Cores.

Vivado
======

The structure iof the nine-phase PMSM CIL model is similar to the :ref:`uz_6ph_cil_example`.
Therefore the basics and details are omitted here.
To simplify the usage of the CIL and to reduce possible errors, a tcl script was created, that places all necessary IP-Cores automatically and connects them.
To use it, open the Vivado project and on the top level of the block design, run the following commands seperately:

"cd [ get_property DIRECTORY [current_project] ]" 

"source ../../docs/source/mpsoc/ip_cores/uz_cil_pmsm/uz_cil_examples/ninephase_cil.tcl"

A hierarchy with all CIL-IP-Cores is created and can be moved to the ``uz_user`` hierarchy.
Connect the ports ``AXI``, ``aresetn`` and ``aclk`` as follows inside of ``uz_user``.

.. figure:: vivado_9ph.png

    Vivado setup

The ``trigger_adc`` signal is taken from the outside and connected with ``trigger_conversions`` of the ``uz_system`` hierarchy.

For the gate signals, the existing PWM IP-Cores of the ``D1_adapter`` can be used.
For that, use the ``concat`` block to combine the six gate signals in the order of ``H1T``, ``H1B``, ``H2T``, ..., ``H3B`` and route the signal to the respective ``gate_sys`` port.

Vivado
======

To initialize all IP-Cores, the files ``hw_init/ninephase_CIL.c`` and ``include/ninephase_CIL.h`` are created.

.. code-block:: c
  :caption: ``ninephase_CIL.h`` (R5)
    #include "../uz/uz_global_configuration.h"
    #include "../IP_Cores/uz_pmsm_model_9ph_dq/uz_pmsm_model9ph_dq.h"
    #include "../IP_Cores/uz_pmsm9ph_transformation/uz_pmsm9ph_transformation.h"
    #include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
    uz_inverter_3ph_t* init_CIL_inv1(void);
    uz_inverter_3ph_t* init_CIL_inv2(void);
    uz_inverter_3ph_t* init_CIL_inv3(void);
    uz_pmsm9ph_transformation_t* init_CIL_trafo(void);
    uz_pmsm_model9ph_dq_t* init_CIL_pmsm(void);

.. code-block:: c
  :caption: ``ninephase_CIL.c`` (R5)

    #include "../include/ninephase_CIL.c"
    uz_inverter_3ph_t* init_CIL_inv1(void){
        struct uz_inverter_3ph_config_t cil_inverter1_config = {
            .base_address = 0,
            .ip_core_frequency_Hz = 100000000.0f,
            .switch_pspl_abc = false,
            .switch_pspl_gate = false,
            .udc = 250.0f};
        return uz_inverter_3ph_init(cil_inverter1_config);
    }

    uz_inverter_3ph_t* init_CIL_inv2(void){
        struct uz_inverter_3ph_config_t cil_inverter2_config = {
            .base_address = 0,
            .ip_core_frequency_Hz = 100000000.0f,
            .switch_pspl_abc = false,
            .switch_pspl_gate = false,
            .udc = 250.0f};
        return uz_inverter_3ph_init(cil_inverter2_config);
    }

    uz_inverter_3ph_t* init_CIL_inv3(void){
        struct uz_inverter_3ph_config_t cil_inverter3_config = {
            .base_address = 0,
            .ip_core_frequency_Hz = 100000000.0f,
            .switch_pspl_abc = false,
            .switch_pspl_gate = false,
            .udc = 250.0f};
        return uz_inverter_3ph_init(cil_inverter3_config);
    }

    uz_pmsm9ph_transformation_t* init_CIL_trafo(void){
        struct uz_pmsm9ph_config_t trafo_config = {
            .base_address = 0,
            .ip_core_frequency_Hz = 100000000.0f
        };
        return uz_pmsm9ph_transformation_init(trafo_config);
    }

    uz_pmsm_model9ph_dq_t* init_CIL_pmsm(void){
        struct uz_pmsm_model9ph_dq_config_t pmsm_config = {
            .base_address = 0,
            .ip_core_frequency_Hz = 100000000.0f,
            .polepairs = UZ_D5_MOTOR_POLE_PAIR_NUMBER,
            .r_1 = 0.3411f,
            .inductance.d = 0.0029587f,
            .inductance.q = 0.0038f,
            .inductance.x1 = 0.0019410f,
            .inductance.y1 = 0.0014541f,
            .inductance.x2 = 0.0020143f,
            .inductance.y2 = 0.0021166f,
            .inductance.x3 = 0.0019249f,
            .inductance.y3 = 0.0030169f,
            .inductance.zero = 0.0019548f,
            .psi_pm = 0.0741442f,
            .friction_coefficient = 0.01f,
            .coulomb_friction_constant = 0.01f,
            .inertia = 0.01,
            .simulate_mechanical_system = false,
            .switch_pspl = false
        };
        return uz_pmsm_model9ph_dq_init(pmsm_config);
    }

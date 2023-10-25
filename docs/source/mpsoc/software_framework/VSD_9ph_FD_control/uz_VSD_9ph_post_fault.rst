============================
VSD Open-phase-fault control
============================

General
=======

Derating
--------

If a multiphase machine is operated in faulty condition, the phase current amplitudes might not be equal any longer.
This is problematic, since they can exceed the rated currents of machine or inverters which must be avoided.
This is done by derating the current setpoints with a predetermined factor.

K-factors
---------

For the intended control structure in the figure below, setpoints for the additional system PI-controllers are necessary.
The additional systems are not generally controlled to zero, as they are coupled with the :math:`\alpha\beta`-system in post-fault operation and could therefore hinder the reaching of the desired operating point.

.. figure:: fault_control.png

    Controller structure


Therefore, the k-factors are calculated and used to determine the additional system setpoints in relation with the :math:`\alpha\beta`-currents.

.. math::
    \begin{bmatrix}
    i_{set}^{x1} \\
    i_{set}^{y1} \\
    i_{set}^{x2} \\
    i_{set}^{y2} \\
    i_{set}^{x3} \\
    i_{set}^{y3} \\
  \end{bmatrix} = 
  \begin{bmatrix}
    k_{x1,\alpha} \cdot i^{\alpha} + k_{x1,\beta} \cdot i^{\beta} \\
    k_{y1,\alpha} \cdot i^{\alpha} + k_{y1,\beta} \cdot i^{\beta} \\
    k_{x2,\alpha} \cdot i^{\alpha} + k_{x2,\beta} \cdot i^{\beta} \\
    k_{y2,\alpha} \cdot i^{\alpha} + k_{y2,\beta} \cdot i^{\beta} \\
    k_{x3,\alpha} \cdot i^{\alpha} + k_{x3,\beta} \cdot i^{\beta} \\
    k_{y3,\alpha} \cdot i^{\alpha} + k_{y3,\beta} \cdot i^{\beta} \\
  \end{bmatrix}


Since there are degrees of freedom left in the machine in many OPFs, there is room for optimization.
In literature, the criteria ``Minumum Loss`` (ML) and ``Maximum Torque`` (MT) are common.
The ML optimization aims to minimize the additional system copper losses and therefore the fundamental additional system currents, without influencing the :math:`\alpha\beta`-currents.
The MT optimization maximizes the torque range of the machine in post fault operation, by keeping the derating factor as close to 1 as possible.

Limitations
===========

The k-factors and derating factors are determined with an optimization function in Matlab (see ``docs\source\mpsoc\software_framework\VSD_9ph_FD_control\optimization.zip``).
Every phase-fault combination has to be optimized individually (e.g. :math:`a_1+a_2`, :math:`a_1+a_3` are different optimizations) and this has to be done for ``1N`` and ``3N`` and ``ML`` and ``MT``.
So far, this has been done for one and two phase-faults and the special case of three phase faults, where a complete system is faulty.
If more cases should be taken into account, the Matlab scripts can be used to generate them (no further implementation needed).

Function references
===================

.. doxygenstruct:: uz_9ph_MLMT_kparameter_t
  :members:

.. doxygenfunction:: uz_get_k_parameter_9ph

.. doxygenfunction:: fault_indices_to_OPF_index


Code example
============

.. code-block:: c
  :linenos:
  :caption: Example for using the functions of the module for the fault control (isr.c)

  #include "../uz/uz_VSD_9ph_FD_control/uz_VSD_9ph_FD.h"
  #include "../uz/uz_VSD_9ph_FD_control/uz_VSD_9ph_ML_MT_Control.h"
  uz_9ph_abc_t fault_single_indices  = {0};
  int fault_n_OPF = 0;
  uz_9ph_MLMT_kparameter_t k_param = {0};

  //..
    // find fault index
    fault_single_indices = uz_vsd_opf_9ph_faultdetection_step(Global_Data.objects.fault_detection, Global_Data.av.currents_alphabeta, Global_Data.av.omega_el);
	  fault_n_OPF = uz_vsd_opf_9ph_get_n_fault(fault_single_indices);
    // use fault_single_indices, ML or MT and neutral connection 1U or 3U
    k_param = uz_get_k_parameter_9ph(fault_single_indices, ML, 1U);
    // optional but recommended: set a threshold for minimum current amplitudes (e.g. iq>1A)
    // since fault control does not work reliable close to zero current operating point
      if(sqrt(dq_setpoints_in.q*dq_setpoints_in.q + dq_setpoints_in.d*dq_setpoints_in.d) < 1.0f){
        k_param.valid = false;
      }
    // if valid param set was found, derate the setpoints
    if(k_param.valid){
      dq_setpoints.d *= dq_setpoints_in.d * k_param.derating;
      dq_setpoints.q *= dq_setpoints_in.q * k_param.derating;
    }
    // in control state
    // place your controller function here and use the k-param setpoints
    // reduce your controllers according to the amount of faulty phases and remaining degrees of freedom


Another application example can be found in the branch ``feature/THN_ninephase_PMSM/FOC``.
This branch also includes an implementation example of the controllers and application of k-factors to the setpoints.

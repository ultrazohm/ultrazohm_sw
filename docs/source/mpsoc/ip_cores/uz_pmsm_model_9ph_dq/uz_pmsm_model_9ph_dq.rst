.. _uz_pmsm_model_9ph_dq:

====================
Ninephase PMSM Model
====================
Important: This IP-core is based on the :ref:`uz_pmsmModel` IP-core, where the basics (e.g. working principle of the integrations is explained).

Differences to the threephase PMSM model IP-core:

- IP-Core of a ninephase PMSM model
- Sample frequency of the integrator is :math:`T_s=\frac{1}{1\,MHz}`
- IP-Core clock frequency **must** be :math:`f_{clk}=100\,MHz`!
- All calculations in the IP-Core are done in double precision
- Interfaces to PL are realized in fixpoint, while interfaces to the PS use single precision float values

System description
==================

The modelling of the ninephase maschine is based on [[#Slunjski_Diss]_].
The general idea in this work and also the common approach to model multiphase machines is to transform the phase variables with the VSD and Park transformations as shown and done in :ref:`uz_pmsm9ph_transformation` and :ref:`uz_transformation`.
Transformed voltages are used as input for this IP-core and the outputs will also be in the rotary or stationary reference frame ant not phase variables.
This IP-core contains the electric differential equations and the mechanical part where the torque is calculated.
Additionally, either a torque load or a fixed speed can be set to test the machine model.
While the equations are mostly similar to the ones of :ref:`uz_pmsmModel`, thy will be shown here again for the sake of completeness.
To obtain more details about the equations and integrators, reading :ref:`uz_pmsmModel` is advised.

dq equations
************

.. math::

  \begin{align}
      \psi_{d}(k+1) &= T_s \big( v_{d}(k) - R_{1} i_{d}(k) + \omega_{el} \psi_{q}(k) \big) + \psi_{d}(k)\\
      \psi_{q}(k+1) &= T_s \big( v_{q}(k) - R_{1} i_{q}(k) - \omega_{el} \psi_{d}(k) \big) + \psi_{q}(k)\\
      \psi_{d}(k) &= \psi_{PM} + L_{d} i_{d}(k) \\
      \psi_{q}(k) &= L_{q} i_{q}(k) \label{eq:psiq_ld}
  \end{align}

Additional system equations
***************************

.. math::

  \begin{align}
    \psi_{xi}(k+1) &= T_s \big( v_{xi}(k) - R_{1} i_{xi}(k)); i=1,2,3\\
    \psi_{xi}(k) &= L_{ls} i_{xi}(k) \\
    \psi_{yi}(k+1) &= T_s \big( v_{yi}(k) - R_{1} i_{yi}(k)); i=1,2,3\\
    \psi_{yi}(k) &= L_{ls} i_{yi}(k)\\
    \psi_{0}(k+1) &= T_s \big( v_{0}(k) - R_{1} i_{0}(k))\\
    \psi_{0}(k) &= L_{ls} i_{0}(k)
  \end{align}

Mechanical equations
********************

.. math::

  \begin{align}
    M_M &= \frac{9}{2}\cdot{p}\cdot{(\Psi_{PM}\cdot{i_q}+(L_d-L_q)\cdot{i_d}\cdot{i_q})}\\ 
    \theta_{el}(k+1) &= T_s \big(\omega_{mech}(k)\cdot{p})\\
    \omega_{mech}(k+1) &=  T_s \big(\frac{M_M(k)-M_L(k)}{J})
  \end{align}

Note that the integrator for :math:`\theta_{el}` is limited to :math:`+/-\pi` to avoid overflow of the integrator.

IP-core interfaces
==================

.. csv-table:: Interface of ninephase PMSM Model IP-Core
   :file: uz_pmsm_model_9ph_dq_interfaces.csv
   :widths: 50 40 60 60 60 210
   :header-rows: 1

Example usage
=============

The IP-core has two intended use cases:
The model can be used with in the dq domain only and the inputs are set from the PS.
It is also possible to combine the model with the IP-cores :ref: "inverter", :ref:`uz_pmsm9ph_transformation` and :ref:`uz_pwm_ss_2l` to simulate a complete ninephase drive system.

Usage in PS only
****************

Using the model in PS only is similar to the use cases shown in :ref:`uz_pmsmModel`.
Therefore only the open loop example is presented here.


Ninephase drive system in PL (HIL)
**********************************

Sources
=======

.. [#Slunjski_Diss] M. Slunjski, “Control of a ninephase symmetrical pmsm with reduced rare earth material,” Dissertation, Liverpool John Moores University, 2020. [Online]. Available: https://researchonline.ljmu.ac.uk/id/eprint/14732/1/2021MarkoPhD.pdf

==================================
ML-MT-Optimized control during OPF
==================================

The VSD-currents during pre-fault operation in multiphase machines are independent from each other and can be controlled separately e.g. by using PI- and resonant controller in the three VSD-subsystems.
During one or more open-phase-faults (OPF) the VSD-currents are no longer independent from each other, as the system looses a degree of freedom per faulted phase, resulting in a coupling between the systems.
The coupling between the systems depend on the specific fault scenario and can be calculated.
The generated torque of the six phase machine depends only on the alpha-beta current, because through the VSD-Transformation alle torque producing components are mapped into the :math:`\alpha\beta`-plane.
To generate constant torque, in pre-fault and the post-fault case, the alpha-beta-currents :math:`\mathbf{i}^{\alpha\beta}` have to be controlled accordingly.
In a PMSM the alpha-beta-currents should take the following form

.. math::
  \begin{bmatrix}
    i_{ref}^{\alpha} \\
    i_{ref}^{\beta} \\
  \end{bmatrix} =  
  \begin{bmatrix}
    \hat{I}_{\alpha\beta} \cdot cos(\omega_e \cdot t + \psi) \\
    \hat{I}_{\alpha\beta} \cdot sin(\omega_e \cdot t + \psi) \\
  \end{bmatrix} 

to reach constant torque. :math:`\hat{I}` is the amplitude of the currents, :math:`\omega_e` the angular velocity and :math:`\psi` the phase.

The currents :math:`\mathbf{i}^{xy}` and :math:`\mathbf{i}^{0^+0^-}` in the other two subsystems are not torque producing and so can be controlled arbitrarily in the pre-fault case, for example to reduce copper losses the currents can be controlled to be zero.

Since in the post-fault situation the VSD-subsystems are no longer independent controlling the currents :math:`\mathbf{i}^{xy}` and :math:`\mathbf{i}^{0^+0^-}`  arbitrarily is no longer possible.
As :math:`\mathbf{i}^{\alpha\beta}` are torque producing their reference values is given by the desired torque.
The reference values of the other VSD-currents has to be specified as a function of the alpha-beta currents to adhere to the coupling between the VSD-currents and to not interfere with the control of the alpha-beta currents for constant torque.

The reference values of the VSD-currents are therefore defined depending on the alpha-beta currents:

.. math::
    \begin{bmatrix}
    i_{ref}^x \\
    i_{ref}^y \\
    i_{ref}^{z1} \\
    i_{ref}^{z2} \\
  \end{bmatrix} = 
  \begin{bmatrix}
    k_1 \cdot i^{\alpha} + k_2 \cdot i^{\beta} \\
    k_3 \cdot i^{\alpha} + k_4 \cdot i^{\beta} \\
    k_5 \cdot i^{\alpha} + k_6 \cdot i^{\beta} \\
    k_7 \cdot i^{\alpha} + k_8 \cdot i^{\beta} \\
  \end{bmatrix}

The k-parameters in these equations depend on the fault scenario and can either be calculated or optimized depending on the available degrees of freedom in the system.
Frequently used for determining the k-parameters are the Minimum Loss (ML) and Maximum Torque (MT) optimization strategies, optimizing for minimal copper losses and maximum torque operation range respectively while complying to the coupling between the vsd-subsystems because of the fault-scenario.[[#Munim]_] [[#Che_Duran]_]

The following module with the function ``uz_get_k_parameter`` contains the ML and MT optimized k-parameters for up to 3 OPFs of an asymmetric six-phase PMSM with one (1N) or two (2N) neutral points.
Based on these parameters a fault tolerant control system for asymmetric six-phase PMSM can be created by controlling the VSD-Currents with the calculated reference values.

In addition to the k-parameters a derating factor for the fault scenario is supplied, by which the nominal currents of the machine have to be scaled down to ensure a safe continuous operation.
The derating is needed as the phase currents in post-fault operation are increased compared to the pre-fault operation for the same torque produced as fewer phases are accessible.


.. _kparameter:

k-Parameter
-----------


.. doxygenstruct:: uz_6ph_MLMT_kparameter
   :members:

Description
^^^^^^^^^^^

Parameter for calculating the reference values for the vsd-control during OPF in an asymmetric 6 phase PMSM


Get k parameter function
------------------------

.. doxygenfunction:: uz_get_k_parameter


Description
^^^^^^^^^^^

Function for reading the k-parameter for a given fault-scenario. 


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call of uz_get_k_parameter()

  int main(void) {

    // fault indices from open phase fault detection
    uz_6phFD_indices FD_indices;

	uz_6ph_MLMT_kparameter k_parameter;

    // get k-parameters according to the fault indices
	k_parameter = uz_get_k_parameter(FD_indices, N1, ML);
    
  }

Enums
^^^^^

Enumerations for input parameters of the function ``uz_get_k_parameter``.

  .. doxygenenum:: neutral_point_configuration

  .. doxygenenum:: ML_MT_optimization





.. [#Munim] W. N. W. A. Munim, M. J. Duran, H. S. Che, M. Bermúdez, I. Ganzález-Prieto, and N. A. Rahim, "A Unified Analysis of the Fault Tolerance Capability in Six-Phase Induction Motor Drives," IEEE Transactions on Power Electronics, vol. 32, no. 10, pp. 7824-7836, Oct. 2017
.. [#Che_Duran] H. S. Che, M. J. Duran, E. Levi, M. Jones, W.-P. Hew, and N. A. Rahim, "Postfault Operation of an Asymmetrical Six-Phase Induction Machine With Single and Two Isolated Neutral Points", IEEE Transactions on Power Electronics, vol. 29, no 10, pp. 5406-5416, Oct. 2014

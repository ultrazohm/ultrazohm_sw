
==================================
ML-MT-Optimized control during OPF
==================================

The VSD-currents during pre-fault operation are independent from each other and can be controlled separately.
During one or more open-phase-faults (OPF) the vsd-currents are no longer independent from each other, as the system looses a degree of freedom per faulted phase.
The generated torque depends only on the alpha-beta current. To generate constant torque in the post-fault case the alpha-beta-currents have to be controlled accordingly.
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

to reach constant torque, just like in the pre-fault case.

Since all VSD-currents are no longer independent in post-fault operation, the reference values for the other VSD-currents have to be specified as a function of the alpha-beta currents.

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

The k-parameters of these functions are not identical for all fault scenarios and can be optimized if there are degrees of freedom available. Otherwise they can be calculated.

Frequently used are the Minimum Loss (ML) and Maximum Torque (MT) optimization strategies, optimizing for minimal copper losses and maximum torque operation range respectively.[[#Munim]_] [[#Che_Duran]_]

The following module with the function ``get_k_parameter`` contains the ML and MT optimized k-parameters for up to 3 OPFs of an asymmetric six-phase PMSM with one (1N) or two (2N) neutral points.
Based on these parameters a fault tolerant control system for asymmetric six-phase PMSM can be created by controlling the VSD-Currents with the calculated reference values.

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

.. doxygenfunction:: get_k_parameter


Description
^^^^^^^^^^^

Function for reading the k-parameter for a given fault-scenario. 


Example
^^^^^^^

.. code-block:: c
  :linenos:
  :caption: Example function call of get_k_parameter()

  int main(void) {

    // fault indices from open phase fault detection
    uz_6phFD_indices FD_indices;

	uz_6ph_MLMT_kparameter k_parameter;

    // get k-parameters according to the fault indices
	k_parameter = get_k_parameter(FD_indices, N1, ML);
    
  }

Enums
^^^^^

Enumerations for input parameters of the function ``get_k_parameter``.

  .. doxygenenum:: neutral_point_configuration

  .. doxygenenum:: ML_MT_optimization





.. [#Munim] W. N. W. A. Munim, M. J. Duran, H. S. Che, M. Bermúdez, I. Ganzález-Prieto, and N. A. Rahim, "A Unified Analysis of the Fault Tolerance Capability in Six-Phase Induction Motor Drives," IEEE Transactions on Power Electronics, vol. 32, no. 10, pp. 7824-7836, Oct. 2017
.. [#Che_Duran] H. S. Che, M. J. Duran, E. Levi, M. Jones, W.-P. Hew, and N. A. Rahim, "Postfault Operation of an Asymmetrical Six-Phase Induction Machine With Single and Two Isolated Neutral Points", IEEE Transactions on Power Electronics, vol. 29, no 10, pp. 5406-5416, Oct. 2014

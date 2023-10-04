.. _uz_svm_6ph:

===========================
Space vector Modulation 6ph
===========================

General
=======

This module implements a space vector modulation for asymmetrical six-phase machine with isolated neutral points (2N).
The implementation is adaptable to 1N and described in the references.

Usage
=====

Function references
-------------------

.. doxygenstruct:: uz_svm_asym_6ph_CSVPWM24_out
  :members:

.. doxygenfunction:: uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta

.. doxygenfunction:: uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_dq

Example
-------

need to copy here!!

Theoretical details
===================

Limitation
----------

The 6ph SVM uses two setpoint limitations.
Both of them limit the absolute value (length) of the space vector (SV), while leaving the phase angle untouched.
Th checks for the limitations are executed in the listed order below:

The :math:`xy`-SV must not be longer than 10% of the :math:`\alpha\beta`-SV.
As can be seen from [[#Eldeeb_diss]_] Fig. 3.3, a large :math:`\alpha\beta`-SV represents a small :math:`xy`-SV and vice versa.
Therefore if the :math:`\alpha\beta`-SV is near the maximum, the :math:`xy`-SV can only be small.
Although a general limitation can not achieve maximum usage in all operating points, with this rule an overall good performance can be expected.

Since the maximum voltage is given by the DC-Bus-Voltage and the modulation index :math:`m_i=0.62` (determined in simulation), the combined length of the space vectors has to be limited.
Therefore both lengths are added and if the exceed the maximum allowed voltage, they will be shortened in their existing relations.
Since the :math:`xy`-SV limitation is executed before and the relation of the :math:`\alpha\beta`-SV and :math:`xy`-SV are kept the same, the previous limitation will not be violated.

Space vectors
-------------

From the existing :math:`2^6` SVs in a six-phase system, not all of them are used.
Instead, the selected sequences of [[#Eldeeb_diss]_] Tab. 3.III are used.
Please note that the decimal notation of [[#Eldeeb_paper]_] and [[#other_paper]_] are used.
Therefore, the binary values of [[#Eldeeb_diss]_] must be mirrored, making the switch a1 being represented by the LSB and c2 by the MSB.

Offline calculations
--------------------


.. [#Eldeeb_diss] H. Eldeeb, "Modelling, Control and Post-Fault Operation of Dual Three-phase Drives for Airborne Wind Energy," Diss., Technische Universität München, München, 2019
.. [#Eldeeb_paper] H. Eldeeb, C. Hackl, M. Abdelrahem and A. S. Abdel-Khalik, "A unified SVPWM realization for minimizing circulating currents of dual three phase machines," 2017 IEEE 12th International Conference on Power Electronics and Drive Systems (PEDS), Honolulu, HI, USA, 2017, pp. 925-931, doi: 10.1109/PEDS.2017.8289127.
.. [#other_paper] C. Wang, K. Wang, and X. You, “Research on synchronized svpwm strategies under low switching frequency for six-phase vsi-fed asymmetrical dual stator induction machine,” IEEE Trans. on Ind. Electron., vol. 63, no. 11, pp. 6767–6776, Nov. 2016
=========================
How to set encoder offset
=========================

Motor control often relies on using the rotating dq-reference frame.
The rotating dq-reference frame for synchronous machines is aligned with the d-axis and relies on the knowledge of the angle :math:`\vartheta` between d-axis and :math:`\alpha` axis.
The angle :math:`\vartheta` can be measured or estimated and is used in the transformation, e.g., using :ref:`uz_transformation`.
Additionally, machine models in dq-frame assume this alignment.
Several different encoder technologies exist, e.g., :ref:`ipCore_incremental_encoder`.
The encoder reference (the zero-point of the encoder) is not necessarily aligned with the d-axis of the machine.

.. _encoder_alignment_picture:

.. figure:: encoder_alignment.png
   :width: 400px
   :align: center

   Alignment of encoder, :math:`alpha` and d-axis

This alignment is shown in fig. :numref:`encoder_alignment_picture` with the angle :math:`\vartheta_m` between the :math:`\alpha`-axis and the d-axis and the encoder offset :math:`\vartheta_{m,offset}` between the :math:`alpha`-axis of the machine and the encoder reference.
The following methods for setting the offset are commonly used for permanent magnet synchronous machines:

#. Duty cycle on the :math:`a` phase
#. Control negative d-current
#. Back-EMF
#. Flux-based (open circuit)
#. Flux-based (controlled)


Duty cycle on the :math:`a`-phase 
=================================

The winding of the :math:`a`-phase is aligned with the :math:`\alpha`-axis of the machine.
The main idea in this offset estimation is to drive a current  through the :math:`a`-phase of the machine, which in turn generates a linked magnetic flux leading the d-axis with the permanent magnet to mechanically turn and align with the :math:`alpha`-axis of the machine.
This can be achieved by stepping the duty cycle of the :math:`a`-phase from zero to an arbitrary duty cycle.
The duty cycle is kept on its value and the current angle :math:`\vartheta_m` is set as :math:`\vartheta_{m,offset}`.
Since the method does not use a closed loop current control, a duty cycle has to be chosen that does not lead to a phase current above the rated current of the machine.
However, the duty cycle has to be sufficiently large to move the rotor reliably into the :math:`\alpha` axis.
This method is quick but results in sub-optimal alignment, requires manual tuning of the duty cycle and is often unreliable in the laboratory.
Additionally, :math:`L_d=L_q` is assumed.

.. _torque_over_angle:

.. figure:: asym_torque.png
   :width: 400px
   :align: center

   dq-reference frame in PMSM (left) and torque over current angle (right) [[#asym_pmsm]_, p. 7]

Fig. :numref:`torque_over_angle` showcases the relationship between current angle and machine torque with :math:`m_{Rel}` indicating the torque due to the reluctance effect, :math:`m_{syn}` indicating the torque due to the linked flux of the permanent magnet and :math:`m_{ges}` indicating the resulting sum of both torque components.
For machines with :math:`L_d=L_q` only the green torque curve applies.
Therefore, current in the :math:`a`-phase prompts the rotor to move into the :math:`\alpha`-axis aligning the peak of the torque with the d-axis.
If :math:`L_d \neq L_q`, the green curve is superimposed with the blue curve yielding the resulting torque (black line).
Thus, current in the :math:`a`-phase does not align the :math:`\alpha`-axis with the d-axis but with an angle that is skewed depending on the specific values of the inductances :math:`L_d`, :math:`L_q`, and flux linkage of the permanent magnet :math:`\psi_{PM}`.




.. [#Schroeder_Regelung] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Springer, 2015, 4. Edition (German)
.. [#rahman_encoder_offset] K. M. Rahman and S. Hiti, "Identification of machine parameters of a synchronous motor," in IEEE Transactions on Industry Applications, vol. 41, no. 2, pp. 557-565, March-April 2005, doi: 10.1109/TIA.2005.844379.
.. [#asym_pmsm] Winzer, Patrick, 2017, Dissertation, "Steigerung von Drehmoment und Wirkungsgrad bei Synchronmaschinen durch Nutzung der magnetischen Asymmetrie", DOI: 10.5445/IR/1000071097, https://publikationen.bibliothek.kit.edu/1000071097
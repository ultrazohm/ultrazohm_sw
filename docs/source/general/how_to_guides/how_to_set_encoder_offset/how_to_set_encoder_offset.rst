=========================
How to set encoder offset
=========================

Motor control often relies on using the rotating dq-reference frame.
The rotating dq-reference frame for permanent magnet synchronous machines (PMSM) is aligned with the d-axis and relies on the knowledge of the angle :math:`\vartheta_{el}` between d-axis and :math:`\alpha` axis.
The angle :math:`\vartheta_{el}` can be measured or estimated and is used in the transformation, e.g., using :ref:`uz_transformation`.
Additionally, machine models in dq-frame assume this alignment.
Several different encoder technologies exist, e.g., :ref:`ipCore_incremental_encoder`.
The encoder reference (the zero-point of the encoder) is not necessarily aligned with the d-axis of the machine.

.. _encoder_alignment_picture:

.. figure:: encoder_alignment.png
   :width: 400px
   :align: center

   Mechanical alignment of the encoder with respect to the :math:`\alpha`-axis and d-axis

This alignment is shown in fig. :numref:`encoder_alignment_picture` with the angle :math:`\vartheta_m` between the :math:`\alpha`-axis and the d-axis and the mechanical encoder offset :math:`\vartheta_{m,offset}` between the :math:`\alpha`-axis of the machine and the encoder reference.
Note that a machine with :math:`p` pole pairs has :math:`p` different d-axis (each with a positive and negative pole).
While the encoder measures the mechanical angle :math:`\vartheta_m` of the machine , the electrical angle :math:`\vartheta_{el}` is required for the dq-transformations.
The electrical angle is calculated using the modulo operation:

.. math::

  \vartheta_{el} = (\vartheta_m \cdot p - \vartheta_{el,offset}) \bmod 2\pi

With the encoder offset in the electrical radian :math:`\vartheta_{el,offset}` assuming :math:`\vartheta_m` is measured in radian and one mechanical rotation is equal to :math:`\vartheta_m=2\pi`.
The usage of the offset :math:`\vartheta_{el,offset}` is assumed in the subsequent sections.
The following methods for determining the offset are commonly used for PMSM:

#. Duty cycle on the :math:`a` phase
#. No-torque by d-current
#. Back-EMF
#. Flux-based (with test-bench machine)
#. Flux-based (without test-bench machine)


Duty cycle on the :math:`a`-phase 
=================================

The linked flux of the :math:`a`-phase winding is aligned with the :math:`\alpha`-axis of the machine.
The main idea in this offset estimation is to drive a current through the :math:`a`-phase of the machine, which generates a linked magnetic flux leading the d-axis with the permanent magnet to mechanically turn and align with the :math:`\alpha`-axis of the machine.
This can be achieved by stepping the duty cycle of the :math:`a`-phase from zero to an arbitrary duty cycle.
The duty cycle is kept on its value and the current angle :math:`\vartheta_{el}` is set as :math:`\vartheta_{el,offset}`.
Since the method does not use a closed-loop current control, a duty cycle has to be chosen that does not lead to a phase current above the rated current of the machine.
However, the duty cycle has to be sufficiently large to move the rotor reliably into the :math:`\alpha` axis.
This method is quick but results in sub-optimal alignment, requires manual tuning of the duty cycle, and is often unreliable in the laboratory.
Additionally, :math:`L_d=L_q` is assumed.

.. Using tables for side by side figure:
.. list-table::

    * - .. tikz:: dq-reference frame in PMSM based on [[#asym_pmsm]_, p. 7]
           :libs: shapes, arrows, positioning, calc, angles, quotes
           :xscale: 80
           
           \begin{tikzpicture}[auto, node distance=2cm,>=latex']
             \coordinate (origo) at (0,0);
             \coordinate (angle_start) at (0,3.5);
           
             \draw[color=black!60, very thick](0,0) circle (1.8);
             \draw[color=black!60, very thick](0,0) circle (2);
             \draw[color=black!60, very thick](0,0) circle (3);
             \filldraw[black, fill=red!20] (1,1) rectangle (0.75,-1);
             \filldraw[black, fill=green!20] (0.75,1) rectangle (0.5,-1);
           
             \filldraw[black, fill=green!20] (-1,1) rectangle (-0.75,-1);
             \filldraw[black, fill=red!20] (-0.75,1) rectangle (-0.5,-1);
           
             \draw[->, black] (0,0) -- node(d_axis)[below, very near end]{d} (4,0);
             \draw[->, black] (0,0) -- node(q_axis)[right, very near end]{q} (0,4);
             \draw[->, red] (0,0) -- node(current)[right, very near end]{$\underline{i}$} (-2,4);
             \pic [draw, ->,
             angle radius=35mm, angle eccentricity=1.1,
             "$\beta$"] {angle = angle_start--origo--current};
             \draw (2,-3) node [name=stator]{Stator};
             \draw (-3,-3) node [name=rotor]{Rotor};
             \draw (rotor) -- (0,-1);
             \draw (stator) -- (0,-2.5);
           \end{tikzpicture}

      - .. tikz:: Torque components over current angle based on [[#asym_pmsm]_, p. 7]
           :align: left
         
             \begin{axis}[domain=-1*pi:1*pi,samples=100,legend pos=outer north east, grid,
                 xtick={-1*pi,-0.5*pi, 0,0.5*pi, 1*pi},
                 xticklabels={$-\pi$,$-\frac{\pi}{2}$, 0,$\frac{\pi}{2}$, $\pi$},
                 very thick,
                 ytick={0},
                 xlabel={$\beta$},
                 ylabel={$T_I$}]
                 \addplot[dashed,color=blue,mark=none] {cos(deg(x)) }; 
                 \addplot[dashed,color=red,mark=none] {0.5*sin(deg(x*2)) }; 
                 \addplot[color=black,mark=none] {0.5*sin(deg(x*2))+cos(deg(x)) }; 
                 \legend{$T_{PM}$,$T_{Rel}$,$T_I$}
             \end{axis}

The figure left showcases the relationship between the current angle :math:`\beta` and machine torque with the torque generated by the reluctance effect :math:`T_{Rel}`, the torque generated by the linked flux of the permanent magnet :math:`T_{PM}` and the sum of both torque components :math:`T_{I}` (the inner torque of the machine).
The current angle :math:`\beta` describes the angle between the q-axis and the space vector of the stator current :math:`\underline{i}=i_d + ji_q` (with the imaginary unit :math:`j`).
Therefore, :math:`\beta=\arctan{\big( \frac{-i_d}{i_q} \big) }`.
For machines with :math:`L_d=L_q` only the green torque curve applies.
Therefore, current in the :math:`a`-phase prompts the rotor to move into the :math:`\alpha`-axis aligning the peak of the torque with the d-axis.
If :math:`L_d \neq L_q`, the green curve is superimposed with the blue curve yielding the resulting torque (black line).
Thus, current in the :math:`a`-phase does not align the :math:`\alpha`-axis with the d-axis but with an angle that is skewed depending on the specific values of the inductances :math:`L_d`, :math:`L_q`, and flux linkage of the permanent magnet :math:`\psi_{PM}`.
The method for determining the encoder offset :math:`\vartheta_{el,offset}` must not be used on a machine with :math:`L_d \neq L_q`.

- Quick & easy
- Assumes :math:`L_d = L_q`
- Manual estimation of end-value for duty cycle step (high enough to move the rotor, not too high to damage machine)
- No closed-loop control to prevent exceeding the rated current of the machine

No-torque by d-current
======================

A possible alternative for driving current through the :math:`a`-phase of the machine is to ensure that no torque is generated if :math:`i_q=0` and :math:`i_d \neq 0` since the PMSM does not generate torque in this case [[#Schroeder_Regelung]_,p. 1092]:

.. math::

    T_I=\frac{3}{2} p \big(i_q \psi_{pm} + i_d i_q (L_d -L_q) \big)

This alignment method uses a closed-loop current control and control the set-points :math:`i_q^*=0` and :math:`i_d^* \neq 0`.
Using a torque sensor on the test bench (as described in [[#rahman_encoder_offset]_]), the encoder offset can manually be adjusted until the torque sensor measures zero torque.
The set-point for the current :math:`i_d` depends on the machine under test.

- Simple concept
- Manual tuning
- Requires torque sensor
- Suitable for machines with :math:`L_d = L_q` and :math:`L_d \neq L_q`
- Not suitable for synchronous reluctance machines with :math:`\psi_{PM}=0\,Vs` (since neither :math:`I_d` nor :math:`I_q` generates torque if the other current is zero)
- The accuracy of the torque sensor determines the accuracy of the encoder alignment

Back-EMF
========

Alignment of the encoder and the d-axis can be achieved if the zero-crossing of the back-EMF and the position signal is aligned as shown in :numref:`encoder_alignment_backemf` [[#rahman_encoder_offset]_].
However, this method for determining the encoder offset :math:`\vartheta_{el,offset}` requires that the machine under test is driven by an external machine to a fixed rotational speed and the back-EMF, as well as the encoder signal, are measured by one oscilloscope or the controller.
The machine under test is operated with open circuit, i.e., :math:`i_d=i_q=0`.
If the back-EMF should be measured by the controller, a phase voltage measurement is required on the power electronics.
Voltage measurement on the power electronics is not always available and if it is, usually a low pass filter is included which adds a phase lag to the measured voltage which has to be accounted for when aligning the encoder.
Furthermore, the position alignment does not account for iron losses.

.. _encoder_alignment_backemf:

.. tikz:: Alignment of zero-crossing of back-EMF with zero-crossing of encoder position  [[#rahman_encoder_offset]_]
           :align: center
           :xscale: 50
         
             \begin{axis}[domain=-pi/3:2*pi,samples=100,legend pos=outer north east, grid,
                 xtick={0,pi, 2*pi},
                 xticklabels={$0$,$\pi$, $2\pi$},
                 very thick,
                 ytick={0},
                 xlabel={Position $\vartheta_m$},
                 ylabel={Back-EMF, Position}]
                 \addplot[color=blue,mark=none] {cos(deg(x + (0.7*pi)/2)) }; 
                 \addplot[color=red,mark=none] { 0.2/pi*x }; 
                 \addplot[mark=none,color=black] coordinates{ (0,-0.6) (0,0.6)};
                 \addplot[mark=none,color=black,dashed] coordinates{ (0.47,-0.6) (0.47,0.6)};
                 \legend{Back-EMF, Position $\vartheta_m$};
                 \node[anchor=west] (source) at (30,180){Offset};
             \end{axis}

- Complex setup with encoder signal on external measurement device (e.g., oscilloscope) or voltage measurement on inverter
- Does not account for iron losses, potentially leading to misalignment

Flux-based (with test-bench machine)
====================================

The flux-based encoder alignment is based on the induced voltage (back-EMF) and uses the same operating condition as the back-EMF-based method.
The machine under test for which the encoder offset should be determined is driven by a test bench machine to a constant speed (open circuit, thus :math:`I_d=I_q=0`).
In steady state, the voltage equations of the PMSM are given by [[#kellner_diss]_,p. 16]:

.. math::

  \begin{align}
  U_d &=R_1 I_d - \omega_{el} L_q I_q \\
  U_q &=R_1 I_q + \omega_{el} L_d I_d + \omega_{el} \psi_{PM}
  \end{align}

With :math:`I_d=0` and :math:`I_q=0` due to open circuit, the equations simplify to:

.. math::

  \begin{align}
  U_d &=0 \\
  U_q &=0 + \omega_{el} \psi_{PM}
  \end{align}

Based on these equations, encoder alignment is reached for an offset :math:`\vartheta_{el,offset}` in which :math:`U_d=0` and :math:`U_q=\omega_{el} \psi_{PM}` is measured.
However, this approach does not work due to iron losses in the machine and the alignment is skewed if this method is used.

.. _pmsm_esb_iron_losses:

.. figure:: pmsm_esb.svg
   :width: 800px
   :align: center

   Equivalent circuit of PMSM including iron losses of d-axis (left) and q-axis (right) [[#kellner_diss]_, p. 71, [#Schroeder_Regelung]_, p. 1102]. 

:numref:`pmsm_esb_iron_losses` shows the equivalent circuit of the PMSM including iron losses.
With the parallel iron resistance :math:`R_c`, the equations of the PMSM in steady state can be written as:

.. math::

  U_d &=R_1 I_d + R_c I_{dc} \\
  U_q &=R_1 I_q + R_c I_{qc} \\
  I_d &=I_{dc}+I_{d0} \\
  I_q &=I_{qc}+I_{q0} 

Simplifying the equations by using open circuit operation with :math:`I_d=I_q=0` and :math:`\omega_{el}\neq 0`:

.. math::

  U_d &=R_c I_{dc} =-\omega_{el} L_q I_{q0}\\
  U_q &=R_c I_{qc} = \omega_{el} \psi_{PM} + \omega_{el} L_d I_{d0}\\
  I_{dc} &= -I_{d0} \\
  I_{qc} &= -I_{q0} 

Following the equivalent circuit and the equations, the induced voltage :math:`\omega_{el}\psi_d` leads to the iron loss current :math:`I_{q0}` and the current :math:`I_{q0}` generates the flux linkage :math:`-\omega_{el} \psi_q` [[#richter_diss]_, p. 44].
If the dq-frame is aligned with the d-axis, the induced voltage in the d-axis :math:`U_d \neq 0` according to :numref:`pmsm_esb_iron_losses`.
Therefore, the encoder offset to match :math:`U_d=0` and :math:`U_q=\omega_{el} \psi_{PM}` does not lead to an alignment of the dq-frame to the d-axis in the aforementioned operating conditions.
Instead, the encoder offset :math:`\vartheta_{el}` has to be determined for positive and negative rotational speeds accounting for the effect of the iron losses as discussed.
The dq-frame is aligned with the d-axis if :math:`U_q` changes the sign for positive and negative rotational speed but not its magnitude and the value for :math:`U_d` does not change when changing the direction.

To simplify the method, a closed-loop current control with set points :math:`I_q^*=0` and :math:`I_d^*=0` can be used instead of open circuit.
The following steps have to be performed to align the encoder and determine :math:`\vartheta_{el,offset}`:

#. Machine coupled with test bench machine
#. Closed-loop current control with set points :math:`I_q^*=0` and :math:`I_d^*=0`
#. Measure :math:`U_d` and :math:`U_q` or measure controller outputs :math:`U_d^*` and :math:`U_q^*`
#. Set test bench machine to some :math:`\omega \neq 0` within the operating range and alternate between positive and negative rotation
#. Adjust encoder offset :math:`\vartheta_{el,offset}` until :math:`U_{d,\omega > 0}=U_{d,\omega < 0}` and :math:`U_{q,\omega > 0}= - U_{q,\omega < 0}`

This method yields good results for determining the encoder offset but requires a test-bench machine.

.. _measurement_flux_external_driven_full:

.. tikz:: Measurement results of Heidrive HDM06-005 based on the control value of the d- and q-axis PI-controller with constant speed :math:`n=1000 min^{-1}`
   :include: external_driven_full.tex
   :align: center
   :xscale: 50

:numref:`measurement_flux_external_driven_full` shows measurement results for the voltages (control value of the current controller) :math:`U_d^*`, :math:`U_q^*` and the calculated flux linkage :math:`\psi_d=\frac{U_q^*}{\omega_{el} }`, :math:`\psi_q=\frac{U_d^*}{-\omega_{el} }`.

.. _measurement_flux_external_driven_focus:

.. tikz:: Measurement results of Heidrive HDM06-005 based on the control value of the d- and q-axis PI-controller with constant speed :math:`n=1000 min^{-1}`
   :include: external_driven_full_focus.tex
   :align: center
   :xscale: 50

:numref:`measurement_flux_external_driven_focus` shows a section of the measurement to highlight the described point in which the dq-frame is aligned (dashed line). 


Flux-based (without test-bench machine)
=======================================

The concept of the flux-based alignment can be extended to not require a test-bench with a load machine.
The basic principle stays the same regarding the aim of the encoder offset, i.e., :math:`U_{d,\omega > 0}=U_{d,\omega < 0}` and :math:`U_{q,\omega > 0}= - U_{q,\omega < 0}`.
However, instead of using a load machine to keep the machine for which the encoder offset should be determined at a constant rotational speed the machine itself is controlled to a rotational speed, then the currents in d- and q-axis are controlled to zero :math:`I_q^*=0` and :math:`I_d^*=0` and the measurement is automatically done during run out of the machine.

.. _encoder_offset_runout:

.. tikz:: Principle of the measurement during run out of the machine
           :align: center
           :xscale: 50
         
             \begin{axis}[domain=0:100,samples=100,legend pos=outer north east, grid,
                 very thick,xlabel={Time}] 
                 \addplot[mark=none,color=black] coordinates{ (0,10) (10,10) (20,0) (25,0)};
                 \addplot[mark=none,color=blue] coordinates{ (0,5) (10,5) (20,0) (25,0)};
                 \addplot[mark=none,color=red] coordinates{ (0,2) (10,2) (11,0) (25,0)};
                 \addplot[mark=none,color=red,dashed] coordinates{ (0,0) (25,0)};
                 \addplot[mark=none,color=blue,dashed] coordinates{ (0,-1) (10,-1) (20,0) (25,0)};
                 \addplot[mark=none,color=black!50,dashed] coordinates{ (12,10) (12,-2)};
                 \addplot[mark=none,color=black!50,dashed] coordinates{ (16,10) (16,-2)};
                 \node[anchor=west,align=center] (source) at (160,100){Measurement\\window};
                 \legend{$\omega$,$U_q$,$I_q$,$I_d$,$U_d$};
             \end{axis}

:numref:`encoder_offset_runout` shows the basic principle of the measurement during run-out of the machine.
As described in the preceding section, the control value of the current controller are used for the calculation.

.. math::

    U_d &= -\omega_{el} \psi_q \\
    U_q &= \omega_{el} \psi_d \\

Rearranged:

.. math::

    \frac{U_d}{-\omega_{el}} &=  \psi_q  \\
    \frac{U_q}{\omega_{el}} &=  \psi_d 


.. _encoder_offset_measurement:

.. tikz:: Measurement results of Heidrive HDM06-005 based on the control value of the d- and q-axis PI-controller with run out starting at different rotational speeds
   :include: measurement_run_out.tex
   :align: center
   :xscale: 50

:numref:`encoder_offset_measurement` shows the measurement result for measuring in the run out of the machine with the run out starting at :math:`n=2300\,min^{-1}` and :math:`n=-2300\,min^{-1}`.


Sources
=======

.. [#Schroeder_Regelung] Elektrische Antriebe - Regelung von Antriebssystemen, Dierk Schröder, Springer, 2015, 4. Edition (German)
.. [#rahman_encoder_offset] K. M. Rahman and S. Hiti, "Identification of machine parameters of a synchronous motor," in IEEE Transactions on Industry Applications, vol. 41, no. 2, pp. 557-565, March-April 2005, doi: 10.1109/TIA.2005.844379.
.. [#asym_pmsm] Winzer, Patrick, 2017, Dissertation, "Steigerung von Drehmoment und Wirkungsgrad bei Synchronmaschinen durch Nutzung der magnetischen Asymmetrie", DOI: 10.5445/IR/1000071097, https://publikationen.bibliothek.kit.edu/1000071097
.. [#kellner_diss] Sven Kellner, Dissertation, "Parameteridentifikation bei permanenterregten Synchronmaschinen", Verlag Dr. Hut, ISBN 978-3-8439-0845-0, https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwja6rLEx_v6AhUEX_EDHSrRAb4QFnoECBAQAQ&url=https%3A%2F%2Fopus4.kobv.de%2Fopus4-fau%2Ffiles%2F2738%2FSvenKellnerDissertation.pdf&usg=AOvVaw3h5c9Z0-2m8zLh30i5mtz1
.. [#richter_diss] Jan Richter, Dissertation, "Modellbildung, Parameteridentifikation und Regelung hoch ausgenutzter Synchronmaschinen", https://www.ksp.kit.edu/site/books/m/10.5445/KSP/1000057097/

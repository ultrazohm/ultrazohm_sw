.. _uz_spacevectorlimiation:

=======================
Space vector limitation
=======================

.. doxygenfunction:: uz_CurrentControl_SpaceVector_Limitation

.. doxygenfunction:: uz_6ph_Space_Vector_Limitation

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call for 3ph-space vector limitation

  #include "uz/uz_CurrentControl/uz_space_vector_limitation.h"
  int main(void) {
     float V_dc_volts = 24.0f;
     float omega_el_rad_per_sec = 100.0f;
     uz_3ph_dq_t i_reference_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     uz_3ph_dq_t v_input_Volts = {.d = 5.0f, .q = 8.0f, .zero = 0.0f};
     bool ext_clamping = false;
     float max_modulation_index = 1.0f / sqrtf(3.0f);
     uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts, V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_reference_Ampere, &ext_clamping);
  }

.. code-block:: c
  :linenos:
  :caption: Example function call for 6ph-space vector limitation

  #include "uz/uz_CurrentControl/uz_space_vector_limitation.h"
  int main(void) {
     float V_dc_volts = 24.0f;
     float omega_el_rad_per_sec = 100.0f;
     uz_6ph_dq_t i_reference_Ampere = {.d = 1.0f, .q = 2.0f, .x = 3.0f, y = 4.0f};
     uz_6ph_dq_t v_input_Volts = {.d = 5.0f, .q = 8.0f, .x = 10.0f, .y = 3.0f};
     bool ext_clamping = false;
     float max_modulation_index = 1.0f / sqrtf(3.0f);
     uz_6ph_dq_t output = uz_6ph_Space_Vector_Limitation(v_input_Volts, V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_reference_Ampere, &ext_clamping);
  }


Description
===========

Limitation for dq-axis
----------------------

Limits the input voltages according to the following flowchart. 
Further information can be found in [#Quang]_ . 
This function is already included in the :ref:`uz_CurrentControl`.
With the max modulation index :math:`m_\mathrm{max}` the following voltages can be calculated.

.. math::

  V_\mathrm{max} &= V_\mathrm{DC} \cdot m_\mathrm{max} \\
  V_\mathrm{abs} &= \sqrt{v_d^2 + v_q^2}

.. _limit_flowchart:

.. tikz:: space vector limitation flow chart for dq-axis
  :align: center

  \usetikzlibrary{shapes,arrows, patterns,calc,shadows};
  \node[draw, drop shadow,rectangle, fill=black!20,align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large](Eval1){$U_{SV,abs} > U_{SV,max}$};
  \node[draw,  drop shadow,rectangle, fill=green!20,align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval1.east)+(7,0)$)(End5){$u_{d,lim} = u_d$ \\\\ $u_{q,lim} = u_q$};
  \node[draw,  drop shadow,rectangle, fill=yellow!20, align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval1.south)+(0,-3)$)(Eval2){$sign(\omega_{el}) == sign(i_{q,ref})$};
  \draw[-latex](Eval1.east) -- (End5.west);
  \node[font=\Large] at($(Eval1.east)+(2,0.3)$){No};
  \draw[-latex](Eval1.south) -- (Eval2.north);
  \node[font=\Large] at($(Eval1.south)+(0.5,-1)$){Yes};
  \node[draw,  drop shadow,rectangle, fill=yellow!20,align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval2.west)+(-7,-3)$)(Eval3left){$|u_d| > 0.95 \cdot U_{SV,max}$};
  \node[draw,  drop shadow,rectangle, fill=yellow!20,align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval2.east)+(7,-3)$)(Eval3right){$|u_q| > 0.95 \cdot U_{SV,max}$};
  \draw[-latex](Eval2.east) -| (Eval3right.north);
  \draw[-latex](Eval2.west) -| (Eval3left.north);
  \node[font=\Large] at($(Eval2.west)+(-2,0.3)$){Yes};
  \node[font=\Large] at($(Eval2.west)+(-2,-0.3)$){generator mode};
  \node[font=\Large] at($(Eval2.east)+(2,0.3)$){No};
  \node[font=\Large] at($(Eval2.east)+(2,-0.3)$){motor mode};
  \node[draw,  drop shadow,rectangle, fill=green!20, align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3left.west)+(-2.2,-3)$)(End1){$u_{d,lim} = 0.95 \cdot sign(u_d) \cdot U_{SV,max}$ \\\\ $u_{q,lim} = sign(u_q)\cdot \sqrt{U_{SV,max}^2 - u_{d,lim}^2}$};
  \node[draw,  drop shadow,rectangle,  fill=green!20,align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3left.east)+(2.2,-3)$)(End2){$u_{d,lim} = u_d$ \\\\ $u_{q,lim} = sign(u_q)\cdot \sqrt{U_{SV,max}^2 - u_{d,lim}^2}$};
  \node[draw,  drop shadow,rectangle,  fill=green!20,align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3right.west)+(-2.2,-3)$)(End3){$u_{q,lim} = 0.95 \cdot sign(u_q) \cdot U_{SV,max}$ \\\\ $u_{d,lim} = sign(u_d)\cdot \sqrt{U_{SV,max}^2 - u_{q,lim}^2}$};
  \node[draw,  drop shadow,rectangle,  fill=green!20,align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3right.east)+(2.2,-3)$)(End4){$u_{q,lim} = u_q$ \\\\ $u_{d,lim} = sign(u_d)\cdot \sqrt{U_{SV,max}^2 - u_{q,lim}^2}$};
  \draw[-latex](Eval3left.west) -| (End1.north);
  \draw[-latex](Eval3left.east) -| (End2.north);
  \draw[-latex](Eval3right.west) -| (End3.north);
  \draw[-latex](Eval3right.east) -| (End4.north);
  \node[font=\Large] at($(Eval3left.west)+(-1,0.3)$){Yes};
  \node[font=\Large] at($(Eval3right.west)+(-1,0.3)$){Yes};
  \node[font=\Large] at($(Eval3left.east)+(1,0.3)$){No};
  \node[font=\Large] at($(Eval3right.east)+(1,0.3)$){No};

Limitation for six phases
-------------------------

Limits the input voltages according to the following scheme. 

.. note::

    This only applies for a six-phase machine, where the :math:`\alpha\beta`-system is transformed 
    with :math:`\vartheta_{el}` into the :math:`dq` system and the :math:`XY`-system is transformed with :math:`-\vartheta_{el}` into the :math:`xy`-system.
    The basis for the :math:`\alpha\beta`- and :math:`XY`-systems is the :ref:`uz_transformation`.
    Furthermore, this approach is only valid, if the two neutral points of the 6ph-PMSM are disconnected from each other (2N-configuration).

With the max modulation index :math:`m_\mathrm{max}`, the maximum stator voltage according to 

.. math::

  V_\mathrm{max} = V_\mathrm{DC} \cdot m_\mathrm{max}\,,

can be realized. 
First, the :math:`xy`-subspace is limited to a maximum voltage of 

.. math::

  	V_\mathrm{lim}^{xy} = \frac{V_\mathrm{max}}{\sqrt{2}} = \frac{V_\mathrm{DC} \cdot m_{max}}{\sqrt{2}}\,.

The absolute value of the :math:`xy`-voltages is 

.. math::

  	V_\mathrm{abs}^{xy} = \sqrt{v_x^2 + v_y^2}\,.

.. tikz:: space vector limitation flow chart for xy-axis
  :align: center
  :xscale: 70

  \usetikzlibrary{shapes,arrows, patterns,calc,shadows};
  \node[draw, rectangle,  drop shadow, fill=black!20,align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large](Eval1){$V_{abs}^{xy} > V_{lim}^{xy}$};
  \node[draw, rectangle, drop shadow, fill=green!20, align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval1.east)+(5,0)$)(End5){$v_{x,out} = v_x$ \\\\ $v_{y,out} = v_y$};
  \node[draw, rectangle,  drop shadow,fill=yellow!20,align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval1.east)+(-2.5,-5)$)(Eval3right){$|v_y| > 0.95 \cdot V_{max}$};
  \node[draw, rectangle,  drop shadow,fill=green!20,align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3right.west)+(-2.2,-3)$)(End3){$v_{y,out} = 0.95 \cdot sign(v_y) \cdot V_{SV,max}$ \\\\ $v_{x,out} = sign(v_x)\cdot \sqrt{V_{max}^2 - v_{y,out}^2}$};
  \node[draw, rectangle,  drop shadow,fill=green!20,align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3right.east)+(2.2,-3)$)(End4){$v_{y,out} = v_y$ \\\\ $v_{x,out} = sign(v_x)\cdot \sqrt{V_{max}^2 - v_{y,out}^2}$};
  \draw[-latex](Eval1.south) -- (Eval3right.north);
  \path ([xshift=5mm]Eval1.south) -- ([xshift=5mm]Eval3right.north) node[midway,font=\Large] () {Yes};
  \draw[-latex](Eval1.east) -- (End5.west);
  \path ([yshift=5mm]Eval1.east) -- ([yshift=5mm]End5.west) node[midway,font=\Large] () {No};
  \draw[-latex](Eval3right.west) -| (End3.north);
  \draw[-latex](Eval3right.east) -| (End4.north);
  \node[font=\Large] at($(Eval3right.west)+(-1,0.3)$){Yes};
  \node[font=\Large] at($(Eval3right.east)+(1,0.3)$){No};

Afterwards, the :math:`dq`-voltages are limited with the resulting voltages :math:`v_{x,out}` and :math:`v_{y,out}` of the :math:`xy`-limitation according to

.. math::

  	V_\mathrm{lim}^{dq} = \sqrt{V_\mathrm{max}^2 - (V_\mathrm{out}^{xy})^2}\,,

with

.. math::

  	V_\mathrm{out}^{xy} = \sqrt{(v_\mathrm{out}^x)^2 + (v_\mathrm{out}^y)^2}\,,

being the limited voltages of the :math:`xy`-axis which will be output.


The voltages of the :math:`dq`-subspace are limited according to the flowchart in :numref:`limit_flowchart`, with :math:`V_\mathrm{max}` being replaced by :math:`V_\mathrm{lim}^{dq}`.


Sources
=======

.. [#Quang] Vector Control of Three-Phase AC Machines, Nguyen Phung Quang, Jörg-Andreas Dittrich, Springer, ISBN 978-3-662-46914-9

Designed by
===========

The Limitation for six phases was designed by Dennis Hufnagel.
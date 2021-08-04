.. _spacevectorlimiation:

=======================
Space vector limitation
=======================

.. doxygenfunction:: uz_FOC_SpaceVector_Limitation

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call for space vector limitation

  #include "uz_linear_decoupling.h"
  int main(void) {
     float U_zk_Volts = 24.0f;
     float omega_el_rad_per_sec = 100.0f;
     struct uz_dq_t i_dq_meas_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     struct uz_dq_t u_dq_ref_Volts = {.d = 5.0f, .q = 8.0f, .zero = 0.0f};
     bool ext_clamping = false;
     struct uz_dq_t output = uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts, U_zk_Volts, omega_el_rad_per_sec, i_dq_meas_Ampere, &ext_clamping);
  }

Description
===========

Limits the input voltages according to the following flowchart. 
Further information can be found in [#Quang]_ . 
This function is already included in the :ref:`uz_FOC`.

.. math::

  U_{SV,max} &= \dfrac{U_{zk}}{\sqrt{3}} \\
  U_{SV,abs} &= \sqrt{u_d^2 + u_q^2}

.. tikz:: space vector limitation flow chart
  :align: left

  \usetikzlibrary{shapes,arrows, patterns,calc};
  \node[draw, rectangle, align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large](Eval1){$U_{SV,abs} > U_{SV,max}$};
  \node[draw, rectangle, align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval1.east)+(7,0)$)(End5){$u_{d,lim} = u_d$ \\\\ $u_{q,lim} = u_q$};
  \node[draw, rectangle, align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval1.south)+(0,-3)$)(Eval2){$sign(\omega_{el}) == sign(i_q)$};
  \draw[-latex](Eval1.east) -- (End5.west);
  \node[font=\Large] at($(Eval1.east)+(2,0.3)$){No};
  \draw(End5.north) |- ($(Eval1.north)+(0.5,1)$);
  \draw[-latex]($(Eval1.north)+(0.5,1)$) -- ($(Eval1.north)+(0.5,0)$);
  \draw[-latex](Eval1.south) -- (Eval2.north);
  \node[font=\Large] at($(Eval1.south)+(0.5,-1)$){Yes};
  \node[draw, rectangle, align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval2.west)+(-7,-3)$)(Eval3left){$|u_d| > 0.95 \cdot U_{SV,max}$};
  \node[draw, rectangle, align = center, rounded corners=6pt, minimum width=5cm,minimum height = 2.5cm, font=\Large] at ($(Eval2.east)+(7,-3)$)(Eval3right){$|u_q| > 0.95 \cdot U_{SV,max}$};
  \draw[-latex](Eval2.east) -| (Eval3right.north);
  \draw[-latex](Eval2.west) -| (Eval3left.north);
  \node[font=\Large] at($(Eval2.west)+(-2,0.3)$){Yes};
  \node[font=\Large] at($(Eval2.west)+(-2,-0.3)$){generator mode};
  \node[font=\Large] at($(Eval2.east)+(2,0.3)$){No};
  \node[font=\Large] at($(Eval2.east)+(2,-0.3)$){motor mode};
  \node[draw, rectangle, align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3left.west)+(-2.2,-3)$)(End1){$u_{d,lim} = 0.95 \cdot sign(u_d) \cdot U_{SV,max}$ \\\\ $u_{q,lim} = sign(u_q)\cdot \sqrt{U_{SV,max}^2 - u_{d,lim}^2}$};
  \node[draw, rectangle, align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3left.east)+(2.2,-3)$)(End2){$u_{d,lim} = u_d$ \\\\ $u_{q,lim} = sign(u_q)\cdot \sqrt{U_{SV,max}^2 - u_{d,lim}^2}$};
  \node[draw, rectangle, align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3right.west)+(-2.2,-3)$)(End3){$u_{q,lim} = 0.95 \cdot sign(u_q) \cdot U_{SV,max}$ \\\\ $u_{d,lim} = sign(u_d)\cdot \sqrt{U_{SV,max}^2 - u_{q,lim}^2}$};
  \node[draw, rectangle, align = center,rounded corners=6pt, minimum width=5cm,minimum height = 2.6cm, font=\Large] at ($(Eval3right.east)+(2.2,-3)$)(End4){$u_{q,lim} = u_q$ \\\\ $u_{d,lim} = sign(u_d)\cdot \sqrt{U_{SV,max}^2 - u_{q,lim}^2}$};
  \draw[-latex](Eval3left.west) -| (End1.north);
  \draw[-latex](Eval3left.east) -| (End2.north);
  \draw[-latex](Eval3right.west) -| (End3.north);
  \draw[-latex](Eval3right.east) -| (End4.north);
  \node[font=\Large] at($(Eval3left.west)+(-1,0.3)$){Yes};
  \node[font=\Large] at($(Eval3right.west)+(-1,0.3)$){Yes};
  \node[font=\Large] at($(Eval3left.east)+(1,0.3)$){No};
  \node[font=\Large] at($(Eval3right.east)+(1,0.3)$){No};
  \draw(End4.south) |- ($(End1.south)+(-5,-1)$);
  \draw($(End1.south)+(-5,-1)$) |- ($(Eval1.north)+(-0.5,1)$);
  \draw[-latex]($(Eval1.north)+(-0.5,1)$) -- ($(Eval1.north)+(-0.5,0)$) ;
  \draw(End3.south) -- ($(End3.south)+(0,-1)$);
  \draw(End2.south) -- ($(End2.south)+(0,-1)$);
  \draw(End1.south) -- ($(End1.south)+(0,-1)$);
  \node [circle,fill,inner sep=1pt] at ($(End1.south)+(0,-1)$){};
  \node [circle,fill,inner sep=1pt] at ($(End2.south)+(0,-1)$){};
  \node [circle,fill,inner sep=1pt] at ($(End3.south)+(0,-1)$){};

Sources
=======

.. [#Quang] Vector Control of Three-Phase AC Machines, Nguyen Phung Quang, Jörg-Andreas Dittrich, Springer, ISBN 978-3-662-46914-9
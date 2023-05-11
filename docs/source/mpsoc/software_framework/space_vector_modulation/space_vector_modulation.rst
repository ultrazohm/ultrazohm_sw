.. _uz_spacevectormodulation:

=======================
Space vector Modulation
=======================

.. doxygenstruct:: uz_DutyCycle_t
  :members:

.. doxygenstruct:: uz_DutyCycle_2x3ph_t
  :members:

.. doxygenfunction:: uz_Space_Vector_Modulation

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call for space vector limitation

  #include "uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
  int main(void) {
     float V_DC_Volts = 24.0f;
     float theta_el_rad = 100.0f;
     uz_3ph_dq_t v_input_Volts = {.d = 5.0f, .q = 8.0f, .zero = 0.0f};
     struct uz_DutyCycle_t output = uz_Space_Vector_Modulation(v_input_Volts, V_DC_Volts, theta_el_rad);
  }

Description
===========

Generates a DutyCycle from dq-reference voltages via Space Vector Limitation for a carrier based PWM generation.
This is realized according to [[#Quang]_] . Further information can be found there. 

.. _space_vector_coordinates:

.. tikz:: Space vector coordinate system
  :align: center
  :libs: shapes, arrows, positioning, calc,fit, backgrounds, shadows,  patterns

  \begin{tikzpicture}
  \draw[-latex, line width=0.4mm](-10cm,0cm) --(10cm, 0cm); 
  \draw[-latex, line width=0.4mm](0cm,-10cm) --(0cm, 10cm); 
  \node (alpha) at (10.5cm,0cm) {\LARGE{$\alpha$}};
  \node (beta) at (0,10.5cm) {\LARGE{$\beta$}};
  \draw [fill=black] (11,0.25) rectangle (12,-0.25);
  \draw[-latex, line width=0.4mm](10.8cm,0cm) --(12.5cm, 0cm); 
  \node (PhaseA) at (11.5cm,-0.5cm) {\Large{Phase A}};
  \draw [fill=black,rotate=120] (9,0.25) rectangle (10,-0.25);
  \node (PhaseA) at (-6cm, 9.5cm) {\Large{Phase B}};
  \draw[-latex, line width=0.4mm, rotate=120](8.8cm,0cm) --(10.5cm, 0cm); 
  \draw [fill=black,rotate=240] (9,0.25) rectangle (10,-0.25);
  \node (PhaseA) at (-6cm, -9.5cm) {\Large{Phase C}};
  \draw[-latex, line width=0.4mm, rotate=240](8.8cm,0cm) --(10.5cm, 0cm); 
  \begin{scope}[color=green]
  \draw[-latex, line width=1mm](0cm,0cm) --(8cm, 0cm); 
  \draw[-latex, line width=1mm, rotate=60](0cm,0cm) --(8cm, 0cm); 
  \draw[-latex, line width=1mm, rotate=120](0cm,0cm) --(8cm, 0cm); 
  \draw[-latex, line width=1mm, rotate=180](0cm,0cm) --(8cm, 0cm); 
  \draw[-latex, line width=1mm, rotate=240](0cm,0cm) --(8cm, 0cm); 
  \draw[-latex, line width=1mm, rotate=300](0cm,0cm) --(8cm, 0cm); 
  \node (U1) at (8cm, 0.35cm) {\Large{$U_1$}};
  \node (U2) at (4cm, 7.25cm) {\Large{$U_2$}};
  \node (U3) at (-4cm, 7.25cm) {\Large{$U_3$}};
  \node (U4) at (-8cm, -0.35cm) {\Large{$U_4$}};
  \node (U5) at (-4cm, -7.25cm) {\Large{$U_5$}};
  \node (U6) at (4cm, -7.25cm) {\Large{$U_6$}};
  \node (U0) at (0.75cm, -0.35cm) {\Large{$U_0$}};
  \node (U7) at (-0.75cm, -0.35cm) {\Large{$U_7$}};
  \end{scope}
  \begin{scope}[color=blue]
  \draw[-latex, line width=0.4mm](4cm,0cm) to [out=90, in=0](0cm, 4cm); 
  \node (Q1) at (3.3cm, 3.3cm) {\Large{$Q_1$}};
  \draw[-latex, line width=0.4mm,rotate=90](4cm,0cm) to [out=90, in=0](0cm, 4cm); 
  \node (Q2) at (-3.3cm, 3.3cm) {\Large{$Q_2$}};
  \draw[-latex, line width=0.4mm,rotate=180](4cm,0cm) to [out=90, in=0](0cm, 4cm); 
  \node (Q3) at (-3.3cm, -3.3cm) {\Large{$Q_3$}};
  \draw[-latex, line width=0.4mm,rotate=270](4cm,0cm) to [out=90, in=0](0cm, 4cm); 
  \node (Q4) at (3.3cm, -3.3cm) {\Large{$Q_4$}};
  \end{scope}
  \begin{scope}[color=red]
  \draw[-latex,line width=0.4mm, rotate=0] (6,0) arc[x radius=6cm, y radius =6cm, start angle=0, end angle=60];
  \node (S1) at (5.75cm, 3.4cm) {\Large{$S_1$}};
  \draw[-latex,line width=0.4mm, rotate=60] (6,0) arc[x radius=6cm, y radius =6cm, start angle=0, end angle=60];
  \node (S2) at (-0.3cm, 6.3cm) {\Large{$S_2$}};
  \draw[-latex,line width=0.4mm, rotate=120] (6,0) arc[x radius=6cm, y radius =6cm, start angle=0, end angle=60];
  \node (S3) at (-5.75cm, 3.4cm) {\Large{$S_3$}};
  \draw[-latex,line width=0.4mm, rotate=180] (6,0) arc[x radius=6cm, y radius =6cm, start angle=0, end angle=60];
  \node (S4) at (-5.75cm, -3.4cm) {\Large{$S_4$}};
  \draw[-latex,line width=0.4mm, rotate=240] (6,0) arc[x radius=6cm, y radius =6cm, start angle=0, end angle=60];
  \node (S5) at (0.3cm, -6.3cm) {\Large{$S_5$}};
  \draw[-latex,line width=0.4mm, rotate=300] (6,0) arc[x radius=6cm, y radius =6cm, start angle=0, end angle=60];
  \node (S6) at (5.75cm, -3.4cm) {\Large{$S_6$}};
  \end{scope}
  \draw[-latex, line width=1mm, rotate=30](0cm,0cm) --(3cm, 0cm); 
  \node (US) at (2.75cm, 1.75cm) {\Large{$U_S$}};
  \draw[dashed](2.6,1.5)--(0.75,1.5);
  \draw[dashed](2.6,1.5)--(1.7,0);
  \draw[-latex, line width=0.4mm](0cm,0cm) -- (0.85cm, 1.5cm); 
  \draw[-latex, line width=0.4mm](0cm,0cm) -- (1.7cm, 0cm); 
  \node (UR) at (1.7cm, -0.3cm) {\large{$U_R$}};
  \node (UL) at (0.35cm, 1.5cm) {\large{$U_L$}};
  \end{tikzpicture}

Any arbitrary stator voltage vector can be produced from the eight standard vectors, which represent the eight possible logic states of a three phase voltage source inverter.

.. list-table:: The logic states of the standard voltage vectors
   :align: center
   :widths: auto
   :header-rows: 1

   * - 
     - :math:`U_0`
     - :math:`U_1`
     - :math:`U_2`
     - :math:`U_3`
     - :math:`U_4`
     - :math:`U_5`
     - :math:`U_6`
     - :math:`U_7`
   * - A
     - 0
     - 1
     - 1
     - 0
     - 0
     - 0
     - 1
     - 1
   * - B
     - 0
     - 0
     - 1
     - 1
     - 1
     - 0
     - 0
     - 1
   * - C
     - 0
     - 0
     - 0
     - 0
     - 1
     - 1
     - 1
     - 1  


:math:`U_S` is achieved by vectorial addition of the two boundary vectors :math:`U_L` and :math:`U_R` in the directions of the standard vectors.
This is achieved by modulating the on/off time of the two closest standard vectors and/or the two zero-voltage vectors (:math:`U_0, U_7`).
E.g. for the example provided in figure :numref:`space_vector_coordinates`, a modulation between :math:`U_1, U_2` and :math:`U_0`/ :math:`U_7` is required.
Depending on the location of :math:`U_S`, the boundary vectors can be directly calculated from the :math:`\alpha` and :math:`\beta` voltages. 

.. list-table:: Moduli of the boundary components
   :align: center
   :widths: auto
   :header-rows: 1

   * - 
     - 
     - :math:`|U_R|`
     - :math:`|U_L|`
   * - :math:`|S_1|`
     - :math:`|Q_1|`
     - :math:`|U_{\alpha}| - \frac{1}{\sqrt{3}}|U_{\beta}|`
     - :math:`\frac{2}{\sqrt{3}}|U_{\beta}|`
   * - :math:`|S_2|`
     - :math:`|Q_1|`
     - :math:`|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
     - :math:`-|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
   * - :math:`|S_2|`
     - :math:`|Q_2|`
     - :math:`-|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
     - :math:`|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
   * - :math:`|S_3|`
     - :math:`|Q_2|`
     - :math:`\frac{2}{\sqrt{3}}|U_{\beta}|`
     - :math:`|U_{\alpha}| - \frac{1}{\sqrt{3}}|U_{\beta}|`
   * - :math:`|S_4|`
     - :math:`|Q_3|`   
     - :math:`|U_{\alpha}| - \frac{1}{\sqrt{3}}|U_{\beta}|`
     - :math:`\frac{2}{\sqrt{3}}|U_{\beta}|`  
   * - :math:`|S_5|`
     - :math:`|Q_3|` 
     - :math:`|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
     - :math:`-|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
   * - :math:`|S_5|`
     - :math:`|Q_4|` 
     - :math:`-|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
     - :math:`|U_{\alpha}| + \frac{1}{\sqrt{3}}|U_{\beta}|`
   * - :math:`|S_6|`
     - :math:`|Q_4|` 
     - :math:`\frac{2}{\sqrt{3}}|U_{\beta}|`
     - :math:`|U_{\alpha}| - \frac{1}{\sqrt{3}}|U_{\beta}|`

Depending on the current sector and quadrant, the appropriate boundary vectors :math:`U_L` and :math:`U_R` will be calculated and converted into DutyCycles. 
The DutyCycles are limited with the :ref:`uz_signals_saturation` to 1, respectively 0.




Sources
=======

.. [#Quang] Vector Control of Three-Phase AC Machines, Nguyen Phung Quang, Jörg-Andreas Dittrich, Springer, ISBN 978-3-662-46914-9
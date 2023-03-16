.. _uz_piController_sample:

===============
Sample function
===============

.. doxygenfunction:: uz_PI_Controller_sample

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to calculate the PI-Controller output. PI-Instance via :ref:`init-function <uz_piController_init>`

  #include "uz_piController.h"
  int main(void) {
     float referenceValue = 1.5f;
     float actualValue = 1.1f;
     bool ext_clamping = false;
     float output = uz_PI_Controller_sample(PI_instance, referenceValue, actualValue, ext_clamping);
  }

Description
===========

Calculates one sample of the PI-Controller.
It has an output limitation and a corresponding :ref:`clamping circuit <uz_piController_clamping>`.
Furthermore, it has an input port for an external clamping signal.
The error between the reference and actual value will be calculated inside the function. 

.. warning::

  The sample function has to be called with the same sample time as specified in the ``samplingTime_sec`` member of the :ref:`configuration struct <uz_piController_config>`.

.. tikz:: parallel PI-Controller schematic
  :align: left

  \usetikzlibrary{shapes,arrows, patterns,calc};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-4.25)}](actual){actualValue};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-1.75)}](Ki){Ki};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-3)}](ref){referenceValue};
  \begin{scope}[shift={(-24.4,-3)}]
  \node[minimum size=0.7cm, draw, circle] (add) at (0,0) {};
  \node[] at (0,-0.25) {-};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[draw, rectangle, minimum height=1.3cm] (Multiply1) at (-22.5,-2.6) {~~~\,\large{x}\,\,~~~};
  \draw[-latex](ref.east)--(add.west);
  \draw[-latex](actual.east)-|(add.south);
  \draw(Ki.east)-|($(Multiply1.west)+(-1.3,0.3)$);
  \draw[-latex]($(Multiply1.west)+(-1.3,0.3)$) to ($(Multiply1.west)+(0,0.3)$);
  \draw[-latex,color=red](add.east) to ($(Multiply1.west)+(0,-0.4)$);  
  \begin{scope}[shift={(-14,-2.2)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch1) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex,color=blue] (Multiply1.east) to ($(Switch1.west)+(0,-0.4)$);
  \begin{scope}[shift={(-18,-4.5)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 3cm, fill=lightgray] (Clamping) at (0,0) {};
  \node[font=\footnotesize,rotate=90] at (0,0) {preIntegrator};
  \node[font=\footnotesize] at (0.9,0) {preSat};
  \node[font=\footnotesize] at (-0.9,0) {Clamp};
  \node[font=\footnotesize] at (0,-1.5) {Clamping circuit};
  \end{scope}
  \node[draw, rectangle, minimum height = 2.5cm] (OR) at (-18,0.5) {~~~\,OR\,\,~~~};
  \draw[-latex,color=blue] ($(Clamping.north)+(0,0.75)$)--(Clamping.north);
  \draw[-,color=purple](Clamping.west) -| ($(Clamping.west)+(-1,1.7)$);
  \draw[-, bend angle=45, bend left,color=purple]($(Clamping.west)+(-1,1.7)$)to node[below,align=center]{}($(Clamping.west)+(-1,2.1)$);
  \draw[-latex,color=purple]($(Clamping.west)+(-1,2.1)$) |- ($(OR.west)+(0,-0.7)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-22.5,1.2)}](ext){ext\_clamping};
  \draw[-latex] (ext.east)--($(OR.west)+(0,0.7)$);
  \draw[color=cyan](OR.east)-| ($(Switch1.west)+(-1.5,0)$);
  \draw[-latex,color=cyan]($(Switch1.west)+(-1.5,0)$) -- (Switch1.west);
  \node[draw, rectangle, minimum height=1.1cm] (Constant2) at (-10,0.5) {~~~\,0\,\,~~~};
  \draw(Constant2.south) |- ($(Switch1.west)+(-0.5,1.5)$);
  \draw[-latex]($(Switch1.west)+(-0.5,1.5)$) |- ($(Switch1.west)+(0,0.4)$);
  \begin{scope}[shift={(1,-1.8)}]
  \node[minimum size=0.7cm, draw, circle] (add1) at (0,0) {};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(6,-1.8)}](out){output};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-7.3)}](Kp){Kp};
  \node[draw, rectangle, minimum height=1.1cm] (Multiply2) at (-22.5,-7) {~~~\,\large{x}\,\,~~~};
  \draw[-latex](Kp.east)--($(Multiply2.west)+(0,-0.3)$);
  \draw[-latex,color=red]($(add.east)+(0.4,0)$)|-($(Multiply2.west)+(0,0.3)$);
  \node [circle,fill,inner sep=1pt,color=red] at ($(add.east)+(0.4,0)$){};
  \draw[-latex,color=gray](Multiply2.east)-|(add1.south);
  \node [circle,fill,inner sep=1pt,color=blue] at ($(Clamping.north)+(0,0.75)$){};
  \draw[-latex,color=green]($(add1.south)+(-0.25,-2.35)$) -- (Clamping.east);
  \draw[-, bend angle=45, bend left,color=green]($(add1.south)+(-0.25,-2.35)$)to node[below,align=center]{}($(add1.south)+(+0.25,-2.35)$);
  \draw[color=green]($(add1.south)+(0.25,-2.35)$) -| ($(add1.east)+(0.75,0)$);
  \node [circle,fill,inner sep=1pt,color=green] at ($(add1.east)+(0.75,0)$) {};
  \node[draw, rectangle, minimum height=1.1cm] (delay2) at (-2.5,-1.8) {~~~\,\large{$\frac{1}{z}$}\,\,~~~}; 
  \begin{scope}[shift={(-8.5,-2.2)}]
  \node[minimum size=0.7cm, draw, circle] (add3) at (0,0) {};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \draw[-latex,color=orange](delay2.east)--(add1.west);
  \draw[color=orange]($(delay2.east)+(0.5,0)$)|-($(add3.south)+(0,-1)$);
  \draw[color=orange,-latex]($(add3.south)+(0,-1)$)--(add3.south);
  \node [circle,fill,inner sep=1pt,color=orange] at ($(delay2.east)+(0.5,0)$) {};
  \begin{scope}[shift={(-4.8,-1.8)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch3) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex,color=darkgray](add3.east)--($(Switch3.west)+(0,-0.4)$);
  \draw[-latex,color=darkgray](Switch3.east)--(delay2.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, color=magenta, shift={(-8.25,-1.25)}](Reset){Reset};
  \node[color=magenta,align=center,shift={(-10.25,-1.25)}](Reset.north){done via \\Reset function};
  \draw[-latex,color=magenta]($(Reset.east)+(0.0,0)$)--($(Reset.east)+(0.25,0)$)|-($(Switch3.west)+(-1.5,0.0)$)--(Switch3.west);
  \draw(Constant2.south)|-($(Switch3.west)+(-1,1.1)$);
  \draw[-latex]($(Switch3.west)+(-1,1.1)$)|-($(Switch3.west)+(0,0.4)$);
  \node [circle,fill,inner sep=1pt] at ($(Constant2.south)+(0,-0.64)$){};
  \begin{scope}[shift={(3.5,-1.8)}]
  \node [draw, rectangle, minimum height=1.1cm] (Limit) at (0,0) {~~~~~~\,~~~};
  \draw[color=lightgray](-0.35,0) -- (0.35,0);
  \draw[color=lightgray](0,-0.27) -- (0,0.27);
  \draw(Limit.south)[draw, color=black, thick]{(-0.35,-0.25) -- ++(0.2,0) -- ++(0.3,0.5)-- ++(0.2,0)};
  \node[below, font=\footnotesize] at (0,-0.5) {Limitation};
  \end{scope}
  \draw[-latex,color=green](add1.east)--(Limit.west);
  \draw[-latex](Limit.east)--(out.west);
  \node[color=green] at ($(Clamping.east)+(9,0.2)$){output\_before\_saturation};
  \node[color=blue] at ($(Clamping.north)+(0,1)$){preIntegrator};
  \node[color=purple] at ($(OR.west)+(-1.6,-0.45)$){internal\_clamping};
  \node[rotate=90,font=\footnotesize,color=cyan] at ($(OR.east)+(0.4,-1.4)$){clamping\_active};
  \node[color=orange] at ($(delay2.east)+(1,0.2)$){old\_I\_sum};
  \node[color=darkgray] at ($(add3.east)+(1,-0.2)$){I\_sum};
  \node[color=gray] at ($(Multiply2.east)+(5,+0.25)$){P\_sum};
  \node[color=red,rotate=-90] at ($(add.east)+(0.6,-2)$){error};
  \node[isosceles triangle, isosceles triangle apex angle=30,draw,minimum size =0.5cm,font=\tiny] (gain) at (-11.5,-2.2) {samplingTime};
  \draw[-latex](Switch1.east)--(gain.west);
  \draw[-latex](gain.east)--(add3.west);

.. tikz:: ideal PI-Controller schematic
  :align: left

  \usetikzlibrary{shapes,arrows, patterns,calc};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-5.1)}](actual){actualValue};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-2.3)}](Ki){Ki};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-6.7)}](ref){referenceValue};
  \begin{scope}[shift={(-24.4,-6.7)}]
  \node[minimum size=0.7cm, draw, circle] (add) at (0,0) {};
  \node[] at (0,0.2) {-};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[draw, rectangle, minimum height=1.3cm] (Multiply1) at (-22.5,-2.6) {~~~\,\large{x}\,\,~~~};
  \draw[-latex](ref.east)--(add.west);
  \draw[-latex](actual.east)-|(add.north);
  \draw(Ki.east)-|($(Multiply1.west)+(-1.3,0.3)$);
  \draw[-latex]($(Multiply1.west)+(-1.3,0.3)$) to ($(Multiply1.west)+(0,0.3)$);
  \begin{scope}[shift={(-14,-2.2)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch1) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex,color=blue] (Multiply1.east) to ($(Switch1.west)+(0,-0.4)$);
  \begin{scope}[shift={(-18,-4.5)}]
  \node[draw, rectangle, minimum height=2.3cm, minimum width = 3cm, fill=lightgray] (Clamping) at (0,0) {};
  \node[font=\footnotesize,rotate=90] at (0,0) {preIntegrator};
  \node[font=\footnotesize] at (0.9,0) {preSat};
  \node[font=\footnotesize] at (-0.9,0) {Clamp};
  \node[font=\footnotesize] at (0,-1.5) {Clamping circuit};
  \end{scope}
  \node[draw, rectangle, minimum height = 2.5cm] (OR) at (-18,0.5) {~~~\,OR\,\,~~~};
  \draw[-latex,color=blue] ($(Clamping.north)+(0,0.75)$)--(Clamping.north);
  \draw[-,color=purple](Clamping.west) -| ($(Clamping.west)+(-1,1.7)$);
  \draw[-, bend angle=45, bend left,color=purple]($(Clamping.west)+(-1,1.7)$)to node[below,align=center]{}($(Clamping.west)+(-1,2.1)$);
  \draw[-latex,color=purple]($(Clamping.west)+(-1,2.1)$) |- ($(OR.west)+(0,-0.7)$);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-22.5,1.2)}](ext){ext\_clamping};
  \draw[-latex] (ext.east)--($(OR.west)+(0,0.7)$);
  \draw[color=cyan](OR.east)-| ($(Switch1.west)+(-1.5,0)$);
  \draw[-latex,color=cyan]($(Switch1.west)+(-1.5,0)$) -- (Switch1.west);
  \node[draw, rectangle, minimum height=1.1cm] (Constant2) at (-10,0.5) {~~~\,0\,\,~~~};
  \draw(Constant2.south) |- ($(Switch1.west)+(-0.5,1.5)$);
  \draw[-latex]($(Switch1.west)+(-0.5,1.5)$) |- ($(Switch1.west)+(0,0.4)$);
  \begin{scope}[shift={(1,-1.8)}]
  \node[minimum size=0.7cm, draw, circle] (add1) at (0,0) {};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(6,-1.8)}](out){output};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-27,-7.3)}](Kp){Kp};
  \node[draw, rectangle, minimum height=1.1cm] (Multiply2) at (-22.5,-7) {~~~\,\large{x}\,\,~~~};
  \draw[-latex](Kp.east)--($(Multiply2.west)+(0,-0.3)$);
  \draw[-latex,color=red](add.east)|-($(Multiply2.west)+(0,0.3)$);
  \draw[-latex,color=gray](Multiply2.east)-|(add1.south);
  \node [circle,fill,inner sep=1pt,color=blue] at ($(Clamping.north)+(0,0.75)$){};
  \draw[-latex,color=green]($(add1.south)+(-0.25,-2.35)$) -- (Clamping.east);
  \draw[-, bend angle=45, bend left,color=green]($(add1.south)+(-0.25,-2.35)$)to node[below,align=center]{}($(add1.south)+(+0.25,-2.35)$);
  \draw[color=green]($(add1.south)+(0.25,-2.35)$) -| ($(add1.east)+(0.75,0)$);
  \node [circle,fill,inner sep=1pt,color=green] at ($(add1.east)+(0.75,0)$) {};
  \node[draw, rectangle, minimum height=1.1cm] (delay2) at (-2.5,-1.8) {~~~\,\large{$\frac{1}{z}$}\,\,~~~}; 
  \begin{scope}[shift={(-8.5,-2.2)}]
  \node[minimum size=0.7cm, draw, circle] (add3) at (0,0) {};
  \node[] at (0,-0.2) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \draw[-latex,color=orange](delay2.east)--(add1.west);
  \draw[color=orange]($(delay2.east)+(0.5,0)$)|-($(add3.south)+(0,-1)$);
  \draw[color=orange,-latex]($(add3.south)+(0,-1)$)--(add3.south);
  \node [circle,fill,inner sep=1pt,color=orange] at ($(delay2.east)+(0.5,0)$) {};
  \begin{scope}[shift={(-5,-1.8)}]
  \node[draw, rectangle, minimum height=1.3cm, minimum width = 2cm] (Switch3) at (0,0) {\footnotesize{$>0$}};
  \draw(-1,0.4) to (0,0.4); 
  \draw(-1,-0.4) to (0,-0.4); 
  \draw(-1,0) to (-0.5,0);
  \draw(-0.5,0.1) to (-0.5,-0.1);
  \draw (0.05,0.45) rectangle (-0.05,0.35){};
  \draw (0.05,-0.45) rectangle (-0.05,-0.35){};
  \draw(0,0.4) to (0.7,0);
  \draw(0.7,0) to (1,0);
  \end{scope}
  \draw[-latex,color=darkgray](add3.east)--($(Switch3.west)+(0,-0.4)$);
  \draw[-latex,color=darkgray](Switch3.east)--(delay2.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, color=magenta, shift={(-8.25,-1.25)}](Reset){Reset};
  \node[color=magenta,align=center,shift={(-10.25,-1.25)}](Reset.north){done via \\Reset function};
  \draw[-latex,color=magenta](Reset.east)--($(Reset.east)+(0.25,0)$)|-(Switch3.west);
  \draw(Constant2.south)|-($(Switch3.west)+(-1,1.1)$);
  \draw[-latex]($(Switch3.west)+(-1,1.1)$)|-($(Switch3.west)+(0,0.4)$);
  \node [circle,fill,inner sep=1pt] at ($(Constant2.south)+(0,-0.64)$){};
  \begin{scope}[shift={(3.5,-1.8)}]
  \node [draw, rectangle, minimum height=1.1cm] (Limit) at (0,0) {~~~~~~\,~~~};
  \draw[color=lightgray](-0.35,0) -- (0.35,0);
  \draw[color=lightgray](0,-0.27) -- (0,0.27);
  \draw(Limit.south)[draw, color=black, thick]{(-0.35,-0.25) -- ++(0.2,0) -- ++(0.3,0.5)-- ++(0.2,0)};
  \node[below, font=\footnotesize] at (0,-0.5) {Limitation};
  \end{scope}
  \draw[-latex,color=green](add1.east)--(Limit.west);
  \draw[-latex](Limit.east)--(out.west);
  \node[color=green] at ($(Clamping.east)+(9,0.2)$){output\_before\_saturation};
  \node[color=blue] at ($(Clamping.north)+(0,1)$){preIntegrator};
  \node[color=purple] at ($(OR.west)+(-1.6,-0.45)$){internal\_clamping};
  \node[rotate=90,font=\footnotesize,color=cyan] at ($(OR.east)+(0.4,-1.4)$){clamping\_active};
  \node[color=orange] at ($(delay2.east)+(1,0.2)$){old\_I\_sum};
  \node[color=darkgray] at ($(add3.east)+(1,-0.2)$){I\_sum};
  \node[color=gray] at ($(Multiply2.east)+(5,+0.2)$){P\_sum};
  \node[color=red] at ($(add.east)+(0.45,0.25)$){error};
  \node[isosceles triangle, isosceles triangle apex angle=30,draw,minimum size =0.5cm,font=\tiny] (gain) at (-11.5,-2.2) {samplingTime};
  \draw[-latex](Switch1.east)--(gain.west);
  \draw[-latex](gain.east)--(add3.west);
  \draw[-latex, color=gray]($(Multiply2.east)+(0.3,0)$) |- ($(Multiply1.west)+(-0.3,-2)$) |- ($(Multiply1.west)+(-0.3,-0.3)$) -- ($(Multiply1.west)+(-0,-0.3)$);
  \node[color=gray,rotate=90] at ($(Multiply2.west)+(-0.5,3)$){P\_sum};
  \node [circle,fill,inner sep=1pt,color=gray] at ($(Multiply2.east)+(0.3,0)$) {};
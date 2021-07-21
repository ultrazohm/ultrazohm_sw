.. _uz_piController_clamping:


=================
Clamping function
=================

.. doxygenfunction:: uz_PI_Controller_Clamping_Circuit

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call for clamping circuit

  #include "uz_piController.h"
  int main(void) {
     float preIntegrator = 10.5f;
     float preSat = 1.1f;
     float upper_limit = 10.0f;
     float lower_limit = -8.0f;
     bool clamp = uz_PI_Controller_Clamping_Circuit(preIntegrator, preSat, upper_threshold, lower_threshold);
  }

Description
===========

Compares the values before the integrator ``preIntegrator`` and before the output limitation ``preSat``. Activates clamping if ``preSat``  is outside the limit and ``preIntegrator`` and ``preSat`` have the same sign.
The function is called by :ref:`sample-function <uz_piController_sample>`. 

.. warning::

  The values for ``upper_limit`` and ``lower_limit`` must be the same as configured in the :ref:`PI-Controller configuration struct <uz_piController_config>`.

.. tikz:: Clamping circuit
  :align: left

  \draw[rounded corners=6pt] (-0.6, -0.25) rectangle (0.6, 0.25){};
  \node[font=\footnotesize] at (0,0){preSat};
  \draw[rounded corners=6pt] (-1.1, -1.75) rectangle (1.1, -2.25){};
  \node[font=\footnotesize] at (0.0,-2){preIntegrator};
  \draw[rounded corners=6pt] (-16.7, -0.15) rectangle (-15.5, 0.35){};
  \node[font=\footnotesize] at (-16.1,0.1){Clamp};
  \node (1) [draw, rectangle, minimum height=1.1cm]at (-4,2.25)(Constant) {~~~\,0\,\,~~~};
  \node[font=\footnotesize, yshift=-5pt] at (Constant.south){Zero};
  \node (1) [draw, rectangle, minimum height = 2.5cm]at (-14,0.1)(AND) {~~~\,AND\,\,~~~};
  \node (1) [draw, rectangle, minimum height=1.1cm]at (-8,2)(NotEqual) {~~~$\neq$\,~~~};
  \node (1) [draw, rectangle, minimum height=1.1cm]at (-11,-0.3)(Equal) {~\,$==$\,~~};
  \begin{scope}[yshift=0cm, xshift=-8cm]
  \node (1) [draw, rectangle, minimum height=1.1cm]at (0,0)(Sign) {~~~~~~\,~~~};
  \draw[color=lightgray](-0.35,0) -- (0.35,0);
  \draw[color=lightgray](0,-0.27) -- (0,0.27);
  \draw(Sign.south)[draw, color=black, thick]{(-0.35,-0.15) -- ++(0.35,0.0) -- ++(0,0.3)-- ++(0.35,0)};
  \node[below, font=\footnotesize] at (0,-0.5){SignDeadZone};
  \end{scope}
  \begin{scope}[yshift=0cm,xshift=-4cm]
  \node (1) [draw, rectangle, minimum height=1.1cm]at (0,0)(DeadZone) {~~~~~~\,~~~};
  \draw[color=lightgray](-0.35,0) -- (0.35,0);
  \draw[color=lightgray](0,-0.27) -- (0,0.27);
  \draw(DeadZone.south)[draw, color=black, thick]{(-0.35,-0.25) -- ++(0.2,0.25) -- ++(0.3,0)-- ++(0.2,0.25)};
  \node[below, font=\footnotesize] at (0,-0.5){DeadZone};
  \end{scope}
  \begin{scope}[yshift=-2cm, xshift=-8cm]
  \node (1) [draw, rectangle, minimum height=1.1cm]at (0,0)(Sign2) {~~~~~~\,~~~};
  \draw[color=lightgray](-0.35,0) -- (0.35,0);
  \draw[color=lightgray](0,-0.27) -- (0,0.27);
  \draw(Sign2.south)[draw, color=black, thick]{(-0.35,-0.15) -- ++(0.35,0.0) -- ++(0,0.3)-- ++(0.35,0)};
  \node[below, font=\footnotesize] at (0,-0.5){SignPreIntegrator};
  \end{scope}
  \node at (-6,0)[circle,fill,inner sep=1pt]{};
  \draw[-latex](-0.59,0)--(-3.28,0);
  \draw[-latex](-1.1,-2)--(-7.28,-2);
  \draw[-latex](-4.7,2.25)--(-7.32,2.25);
  \draw[-latex](-6,0)|-(-7.32,1.75);
  \draw[-latex](-4.71,0)--(-7.28,0);
  \draw[-latex](-8.72,0)--(-10.32,0);
  \draw(-8.70,2)--(-9.5,2);
  \draw[-latex](-9.5,2)|-(-12.95,0.5);
  \draw(-8.72,-2)--(-9.5,-2);
  \draw[-latex](-9.5,-2)|-(-10.32,-0.5);
  \draw[-latex](-11.7,-0.25)--(-12.95,-0.25);
  \draw[-latex](-15.02,0.1)--(-15.5,0.1);
   



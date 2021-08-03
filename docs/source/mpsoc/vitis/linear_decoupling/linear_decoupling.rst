.. _lineardecoupling:

=================
Linear decoupling
=================


.. doxygenstruct:: uz_lin_decoupling_config
    :members:

.. doxygenfunction:: uz_FOC_linear_decoupling

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call for clamping circuit

  #include "uz_linear_decoupling.h"
  int main(void) {
     uz_lin_decoupling_config config_lin_Decoup = {.Ld_Henry = 0.0001f, .Lq_Henry = 0.0002f, .Psi_PM_Vs = 0.008f};
     float omega_el_rad_per_sec = 100.0f;
     struct uz_dq_t i_dq_meas_Ampere = {.d = 1.0f, .q = 2.0f, .zero = 0.0f};
     struct uz_dq_t output = uz_FOC_linear_decoupling(config_lin_Decoup, i_dq_meas_Ampere, omega_el_rad_per_sec);
  }

Description
===========

Calculates the values for a linear decoupling according to the following formulars:

.. math::

    u_{d,decoup} &= -\omega_{el} \cdot L_q \cdot i_q \\
    u_{q,decoup} &= \omega_{el} \cdot (L_d \cdot i_d + \psi_{PM})

This function is already included in the ``uz_FOC``, but it can be used independently for any other purpose.

.. tikz:: Clamping circuit
  :align: left

  \usetikzlibrary{shapes,arrows, patterns,calc};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm, shift={(-3,0)}](current){uz\_dq\_t};
  \node[draw, rectangle, minimum height=1.8cm] (Multiply1) at ($(current.east)+(10,-0.5)$) {~~~\,\large{x}\,\,~~~};
  \node[draw, rectangle, minimum height=1.8cm] (Multiply2) at ($(Multiply1.south)+(0,-2)$) {~~~\,\large{x}\,\,~~~};
  \begin{scope}[shift={(5,-2.9)}]
  \node[minimum size=0.7cm, draw, circle] (add) at (0,0) {};
  \node at (0,-0.25) {+};
  \node at (-0.2,0) {+};
  \end{scope}
  \node[isosceles triangle, isosceles triangle apex angle=20,draw,minimum size =0.5cm,font=\scriptsize] (Lq) at ($(Multiply1.west)+(-6,-0.5)$) {config.Lq\_Henry};
  \node[isosceles triangle, isosceles triangle apex angle=20,draw,minimum size =0.5cm,font=\scriptsize] (Ld) at ($(Multiply2.west)+(-6,0.5)$) {config.Ld\_Henry};
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm](omega) at ($(current.south)+(0,-5.5)$){$\omega_{el}$};
  \node[draw, rectangle, minimum width=1cm,minimum height = 0.5cm,font=\scriptsize] at ($(Ld.south)+(0.5,-1.25)$)(psi){config.Psi\_PM\_Vs};
  \draw[-latex](current.east) -- ($(Multiply1.west)+(0,0.5)$);
  \node at ($(current.east)+(0.25,0.25)$){$i_q$};
  \draw[-latex](Lq.east) -- ($(Multiply1.west)+(0,-0.5)$);
  \draw[-latex](add.east) -- ($(Multiply2.west)+(0,0.5)$);
  \draw[-latex](Ld.east) -- (add.west);
  \draw[-latex](current.south) |- (Ld.west);
  \node at ($(current.south)+(0.25,-0.25)$){$i_d$};
  \draw[-latex](psi.east) -| (add.south);
  \draw(omega.east) -- ($(omega.east)+(8.5,0)$);
  \draw[-latex]($(omega.east)+(8.5,0)$) |- ($(Multiply2.west)+(0,-0.5)$);
  \node [circle,fill,inner sep=1pt] at ($(omega.east)+(1,0)$){};
  \draw($(omega.east)+(1,0)$)--($(omega.east)+(1,2.7)$);
  \draw[-, bend angle=45, bend left]($(omega.east)+(1,2.7)$)to node[below,align=center]{}($(omega.east)+(1,3.1)$);
  \draw[-latex]($(omega.east)+(1,3.1)$) |- (Lq.west);
  \node[draw, rectangle, rounded corners=6pt, minimum width=1cm,minimum height = 0.5cm]at($(Multiply1.south)+(3,-0.5)$)(output){uz\_dq\_t};
  \draw[-latex](Multiply1.east) -| (output.north);
  \draw[-latex](Multiply2.east) -| (output.south);
  \node at ($(Multiply1.east)+(0.8,0.25)$){$u_{d,decoup}$};
  \node at ($(Multiply2.east)+(0.8,-0.25)$){$u_{q,decoup}$};
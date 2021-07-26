.. _dq_transformation:

=================
dq-Transformation
=================

The following amplitude invariant coordinate transformations are incorporated in this module. 
All of them are general purpose. 
This means, that they can be used to either transform voltages, currents or any other applicable unit. 

* dq-Transformation
* inverse dq-Transformation
* clarke-Transformation
* inverse clarke-Transformation

Variables structs
=================

These structs are needed to hand over the input values and get the output values of the functions.
    
.. doxygenstruct:: uz_UVW_t
  :members:

.. doxygenstruct:: uz_dq_t
  :members:

.. doxygenstruct:: uz_alphabeta_t
  :members:

dq-Transformation
=================

.. doxygenfunction:: uz_dq_transformation

This uses the Park transformation to transform a three-phase (uvw) signal to a dq0 rotating reference frame. 
``X`` is a placeholder and can be replaced by either ``U``, ``I`` or any other applicable unit. 
The d-Axis has to be aligned with the U-phase.

.. math::

  \begin{bmatrix}
    X_d \\
    X_q \\
    X_0 \\
  \end{bmatrix} = \frac{2}{3}
  \begin{bmatrix}
    cos{(\theta_{el})} & cos{(\theta_{el}-\frac{2\pi}{3})} & cos{(\theta_{el}-\frac{4\pi}{3})} \\
    -sin{(\theta_{el})} & -sin{(\theta_{el}-\frac{2\pi}{3})} & -sin{(\theta_{el}-\frac{4\pi}{3})} \\
    \frac{1}{2} & \frac{1}{2} & \frac{1}{2}\\
  \end{bmatrix}
  \begin{bmatrix}
  X_U \\
  X_V \\
  X_W \\
  \end{bmatrix}

inverse dq-Transformation
=========================

.. doxygenfunction:: uz_dq_inverse_transformation

This uses the inverse Park transformation to transform a dq0 rotating reference frame to a three-phase (uvw) signal. 
``X`` is a placeholder and can be replaced by either ``U``, ``I`` or any other applicable unit. 
The d-Axis has to be aligned with the U-phase.
  
.. math::
  
  \begin{bmatrix}
    X_U \\
    X_V \\
    X_W \\
  \end{bmatrix} = \frac{2}{3}
  \begin{bmatrix}
    cos{(\theta_{el})} & -sin{(\theta_{el})} & 1 \\
    cos{(\theta_{el}-\frac{2\pi}{3})} & -sin{(\theta_{el}-\frac{2\pi}{3})} & 1\\
    cos{(\theta_{el}-\frac{4\pi}{3})} & -sin{(\theta_{el}-\frac{4\pi}{3})} & 1\\
  \end{bmatrix}
  \begin{bmatrix}
    X_d \\
    X_q \\
    X_0 \\
  \end{bmatrix}

clarke-Transformation
=====================

.. doxygenfunction:: uz_clarke_transformation

The clarke transformation converts the time-domain components of a three-phase system in an uvw reference frame to components in a stationary αβγ reference frame. 
``X`` is a placeholder and can be replaced by either ``U``, ``I`` or any other applicable unit.
  
.. math::
  
  \begin{bmatrix}
    X_{\alpha} \\
    X_{\beta} \\
    X_{\gamma} \\
  \end{bmatrix} = \frac{2}{3}
  \begin{bmatrix}
    1 & -\frac{1}{2} & -\frac{1}{2} \\
    0 & \frac{\sqrt{3}}{2} & -\frac{\sqrt{3}}{2} \\
    \frac{1}{2} & \frac{1}{2} & \frac{1}{2} \\
  \end{bmatrix}
  \begin{bmatrix}
    X_U \\
    X_V \\
    X_W \\
  \end{bmatrix}
  
inverse clarke-Transformation
=============================

.. doxygenfunction:: uz_clarke_inverse_transformation
  
The inverse clarke transformation converts the components in a stationary αβγ reference frame to the time-domain components of a three-phase system in an uvw reference frame. 
``X`` is a placeholder and can be replaced by either ``U``, ``I`` or any other applicable unit.
    
.. math::
    
  \begin{bmatrix}
    X_U \\
    X_V \\
    X_W \\
  \end{bmatrix} =
  \begin{bmatrix}
    1 & 0 & 1 \\
    -\frac{1}{2} & \frac{\sqrt{3}}{2} & 1 \\
    -\frac{1}{2} & -\frac{\sqrt{3}}{2} & 1 \\
  \end{bmatrix}
  \begin{bmatrix}
  X_{\alpha} \\
  X_{\beta} \\
  X_{\gamma} \\
  \end{bmatrix}
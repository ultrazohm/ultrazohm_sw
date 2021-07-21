.. _Transformation:

================================
Signal Transformations
================================

The following signal transformations are incorporated in this module. All of them are general purpose. This means, that they can
be used to either transform voltages, currents or any other applicable unit. 

* dq-Transformation
* inverse dq-Transformation
* clarke-Transformation
* inverse clarke-Transformation


dq-Transformation
=================

``X`` is a placeholder and can be replaced by either ``U``, ``I`` or any other applicable unit. 

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


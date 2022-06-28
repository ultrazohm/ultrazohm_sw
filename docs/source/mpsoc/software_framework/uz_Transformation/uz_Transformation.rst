.. _uz_transformation:

==========================
Coordinate Transformation
==========================

The following amplitude invariant coordinate transformations are incorporated in this module. 
All of them are general purpose. 
This means, that they can be used to either transform voltages, currents, or any other applicable unit. 
Transformations for multiphase systems do exist as well.

* :ref:`dq_transformation`  
* :ref:`inverse_dq_transformation`
* :ref:`clarke_transformation`
* :ref:`inverse_clarke_transformation`
* :ref:`alphabeta_dq_transformation`
* :ref:`dq_alphabeta_transformation`
* :ref:`6ph_abc_to_alphabeta`
* :ref:`6ph_alphabeta_to_abc`
* :ref:`9ph_abc_to_alphabeta`
* :ref:`9ph_alphabeta_to_abc`

Three phase systems
===================

Variables structs
*****************

These structs are needed to hand over the input values and get the output values of the functions.
    
.. doxygenstruct:: uz_3ph_abc_t
  :members:

.. doxygenstruct:: uz_3ph_dq_t
  :members:

.. doxygenstruct:: uz_3ph_alphabeta_t
  :members:

Transformation functions
************************

.. _dq_transformation:

abc to dq0 transformation
-------------------------

.. doxygenfunction:: uz_transformation_3ph_abc_to_dq

This uses the Park transformation to transform a three-phase (abc) signal to a dq0 rotating reference frame. 
``X`` is a placeholder and can be replaced by either ``V``, ``I``, or any other applicable unit. 
The d-Axis has to be aligned with the A-phase.

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
  X_a \\
  X_b \\
  X_c \\
  \end{bmatrix}

.. _inverse_dq_transformation:

dq0 to abc transformation
-------------------------

.. doxygenfunction:: uz_transformation_3ph_dq_to_abc

This uses the inverse Park transformation to transform a dq0 rotating reference frame to a three-phase (abc) signal. 
``X`` is a placeholder and can be replaced by either ``V``, ``I``, or any other applicable unit. 
The d-Axis has to be aligned with the A-phase.
  
.. math::
  
  \begin{bmatrix}
    X_a \\
    X_b \\
    X_c \\
  \end{bmatrix} = 
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

.. _clarke_transformation:

abc to αβγ transformation
-------------------------

.. doxygenfunction:: uz_transformation_3ph_abc_to_alphabeta

The Clarke transformation converts the time-domain components of a three-phase system in an abc reference frame to components in a stationary 
:math:`\alpha\beta\gamma` reference frame. 
``X`` is a placeholder and can be replaced by either ``V``, ``I``, or any other applicable unit.
  
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
    X_a \\
    X_b \\
    X_c \\
  \end{bmatrix}

.. _inverse_clarke_transformation:

αβγ to abc transformation
-------------------------

.. doxygenfunction:: uz_transformation_3ph_alphabeta_to_abc
 
The inverse Clarke transformation converts the components in a stationary :math:`\alpha\beta\gamma` reference frame to the time-domain components of a three-phase system in an abc reference frame. 
``X`` is a placeholder and can be replaced by either ``V``, ``I``, or any other applicable unit.
    
.. math::
    
  \begin{bmatrix}
    X_a \\
    X_b \\
    X_c \\
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

.. _alphabeta_dq_transformation:

αβγ to dq0 transformation 
-------------------------

.. doxygenfunction:: uz_transformation_3ph_alphabeta_to_dq

This function converts the stationary :math:`\alpha\beta\gamma` reference frame components into the dq0 rotating reference frame. 
``X`` is a placeholder and can be replaced by either ``V``, ``I``, or any other applicable unit. 
The d-Axis has to be aligned with the A-phase.

.. math::

  \begin{bmatrix} X_{d} \\ X_{q} \\ X_{0} \end{bmatrix} =
  \begin{bmatrix} 
  cos(\theta_{el}) & sin(\theta_{el}) & 0\\
  -sin(\theta_{el}) & cos(\theta_{el}) & 0 \\
  0 & 0 & 1
  \end{bmatrix}
  \begin{bmatrix} X_{\alpha} \\ X_{\beta} \\ X_{\gamma} \end{bmatrix} \\

.. _dq_alphabeta_transformation:

dq0 to αβγ transformation 
-------------------------

.. doxygenfunction:: uz_transformation_3ph_dq_to_alphabeta

This function converts the dq0 rotating reference frame components into the stationary αβγ reference frame. 
``X`` is a placeholder and can be replaced by either ``V``, ``I``, or any other applicable unit. 
The d-Axis has to be aligned with the A-phase.

.. math::

  \begin{bmatrix} X_{\alpha} \\ X_{\beta} \\  X_{\gamma} \end{bmatrix} =
  \begin{bmatrix} 
  cos(\theta_{el}) & -sin(\theta_{el}) & 0\\
  sin(\theta_{el}) & cos(\theta_{el}) & 0 \\
  0 & 0 & 1
  \end{bmatrix}
  \begin{bmatrix} X_{d} \\ X_{q} \\ X_{0} \end{bmatrix} \\

Multiphase systems
==================

structs for sixphase VSD transformation
****************************************

.. doxygenstruct:: uz_6ph_abc_t
  :members:

.. doxygenstruct:: uz_6ph_alphabeta_t
  :members:

Functions for sixphase VSD systems transformation
**************************************************

.. _6ph_abc_to_alphabeta:

6ph-abc to 6ph-αβγ transformation 
---------------------------------

.. doxygenfunction:: uz_transformation_asym30deg_6ph_abc_to_alphabeta

The sixphase VSD transformation works like the following equations show:

.. math::
  
  \begin{bmatrix} C \end{bmatrix}=
    \frac{1}{3}
    \begin{bmatrix}
      cos(1\cdot 0\cdot\frac{\pi}{6}) & cos(1\cdot 4\cdot\frac{\pi}{6}) & cos(1\cdot 8\cdot\frac{\pi}{6}) & cos(1\cdot 1\cdot\frac{\pi}{6}) & cos(1\cdot 5\cdot\frac{\pi}{6}) & cos(1\cdot 9\cdot\frac{\pi}{6}) \\
      sin(1\cdot 0\cdot\frac{\pi}{6}) & sin(1\cdot 4\cdot\frac{\pi}{6}) & sin(1\cdot 8\cdot\frac{\pi}{6}) & sin(1\cdot 1\cdot\frac{\pi}{6}) & sin(1\cdot 5\cdot\frac{\pi}{6}) & sin(1\cdot 9\cdot\frac{\pi}{6}) \\
      cos(5\cdot 0\cdot\frac{\pi}{6}) & cos(5\cdot 4\cdot\frac{\pi}{6}) & cos(5\cdot 8\cdot\frac{\pi}{6}) & cos(5\cdot 1\cdot\frac{\pi}{6}) & cos(5\cdot 5\cdot\frac{\pi}{6}) & cos(5\cdot 9\cdot\frac{\pi}{6}) \\
      sin(5\cdot 0\cdot\frac{\pi}{6}) & sin(5\cdot 4\cdot\frac{\pi}{6}) & sin(5\cdot 8\cdot\frac{\pi}{6}) & sin(5\cdot 1\cdot\frac{\pi}{6}) & sin(5\cdot 5\cdot\frac{\pi}{6}) & sin(5\cdot 9\cdot\frac{\pi}{6}) \\
      cos(3\cdot 0\cdot\frac{\pi}{6}) & cos(3\cdot 4\cdot\frac{\pi}{6}) & cos(3\cdot 8\cdot\frac{\pi}{6}) & cos(3\cdot 1\cdot\frac{\pi}{6}) & cos(3\cdot 5\cdot\frac{\pi}{6}) & cos(3\cdot 9\cdot\frac{\pi}{6}) \\
      sin(3\cdot 0\cdot\frac{\pi}{6}) & sin(3\cdot 4\cdot\frac{\pi}{6}) & sin(3\cdot 8\cdot\frac{\pi}{6}) & sin(3\cdot 1\cdot\frac{\pi}{6}) & sin(3\cdot 5\cdot\frac{\pi}{6}) & sin(3\cdot 9\cdot\frac{\pi}{6}) \\
    \end{bmatrix}

.. math::

  \begin{bmatrix} X_{\alpha} \\ X_{\beta} \\ X_{x} \\ X_{y} \\ X_{z_1} \\ X_{z_2}  \end{bmatrix} = 
  \begin{bmatrix} C \end{bmatrix}\cdot\begin{bmatrix} X_{a_1} \\ X_{b_1} \\ X_{c_1} \\ X_{a_2} \\ X_{b_2} \\ X_{c_2}  \end{bmatrix}


.. _6ph_alphabeta_to_abc:

6ph-alpha-beta-gamma to 6ph-abc transformation 
----------------------------------------------------

.. doxygenfunction:: uz_transformation_asym30deg_6ph_alphabeta_to_abc

The inverse transformation uses the inverse of the before shown matrix.

.. math::

  \begin{bmatrix} X_{a_1} \\ X_{b_1} \\ X_{c_1} \\ X_{a_2} \\ X_{b_2} \\ X_{c_2}  \end{bmatrix} = 
  \begin{bmatrix} C \end{bmatrix}^{-1}\cdot\begin{bmatrix} X_{\alpha} \\ X_{\beta} \\ X_{x} \\ X_{y} \\ X_{z_1} \\ X_{z_2}   \end{bmatrix}


structs for ninephase VSD transformation
****************************************

.. doxygenstruct:: uz_9ph_abc_t
  :members:

.. doxygenstruct:: uz_9ph_alphabeta_t
  :members:

Naming of the subspaces according to [[#Zabaleta_diss]_].

Functions for ninephase VSD systems transformation
**************************************************

.. _9ph_abc_to_alphabeta:

9ph-abc to 9ph-αβγ transformation 
---------------------------------

.. doxygenfunction:: uz_transformation_9ph_abc_to_alphabeta

The ninephase VSD transformation works like the following equations show:

.. math::
  
  \begin{bmatrix} C \end{bmatrix}=
    \frac{2}{9}
    \begin{bmatrix}
        cos(1\cdot 0\cdot\frac{\pi}{9}) & cos(1\cdot 6\cdot\frac{\pi}{9}) & cos(1\cdot 12\cdot\frac{\pi}{9}) & cos(1\cdot 1\cdot\frac{\pi}{9}) & cos(1\cdot 7\cdot\frac{\pi}{9}) & cos(1\cdot 13\cdot\frac{\pi}{9}) & cos(1\cdot 2\cdot\frac{\pi}{9}) & cos(1\cdot 8\cdot\frac{\pi}{9}) & cos(1\cdot 14\cdot\frac{\pi}{9}) &\\
        sin(1\cdot 0\cdot\frac{\pi}{9}) & sin(1\cdot 6\cdot\frac{\pi}{9}) & sin(1\cdot 12\cdot\frac{\pi}{9}) & sin(1\cdot 1\cdot\frac{\pi}{9}) & sin(1\cdot 7\cdot\frac{\pi}{9}) & sin(1\cdot 13\cdot\frac{\pi}{9}) & sin(1\cdot 2\cdot\frac{\pi}{9}) & sin(1\cdot 8\cdot\frac{\pi}{9}) & sin(1\cdot 14\cdot\frac{\pi}{9}) \\
    cos(3\cdot 0\cdot\frac{\pi}{9}) & cos(3\cdot 6\cdot\frac{\pi}{9}) & cos(3\cdot 12\cdot\frac{\pi}{9}) & cos(3\cdot 1\cdot\frac{\pi}{9}) & cos(3\cdot 7\cdot\frac{\pi}{9}) & cos(3\cdot 13\cdot\frac{\pi}{9}) & cos(3\cdot 2\cdot\frac{\pi}{9}) & cos(3\cdot 8\cdot\frac{\pi}{9}) & cos(3\cdot 14\cdot\frac{\pi}{9}) \\
      sin(3\cdot 0\cdot\frac{\pi}{9}) & sin(3\cdot 6\cdot\frac{\pi}{9}) & sin(3\cdot 12\cdot\frac{\pi}{9}) & sin(3\cdot 1\cdot\frac{\pi}{9}) & sin(3\cdot 7\cdot\frac{\pi}{9}) & sin(3\cdot 13\cdot\frac{\pi}{9}) & sin(3\cdot 2\cdot\frac{\pi}{9}) & sin(3\cdot 8\cdot\frac{\pi}{9}) & sin(3\cdot 14\cdot\frac{\pi}{9}) \\
      cos(5\cdot 0\cdot\frac{\pi}{9}) & cos(5\cdot 6\cdot\frac{\pi}{9}) & cos(5\cdot 12\cdot\frac{\pi}{9}) & cos(5\cdot 1\cdot\frac{\pi}{9}) & cos(5\cdot 7\cdot\frac{\pi}{9}) & cos(5\cdot 13\cdot\frac{\pi}{9}) & cos(5\cdot 2\cdot\frac{\pi}{9}) & cos(5\cdot 8\cdot\frac{\pi}{9}) & cos(5\cdot 14\cdot\frac{\pi}{9}) \\
      sin(5\cdot 0\cdot\frac{\pi}{9}) & sin(5\cdot 6\cdot\frac{\pi}{9}) & sin(5\cdot 12\cdot\frac{\pi}{9}) & sin(5\cdot 1\cdot\frac{\pi}{9}) & sin(5\cdot 7\cdot\frac{\pi}{9}) & sin(5\cdot 13\cdot\frac{\pi}{9}) & sin(5\cdot 2\cdot\frac{\pi}{9}) & sin(5\cdot 8\cdot\frac{\pi}{9}) & sin(5\cdot 14\cdot\frac{\pi}{9}) \\
      cos(7\cdot 0\cdot\frac{\pi}{9}) & cos(7\cdot 6\cdot\frac{\pi}{9}) & cos(7\cdot 12\cdot\frac{\pi}{9}) & cos(7\cdot 1\cdot\frac{\pi}{9}) & cos(7\cdot 7\cdot\frac{\pi}{9}) & cos(7\cdot 13\cdot\frac{\pi}{9}) & cos(7\cdot 2\cdot\frac{\pi}{9}) & cos(7\cdot 8\cdot\frac{\pi}{9}) & cos(7\cdot 14\cdot\frac{\pi}{9}) \\
      sin(7\cdot 0\cdot\frac{\pi}{9}) & sin(7\cdot 6\cdot\frac{\pi}{9}) & sin(7\cdot 12\cdot\frac{\pi}{9}) & sin(7\cdot 1\cdot\frac{\pi}{9}) & sin(7\cdot 7\cdot\frac{\pi}{9}) & sin(7\cdot 13\cdot\frac{\pi}{9}) & sin(7\cdot 2\cdot\frac{\pi}{9}) & sin(7\cdot 8\cdot\frac{\pi}{9}) & sin(7\cdot 14\cdot\frac{\pi}{9}) \\
      \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & -\frac{1}{2} & -\frac{1}{2} & -\frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} \\
    \end{bmatrix}

.. math::

  \begin{bmatrix} X_{\alpha} \\ X_{\beta} \\ X_{o_1} \\ X_{o_2} \\ X_{x_1} \\ X_{y_1} \\ X_{x_2} \\ X_{y_2} \\ X_{zero} \end{bmatrix} = 
  \begin{bmatrix} C \end{bmatrix}\cdot\begin{bmatrix} X_{a_1} \\ X_{b_1} \\ X_{c_1} \\ X_{a_2} \\ X_{b_2} \\ X_{c_2} \\ X_{a_3} \\ X_{b_3} \\ X_{c_3} \end{bmatrix}

Transformation matrix according to [[#Rockhill_gerneral]_][[#Rockhill_ninephase]_].

.. _9ph_alphabeta_to_abc:

9ph-alpha-beta-gamma to 9ph-abc transformation 
----------------------------------------------------

.. doxygenfunction:: uz_transformation_9ph_alphabeta_to_abc

The inverse transformation uses the inverse of the before shown matrix.

.. math::

  \begin{bmatrix} X_{a_1} \\ X_{b_1} \\ X_{c_1} \\ X_{a_2} \\ X_{b_2} \\ X_{c_2} \\ X_{a_3} \\ X_{b_3} \\ X_{c_3} \end{bmatrix} = 
  \begin{bmatrix} C \end{bmatrix}^{-1}\cdot\begin{bmatrix} X_{\alpha} \\ X_{\beta} \\ X_{o_1} \\ X_{o_2} \\ X_{x_1} \\ X_{y_1} \\ X_{x_2} \\ X_{y_2} \\ X_{zero} \end{bmatrix}

Example usage of the ninephase transformation
*********************************************

The existing functions offer the possibility to convert ninephase asymmetrical systems into a stationary reference frame (αβ).
Afterward, the Park transformation can be applied to transform them into the rotating reference frame.
The inverse transformations are also available.
To use the ninephase transformation, one must create a struct for the natural phase domain values.

.. code-block:: c
  :caption: Declarations
  
  // declare necessary structs and variables
  uz_9ph_abc_t natural_values = {0};             // holds the natural values
  uz_9ph_alphabeta_t stationary_values = {0};    // holds the stationary reference frame values
  uz_3ph_alphabeta_t alphabeta = {0};            // used to give only alpha and beta to the Park transformation
  uz_3ph_dq_t rotating_dq = {0};                 // holds the results of the Park transformation
  float d_current = 0.0f;                        // example variable, used to process the dq values in the following code
  float q_current = 0.0f;                        // example variable, used to process the dq values in the following code
  float theta_el = 0.0f;                         // electric rotor angle

  ...

  // assert example values
  natural_values.a1 =  1.0f;                     // example value for phase a1, store your real values here
  natural_values.b1 = -0.5f;
  //...
  natural_values.c3 = -0.5f;
    
The struct can then be given to the transformation function which will return a struct containing the transformed values in the stationary reference frame.

.. code-block:: c
  :caption: VSD transformation

  stationary_values = uz_transformation_9ph_abc_to_alphabeta(natural_values);

As it is common to transform only the :math:`\alpha\beta` components to the rotating reference frame, those two must be written into the threephase ``uz_3ph_alphabeta_t`` struct and be given to the dq transformation function.
As commonly known, the electrical angle is also necessary. 
The dq and values can then be read from the struct. The inverse transformation follows the same principle.

.. code-block:: c
  :caption: Park transformation

  alphabeta.alpha = stationary_values.alpha;
  alphabeta.beta = stationary_values.beta;
  rotating_dq = uz_transformation_3ph_alphabeta_to_dq(alphabeta,theta_el);
  d_current = rotating_dq.d;
  q_current = rotating_dq.q;

Adding transformations
**********************

When adding a new transformation for systems with different amounts of phases one must know if the principle of the existing VSD transformation can be used.
If this is the case, go through the following steps:

1. Copy the functions uz_9ph_clarke_transformation, uz_transformation_9ph_alphabeta_to_abc and uz_9ph_arraymul and rename them accordingly (e.g. uz_6ph_arraymul).

2. Create the structs uz_alphabeta_9ph_t and uz_abc_9ph_t for the newly added phase system.

3. In uz_9ph_arraymul adapt the expected array dimensions and limit of the for-loop to your amount of phases (everywhere where there is a 9).

4. Do the same with the Clarke transformation functions and change the structs to your newly created ones. For the VSD transformation, the Matlab script (see below) can be used.

5. Adapt the input/output writing accordingly.


To use the Matlab script that outputs the VSD matrix in C code, the variable "n" must be changed to the target amount of phases.
The placeholder "VSD_MATRIX" should be replaced with the Matlab variable that holds the VSD matrix (e.g. from your workspace).
The factor for *amplitude invariance* will be multiplied afterward so the user should not apply it to your VSD matrix by himself.
The creation of a transformation matrix with this method was presented in [[#Zoric_paper]_].


.. code-block:: matlab
  :caption: Matlab script

  %% VSD matrix
  n = 9;
  z = single(2/n*VSD_MATRIX);
  invz = inv(z);

  %% print code for normal matrix
  fprintf('\nTransformation Matrix:\n');
  printcode(z,n);

  %% print code for inverse matrix
  fprintf('\nInverse Transformation Matrix:\n');
  printcode(invz,n);

  %% function printcode function declare: print c code for matrix to 2D array
  function printcode(matrix,phases)
    fprintf('float const vsd_mat[%d][%d] = \n{\n',phases,phases);
    for y = (0:(phases-1))
      fprintf('    { ');
      for x = (0:(phases-1))
        fprintf('%.7ff',matrix(y+1,x+1));
        if x<(phases-1)
          fprintf(', ');
        end
      end
    if y<(phases-1)
      fprintf(' },\n');
    else
      fprintf(' }\n');
    end
  end
  fprintf('};\n');
  end



Sources
-------

.. [#Zoric_paper] I. Zoric, M. Jones and E. Levi, "Vector space decomposition algorithm for asymmetrical multiphase machines," 2017 International Symposium on Power Electronics (Ee), 2017, pp. 1-6, doi: 10.1109/PEE.2017.8171682.
.. [#Zabaleta_diss] M. Zabaleta, "Permament Magnet Multiphase Machine Modeling and Control for MV Wind Energy Applications", Dissertation, Liverpool John Moores University, 2018, doi: 10.24377/LJMU.t.00008818.
.. [#Rockhill_gerneral] A. A. Rockhill and T. A. Lipo, "A generalized transformation methodology for polyphase electric machines and networks," 2015 IEEE International Electric Machines & Drives Conference (IEMDC), 2015, pp. 27-34, doi: 10.1109/IEMDC.2015.7409032.
.. [#Rockhill_ninephase] A. A. Rockhill and T. A. Lipo, "A simplified model of a nine phase synchronous machine using vector space decomposition," 2009 IEEE Power Electronics and Machines in Wind Applications, 2009, pp. 1-5, doi: 10.1109/PEMWA.2009.5208335.
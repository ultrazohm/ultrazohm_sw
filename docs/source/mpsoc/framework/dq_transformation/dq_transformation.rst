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

Threephase systems
==================

Variables structs
*****************

These structs are needed to hand over the input values and get the output values of the functions.
    
.. doxygenstruct:: uz_UVW_t
  :members:

.. doxygenstruct:: uz_dq_t
  :members:

.. doxygenstruct:: uz_alphabeta_t
  :members:

dq-Transformation
*****************

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
*************************

.. doxygenfunction:: uz_dq_inverse_transformation

This uses the inverse Park transformation to transform a dq0 rotating reference frame to a three-phase (uvw) signal. 
``X`` is a placeholder and can be replaced by either ``U``, ``I`` or any other applicable unit. 
The d-Axis has to be aligned with the U-phase.
  
.. math::
  
  \begin{bmatrix}
    X_U \\
    X_V \\
    X_W \\
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

clarke-Transformation
*********************

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
*****************************

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


Multiphase systems
==================
Example usage of the ninephase transformation
*********************************************
The existing functions offer the possibility to convert ninephase asymetrical systems into a the stationary reference frame (αβ).
Afterwards a Park transformation can be applied to transform into the rotating reference frame.
The inverse transformations are also available.
To use the ninephase transformation, one must create a struct for the natural phase domain values.

.. code-block:: c
  :caption: Declarations
  
  // declare necessary structs and variables
  struct uz_abc_9ph_t natural_values = {0};             // holds the natural values
  struct uz_alphabeta_9ph_t stationary_values = {0};    // holds the stationary reference frame values
  uz_alphabeta_t alphabeta = {0};                       // used to give only α and β to the Park transformation
  uz_dq_t rotating_dq = {0};                            // holds the results of the Park transformation
  float d_current = 0.0f;                               // example variable, used to process the dq values in the following code
  float q_current = 0.0f;                               // example variable, used to process the dq values in the following code
  float theta_el = 0.0f;                                // electric rotor angle

  // assert example values
  natural_values.a1 =  1.0f;                            // example value for phase a1, store your real values here
  natural_values.b1 = -0.5f;
  //...
  natural_values.c3 = -0.5f;
    
The struct can then be given to the transformation function which will return a struct containing the transformed values in the stationary reference frame.

.. code-block:: c
  :caption: VSD transformation

  stationary_values = uz_9ph_clarke_transformation(natural_values);

As it is common to transform only the αβ components to the rotating reference frame, those two must be written into the threephase uz_alphabeta_t struct and be given to the dq transformation function.
As commonly known, the electrical angle is also necessary. 
Note that the gamma and the zero values in the uz_alphabeta_t and uz_dq_t struct will not be read from or written to.
They will be set to -999999.0f.
The dq and values can then be read from the struct. The inverse transformation follows the same principle.

.. code-block:: c
  :caption: Park transformation

  alphabeta.alpha = stationary_values.alpha;
  alphabeta.beta = stationary_values.beta;
  rotating_dq = uz_ab_to_dq_transformation(alphabeta,theta_el);
  d_current = rotating_dq.d;
  q_current = rotating_dq.q;

Adding transformations
**********************
When adding a new transformation for systems with other amounts of phases one must know if the principle of the existing VSD transformation can be used.
If this is the case, the two functions for the multiphase Clarke transformation and inverse transformation can be copied. 
For different amount of phases the arraysizes will need to be adapted as well as the input/output structs.
The writing to the output structs also needs to be adapted.
For the two dimensional vsd_struct containing the transformation matrix, a Matlab script can be used.

.. code-block:: matlab
  :caption: Matlab script

  %% VSD matrix
  n = 9;
  z = single(2/n*YOURMATRIX);
  invz = inv(z);

  %% print code for normal matrix
  printcode(z,n);

  %% print code for inverse matrix
  printcode(invz,n);

  %% function printcode function declare: print c code for matrix to 2D array
  function printcode(matrix,phases)
    for y = (0:(phases-1))
      for x = (0:(phases-1))
        fprintf('vsd_mat[%d][%d] = %.7ff;\n',y,x,matrix(y+1,x+1));
      end
    end
  end

Functions and structs for ninephase VSD transformation
******************************************************
.. doxygenstruct:: uz_abc_9ph_t
  :members:

.. doxygenstruct:: uz_alphabeta_9ph_t
  :members:

.. doxygenfunction:: uz_9ph_clarke_transformation

The ninephase VSD transformation works like the following equations show:

.. math::
  
  \begin{bmatrix} C \end{bmatrix}=
	\frac{2}{9}*
	\begin{bmatrix}
		cos(1*0*\frac{\pi}{9}) & cos(1*6*\frac{\pi}{9}) & cos(1*12*\frac{\pi}{9}) & cos(1*1*\frac{\pi}{9}) & cos(1*7*\frac{\pi}{9}) & cos(1*13*\frac{\pi}{9}) & cos(1*2*\frac{\pi}{9}) & cos(1*8*\frac{\pi}{9}) & cos(1*14*\frac{\pi}{9}) &\\
		sin(1*0*\frac{\pi}{9}) & sin(1*6*\frac{\pi}{9}) & sin(1*12*\frac{\pi}{9}) & sin(1*1*\frac{\pi}{9}) & sin(1*7*\frac{\pi}{9}) & sin(1*13*\frac{\pi}{9}) & sin(1*2*\frac{\pi}{9}) & sin(1*8*\frac{\pi}{9}) & sin(1*14*\frac{\pi}{9}) \\
    cos(3*0*\frac{\pi}{9}) & cos(3*6*\frac{\pi}{9}) & cos(3*12*\frac{\pi}{9}) & cos(3*1*\frac{\pi}{9}) & cos(3*7*\frac{\pi}{9}) & cos(3*13*\frac{\pi}{9}) & cos(3*2*\frac{\pi}{9}) & cos(3*8*\frac{\pi}{9}) & cos(3*14*\frac{\pi}{9}) \\
	  sin(3*0*\frac{\pi}{9}) & sin(3*6*\frac{\pi}{9}) & sin(3*12*\frac{\pi}{9}) & sin(3*1*\frac{\pi}{9}) & sin(3*7*\frac{\pi}{9}) & sin(3*13*\frac{\pi}{9}) & sin(3*2*\frac{\pi}{9}) & sin(3*8*\frac{\pi}{9}) & sin(3*14*\frac{\pi}{9}) \\
	  cos(5*0*\frac{\pi}{9}) & cos(5*6*\frac{\pi}{9}) & cos(5*12*\frac{\pi}{9}) & cos(5*1*\frac{\pi}{9}) & cos(5*7*\frac{\pi}{9}) & cos(5*13*\frac{\pi}{9}) & cos(5*2*\frac{\pi}{9}) & cos(5*8*\frac{\pi}{9}) & cos(5*14*\frac{\pi}{9}) \\
	  sin(5*0*\frac{\pi}{9}) & sin(5*6*\frac{\pi}{9}) & sin(5*12*\frac{\pi}{9}) & sin(5*1*\frac{\pi}{9}) & sin(5*7*\frac{\pi}{9}) & sin(5*13*\frac{\pi}{9}) & sin(5*2*\frac{\pi}{9}) & sin(5*8*\frac{\pi}{9}) & sin(5*14*\frac{\pi}{9}) \\
	  cos(7*0*\frac{\pi}{9}) & cos(7*6*\frac{\pi}{9}) & cos(7*12*\frac{\pi}{9}) & cos(7*1*\frac{\pi}{9}) & cos(7*7*\frac{\pi}{9}) & cos(7*13*\frac{\pi}{9}) & cos(7*2*\frac{\pi}{9}) & cos(7*8*\frac{\pi}{9}) & cos(7*14*\frac{\pi}{9}) \\
	  sin(7*0*\frac{\pi}{9}) & sin(7*6*\frac{\pi}{9}) & sin(7*12*\frac{\pi}{9}) & sin(7*1*\frac{\pi}{9}) & sin(7*7*\frac{\pi}{9}) & sin(7*13*\frac{\pi}{9}) & sin(7*2*\frac{\pi}{9}) & sin(7*8*\frac{\pi}{9}) & sin(7*14*\frac{\pi}{9}) \\
	  \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} & \frac{1}{2} \\
	\end{bmatrix} \\
  \begin{bmatrix} X_{\alpha} \\ X_{\beta} \\ X_{o_1} \\ X_{o_2} \\ X_{x_1} \\ X_{y_1} \\ X_{x_2} \\ X_{y_2} \\ X_{zero} \end{bmatrix} = 
  \begin{bmatrix} C \end{bmatrix}*\begin{bmatrix} X_{a_1} \\ X_{b_1} \\ X_{c_1} \\ X_{a_2} \\ X_{b_2} \\ X_{c_2} \\ X_{a_3} \\ X_{b_3} \\ X_{c_3} \end{bmatrix}

.. doxygenfunction:: uz_9ph_clarke_inverse_transformation

The inverse transformation uses the inverse of the before shown matrix.

.. math::

  \begin{bmatrix} X_{a_1} \\ X_{b_1} \\ X_{c_1} \\ X_{a_2} \\ X_{b_2} \\ X_{c_2} \\ X_{a_3} \\ X_{b_3} \\ X_{c_3} \end{bmatrix} = 
  \begin{bmatrix} C \end{bmatrix}^{-1}*\begin{bmatrix} X_{\alpha} \\ X_{\beta} \\ X_{o_1} \\ X_{o_2} \\ X_{x_1} \\ X_{y_1} \\ X_{x_2} \\ X_{y_2} \\ X_{zero} \end{bmatrix}

.. doxygenfunction:: uz_9ph_arraymul

The function implements a matrix multiplication for a linevector with a rowvector. 
It hast to be implemented explicitly for each amount of phases. ADDITION: ADD IN MATLAB SKRIPT

.. _uz_flux_approximation_script:

=========================
Flux approximation script
=========================

.. note::

    This is a Placeholder and part of a different Pull-Request. It is here to clarify how the docs pages would interact with each other.


Script to approximate flux-linkages from a 3D-Lookup-Table. 
To enable this dynamic implementation, the flux-linkages are approximated using analytic-Prototype functions.
This is based on the approach and findings from [#Shih_Wei_Su_flux_approximation]_.
The flux-linkages can be approximated using the following equations. 

.. math::
  
    \hat{\psi}_{d}(i_{d},i_{q}) = \hat{\psi}_{self}^{d}(i_{d}) - \hat{\psi}_{cross}^{d}(i_{d},i_{q})

.. math::
 
    \hat{\psi}_{q}(i_{d},i_{q}) = \hat{\psi}_{self}^{q}(i_{q})-\hat{\psi}_{cross}^{q}(i_{d},i_{q})

For the self-axis saturation prototype function a hyperbolic tangent function and a linear function to mimic the saturation effect in a single axis can be employed [#Shih_Wei_Su_flux_approximation]_.

.. math::

    \hat\psi_{self}^{d} = \hat\psi_{d}(i_{d},i_{q}=0) = a_{d1} \cdot \tanh(a_{d2} \cdot (i_{d}-a_{d3}))

.. math::

    \hat\psi_{self}^{q} = \hat\psi_{q}(i_{d}=0,i_{q}) = a_{q1} \cdot \tanh(a_{q2} \cdot i_{q})+ i_{q} \cdot a_{q3}

The cross-coupling saturation terms can be found if the the flux-linkages are evaluated at their maximum cross-coupling currents :math:`I_{d1}` and :math:`I_{d1}`.

.. math::

    \hat{\psi}_{cross}^{d,s1}(i_{d},i_{q}=I_{q1}) = \hat{\psi}_{self}^{d}(i_{d})-\psi_{d,s1}(i_{d},I_{q1})
  
.. math::

    \hat{\psi}_{cross}^{q,s1}(i_{d}=I_{d1},i_{q}) = \hat{\psi}_{self}^{q}(i_{q})-\psi_{q,s1}(I_{d1},i_{q})

The flux-linkages in these points can be approximated with the following equations [#Shih_Wei_Su_flux_approximation]_: 

.. math:: 

    \hat\psi_{d,s1}(i_{d}) = \hat\psi_{d}(i_{d},i_{q}=I_{q1}) = a_{d4} \cdot \tanh(a_{d5} \cdot (i_{d}-a_{d6}))

.. math::

    \hat\psi_{q,s1}(i_{q}) = \hat\psi_{q}(i_{d}=I_{d1},i_{q}) = a_{q4} \cdot \tanh(a_{q5} \cdot i_{q})+ i_{q} \cdot a_{q6}

With that the cross-coupling terms are resulting.

.. math:: 

    \hat\psi_{cross}^{d,s1}(i_{d},i_{q}=I_{q1}) = a_{d1} \cdot \tanh(a_{d2} \cdot (i_{d}-a_{d3})) - a_{d4} \cdot \tanh(a_{d5} \cdot (i_{d}-a_{d6})

.. math::

    \hat\psi_{cross}^{q,s1}(i_{d}=I_{d1},i_{q}) = a_{q1} \cdot \tanh(a_{q2} \cdot i_{q})+ i_{q} \cdot a_{q3} - a_{q4} \cdot \tanh(a{q5} \cdot i_{q})- i_{q} \cdot a_{q6}

These have to be integrated [#Shih_Wei_Su_flux_approximation]_ , which yields.

.. math::

    \int \hat{\psi}_{cross}^{d,s1}(i_{d}) \, di_{d} = \frac{a_{d1}}{a_{d2}} \cdot \log(\cosh(a_{d2}(i_{d}-a_{d3}))) - \frac{a_{d4}}{a_{d5}} \cdot \log(\cosh(a_{d5}(i_{d}-a_{d6})))

.. math::

    \int \hat{\psi}_{cross}^{q,s1}(i_{q}) \, di_{q} = \frac{1}{2}(a_{q3}-a_{q6}) \cdot i_{q}^2 + \frac{a_{q1}}{a_{q2}} \cdot \log(\cosh(a_{q2}i_{q})) - \frac{a_{q4}}{a_{q5}} \cdot \log(\cosh(a_{q5}i_{q}))

With that the entire range of the flux-linkage is found. Note that the terms :math:`\int \hat{\psi}_{cross}^{q,s1}(I_{q1}) di_{q}` and :math:`\int \hat{\psi}_{cross}^{d,s1}(I_{d1}) di_{d}` are constant values and will be used in the fitting parameters.

.. math::

    \hat{\psi}_{d}(i_{d},i_{q}) = \hat{\psi}_{d,self}(i_{d}) - \underbrace{\frac{1}{\int \hat{\psi}_{cross}^{q,s1}(i_{q}) \, di_{q}} \left( \hat{\psi}_{cross}^{d,s1}(i_{d},i_{q}=I_{q1}) \right) \left( \int \hat{\psi}_{cross}^{q,s1}(i_{q}) \, di_{q} \right)}_{=\hat{\psi}_{cross}^{d}(i_{d},i_{q})}

.. math::

    \hat{\psi}_{q}(i_{d},i_{q}) = \hat{\psi}_{q,self}(i_{q}) - \underbrace{\frac{1}{\int \hat{\psi}_{cross}^{d,s1}(i_{d}) \, di_{d}} \left( \hat{\psi}_{cross}^{q,s1}(i_{d}=I_{d1},i_{q}) \right) \left( \int \hat{\psi}_{cross}^{d,s1}(i_{d}) \, di_{d} \right)}_{=\hat{\psi}_{cross}^{q}(i_{d},i_{q})}

To find the fitting-Parameter the following nonlinear-square Problems have to be minimized. 
For that the MATLAB  nonlinear-regression function lsqnonlin with the Levenberg-Marquart algorithm is used.

.. math::

    \min_{a_{d1},a_{d2},a_{d3}} \sum_{j=1}^{m} \left[ \psi_{d} \left(i_{d,j}, 0\right) - \hat{\psi}_{d,self}\left(i_{d,j},a_{d1},a_{d2},a_{d3}\right) \right]^2 

.. math::

    \min_{a_{q1},a_{q2},a_{q3}} \sum_{k=1}^{n} \left[ \psi_{q} \left( 0, i_{q,k}\right) - \hat{\psi}_{q,self}\left(i_{q,k},a_{q1},a_{q2},a_{q3}\right) \right]^2 

.. math::
  
    \min_{a_{d4},a_{d5},a_{d6}} \sum_{j=1}^{m} \left[ \psi_{d} \left(i_{d,j}, I_{q1}\right) - \hat{\psi}_{d,s1}\left(i_{d,j},a_{d4},a_{d5},a_{d6}\right) \right]^2 

.. math::
  
    \min_{a_{q4},a_{q5},a_{q6}} \sum_{k=1}^{n} \left[ \psi_{d} \left(I_{d1}, i_{q,k}\right) - \hat{\psi}_{q,s1}\left(i_{d},a_{q4},a_{q5},a_{q6}\right) \right]^2 

Example usage
=============

In this example usage, flux-linkages of a example motor are getting approximated.

- There needs to be a Excel data sheet in the same directory as the PMSM IP core at ``ultrazohm_sw\ip_cores\uz_pmsm_model``.

- The naming in the script has to be adjusted. 

.. code-block:: matlab
    :linenos:
    :caption: Example to get data out of a Excel data sheet.

    ...
    FluxMapData = readtable('FluxMapData_Prototyp_1000rpm_');
    ...

- Afterwards the area where the Array is in the excel sheet has to be specified. 
  
.. code-block:: matlab
    :linenos:
    :caption: Example to specify array location and size.

    ...
    % Currents
    id = FluxMapData{1,1:20};
    iq = FluxMapData{22:41,1};
    %Psi_d
    psi_d = FluxMapData{43:62,1:20}*(1e-3);
    %Psi_q
    psi_q = FluxMapData{108:127,1:20}*(1e-3);
    ...

- To run the approximation script, first the ``uz_pmsm_model_init_parameter.m file has to be ran``.
- If the the script ran successfully the fitting parameters are in the MATLAB workspace an can be used in the IP core for nonlinear behavior or for different use in the sw-framework.

Sources
-------

.. [#Shih_Wei_Su_flux_approximation] Analytical Prototype Functions for Flux Linkage Approximation in Synchronous Machines, Shih-Wei Su, Christoph M. Hackl, and Ralph Kennel, IEEE Open Journal of the Industrial Electronics Society, vol. 3, pp. 265-282, 2022, doi: 10.1109/OJIES.2022.3162336
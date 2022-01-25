=======================
Import external C types
=======================

The `Matlab/Simulink Embedded-Coder <https://de.mathworks.com/products/embedded-coder.html>`_ generates C-Code from Simulink models.
The page :ref:`embedded_coder` describes an easy way to get started with the Embedded-Coder on the UltraZohm.
In order to streamline the inclusion of generated C-Code from Simulink into the UltraZohm workspace the Matlab function `Simulink.importExternalCTypes <https://de.mathworks.com/help/simulink/slref/simulink.importexternalctypes.html>`_ can be used.
This function parses the C (.h) header files for typedef, struct, and enum type definitions, and generates Simulink representations of the types.

How to use
----------

In your ``init.m`` Matlab script for your Simulink model include the following command. 

.. code-block:: 

    Simulink.importExternalCTypes('headerfile.h');


.. tip:: Use a relative path to link back to the ``ultrazohm_sw`` library. This way changes to the C-source-code are reflected in your model. 

This will create a bus object in your workspace with the appropriate types (i.e. float -> single).
Theses buses can then be used in your Simulink object as normal data type.

.. warning:: For this to properly work all ``structs`` and ``enums``, which are used in the Simulink model, have to be ``typedef``. 
             Otherwise, Simulink generates bus objects with incompatible names, which, if code generated, are not compatible with the initially included header-file
             (i.e. using ``struct uz_dq_t`` in the header-file leads with code-generation to ``struct_uz_dq_t name`` instead of ``struct uz_dq_t name``. Using ``typedef`` fixes this).

Example
-------

Include the data types for the dq-transformation.

.. code-block:: 

    Simulink.importExternalCTypes('uz_Transformation.h');

In the Simulink workspace the following bus objects will be created:

.. image:: bus_editor.png

These buses can be used, e.g., as an output for dq-reference currents.

.. image:: property_inspector.png

This output can be directly assigned to other ``uz_dq_t`` structs or functions, which use this type.

.. code-block:: C
    :caption: Example for the usage of the generated code from imported C-types

    float theta_el_rad = 23.4f;
    uz_dq_t dq_currents = codegenInstance.output.i_dq_ref;
    uz_UVW_t UVW_currents = uz_dq_inverse_transformation(codegenInstance.output.i_dq_ref, theta_el_rad);

More Information
----------------

- `Simulink.importExternalCTypes <https://de.mathworks.com/help/simulink/slref/simulink.importexternalctypes.html>`_
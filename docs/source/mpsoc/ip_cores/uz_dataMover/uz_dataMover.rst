.. _uz_dataMover:

====================
Data Mover / AXI2TCM
====================


- Moves data from PL to R5 (R5_0) by writing data directly to the BTCM


Software driver
===============

- direct pointer to data
- buffered data


.. doxygenfunction:: uz_dataMover_get_data_by_pointer

.. doxygenfunction:: uz_dataMover_update_buffer_and_get_data

.. doxygenfunction:: uz_dataMover_update_buffer
    
.. doxygenfunction:: uz_dataMover_get_data_from_buffer
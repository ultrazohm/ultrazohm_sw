.. _uz_PMSM_config:

===========
PMSM config
===========

Motor parameters of a permanent magnet synchronous motor (PMSM) are needed for multiple functions.
To streamline the coding process, every necessary PMSM parameter will be bundled inside a ``uz_PMSM_t`` struct, which can be used in the whole UltraZohm project. 

.. doxygenstruct:: uz_PMSM_t
    :members:

To avoid code duplication a function, which asserts every struct member, is available. 

.. doxygenfunction:: uz_PMSM_config_assert
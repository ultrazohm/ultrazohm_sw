.. _uz_FOC_change_decoupling:

=============================
Change the type of decoupling
=============================

.. doxygenfunction:: uz_FOC_change_decoupling_select

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change decoupling during runtime. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     uz_FOC_change_decoupling_select(FOC_instance, linear_decoupling);
  }

Description
===========

Gives the option to change the type of decoupling during runtime. 
As input arguments for the type of decoupling the enum shown in :ref:`uz_FOC_config` is used.

.. _uz_CurrentControl_set_decoupling:

=============================
Change the type of decoupling
=============================

.. doxygenfunction:: uz_CurrentControl_set_decoupling_method

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change decoupling during runtime. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     uz_CurrentControl_set_decoupling_method(CC_instance, linear_decoupling);
  }

Description
===========

Gives the option to change the type of decoupling during runtime. 
As input arguments for the type of decoupling the enum shown in :ref:`uz_CurrentControl_config` is used.

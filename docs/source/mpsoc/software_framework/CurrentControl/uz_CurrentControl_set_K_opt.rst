.. _uz_CurrentControl_set_Kp_Ki_opt:

===============================================
Set Ki or Kp according to optimisation criteria 
===============================================

.. doxygenfunction:: uz_CurrentControl_set_Kp_id_magnitude_optimum

.. doxygenfunction:: uz_CurrentControl_set_Ki_id_magnitude_optimum

.. doxygenfunction:: uz_CurrentControl_set_Kp_iq_magnitude_optimum

.. doxygenfunction:: uz_CurrentControl_set_Ki_iq_magnitude_optimum

.. doxygenfunction:: uz_CurrentControl_set_Kp_id_symmetric_optimum

.. doxygenfunction:: uz_CurrentControl_set_Ki_id_symmetric_optimum

.. doxygenfunction:: uz_CurrentControl_set_Kp_iq_symmetric_optimum

.. doxygenfunction:: uz_CurrentControl_set_Ki_iq_symmetric_optimum

.. doxygenfunction:: uz_CurrentControl_set_Kp_id_bandwidth

.. doxygenfunction:: uz_CurrentControl_set_Ki_id_bandwidth

.. doxygenfunction:: uz_CurrentControl_set_Kp_iq_bandwidth

.. doxygenfunction:: uz_CurrentControl_set_Ki_iq_bandwidth


Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to set Kp or Ki parameters. 

  int main(void) {
     struct uz_PMSM_t config_PMSM = {
      .Ld_Henry = 0.0001f,
      .Lq_Henry = 0.0002f,
      .R_ph_Ohm = 0.008f
     };
     float tau_sigma_sec = 0.0001;
     float bandwidth_rad_per_sec = 2500;
     float Kp_id_mo = uz_CurrentControl_set_Kp_id_magnitude_optimum(config_PMSM, tau_sigma_sec);
     float Ki_id_mo = uz_CurrentControl_set_Kp_id_magnitude_optimum(config_PMSM, tau_sigma_sec);
     float Kp_iq_mo = uz_CurrentControl_set_Kp_id_magnitude_optimum(config_PMSM, tau_sigma_sec);
     float Ki_iq_mo = uz_CurrentControl_set_Kp_id_magnitude_optimum(config_PMSM, tau_sigma_sec);
     float Kp_id_so = uz_CurrentControl_set_Kp_id_symmetric_optimum(config_PMSM, tau_sigma_sec);
     float Ki_id_so = uz_CurrentControl_set_Kp_id_symmetric_optimum(config_PMSM, tau_sigma_sec);
     float Kp_iq_so = uz_CurrentControl_set_Kp_id_symmetric_optimum(config_PMSM, tau_sigma_sec);
     float Ki_iq_so = uz_CurrentControl_set_Kp_id_symmetric_optimum(config_PMSM, tau_sigma_sec);
     float Kp_id_bw = uz_CurrentControl_set_Kp_id_bandwidth(config_PMSM, bandwidth_rad_per_sec);
     float Ki_id_bw = uz_CurrentControl_set_Kp_id_bandwidth(config_PMSM, bandwidth_rad_per_sec);
     float Kp_iq_bw = uz_CurrentControl_set_Kp_id_bandwidth(config_PMSM, bandwidth_rad_per_sec);
     float Ki_iq_bw = uz_CurrentControl_set_Kp_id_bandwidth(config_PMSM, bandwidth_rad_per_sec);     
  }

Description
===========

Calculates the values of ``Kp`` and ``Ki`` according to different optimisation criteria and parameters of the PMSM. 
Three variants are available (magnitude optimum [[#Schroeder]_] (p.81) [[#Gemaßmer]_] (p.98), symmetric optimum [[#Schroeder]_] (p.81) and desired bandwidth[[#TexasI]_] (p.409)), all with their respective functions for ``Kp_id``, ``Ki_id``, ``Kp_iq`` and ``Ki_iq``. 
``tau_sigma_sec`` has to be calculated by hand depending on the used interrupt trigger (see also :ref:`r5_interrupts`) and the chosen ISR frequency (see also :ref:`uz_mux_axi`).

Sources
=======

.. [#Schroeder] Elektrische Antriebe – Regelung von Antriebssystemen, Dierk Schröder, Springer, ISBN 978-3-642-30095-0
.. [#TexasI] "InstaSPIN-FOC™ and InstaSPIN-MOTION™ User’s Guide-0", Texas Instruments, https://www.ti.com/lit/ug/spruhj1i/spruhj1i.pdf?ts=1686841737437
.. [#Gemaßmer] Effiziente und dynamische Drehmomenteinprägung in hoch ausgenutzten Synchronmaschinen mit eingebetteten Magneten, Tobias Gemaßmer, ISBN 978-3-7315-0366-8

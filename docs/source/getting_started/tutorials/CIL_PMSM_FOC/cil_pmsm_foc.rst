.. _cil_pmsm_foc:

=======================================
Controlling a PMSM IP-Core with the FOC
=======================================

Aim of the tutorial
*******************

In this tutorial the :ref:`PMSM IP-Core <uz_pmsmModel>` will be added to the Vivado project and controlled using the :ref:`uz_FOC`.

Requirements
************

The following tutorial requires:

- :ref:`The previous tutorial <gate_signals>`.

Initial steps
*************

#. In the *Vivado* project open up the *Block Design*.
#. Extend the ``uz_user`` block.

   ..  _Vivado_overview:
   ..  figure:: ./img/Vivado1.png
       :align: center

       Block design in Vivado.

#. In the right click on the ``uz_user`` block and select ``Add IP ...`` and search for the ``uz_pmsm_model``.
#. Double click on the result. The IP-Core should now reside inside the ``uz_user`` block.
#. Double click on the ``AXI smartconnect`` and increase the number of *Master interfaces* by one.
#. Connect the IP-Core as shown below.

   ..  _Vivado_pmsm:
   ..  figure:: ./img/Vivado2.png
       :align: center

       Block design in Vivado.

#. Click on the *Adress Editor* tab and assign the new IP-Block a address by right clicking on the entry and selecting *Assign*.

   ..  _Vivado_ip_address:
   ..  figure:: ./img/Vivado3.png
       :align: center

       Assign IP-address in Vivado.

   .. note:: 

      If the new IP-Core shows up as *unconnected* instead of *unassigned*, delete the ``AXI smartconnect`` in the ``uz_user`` block and add it again with the same connections.
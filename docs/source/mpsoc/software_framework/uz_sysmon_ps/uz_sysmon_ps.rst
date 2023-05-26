=================
PS System Monitor
=================

UltraScale+ has multiple system monitors (sysmon).
There are system monitors in the PS and the PL.
The system monitor in the PL is always present, but has extended capabilities if the SYSMON IP-core is instantiated (see https://www.xilinx.com/products/intellectual-property/system-management-wiz.html).
This software module only deals with the PS system monitor and provides a wrapper to access part of the available information, especially the chip temperature.
Information:

- https://docs.xilinx.com/r/en-US/ug1085-zynq-ultrascale-trm/System-Monitors
- https://docs.xilinx.com/v/u/en-US/ug580-ultrascale-sysmon

The wrapper is heavily based on the vendor provided example:

- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/sysmonpsu/examples/xsysmonpsu_polled_example.c
- https://github.com/Xilinx/embeddedsw/tree/master/XilinxProcessorIPLib/drivers/sysmonpsu
- https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/sysmonpsu/src/xsysmonpsu.h

Example
=======

The following example initializes the PS SYSMON and reads out the four available platform states.
Note that reading all four values once takes approx :math:`1.5-2\,\mu s`.
Since the values, especially the temperature, are not time critical, consider not reading the SYSMON in the control interrupt.

.. code-block:: c

    #include "xparameters.h"
    #include "uz/uz_sysmon_ps/uz_sysmon_ps.h"

    main(){
        uz_sysmon_ps_t * sysmon_instance=uz_sysmon_ps_init(XPAR_XSYSMONPSU_0_DEVICE_ID);
        float temp=0.0f;
        float vcc_lp=0.0f;
        float vcc_fp=0.0f;
        float fcc_aux=0.0f;
        while(1){
            temp = uz_sysmon_ps_read_temperature(sysmon_instance);
            vcc_lp =  sysmon_ps_read_vcc_psint_lp_volt(sysmon_instance);
            vcc_fp =  sysmon_ps_read_vcc_psint_fp_volt(sysmon_instance);
            fcc_aux = sysmon_ps_read_vcc_psaux_volt(sysmon_instance);
        }
    }


Reference
=========


.. doxygentypedef:: uz_sysmon_ps_t

.. doxygenfunction:: uz_sysmon_ps_init

.. doxygenfunction:: uz_sysmon_ps_read_temperature

.. doxygenfunction:: sysmon_ps_read_vcc_psint_lp_volt
    
.. doxygenfunction:: sysmon_ps_read_vcc_psint_fp_volt

.. doxygenfunction:: sysmon_ps_read_vcc_psaux_volt










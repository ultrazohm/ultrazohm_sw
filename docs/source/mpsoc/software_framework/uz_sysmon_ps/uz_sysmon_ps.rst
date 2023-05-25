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







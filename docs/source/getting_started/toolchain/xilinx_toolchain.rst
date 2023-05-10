.. _XilinxToolchain:

================
Xilinx Toolchain
================

#. Install Vivado and Vitis 2020.1: `Download Link <https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis/archive-vitis.html>`_ (Xilinx account required)

    .. image:: ./images_installation/vitis_website1_2022.png

#. Choose Name, Address, E-Mail, and the rest of the data
#. File ``Xilinx_Unified_2022.2_1014_8888_Win64.exe`` run. Click Next
#. Select Download and Install Now and sign in with your Xilinx user account. Click Next

    .. image:: ./images_installation/vitis_website2_2022.png

    .. note::

      If the User Authentication in the installer results in an error, eventhough the Xilinx account is valid, an alternative installer without the need to sign in can be downloaded.
   
    .. image:: ./images_installation/vitis_website2_5_2022.png

#. Select the specific products

    .. image:: ./images_installation/vitis_website3_2022.png

#. Install what you want and what you need. It is recommended to install as shown below. Uncheck `System Generator for DSP` and do not install it because this is not used and can lead to errors in MATLAB since this is a MATLAB-Toolbox. To reduce the required disk space, it is sufficient to only install the **Zynq UltraScale+ MPSoC** Devices. Other devices can be added later, but cannot be removed. 

    .. image:: ./images_installation/vitis_website4_2022.png

#. Agree to all license agreements, terms, and conditions. Click Next

    .. image:: ./images_installation/vitis_website5_2022.png

#. Specify where to install

    .. image:: ./images_installation/vitis_website6_2022.png

#. Install

    .. image:: ./images_installation/vitis_website7_2022.png
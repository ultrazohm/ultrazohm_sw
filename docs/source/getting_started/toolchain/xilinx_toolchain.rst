.. _XilinxToolchain:

================
Xilinx Toolchain
================

#. Install Vivado and Vitis 2022.2: `Download Link <https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis/2022-2.html>`_ (Xilinx account required)
#. Choose ``Xilinx Unified Installer 2022.2: Windows Self Extracting Web Installer`` or ``Xilinx Unified Installer 2022.2: Linux Self Extracting Web Installer`` depending on your operating system

    .. image:: ./images_installation/vitis_website1_2022.png

#. Choose Name, Address, E-Mail, and the rest of the data
#. Windows: run the file ``Xilinx_Unified_2022.2_1014_8888_Win64.exe`` and click next
#. Linux: right click on ``Xilinx_Unified_2022.2_1014_8888_Lin64.bin``, go to Permissions and check the box ``Allow executing file as program``. Then call the file as a program in the terminal with ``./Xilinx_Unified_2022.2_1014_8888_Lin64.bin``.
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

#. After the installation, apply the following bugfix: `https://support.xilinx.com/s/article/000034848?language=en_US`_
#. Download the .zip file from the support page
#. Navigate to your Vitis installation (e.g., ``D:\Xilinx\Vitis\2022.2``) and copy the content of the .zip file to this folder (override existing files in the scripts folder inside Vitis installation)

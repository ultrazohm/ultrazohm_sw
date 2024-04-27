========
Java JDK
========

.. _install_java:

Installation
============

#. `Download <https://jdk.java.net/17/>`_ and install newest JDK version for your OS from Open jdk
#. Unzip the folder and move it to your program files (e.g. ``C:\Program Files\Java``)
#. Add your JDK installation folder (e.g. ``C:\Program Files\Java\jdk-17.0.2\bin``) to your system PATH variable

   .. note:: For more information regarding the system PATH, see e.g. https://java.tutorials24x7.com/blog/how-to-install-openjdk-17-on-windows

#. Open your terminal and check the installed java version:

   ..	image:: ./images_install/terminal_check_java_version.png

Improve display scaling
=======================

To improve the scaling and the aliasing of the GUI on Windows on High-DPI monitors, follow the steps below.

#. Locate your latest Java-JDK folder (e.g. ``C:\Program Files\Java\jdk-17.0.2\bin``).
#. Look for the executable file ``java.exe`` and right click on it and select **Settings**.
#. Got to the **Compatibility** tab and click on **Change high dpi-settings**.
#. Check the box at the bottom and select **system** in the dropdown menu.
#. Save the changes.
#. Follow the exact same procedure for the ``javaw.exe`` executable file in the ``\bin`` folder.
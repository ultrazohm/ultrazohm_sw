======================
Problems and Solutions
======================

Cannot support older hw_server version
--------------------------------------

* This happens if you want to connect from Vivado to the ILA:

  ..	image:: ./images_problems/problems0.png

* Or if you want to load the MPSoC via JTAG:

  ..	image:: ./images_problems/problems1.png

* This error occurs if you have several Xilinx/Vivado versions on your computer (maybe running also in parallel).
* Explanation: Each Vivado version has its own hardware server (hw_server). If, for example, the older Vivado was running (even if it is already closed), a new/other Vivado version cannot be used to connect to a target.
* Solution: Go to the task manager, search for ``hw_server.exe``, and terminate this task. As soon as this task is closed (or the computer is restarted) a new hw_server from another/new Vivado version can be opened.

  ..	image:: ./images_problems/problems2.png

* It is not possible with Xilinx/Vivado to use different hw_server instances for different Vivado versions.



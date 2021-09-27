======================
Problems and Solutions
======================

Cannot support older hw_server version
--------------------------------------

	• This happens if you want to connect from Vivado to the ILA:

	..	image:: ./images_problems/problems0.png
	
	• Or if you want to load the MPSoC via JTAG:
	
	..	image:: ./images_problems/problems1.png
	
	• This error occurs, if you have several Xilinx/Vivado versions on your computer (maybe running also in parallel).
	• Explanation: Each Vivado version has his own Hardware server (hw-server), if e.g. the older Vivado was running (even it is already closed), a new/other Vivado version not be used to cennect to a target.
	• Solution: Go to the task manager, and search for "hw_server.exe" and close the task. As soon as this task was closed (or the computer was restarted) a new hw_server from another/new Vivado version can be opened.

	..	image:: ./images_problems/problems2.png

	• It is not possible with Xilinx/Vivado, to use with different Vivado versions, different hw_server.

Coming soon
-----------


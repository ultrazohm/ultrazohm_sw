.. _dig_incEncoder:

=============================
Digital Incremental Encoder
=============================

..	toctree::
	:maxdepth: 1
	:caption: Revisions
   
	incr_encoder_v1
	incr_encoder_v2_rev02


Before first use
----------------------------
* Solder D-Sub 9 pin cable
  
.. image:: incr_encoder_general/incr_encoder_dsub_top.jpg
   :width: 300
.. image:: incr_encoder_general/incr_encoder_dsub_bot.jpg
   :width: 300

Pinout 
"""""""""""""""""""""""""""
=====  =========  =================
Pin     D-Sub 9    Kubrich Encoder 
=====  =========  =================
0+      3           blue
0-      4           red
A+      8           green
A-      7           yellow
B+      5           grey
B-      9           pink
Vcc     2           brown
GND     1           white
=====  =========  =================


* Program CPLDs with firmware, see :ref:`label_cpld_programming` for details


Compatibility 
----------------------
* Slots D1 to D5 can be used without limitations, D5 is suggested


See also
"""""""""""""""
* :ref:`label_cpld_programming`


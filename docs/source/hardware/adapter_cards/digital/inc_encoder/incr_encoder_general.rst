.. _dig_incEncoder:

===========================
Digital Incremental Encoder
===========================

Source
------

- `Incremental encoder repository <https://bitbucket.org/ultrazohm/uz_d_incr_encoder>`_

..  toctree::
    :maxdepth: 1
    :caption: Revisions
   
    incr_encoder_v1
    incr_encoder_rev02
    incr_encoder_rev03
    incr_encoder_rev04


Functionality
-------------

* Connects 1-3 incremental encoder to the FPGA
* Provides isolated 5V supply to encoder
* Reads differential signals from encoder

Connector Male D-Sub 9
-----------------------

* Solder D-Sub 9 Male pin cable
  
.. image:: incr_encoder_general/incr_encoder_dsub_top.jpg
   :width: 300
.. image:: incr_encoder_general/incr_encoder_dsub_bot.jpg
   :width: 300

Pinout
""""""

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


D-Sub 9 Male Connector for soldering 
""""""""""""""""""""""""""""""""""""""

- https://www.mouser.de/ProductDetail/636-171-009-102L001
- https://www.mouser.de/de/ProductDetail/NorComp/171-009-103L001?qs=pHTW2tU%2Fyq5HYqXsR83XCg%3D%3D

D-Sub 9 Housing 
"""""""""""""""

- https://www.mouser.de/ProductDetail/571-1991253-9
- https://www.conrad.de/de/p/tru-components-tc-a-ft-09-203-1586438-d-sub-gehaeuse-polzahl-num-9-1-st-1586438.html

Compatibility 
-------------

* Slots D1 to D5 can be used without limitations, D5 is suggested
* Program CPLDs with firmware, see :ref:`label_cpld_programming` for details

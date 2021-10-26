===================================
Ordering Process with SMT Assembly
===================================

This section will guide you through the ordering process at JLCPCB with the intend to choose SMT assembly. It is useful to mention that no additional setup costs 
arise for basic parts (resistors, diodes, capacitors). On the other hand for all extended parts there will be a setup cost of 3$ each. 

1. Go to `JLCPCB`_ and sign in with your account 
2. Go to your shopping cart and choose ``Add new item`` 

.. figure:: pictures/Add_New_Item.png 
    :width: 700
    :class: with-shadow

    JLC - Add New Item

3. Click on ``Add gerber file`` and upload your Gerber and NC Drill files as .zip 

.. figure:: pictures/Add_Gerber_File.png 
    :width: 700 
    :class: with-shadow

    JLC - Add Gerber File

4. Choose your preferred settings and quantity for the PCB you want to order 
5. Scroll down, choose ``SMT Assembly``, select the side that should be assembled (usually the top side) and click on ``Confirm`` 

.. note:: When choosing SMT assembly some settings are not available e.g. gold fingers. If necessary change them to fit JLC's requirements 

.. figure:: pictures/SMT_Assembly.png 
    :width: 700 
    :class: with-shadow

    JLC - SMT Assembly

6. Now upload your BOM and Pick and Place (CPL) files and click on ``Next`` 

.. figure:: pictures/Upload_BOM_CLP.png 
    :width: 700 
    :class: with-shadow

    JLC - Upload BOM and CLP

7. Check if everything in the shown list is correct and click on ``Next`` 

.. figure:: pictures/Component_Check.png 
    :width: 700 
    :class: with-shadow

    JLC - Component Check

8. Check the orientation of the components in the review window (e.g. red and white dot should be on the same side, if not adjust the rotation in the Pick and Place file in Altium)

.. note:: The orientation of parts will be checked by JLC after submission and adjusted manually according to the orientation mark (the dot ° on pin 1).

<<<<<<< HEAD
.. figure:: pictures/Component_Orientation.png 
=======
.. figure:: pictures/Component_Orientation.png
>>>>>>> 1788c3821dc3abcd7113271072536012b452fdc0
    :width: 700 
    :class: with-shadow

    JLC - Component Orientation

9. Press ``Save To Cart`` 
10. Click on ``Product Details`` to check your settings. You may also adjust the quantity of PCB's before checkout if necessary. To proceed click ``Secure Checkout`` 

.. figure:: pictures/Secure_Checkout.png 
    :width: 700 
    :class: with-shadow

    JLC - Secure Checkout

11. Follow the steps of the delivery and payment 

.. tip:: The recommended payment is credit card, since paypal has very bad current exchange rates and the recommended delivery method is `DHL Express Priority (DDP=Delivered Duty Paid) <https://en.wikipedia.org/wiki/Incoterms#DDP_%E2%80%93_Delivered_Duty_Paid_(named_place_of_destination)>`_.

.. figure:: pictures/Shipping.png 
    :width: 700 
    :class: with-shadow

    JLC - Shipping

.. note:: After JLC shipped the manufactured PCBs and you received the shipping number, a custom declaration (Zollvoranmeldung) has to be done for this shipment via `DHL Express website <https://www.dhl.de/de/geschaeftskunden/express/produkte-und-services/formular-zollabfertigung.html>`_. This is to avoid the package getting stock in customs.
 
.. _JLCPCB: https://jlcpcb.com/
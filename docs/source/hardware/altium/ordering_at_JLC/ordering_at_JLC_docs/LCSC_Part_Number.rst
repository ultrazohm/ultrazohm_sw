============================
Adding the LCSC Part Number
============================

LCSC is JLC's supplier for components. These can be found in `JLC's component library <https://jlcpcb.com/parts>`__. There, every component has
a unique part number called **JLCPCB Part #** (formerly also LCSC Part #). This number is going to be important for the BOM, since you can only use these components for a SMT assembled PCB.
Therefore, every component of the UltraZohm library has a parameter called **LCSC part number** that later needs do be included in the BOM. 

.. figure:: pictures/LCSC_Part_Number.png 
    :width: 1200 
    :class: with-shadow

    Altium - Parameter LCSC Part Number

If there is no LCSC part number yet, you have to pick a suitable component from `JLC's component library <https://jlcpcb.com/parts>`__ 
and add the LCSC part number to the parameter in the UltraZohm library as shown in the screencast below.

.. note:: It might be not obvious but the availability of JLC's components is a major constraint, since it may vary and you have no possibility to get any other parts than those available in their library. It is also possible that components might be out-of-stock without change of re-stocking. Therefore, it is strongly recommended to use parts that have as many pin- and footprint-compatible replacements available as possible.

.. figure:: screencasts/update_lcsc.gif 
       :width: 1200

       Add LCSC Part Number

.. warning:: If the LCSC part number was added after the component was placed in the project, the parameter has to be updated. Follow the screencast below to update the parameter.
    
    .. figure:: screencasts/update_Parameter.gif
        :width: 1200

        Altium - Update Parameter

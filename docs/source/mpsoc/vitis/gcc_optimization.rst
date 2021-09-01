===================================
Optimization Levels of the Compiler
===================================

* You can tell the compiler to use different levels of optimization.
* UltraZohm default for R5 is -O2
* UltraZohm default for A53 is -O3
* It is recommended to keep these options as they are.   
* `Introduction to optimization levels <https://www.linuxtopia.org/online_books/an_introduction_to_gcc/gccintro_49.html>`_

**Step-by-step**
^^^^^^^^^^^^^^^^^^

Open the project properties 

.. image:: ./images_problems/include_math_lib1.png
   :height: 400

Change the optimization level by following the steps:

1. C/C++ build -> Settings
2. ARM R5 gcc compiler -> Optimization
3. Optimization Level -> pull down menu to chose the desired level
4. Apply and Close

..	image:: ./images_problems/gcc_optimization_level.png

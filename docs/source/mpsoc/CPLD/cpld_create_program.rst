.. _label_cpld_create_program:

================================
Create a CPLD program using ABEL
================================

The main goal of this section is to describe the necessary steps for creating a simple program for the CPLDs on the UltraZohm. 
All signals from the FPGA to the Digital Adapter cards have to pass through the CPLDs. 

Everything is programmed inside the .abl file. Here we can set which ports are inputs or outputs and use logic combinations to create the desired behavior. 

Step-by-step
------------

0. Install the **ispLEVER Classic** software from Lattice and clone the CPLD repository, see :ref:`install_lattice` for details. 

#. Create a new branch in the repository, e.g. ``feature/project_name``. 

#. Inside the CPLD repository, create a copy of an existing project folder, e.g. ``optical_14tx_4rx``.

#. Rename the folder to your project name, try to use a meaningful name.

#. Delete all html and jed files from your project folder. Only ``top_level.abl`` and ``optical_14tx_4rx.syn`` should be left.

#. Rename the project file to match your project folder name: ``uz_cpld_project_name.syn``. 

    .. image:: create_cpld_program/folder_structure.jpg

#. Open the top_level.abl file. In the beginning, all pins are defined and assigned to a physical pin on the CPLD.   
  
  - ``fpga_00`` .. ``fpga_29`` pins are connected to the FPGA/Zynq UltraScale+
  - ``d_00`` .. ``d_29`` pins are connected to the digital adapter 

  The numbering is zero-based and equivalent to the one in Vivado and in the Altium schematics of the Carrier Board and the Digital Adapter Cards. **Do not change this part. It is the same in all projects.**

    .. code-block::  

        " PIN ASSIGNMENTS 
        " FPGA pins
        fpga_00 pin 3;
        ... 
        fpga_29 pin 98;

        " Digital Adapter pins
        d_00 pin 50;
        ... 
        d_29 pin 70;


7. At the end of the file, there is the section that defines the logic. In the simplest case, this is just an assignment, in the example below ``fpga_00`` is an input and assigned to the output ``d_00``, and vice-versa for pins ``d_29`` and ``fpga_29``. 

    .. code-block:: 

        EQUATIONS
        d_00 = fpga_00;
        fpga_29 = d_29; 


#. Is it also possible to create combinational logic of multiple inputs. The word ``node`` is an ABEL keyword and creates a signal. This can simplify the logic. The compiler will usually resolve those signals to a combination of inputs only. In the example below, the output is enabled, if ``fpga_26`` and ``fpga_27`` are 0, while ``fpga_28`` and ``fpga_29`` are 1. 

    .. code-block:: 

        enable_signal node; 

        EQUATIONS
        enable_signal = !fpga_26 & !fpga_27 & fpga_28 & fpga_29;
        d_11 = fpga_11 & enable_signal; 

#. Use the following logic to create an interlocking functionality, e.g. for the upper and lower switch of a half-bridge. In this case, the output 
   
  - ``d_00`` is high when ``fpga_00 = 1`` and ``fpga_01 = 0``
  - ``d_00`` is low in all other cases, e.g. if ``fpga_00 = 1`` and ``fpga_00 = 1``

    .. code-block:: 

        EQUATIONS
        d_00 = fpga_00 & !fpga_01; 
        d_01 = fpga_01 & !fpga_00; 

10. Now, open the project file ``uz_cpld_project_name.syn`` with ispLEVER Classic and double-click on **JEDEC File** to create the bitstream for the CPLD. 

    .. image:: create_cpld_program/isplever_first_open.jpg

#. ispLEVER will prompt you asking which constraints to use. Simply press ``Import`` to import them from the ``top_level.abl`` file. 

    .. image:: create_cpld_program/isplever_import_constraints.jpg
    
#. After successful compilation, it should look like this. 
    
    .. image:: create_cpld_program/isplever_successful_compile.jpg
    
#. The folder is quite cluttered now, but we only track the highlighted files in git, i.e. 

  - ``top_level.abl`` (main source file, including constraints and logic)
  - ``uz_cpld_project_name.syn`` (project file)
  - ``uz_cpld_project_name.html`` (report)
  - ``uz_cpld_project_name_rpt.html`` (report)
  - ``uz_cpld_project_name_toc.html`` (report)
  - ``uz_cpld_project_name.jed`` (CPLD bitstream)

    .. image:: create_cpld_program/folder_structure_after_compile.jpg
      :height: 700

14. The file ``uz_cpld_project_name.html`` is the documentation of the crated CPLD program and contains a summary of all settings, e.g. which pin in an input or an output.

    .. image:: create_cpld_program/isplever_input_output_signal_list.jpg
      :height: 800      

#. The report also includes the resulting equations under the tap **PostFit_Equations**. As mentioned above, the ``enable_signal`` was resolved into a combination of input pins. 

    .. image:: create_cpld_program/isplever_postfit_equations.jpg

#. If the report matches the expected outcome, the job in ispLEVER is done. You can program the CPLD as described in :ref:`label_cpld_programming`.

#. After testing it on the UltraZohm, commit your new or modified project to the git repository and open a pull-request. 

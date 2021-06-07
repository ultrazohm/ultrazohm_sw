.. _onboarding:

==============================
How to contribute (Onboarding)
==============================

This page describes how to contribute to the UltraZohm project and serves as a guideline on how to onboard new developers.
The page mostly curates the documentation.

Toolchain installation
**********************

#. Install :ref:`Git`
#. Install the :ref:`XilinxToolchain`
#. Install :ref:`vscode_remote_container`
#. Install latest `Java <https://java.com/de/>`_

Community & git
***************

#. Join the Slack channel by asking a community member for an invite or request access by mail (info@ultrazohm.com) 
#. Create a Bitbucket account `on the bitbucket homepage <https://www.bitbucket.com>`_ since the UltraZohm is hosted there (https://www.bitbucket.org/ultrazohm/ultrzohm_sw) 
#. Ask for your Bitbucket account to be added as a User in Bitbucket
#. Read :ref:`ProjectStructure` to get familiar with the naming conventions and structure of the community
#. Do the Atlassian git tutorials to familiarize yourself with the Bitbucket workflow and git:
   
   *  `Tutorial Part 1 git basics <https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud>`_
   *  `Tutorial Part 2 code review <https://www.atlassian.com/git/tutorials/learn-about-code-review-in-bitbucket-cloud>`_
   *  `Tutorial Part 3 branches <https://www.atlassian.com/git/tutorials/learn-branching-with-bitbucket-cloud>`_
   *  `Tutorial Part 4 revert <https://www.atlassian.com/git/tutorials/learn-undoing-changes-with-bitbucket>`_

UltraZohm Setup & tutorials
***************************

#. Read :ref:`SystemOverview` to get a high level idea what the UltraZohm is about.
#. Follow the :ref:`UltraZohmSetup` guide to setup a local workspace
#. Do the UltraZohm :ref:`Tutorials`

Make your first contribution
****************************

#. Read :ref:`contribution` to understand the UltraZohm workflow (git flow)
#. Read the UltraZohm specific documentation for :ref:`Bitbucket`
#. Make your first contribution by adding yourself to the list of :ref:`Contributors`
#. Request in the Slack channel to be added to the contributor user group (see :ref:`ProjectStructure`)

   #. Create a new feature branch in Bitbucket with the name ``Onboarding_FirstNameSurname``, i.e. ``Onboarding_MaxMustermann``
   #. Open the repository with the :ref:`vscode_remote_container`
   #. Build the documentation by invoking ``make docs`` (see :ref:`howToDocs` for reference)
   #. Add your name to the ``contributors.rst`` file located at ``ultrazohm_sw/docs/source/general``
   #. Save the file and build the docs again, confirm that there are no warnings
   #. Commit the changed file with a descriptive commit message (e.g., **Added MaxMustermann to the contributors list**
   #. Push your new branch to the remote repository
   #. Create a pull-request and assign a maintainer as reviewer (ak in the Slack channel if you are not sure)
   #. A maintainer will review your change, accept the PR and merge it
   #. You now contributed to the UltraZohm project for the first time!

Additional information
**********************

#. The UltraZohm project uses a `Xilinx Zynq UltraScale+ MPSoC <https://www.xilinx.com/products/silicon-devices/soc/zynq-ultrascale-mpsoc.html>`_.

   * A good starting point for the development of the Xilinx Zynq UltraScale+ MPSoC is `Exploring Zynq® MPSoC <https://www.zynq-mpsoc-book.com>`_ 
   * This book walks the reader through all the important aspects of the Xilinx software stack, the multi-processor processing system, and the powerful array of programmable hardware.

#. Useful documents include:
  
     * `Zynq UltraScale+ MPSoCSoftware Developer Guide <https://www.xilinx.com/support/documentation/user_guides/ug1137-zynq-ultrascale-mpsoc-swdev.pdf>`_
     * `Zynq UltraScale+ Device Technical Reference Manual <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf>`_ 
     * `UltraScale Architecture Memory Resources User Guide <https://www.xilinx.com/support/documentation/user_guides/ug573-ultrascale-memory-resources.pdf>`_


MPSoC Software
--------------

#. Do the :ref:`how_to_create_ipcore_driver` tutorial
#. Familiarize yourself with the :ref:`UltraZohm Software Development Guidelines <software_development_guidelines>`.
#. Additional documentation includes:
    
   * `Modern C, Jens Gusted <https://gforge.inria.fr/frs/download.php/latestfile/5298/ModernC.pdf>`_
   * Clean Code, A Handbook of Agile Software Craftsmanship, Robert C Martin, 2009
   * Making Embedded Systems, Elecia White, 2011
   * Test-Driven Development for Embedded C, James W. Grenning, 2011
   * Guidelines for the Use of the C Language in Critical Systems, ISBN 978-1-906400-10-1 (paperback), ISBN 978-1-906400-11-8 (PDF), March 2013.
  

MPSoC FPGA
----------


Lattice CPLD
************

#. Install :ref:`Lattice`, if you are planing to program the CPLD. 
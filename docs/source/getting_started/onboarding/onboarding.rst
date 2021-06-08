.. _onboarding:

==========
Onboarding
==========


This page describes how to use and contribute to the UltraZohm project and serves as a guideline on how to onboard new developers.
The page mostly curates the documentation.
You should start here and follow the steps one by one.

How to use the UltraZohm
========================

Toolchain installation
**********************

The toolchain for the UltraZohm project consists of multiple tools.
Please install all of them in the newest version, except for the Xilinx toolchain which is required in the specified version.

#. Install :ref:`Git`
#. Install the :ref:`XilinxToolchain`
#. Install :ref:`vscode_remote_container`
#. Install latest `Java <https://java.com/de/>`_

Community & git
***************

The UltraZohm project is a community based open source project and the `repository is hosted on Bitucket <https://www.bitbucket.org/ultrazohm/ultrzohm_sw>`_.
We use `Slack <https://slack.com/intl/de-de/>`_ as our primary communication channel.
Follow these steps to join the community and understand how git works.

#. Join the Slack channel by asking a community member for an invite or request access by mail (info@ultrazohm.com) 
#. Create a Bitbucket account `on the bitbucket homepage <https://www.bitbucket.com>`_
#. Ask for your Bitbucket account to be added as a **User** in Bitbucket in the Slack channel
#. Read :ref:`ProjectStructure` to get familiar with the naming conventions and structure of the community
#. Complete the Atlassian git tutorials to familiarize yourself with the Bitbucket workflow and git:
   
   *  `Tutorial Part 1 git basics <https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud>`_
   *  `Tutorial Part 2 code review <https://www.atlassian.com/git/tutorials/learn-about-code-review-in-bitbucket-cloud>`_
   *  `Tutorial Part 3 branches <https://www.atlassian.com/git/tutorials/learn-branching-with-bitbucket-cloud>`_
   *  `Tutorial Part 4 revert <https://www.atlassian.com/git/tutorials/learn-undoing-changes-with-bitbucket>`_

.. warning:: Using and understanding how git and Bitbucket work are mandatory for working with the UltraZohm!

UltraZohm Setup & tutorials
***************************

The following steps set up your UltraZohm and provide tutorials to use different functions of the system.

#. Refer to :ref:`SystemOverview` to get a high level idea what the UltraZohm is about.
#. Follow the :ref:`UltraZohmSetup` guide to setup a local workspace
#. Complete the UltraZohm :ref:`Tutorials`

Your UltraZohm is now set up and ready to be used.
Explore the documentation for more information.
Some useful places to start:

- :ref:`vitis`
- :ref:`ip_cores`
- :ref:`carrier_board`
- :ref:`adapter_cards`

How to contribute
=================

Make your first contribution
****************************

These steps will grant you write access to the repository and you will make your first contribution to the UltraZohm project.
Note that not every user is required to become a contributor, but everybody is encouraged to do so!
Please complete the steps if you are planning to contribute to the project.
You will make your first contribution by adding yourself to the list of :ref:`Contributors` in the following steps.

#. Read :ref:`contribution` to understand the UltraZohm workflow (git flow)
#. Read the UltraZohm specific documentation for :ref:`Bitbucket`
#. Request access to the contributor user group by asking in the Slack channel (see :ref:`ProjectStructure`)
#. Create a new feature branch in Bitbucket with the name ``contributor_name``
#. Open the repository with the :ref:`vscode_remote_container`
#. Build the documentation by invoking ``make docs`` (see :ref:`howToDocs` for reference)
#. Add your name to the ``contributors.rst`` file located at ``ultrazohm_sw/docs/source/general``
#. Save the file and build the docs again, confirm that there are no warnings
#. Commit the changed file with a descriptive commit message (e.g., *Added MaxMustermann to the contributors list*)
#. Push your commit to the remote repository
#. The :ref:`ci` will run. Do not worry, you can not break anything in this step! If there are errors, inspect the log or ask in the Slack channel
#. Create a pull-request and assign a maintainer as reviewer (ask in the Slack channel if you are not sure)
#. A maintainer will review your change, accept the PR, and merge it
#. You now contributed to the UltraZohm project for the first time!

Contribution to MPSoC Software
******************************

#. Complete the :ref:`how_to_create_ipcore_driver` tutorial
#. Use the :ref:`UltraZohm Software Development Guidelines <software_development_guidelines>` as a reference
#. Use `Modern C, Jens Gusted <https://modernc.gforge.inria.fr/>`_ (free download) to refresh your C knowledge
  
Contribution to MPSoC FPGA
**************************

Contributions to the FPGA can either be an IP-Core or structural changes to the default Vivado project.
Changes to the Vivado project (everything in ``ultrazohm_sw/vivado``) can not be merged into the project by creating a pull request! If you plan on changing the Vivado project you have to get in touch with the maintainers in Slack.

Hardware (PCB)
**************

Refer to :ref:`altium`.

Additional information
======================


#. The UltraZohm project uses a `Xilinx Zynq UltraScale+ MPSoC <https://www.xilinx.com/products/silicon-devices/soc/zynq-ultrascale-mpsoc.html>`_.

   * A good starting point for the development of the Xilinx Zynq UltraScale+ MPSoC is `Exploring Zynq® MPSoC <https://www.zynq-mpsoc-book.com>`_ 
   * This book walks the reader through all the important aspects of the Xilinx software stack, the multi-processor processing system, and the powerful array of programmable hardware.

#. Useful documents include:
  
     * `Zynq UltraScale+ MPSoCSoftware Developer Guide <https://www.xilinx.com/support/documentation/user_guides/ug1137-zynq-ultrascale-mpsoc-swdev.pdf>`_
     * `Zynq UltraScale+ Device Technical Reference Manual <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf>`_ 
     * `UltraScale Architecture Memory Resources User Guide <https://www.xilinx.com/support/documentation/user_guides/ug573-ultrascale-memory-resources.pdf>`_
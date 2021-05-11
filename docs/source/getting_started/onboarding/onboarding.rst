==========
Onboarding 
==========

This page serves as an onboarding for new users who want to contribute to the UltraZohm project. 

#. Read the :ref:`SystemOverview` and :ref:`ProjectStructure` pages, to get an understanding about the organization of the UltraZohm project.
#. The UltraZohm project uses a `Xilinx Zynq UltraScale+ MPSoC <https://www.xilinx.com/products/silicon-devices/soc/zynq-ultrascale-mpsoc.html>`_.

   * A good starting point for the development of the Xilinx Zynq UltraScale+ MPSoC is the `Exploring Zynq® MPSoC <https://www.zynq-mpsoc-book.com>`_ 
   * This book walks the reader through all the important aspects of the software stack, the multi-processor processing system, and the powerful array of programmable hardware.
   
#. The UltraZohm project is managed via GitHub/Bitbucket. Therefore a Bitbucket account is required. If you do not have one, create one `on the bitbucket homepage <https://www.bitbucket.com>`_.
#. To familiarize yourself with the Bitbucket workflow (clones, issues, commits, pull-requests, etc.) it is advised to follow the Atlassian git tutorials.
   
   *  `Tutorial Part 1 <https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud>`_
   *  `Tutorial Part 2 <https://www.atlassian.com/git/tutorials/learn-about-code-review-in-bitbucket-cloud>`_
   *  `Tutorial Part 3 <https://www.atlassian.com/git/tutorials/learn-branching-with-bitbucket-cloud>`_
   *  `Tutorial Part 4 <https://www.atlassian.com/git/tutorials/learn-undoing-changes-with-bitbucket>`_

#. Follow the installation process for :ref:`Git`. Documentation and additional tutorials for Git are provided there aswell. 
#. Request access to the UltraZohm Bitbucket workspace from your supervisor.
#. **(Optional)** Follow the installation process for :ref:`Sourcetree`. This is a graphical client to simplify the use of Git. If you are comfortable with using the **Git Bash**, this installation process is not necessary, but recommended.  
#. Read the UltraZohm specific documentation for :ref:`Bitbucket`. 
#. After Bitbucket has been set up and its workflow understood, continue with the installation of the :ref:`XilinxToolchain` and :ref:`VivadoLicense`.

   * These tools are required for the development of the `Xilinx Zynq UltraScale+ MPSoC <https://www.xilinx.com/products/silicon-devices/soc/zynq-ultrascale-mpsoc.html>`_.
   * Useful documents include:
  
     * `Zynq UltraScale+ MPSoCSoftware Developer Guide <https://www.xilinx.com/support/documentation/user_guides/ug1137-zynq-ultrascale-mpsoc-swdev.pdf>`_
     * `Zynq UltraScale+ Device Technical Reference Manual <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf>`_ 
     * `UltraScale Architecture Memory Resources User Guide <https://www.xilinx.com/support/documentation/user_guides/ug573-ultrascale-memory-resources.pdf>`_

#. Familiarize yourself with the :ref:`UltraZohm Software Development Guidelines <software_development_guidelines>`. Additional documentation includes:
    
   * `Modern C, Jens Gusted <https://gforge.inria.fr/frs/download.php/latestfile/5298/ModernC.pdf>`_
   * Clean Code, A Handbook of Agile Software Craftsmanship, Robert C Martin, 2009
   * Making Embedded Systems, Elecia White, 2011
   * Test-Driven Development for Embedded C, James W. Grenning, 2011
   * Guidelines for the Use of the C Language in Critical Systems, ISBN 978-1-906400-10-1 (paperback), ISBN 978-1-906400-11-8 (PDF), March 2013.
  
#. Install :ref:`Lattice`.
#. Install the latest version of `Java <java.com>`_. 
#. Set up the UltraZohm workspace by following the :ref:`UltraZohmSetup` guide.
#. Work through the provided :ref:`Tutorials` to get a better understanding about the UltraZohm.
#. Every change to the project or new feature has to be documented. Therefore read the page :ref:`howToDocs`.

   * A local installation of the required extensions is possible, however not required.
   * Alternatively you can use remote containers in **Virtual Studio Code** by checking out :ref:`vscode_remote_container`.
   * Another alternative is using :ref:`Gitpod <Gitpod_chapter>`, which can be opened in the browser and thus requires no additional installations. 
  
#. To round up the onboarding you will include yourself in the list of :ref:`Contributors`. 

   #. Create a new feature branch with the name ``OnboardingFirstNameSurname``, i.e. ``OnboardingMaxMustermann``
   #. Access the docs either in VSCode, Gitpod or locally on your machine.
   #. Enter your name in the ``contributors.rst`` file located under ``../ultrazohm_sw/docs/source/general``
   #. Save the file and build the docs locally to confirm everything works as intended
   #. Commit the changed file with a descriptive title **OnboardingFirstNameSurname**
   #. Push your new branch to the remote
   #. Create a pull-request and assign as Reviewer your supervisor
   #. Merge the pull-request after your supervisor approved it
.. _vscode_remote_container:

========================
VS Code Remote Container
========================

`VS Code <https://code.visualstudio.com/>`_ is the recommended text editor for the UltraZohm project.
Using the `remote container extension <https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers>`_ allows for a consistent development environment with easy setup.
Further information:

- https://code.visualstudio.com/docs/remote/containers


Prerequisites
*************

- Install `docker <https://docs.docker.com/get-docker/>`_
- Install `VS Code <https://code.visualstudio.com/>`_
- Install `remote container extension <https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers>`_
- Clone the ``ultrazohm_sw`` repository

Running VSCode inside an Ubuntu distribution on Windows
*******************************************************

Setup
-----

The performance of using the remote container in VSCode on Windows is relatively slow. To speed this up significantly we will setup up the remote container and VSCode to run directly in the WSL2.

.. note:: For Windows users, this is highly recommended. Running VSCode on Windows all unit tests took over **10 minutes**. On Ubuntu, it took **8.2 seconds**.


#. Install the programs listed in the prerequisites.
#. Install the WSL2-Linux subsystem for windows with the ``Ubuntu`` distribution by entering the following command in the **cmd**-window.

    .. code-block:: console

       dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
       dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
       wsl --set-default-version 2
       wsl --install -d Ubuntu  

#. Open the Ubuntu terminal by typing ``Ubuntu`` in the window search.
#. Enter a new UNIX username and assign a password to this account.

    .. image:: Ubuntu_setup.png

#. Now you have access to the Ubuntu shell.
#. Install GIT LFS with the following commands.

    .. code-block:: console

       curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash
       sudo apt-get install git-lfs

#. On the root level create a new directory in which you will store all your repositories by typing in the Ubuntu shell. 

    .. code-block:: console

       mkdir uz

#. Enter this directory with

    .. code-block:: console

       cd uz
  
#. Clone the repository from the remote inside the ``uz`` directory (or any other repository)

    .. code-block:: console

        git clone https://bitbucket.org/ultrazohm/ultrazohm_sw.git

    .. note:: The repositories inside the Ubuntu subsystem and on Windows are two different local repositories. They do not sync automatically. You can only sync them via the ``push, pull`` etc. commands.

#. Open the settings of the docker desktop distribution and enable under ``Resources->WSL Integration`` the integration for Ubuntu distribution.

    .. image:: docker_setup_ubuntu.png

#. Add your git-credentials from your **Bitbucket Account** in the Ubuntu shell

    .. code-block:: console

       git config --global user.name "John Doe"
       git config --global user.email johndoe@example.com

#. Apply the changes and restart the computer.

Usage
-----

#. To use the remote container with VSCode inside the Ubuntu distribution open the Ubuntu shell and navigate to the local repository.

    .. code-block:: console

       cd uz

#. Open up VSCode 

    .. code-block:: console

       ls
       code .
    
    .. image:: open_vscode.png

#. VSCode will start. A prompt will pop up asking if the folder should be reopened in Container. Accept this.

    .. image::  reopen_container.png

#. If this prompt does not show up, press ``F1`` in VSCode and select ``Remote Containers: Rebuild Container``

    .. image:: reopen_container2. png

#. To open the file explorer inside the Ubuntu distribution use the following command in the directory you want to open. This may be necessary to copy pictures, files, etc. into the repository.

    .. code-block:: console

       explorer.exe .

.. note:: Sourcetree can not be natively installed in the Ubuntu distribution. The repository in the Ubuntu distro can be added to Sourctree. However, this is not advised since the performance is bad.
          It is recommended to either use the Ubuntu shell with the standard git-commands or the :ref:`git lense extension <vscode_remote_container_gitlense>`. 

Known issues in WSL
-------------------

.. note:: If you have issues with your git credentials in WSL, it is possible to link your WSL git installation to the windows git credential manager. As explained here: https://stackoverflow.com/questions/45925964/how-to-use-git-credential-store-on-wsl-ubuntu-on-windows Run this command in your wsl terminal.

    .. code-block:: console

        git config --global credential.helper "/mnt/c/Program\ Files/Git/mingw64/libexec/git-core/git-credential-manager-core.exe"
    
    
.. note:: On some machines the error ``error: RPC failed; curl 56 GnuTLS recv error (-24): Decryption has failed`` appears during ``git clone`` when connected via WiFi. This can be related to an out-of-date wifi driver https://github.com/microsoft/WSL/issues/4253#issuecomment-799902628. If updating the driver does not solve the issue, try to connect via VPN or LAN as a workaround. 


Usage
*****

- Start VS Code
- ``File`` -> ``Open Folder``
- Choose the ``ultrazohm_sw``
- A prompt opens up that asks if you want to open the folder in the container
- Click *Reopen in Container*
- VS Code restarts
- Development environment is ready to use

.. figure:: open_in_container.gif

  Open repository in remote container

Build documentation
-------------------

In VS Code:

- Menu: Terminal -> ``New Terminal``
- A Terminal opens which can be used, e.g., to build the documentation
- ``cd docs``
- ``make livehtml``
- A new browser window opens with a live preview of the documentation opens
- If you change the documentation and save it, the live preview rebuilds automatically
- Alternative: use ``make clean html`` to build manually

.. figure:: container_livehtml.gif

  Use ``make livehtml`` to create a live preview of the docs

Git
---

.. _vscode_remote_container_gitlense:

VS Code features a git extension (`gitlens <https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens>`_) that can be used to commit changes and see the timeline of a file.

.. figure:: container_git_commit.gif

  Commit changes from VS Code

.. figure:: container_gitlense.gif

  Use gitlense to inspect commits on a file


Alternatives 
************

Podman instead of Docker
------------------------

Using the remote container with Docker might lead to unwanted problems with file permissions on Linux and Docker runs as root by default.
`Podman <https://github.com/containers/podman>`_ can be used as a rootless alternative to Docker.

- `Podman installation <https://podman.io/getting-started/installation>`_
- `VS Code documentation to use podman instead of Docker <https://code.visualstudio.com/docs/remote/containers>`_
- To use, install Podman and write ``podman`` in the VS Code Setting ``Remote -> Container -> Docker Path``

.. note:: It might be possible to use Podman with WSL2 on Windows, yet this is not tested. See https://www.redhat.com/sysadmin/podman-windows-wsl2 

.. _Gitpod_chapter:

Cloud solution: Gitpod
----------------------

`Gitpod <https://gitpod.io>`_ can be used to start a VS Code workspace in the browser without any local installations required.

- `Open UltraZohm workspace in Gitpod <https://gitpod.io/#https://bitbucket.org/ultrazohm/ultrazohm_sw/src/main/>`_
- Login with your Bitbucket account
- The complete development environment as outlined in this document is automatically loaded (sphinx, ceedling)
- Just click the link and start development

.. figure:: gitpod_preview.gif

  Open repository in Gitpod workspace.
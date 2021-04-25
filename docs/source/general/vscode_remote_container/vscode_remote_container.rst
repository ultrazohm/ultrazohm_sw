.. _vscode_remote_container:

==================================================
VS Code Remote Container (Development environment)
==================================================

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

Terminal
--------

In VS Code:

- Menu: Terminal -> ``New Terminal``
- A Terminal opens which can be used, e.g., to build the documentation
- ``cd docs``
- ``make livehtml``
- A new browser window opens with a live preview of the documentation opens
- If you change the documentation an save, the live preview rebuilds automatically
- Alternative: use ``make clean html`` to build manually
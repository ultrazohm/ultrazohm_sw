======================
Continuous Integration
======================

The UltraZohm-Project uses two different build pipelines for continuous integration to test the builds of the UltraZohm software as well as the documentation.

    * Bitbucket test & deploy pipeline for docs
    * Drone test pipeline for Vivado and Vitis


Bitbucket pipeline
------------------

  * ``bitbucket-pipelines.yml`` configures the bitbucket pipeline
  * Pipeline steps to build the sphinx documentation on every *push* to the repository (all branches)
  * Pipeline steps to deploy the documentation to the web-server (docs.ultrazohm.com) after every merged pull request on *main*


.. mermaid::
  :caption: Setup of the bitbucket build pipeline.
  :align: center

  graph LR
    subgraph Bitbucket
    C -->|Successful?| B
    B[ultrazohm_sw] -->|Pipeline| C{Build}
    end
    C -->|Deploy| D(Server)
    D -->|nginx| E[docs.ultrazohm.com]

The build pipeline:

  * Pull the docker image with python
  * Installs the requirements for the build of the sphinx documentation
  * Builds the docs and treats all warnings as errors but keeps building to investigate the logs if the build fails
  * If the pipeline is trigger from ``main``

    * The ``build`` folder after ``make html`` is copied to the web server
    * Done with rsync deploy pipe
    * Variables for username, password and server path are stored as secret repository variables
    * Only accessible for admins: ``repository settings -> repository variables`` in bitbucket

.. literalinclude:: ../../../bitbucket-pipelines.yml
    :linenos:
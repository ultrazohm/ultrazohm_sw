======================
Continuous Integration
======================

The UltraZohm-Project uses two different build pipelines to test the builds of the UltraZohm software as well as the documentation (docs).

* The Bitbucket pipeline tests & deploys the docs
  
  * Tests the build of the sphinx docs
  * Deploys the docs of the main branch to docs.ultrazohm.com
  * Mirrors the branch to https://github.com/ultrazohm/ultrazohm_sw

* The Drone test pipeline builds UltraZohm Vivado and Vitis Project

  * Builds bitstream in Vivado (only main & develop branch)
  * Commits the vivado binarys (.xsa) to the repository and pushes the change (only on main)
  * Creates a new tag and a changelog, commits them to the repository and pushes the changes to bitbucket (only on main)
  * Exports the bitstream
  * Generates the Vitis workspace
  * Builds the software

.. _CI bitbucketPipeline:

Bitbucket pipeline (docs)
-------------------------

* ``bitbucket-pipelines.yml`` configures the Bitbucket pipeline
* Pipeline steps to build the sphinx documentation on **every** *push* to the repository (for all branches)
* Pipeline steps to deploy the documentation to the UltraZohm-Server (docs.ultrazohm.com) after every merged pull request on *main*
* Pipeline reports success or failure to Bitbucket repository (green / red symbol next to branch in Bitbucket)


.. mermaid::
  :caption: Setup of the Bitbucket build pipeline.
  :align: center

  graph LR
    subgraph Bitbucket
    C -->|Successful?| B
    B[ultrazohm_sw] -->|Pipeline| C{Build}
    end
    C -->|Deploy| D(UltraZohm-Server)
    D -->|nginx| E[docs.ultrazohm.com]

The build pipeline:

* Pulls the docker image with python
* Installs the requirements for the build of the sphinx documentation
* Builds the docs and treats all warnings as errors but keeps building to investigate the logs if the build fails
* If the pipeline is triggered from ``main``:

  * The ``build`` folder after ``make html`` is copied to the web server
  * Done with rsync deploy pipe 
  * Variables for username, password and server path are stored as secret repository variables
  * Only accessible for admins: ``repository settings -> repository variables`` in Bitbucket (``ultrazohm_sw`` repository)

.. literalinclude:: ../../../bitbucket-pipelines.yml
    :linenos:

Bitbucket pipeline (GitHub-Mirror)
**********************************

* Adds Github repository as remote repo
* Pushes current branch to https://github.com/ultrazohm/ultrazohm_sw
* A special UltraZohm Github Account (Login information in Keepass) pushes to the Github repository
* The account uses the Bitbucket pipeline SSH key (``ultrazohm_sw -> Repository settings --> SSH keys``, only visible to admins) to push to Github
* Github.com is added to ``Known hosts`` in ``ultrazohm_sw -> Repository settings --> SSH keys``


Drone pipeline (Software)
-------------------------

* Drone pipeline builds 


* Uses `Drone <www.drone.io>`_
* Drone has a Server and a Runner
* Drone Server is the bridge between Bitbucket, User and Runner (`ci.ultrazohm.com <www.ci.ultrazohm.com>`_)
* Runner (Docker runner, see `Drone docs <https://docs.drone.io/runner/docker/overview/>`_) polls the server and executes the build pipeline
* Server and Runner are used as Docker container on the UltraZohm Server
* Setup in Bitbucket **exactly** as in the `drone docs for Bitbucket <https://docs.drone.io/server/provider/bitbucket-cloud/>`_
* Permissions in the OAuth settings of the Bitbucket repository must match the drone docs
* ``drone/Docker-compose.yml`` in `uz_server_main <https://bitbucket.org/ultrazohm/uz_server_main/src/master/>`_ repository (only visible to admins) sets up Drone
* Changes in the docker-compose file are automatically transferred to the UltraZohm by using a rsync pipeline
* ``ssh`` to UltraZohm-Server, `cd` to ``/drone`` and use ``docker-compose up -d`` to restart the Drone Server and Runner after changes in the repository

How-to:

::

  ssh $username@ultrazohm.com
  cd $path/drone
  docker-compose up -d

Setup
*****

.. mermaid::
  :caption: Setup of the Drone pipeline
  :align: center

  graph BT
      ultrazohm_sw -->|Trigger Pipeline| A
      subgraph UltraZohm-Server
      A[Drone Server] -->|Pending Pipeline| B[Drone Runner]
      B --> C[Execute Pipeline]
      C -->|Report Status| A
      end
      A -->|Report Status| ultrazohm_sw

Drone Runner and Vivado Docker image
************************************

The Drone Runner starts a Docker Container for each pipeline step.
To use Vivado and Vitis, we use a costum Vivado docker image (``vivado:2020.1``).
There are two challenges with using Vivado and Vitis in a Docker container.

  * Xilinx license is locked to the MAC
  * Create license on `<xilinx.com/getlicense>`_
  * Lock the license to the MAC of the machine that executes the runner
  * The UltraZohm-Server license is locked to the Docker network ``drone_default`` (see ``docker network ls`` and ``docker network inspect host``)
  * Download the ``.lic`` file
  * Follow the instructions in `uz_server_drone <https://bitbucket.org/ultrazohm/uz_server_drone_server_agent/src/master/create_vivado_docker/>`_ repository (only for admins due to licensing & login information)
  * Make the network adapter that is used for the license MAC-lock to the Drone Runner
  * See `<https://docs.drone.io/runner/docker/configuration/reference/drone-runner-networks/>`_
  * E.g. DRONE_RUNNER_NETWORKS=drone_default

See the docker-compose file for details (`drone/docker-compose.yml <https://bitbucket.org/ultrazohm/uz_server_main/src/master/drone/docker-compose.yml>`_, only for admins due to login information in the file).
Following is an example docker-compose file without login information.
Note that the indentation is relevant since this is a ``yml`` file.
Furthermore, some configuration is specific to the UltraZohm-Server.

::

    version: '3.7'

    services:
      drone-server:
        container_name: drone_server
        image: drone/drone:1
        volumes:
          - /var/lib/drone:/data
          - /var/run/docker.sock:/var/run/docker.sock
        restart: always
        userns_mode: "host"
        environment:
        - DRONE_BITBUCKET_CLIENT_ID=$bitbucket_key
        - DRONE_BITBUCKET_CLIENT_SECRET=$bitbucket_secret
        - DRONE_RPC_SECRET=$common_secret
        - DRONE_SERVER_HOST=ci.ultrazohm.com
        - DRONE_SERVER_PROTO=https
        - DRONE_USER_CREATE=username:$username,admin:true
        networks:
          - frontend
        
      drone-runner:
        container_name: drone_runner
        image: drone/drone-runner-docker:1
        ports:
          - "3000:3000"
        volumes:
          - /var/run/docker.sock:/var/run/docker.sock
        restart: always
        userns_mode: "host"
        environment:
          - DRONE_RPC_PROTO=https
          - DRONE_RPC_HOST=ci.ultrazohm.com
          - DRONE_RPC_SECRET=$common_secret
          - DRONE_RUNNER_CAPACITY=1
          - DRONE_RUNNER_NAME=$runnerName
          - DRONE_LOGS_TRACE=true
          - DRONE_LOGS_PRETTY=true
          - DRONE_LOGS_COLOR=true
          - DRONE_RUNNER_NETWORKS=drone_default
          - DRONE_CPU_SET=1,2,3,4
          - DRONE_MEMORY_LIMIT=20000000000
        

    networks:
      frontend:
        external:
          name: frontend

Push back to repository
***********************

The drone pipeline pushes back to the ``ultrazohm_sw`` repository if a commit is made to main (through a pull request).
The pipeline:

- commits all binarys to the repo
- Creates a tag using `autotag <https://github.com/pantheon-systems/autotag>`_
- Settings for the tag: `conventional commits <https://www.conventionalcommits.org/en/v1.0.0/#examples>`_
- Pushes back to main using ``https``
- Creates ``CHANGELOG.md`` by using `auto-changelog <https://github.com/cookpete/auto-changelog>`_
- Commits the changelog
- Pushes back to main using ``https``
- The tag is on the commit of the binarys, the CHANLOG.md is one commit after the tag
- Commit message is fixed and starts with [skip ci] to prevent infinite CI loop

===========
How to docs
===========

The documentation for the UltraZohm uses `<https://www.sphinx-doc.org>`_.
Sphinx creates the documentation pages in html based on text files.
These text files use `reStructuredText <https://rest-sphinx-memo.readthedocs.io/en/latest/ReST.html>`_ (RST) as a markup language.
Sphinx takes the different RST files and builds them to the docs page.
The documentation is hosted on a web server, the build and deployment is handled by a :ref:`build pipeline <CI bitbucketPipeline>`.

.. note :: The online version on docs.ultrazohm.com is always the documentation for the **main** branch.
           If you build the documentation locally, you build the documentation for the specific branch!
           Building the documentation locally is also useful for writing the documentation and getting a preview of the changes.

Install
=======

To build and edit the documentation you need to:

* Install latest python version
* Install pip (included in current python versions)
* Install everything in the ``requirements.txt`` in ``/docs`` by invoking ``pip install -r requirements.txt`` in a command shell inside ``/docs``
* Build the documentation by invoking ``make html``
* You can open the docs in ``/docs/build/html/index.html``
* You can edit the documentation by using a text editor of your choice

.. tip:: Sometimes you might need to clean the output with ``make clean`` or clean build with ``make clean html``

.. tip:: We have added `sphinx-autobuild <https://github.com/executablebooks/sphinx-autobuild>`_ to the makefile. Therefore, you can use ``make livehtml`` instead of ``make html`` which opens a new browser that synchronizes live with changes that you make locally.

.. image:: https://images2.imgbox.com/ed/32/B0uTI8EZ_o.gif
  :width: 500
  :align: center
  :alt: Alternative text


.. note:: If ``make html`` or ``make livehtml`` do not work due to missing package errors, run ``pip install -r requirements.txt`` again. If this does not solve the problem please open an `issue <https://bitbucket.org/ultrazohm/ultrazohm_sw/issues>`_.

Video
*****

This video shows how to install python, the requirements and build the documentation.

.. youtube:: dxAlD-VzE0c

This video shows how to change something in the documentation, add a new page, commit the changes and create a pull request in bitbucket.

.. youtube:: pcG1XMzVDc8

Write the docs
==============

See `write the docs <https://www.writethedocs.org/guide/>`_ as a great resource on how to write documentation.
A good cheatsheet is located here: * `Example usage from Anaconda <https://docs.anaconda.com/restructuredtext/detailed/>`_ 


Style
*****

Do:

* Keep it simple
* Use simple language
* Describe the current state
* Focus on the interface
* Provide examples on how to use the module, software, PCB, ...
* Provide additional information in a dedicated section
* Have a download section with schematics, additional information, ...
* Use one line per sentece for cleaner git diffs

Don't:

* Write long and complicated sentences
* Add unnecessary chatter
* Chatter about what might change in the future (exception: roadmap)
* Mix interface with rational
* Mix implementation details and user interface
* Have random download links in text blocks
* Have random line breaks in the text

Common functions
****************

Use the following examples for reference on how to write the docs.
Basics:

Code block
^^^^^^^^^^

.. code-block:: rst

    .. code-block:: c

        void function(int argv);

.. code-block:: c

   void function(int argv);


Figures
^^^^^^^

.. code-block:: rst

     .. _labelName:

     .. figure:: figure.svg

       Caption.

Refernce:

.. code-block:: rst

    Reference ::numref:`labelName`.

Links
^^^^^

.. code-block:: rst

    `UltraZohm <ultrazohm.com>`_ 

Mermaid
^^^^^^^

You can and should use `mermaid <https://mermaid-js.github.io/mermaid/#/>`_ to create figures.
Mermaid figures are directly inserted into the docs and **searchable**!

.. code-block:: rst

    .. mermaid::

      graph TD
      A[Text]
      A --> B[More text]


.. mermaid::

  graph TD
  A[Text]
  A --> B[More text]


Tables
^^^^^^

For most information, using a csv table is preferred:

.. code-block:: rst

    .. csv-table:: table
    :file: path_to_table/table.csv
    :widths: 50 50 50
    :header-rows: 1

Technical details
=================

The UltraZohm project uses the following extensions to sphinx.
All extensions are listed in ``ultrazohm_sw/docs/requirements.txt``.

`sphinx <https://www.sphinx-doc.org/en/master/>`_
 Sphinx-doc is the base software to generate the documentation.

`sphinx_rtd_theme <https://github.com/readthedocs/sphinx_rtd_theme>`_
 The theme of the documentation

`sphinxcontrib-mermaid <https://github.com/mgaitan/sphinxcontrib-mermaid>`_
 Enables to embed `Mermaid <https://mermaid-js.github.io/mermaid/#/>`_ graphs.

`sphinxcontrib.yt <https://github.com/divi255/sphinxcontrib.youtube>`_
 Simple embedding of youtube videos.

`six <https://github.com/benjaminp/six>`_
 Provides compatibility between Python 2 and 3, required by some packages.

`sphinx-autobuild <https://github.com/executablebooks/sphinx-autobuild>`_
 Enable autobuild and reload after changes for local development with ``make livehtml``
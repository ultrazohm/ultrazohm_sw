===========
How to docs
===========

The documentation for the UltraZohm uses `sphinx <https://www.sphinx-doc.org>`_.
Sphinx uses reStructuredText as a markup language.
Useful links for more information:

* `reStructuredText <https://rest-sphinx-memo.readthedocs.io/en/latest/ReST.html>`_
* `Example usage from Anaconda <https://docs.anaconda.com/restructuredtext/detailed/>`_ 

Install
=======

To build and edit the documentation you need to:

* Install latest python version
* Install pip (included in current python versions)
* Install everything in the ``requirements.txt`` in ``/docs`` by invoking ``pip install -r requirements.txt`` in a command shell inside ``/docs``
* Build the documentation by invoking ``make html``
* You can open the docs in ``/docs/build/html/index.html``
* You can edit the documentation by using a text editor of your choice

.. note :: The online version on docs.ultrazohm.com is always the documentation for the **main** branch. If you build the documentation locally, you build the documentation for the specific branch!

Video
*****

.. youtube:: dxAlD-VzE0c
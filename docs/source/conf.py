# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))
import sphinx_rtd_theme

# -- Project information -----------------------------------------------------

project = 'UltraZohm'
copyright = 'UltraZohm community'
author = 'UltraZohm community'

# The full version, including alpha/beta/rc tags
release = '0.0.1'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.

extensions = [
    'sphinx_rtd_theme',
    'sphinxcontrib.mermaid',
    'sphinxcontrib.yt',
    'sphinx_issues',
    'sphinx_copybutton',
    'breathe'
]
breathe_projects = { "doxygen_baremetal_r5": "../doxygen_output/xml" }
breathe_default_project = "doxygen_baremetal_r5"

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# Paths for sphinx_issues

issues_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/issues/{issue}"
issues_pr_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/pull-requests/{pr}"
issues_commit_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/commits/{commit}"

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = [
    'global.rst',
]


# -- Options for HTML output ------------------------------------------------- 

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# The RTD theme is included in custom.css
html_style = 'css/custom.css'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

html_css_files = [
    '_static/css/custom.css',
]

html_theme_options = {
    'prev_next_buttons_location': 'both',
}

html_context = {
    "display_bitbucket": True, # Integrate Bitbucket
    "bitbucket_user": "ultrazohm", # Username
    "bitbucket_repo": "ultrazohm_sw", # Repo name
    "bitbucket_version": "main", # Version
    "conf_py_path": "/docs/source/", # Path in the checkout to the docs root
}

html_favicon = 'favicon.png'

# -- RST settings ------------------------------------------------------------

# Custom roles
# Did not get this working so added the global.rst directly to this file
#rst_prolog = open('./global.rst', 'r').read()

rst_prolog = """
.. role:: bg-red
.. role:: bg-green
.. role:: bg-purple
.. role:: bg-gray
.. role:: bg-pink
.. role:: bg-seagreen
.. role:: bg-yellow
.. role:: bg-bisque
.. role:: bg-brown
"""

# enables numbered figures
numfig = True

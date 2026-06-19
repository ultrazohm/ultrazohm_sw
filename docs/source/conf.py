# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

import pathlib
import sys

# uz_dataviewer library API (uz_dataviewer.api does not import the GUI stack)
sys.path.insert(0, str(pathlib.Path(__file__).parents[2] / "uz_dataviewer" / "src"))

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'UltraZohm'
copyright = '2026, UltraZohm Community'
author = 'UltraZohm Community'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinxcontrib.mermaid",
    "sphinxcontrib.youtube",
    "sphinx_issues",
    "sphinx_copybutton",
    "sphinxcontrib.tikz",
    "sphinx.ext.mathjax",
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",
    "breathe",
    "sphinx_plotly_directive", # https://matplotlib.org/stable/api/sphinxext_plot_directive_api.html#module-matplotlib.sphinxext.plot_directive
    "bokeh.sphinxext.bokeh_plot",
    "matplotlib.sphinxext.plot_directive",
    "sphinx_design"
]

autodoc_default_options = {
    "members": True,
    "show-inheritance": True,
}
autodoc_member_order = "bysource"

plotly_pre_code = """
import plotly.io as pio
pio.templates.default = \"plotly_white\"
"""

templates_path = ['_templates']
exclude_patterns = []
html_favicon = "favicon.svg"

tikz_proc_suite = "GhostScript"
breathe_projects = {"doxygen_baremetal_r5": "../doxygen_output/xml"}
breathe_default_project = "doxygen_baremetal_r5"
breathe_domain_by_extension = {
    "h": "c",
}

issues_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/issues/{issue}"
issues_pr_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/pull-requests/{pr}"
issues_commit_uri = "https://bitbucket.org/ultrazohm/ultrazohm_sw/commits/{commit}"

latex_engine = "lualatex"

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'pydata_sphinx_theme'
html_theme_options = {
    "navigation_with_keys":"True"
}

# html_static_path = ['_static']

html_context = {
    "display_bitbucket": True,  # Integrate Bitbucket
    "bitbucket_user": "ultrazohm",  # Username
    "bitbucket_repo": "ultrazohm_sw",  # Repo name
    "bitbucket_version": "main",  # Version
    "conf_py_path": "/docs/source/",  # Path in the checkout to the docs root
}


# enables numbered figures
numfig = True
# For numbering equations directly with sphinx
# https://stackoverflow.com/questions/50631942/how-does-equation-numbering-work-for-sphinx
math_numfig = True
numfig_secnum_depth = 2
math_eqref_format = "Eq.{number}"

# For Mathjax rendering instead of picture, according to
mathjax_config = {
    "TeX": {"equationNumbers": {"autoNumber": "AMS", "useLabelIds": True}},
}
mathjax_path = (
    "https://cdn.jsdelivr.net/npm/mathjax@2/MathJax.js?config=TeX-AMS-MML_HTMLorMML"
)

# https://github.com/michaeljones/breathe/issues/696
nitpick_ignore = [
    ("c:identifier", "int32_t"),
    ("c:identifier", "uint32_t"),
    ("c:identifier", "int64_t"),
    ("c:identifier", "uint64_t"),
    ("c:identifier", "int16_t"),
    ("c:identifier", "uint16_t"),
    ("c:identifier", "size_t"),
    ("c:identifier", "uintptr_t"),
    ("c:identifier", "bool"),
]

tikz_latex_preamble = r"\newcommand\Foo[1]{Z}" # https://github.com/sphinx-contrib/tikz/issues/19